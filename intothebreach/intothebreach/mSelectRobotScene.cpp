#include "mSelectRobotScene.h"
#include "Mech.h"
#include "mSceneManager.h"
#include "mInput.h"
#include "mTransform.h"
#include "mBackground.h"
#include "mSelectGDI.h"
#include "mApplication.h"
#include "mResources.h"
#include "mCamera.h"
#include "mSound.h"
#include "mButton.h"
#include "mImage.h"
#include "mTime.h"
#include "func.h"
extern m::Application application;
namespace m
{
	SelectRobotScene::SelectRobotScene()
		//: Scene()
	{}

	SelectRobotScene::~SelectRobotScene()
	{

	}

	void SelectRobotScene::Initialize()
	{
		Scene::Initialize();

		GameComp::mechInfos.push_back(GameComp::MechInfo{ (int)MECHS::flame, {BASIC_WEAPON_TYPE[(UINT)MECHS::flame]} });
		GameComp::mechInfos.push_back(GameComp::MechInfo{ (int)MECHS::tank, {BASIC_WEAPON_TYPE[(UINT)MECHS::tank]} });
		GameComp::mechInfos.push_back(GameComp::MechInfo{ (int)MECHS::punch, {BASIC_WEAPON_TYPE[(UINT)MECHS::punch]} });
		GameComp::mPilots[0] = PILOT_T::Pilot_Original;
		GameComp::mPilots[1] = PILOT_T::Pilot_Ice;
		GameComp::mPilots[2] = PILOT_T::Pilot_Sand;
		platformOpenIdx = 2;
		moveScene = false;
		titleEndPlayed = false;
		startSoundPlayed = false;
		titleEnd2Played = false;

		//Resources\sound\music
		titleEnd = Resources::Load<Sound>(L"title_end", L"..\\Resources\\sound\\music\\mus_title_ending_transition.wav");
		titleEnd2 = Resources::Load<Sound>(L"title_end2", L"..\\Resources\\sound\\music\\mus_title_ending.wav");

		Background* hangarBack = new Background(L"..\\Resources\\texture\\ui\\selectRobot\\hangar_main2.bmp"
			, L"..\\Resources\\texture\\ui\\selectRobot\\hangar_main2.bmp", 2);
		hangarBack->SetPos(Vector2(-100.f, -70.f));
		hangarBack->SetEC(true);
		AddGameObject(hangarBack, LAYER_TYPE::UI);

		btnStart = new Button(L"..\\Resources\\texture\\ui\\selectRobot\\btn_start.bmp", A_BTN_BACK_2);
		btnStart->SetInner(true);
		btnStart->UseInnerAlpha(false);
		btnStart->SetSize(Vector2(210, 80.f));
		btnStart->SetPos(Vector2(application.GetResolutionWidth() - btnStart->GetSize().x - 10,
			10));
		btnStart->SetInnerPos(Vector2(btnStart->GetSize().x / 2 - btnStart->GetInnerImage()->GetWidth() / 2
			, btnStart->GetSize().y / 2 - btnStart->GetInnerImage()->GetHeight() / 2));
		btnStart->SetState(GameObject::STATE::Visible);
		AddGameObject(btnStart, LAYER_TYPE::UI);

		boxSquad = new Button(L"..\\Resources\\texture\\ui\\selectRobot\\select_mech_box_box.bmp", NO_BACK);
		boxSquad->SetInner(true);
		boxSquad->UseInnerAlpha(false);
		boxSquad->SetSize(boxSquad->GetInnerImage()->GetSize());
		boxSquad->SetPos(Vector2(application.GetResolutionWidth() - boxSquad->GetSize().x - 10,
			application.GetResolutionHeight() - boxSquad->GetSize().y - 10));
		boxSquad->SetState(GameObject::STATE::Visible);
		AddGameObject(boxSquad, LAYER_TYPE::UI);

		boxSquadInfo = new Button(L"..\\Resources\\texture\\ui\\selectRobot\\select_mech_box.bmp", NO_BACK);
		boxSquadInfo->SetInner(true);
		boxSquadInfo->UseInnerAlpha(false);
		boxSquadInfo->SetSize(boxSquadInfo->GetInnerImage()->GetSize());
		boxSquadInfo->SetPos(Vector2(boxSquad->GetPos().x + boxSquad->GetSize().x / 2 - boxSquadInfo->GetSize().x / 2
			, boxSquad->GetPos().y + boxSquad->GetSize().y / 2 - boxSquadInfo->GetSize().y / 2));
		boxSquadInfo->SetState(GameObject::STATE::Visible);
		AddGameObject(boxSquadInfo, LAYER_TYPE::UI);

		btnChangeSquad = new Button(L"..\\Resources\\texture\\ui\\selectRobot\\edit_squad.bmp", A_BTN_BACK_2);
		btnChangeSquad->SetInner(true);
		btnChangeSquad->UseInnerAlpha(false);
		btnChangeSquad->SetSize(Vector2(boxSquad->GetSize().x - 10, 40.f));
		btnChangeSquad->SetPos(Vector2(boxSquad->GetPos().x + boxSquad->GetSize().x / 2 - btnChangeSquad->GetSize().x / 2
			, boxSquad->GetPos().y + boxSquad->GetSize().y - btnChangeSquad->GetSize().y - 5));
		btnChangeSquad->SetInnerPos(Vector2(btnChangeSquad->GetSize().x / 2 - btnChangeSquad->GetInnerImage()->GetWidth() / 2
			, btnChangeSquad->GetSize().y / 2 - btnChangeSquad->GetInnerImage()->GetHeight() / 2));
		AddGameObject(btnChangeSquad, LAYER_TYPE::UI);

		//btnRobotClass;

		//btnChangePilot;

		moon = new Background(L"moon", L"..\\Resources\\texture\\ui\\selectRobot\\hangar_sky_top.bmp", 2, false);
		moon->SetCutPos(true);
		moon->SetPos(Vector2(165.f, -2.f));


		cloud[0] = new Background(L"cloud", L"..\\Resources\\texture\\ui\\selectRobot\\hangar_sky_bottom.bmp", 2, false);
		cloudDiff = cloud[0]->GetWidth() * 2 - moon->GetWidth() * 2 - 40.f;

		cloud[0]->SetCutPos(true);
		cloud[0]->SetPos(Vector2(moon->GetPos().x - cloudDiff, (moon->GetPos().y + moon->GetHeight() * 2)));


		cloud[1] = new Background(L"cloud", L"..\\Resources\\texture\\ui\\selectRobot\\hangar_sky_bottom.bmp", 2, false);
		cloud[1]->SetCutPos(true);
		cloud[1]->SetPos(Vector2(cloud[0]->GetPos().x - cloud[0]->GetWidth() * 2, (moon->GetPos().y + moon->GetHeight() * 2)));



		Background* hangar = new Background(L"selectRobotBg1"
			, L"..\\Resources\\texture\\ui\\selectRobot\\hangar_main.bmp", 2, false);
		hangar->SetCutPos(true);
		hangar->SetPos(Vector2(-100.f, -70.f));

		hangar->SetEC(true);



		moon->SetEC(true);
		cloud[0]->SetEC(true);
		cloud[1]->SetEC(true);


		AddGameObject(moon, LAYER_TYPE::BACKGROUND);
		AddGameObject(cloud[0], LAYER_TYPE::BACKGROUND);
		AddGameObject(cloud[1], LAYER_TYPE::BACKGROUND);

		AddGameObject(hangar, LAYER_TYPE::BACKGROUND);


		float _x = 264.f;
		float _y = 328.f;
		for (int i = 0; i < 3; i++)
		{
			lights[i] = new Background(L"light", L"..\\Resources\\texture\\ui\\selectRobot\\hangar_lights.bmp", 2, false);
			lights[i]->SetCutPos(true);
			lights[i]->SetAlphaConstant(50);
			lights[i]->SetPos(Vector2(_x, _y));
			lights[i]->SetAlpha(true);
			lights[i]->SetIdVar(5.f);
			lights[i]->SetBlink(true);
			lights[i]->SetEC(true);

			platformL[i] = new Background(L"platformL", L"..\\Resources\\texture\\ui\\selectRobot\\hangar_platform_L.bmp", 2);
			platformL[i]->SetCutPos(true);
			platformL[i]->SetPos(Vector2(lights[i]->GetPos().x + lights[i]->GetSize().x - platformL[i]->GetSize().x * 2,
				lights[i]->GetPos().y + lights[i]->GetSize().y - platformL[i]->GetSize().y - 5.f));
			platformL[i]->SetEC(true);

			platformR[i] = new Background(L"platformR", L"..\\Resources\\texture\\ui\\selectRobot\\hangar_platform_R.bmp", 2);
			platformR[i]->SetCutPos(true);
			platformR[i]->SetPos(Vector2(platformL[i]->GetPos().x + platformR[i]->GetSize().x * 2,
				platformL[i]->GetPos().y));
			platformR[i]->SetEC(true);
			platformR[i]->SetOriginPos(platformR[i]->GetPos());


			reflectShadows[i] = new Background(L"firstBack", L"..\\Resources\\texture\\ui\\selectRobot\\hangar_platform_shadow_f.bmp", 2);
			reflectShadows[i]->SetCutPos(true);
			reflectShadows[i]->SetAlpha(true);
			reflectShadows[i]->SetAlphaConstant(200);

			//reflectShadows[i] = new Background(L"firstBack", L"..\\Resources\\texture\\ui\\selectRobot\\hangar_platform_shadow.bmp", 2);
			//reflectShadows[i]->SetAnimation(true);
			reflectShadows[i]->SetPos(Vector2(platformR[i]->GetPos().x
				, platformR[i]->GetPos().y + platformR[i]->GetSize().y));
			AddGameObject(platformR[i], LAYER_TYPE::UI);
			AddGameObject(platformL[i], LAYER_TYPE::UI);

			_x += 90.f;
			_y -= 68.f;
		}

		for (int i = 0; i < 3; i++)
		{
			hangarMechs[i] = new Background(MAKE_UNIT_PATH((MECHS)GameComp::mechInfos[i].unitNum, COMBAT_CONDITION_T::NO_SHADOW),
				MAKE_UNIT_PATH((MECHS)GameComp::mechInfos[i].unitNum, COMBAT_CONDITION_T::NO_SHADOW), 2);
			shadows[i] = new Background(MAKE_UNIT_PATH((MECHS)GameComp::mechInfos[i].unitNum, COMBAT_CONDITION_T::HOLO),
				MAKE_UNIT_PATH((MECHS)GameComp::mechInfos[i].unitNum, COMBAT_CONDITION_T::HOLO), 2);
			//mechImage->SetPos(Vector2(500 - (i * 100), 205 + (i * (10 + (mechImage->GetSize().x * 2)))));
			Vector2 offset = MECHS_HANGAR_OFFSET[GameComp::mechInfos[i].unitNum];
			hangarMechs[i]->SetPos(Vector2(lights[i]->GetPos().x + lights[i]->GetSize().x - hangarMechs[i]->GetSize().x + offset.x
				, lights[i]->GetPos().y + lights[i]->GetSize().y - 55.f + offset.y));
			hangarMechs[i]->SetEC(true);
			shadows[i]->SetPos(hangarMechs[i]->GetPos());
			shadows[i]->SetAlpha(true);
			shadows[i]->SetEC(true);
			shadows[i]->SetAlphaConstant(200);

			hangarMechs[i]->SetState(GameObject::STATE::Visible);
			shadows[i]->SetState(GameObject::STATE::Visible);
			AddGameObject(lights[i], LAYER_TYPE::FRONT_UI2);
			AddGameObject(hangarMechs[i], LAYER_TYPE::FRONT_UI);
			AddGameObject(shadows[i], LAYER_TYPE::FRONT_UI);
		}

		DrawMechInfos();
		//hangar_platform.bmp;

		hangarFront = new Background(L"selectRobotHangarFront", L"..\\Resources\\texture\\ui\\selectRobot\\hangar_main_front.bmp", 2, false);
		hangarFront->SetCutPos(true);
		hangarFront->SetPos(Vector2(-100.f, -70.f));
		hangarFront->SetEC(true);
		AddGameObject(hangarFront, LAYER_TYPE::UI);

		Background* hangarFront2 = new Background(L"selectRobotHangarFront", L"..\\Resources\\texture\\ui\\selectRobot\\hangar_main4.bmp", 2, false);
		hangarFront2->SetCutPos(true);
		hangarFront2->SetPos(Vector2(-100.f, -70.f));
		hangarFront2->SetEC(true);
		AddGameObject(hangarFront2, LAYER_TYPE::FRONT_UI);

		for (int i = 0; i < 3; i++) AddGameObject(reflectShadows[i], LAYER_TYPE::FRONT_UI);

		Background* line = new Background(L"line", L"..\\Resources\\texture\\ui\\selectRobot\\waterbg_transition.bmp", 2, false);
		line->SetCutPos(true);
		line->SetPos(Vector2(0, (float)application.GetResolutionHeight()));
		line->SetEC(true);

		AddGameObject(line, LAYER_TYPE::BACKGROUND);

		swapFake = new Background(L"sf", L"..\\Resources\\texture\\ui\\selectRobot\\shot.bmp", 0, false);
		swapFake->SetCutPos(true);
		swapFake->SetPos(Vector2(0, (float)(line->GetHeight() * 2 + application.GetResolutionHeight())));
		swapFake->SetEC(true);
		AddGameObject(swapFake, LAYER_TYPE::BACKGROUND);

		boxBlackFade = new Background(ALPHA_BACK, ALPHA_BACK, 0, true, CENTER);
		boxBlackFade->SetAlpha(true);
		boxBlackFade->SetAlphaConstant(200);
		boxBlackFade->SetSize(Vector2(application.GetResolutionWidth(), application.GetResolutionHeight()));
		boxBlackFade->SetState(GameObject::STATE::Invisible);
		AddGameObject(boxBlackFade, LAYER_TYPE::FRONT_UI3);

		boxEditSquad = new Button(L"..\\Resources\\texture\\ui\\selectRobot\\preview_squad_box.bmp", NO_BACK);
		boxEditSquad->SetInner(true);
		boxEditSquad->UseInnerAlpha(false);
		boxEditSquad->SetSize(boxEditSquad->GetInnerImage()->GetSize());
		boxEditSquad->SetPos(Vector2(application.GetResolutionWidth() / 2 - boxEditSquad->GetSize().x / 2
			, 10));
		boxEditSquad->SetState(GameObject::STATE::Invisible);
		AddGameObject(boxEditSquad, LAYER_TYPE::FRONT_UI3);

		squadPreview = new Background(L"preview_select_squad", L"..\\Resources\\texture\\ui\\selectRobot\\preview_select_squad.bmp");
		//squadPreview->SetSize(squadPreview->GetImage()->GetSize());
		squadPreview->SetPos(Vector2(boxEditSquad->GetPos().x + boxEditSquad->GetSize().x - squadPreview->GetSize().x
			, boxEditSquad->GetPos().y + boxEditSquad->GetSize().y + 10));
		squadPreview->SetState(GameObject::STATE::Invisible);
		AddGameObject(squadPreview, LAYER_TYPE::FRONT_UI3);

		btnEditConfirm = new Button(L"..\\Resources\\texture\\ui\\selectRobot\\select_squad_before_confirm.bmp", A_BTN_BACK_2);
		btnEditConfirm->SetInner(true);
		btnEditConfirm->UseInnerAlpha(false);
		btnEditConfirm->SetSize(btnEditConfirm->GetInnerImage()->GetSize());
		btnEditConfirm->SetPos(Vector2(squadPreview->GetPos().x - btnEditConfirm->GetSize().x
			, squadPreview->GetPos().y + squadPreview->GetSize().y / 2 - btnEditConfirm->GetSize().y / 2));
		btnEditConfirm->SetInnerPos(Vector2(btnEditConfirm->GetSize().x / 2 - btnEditConfirm->GetInnerImage()->GetWidth() / 2
			, btnEditConfirm->GetSize().y / 2 - btnEditConfirm->GetInnerImage()->GetHeight() / 2));
		btnEditConfirm->SetState(GameObject::STATE::Invisible);
		AddGameObject(btnEditConfirm, LAYER_TYPE::FRONT_UI3);

		btnPrime = new Button(L"..\\Resources\\texture\\ui\\selectRobot\\prime_btn.bmp", A_BTN_BACK_2);
		btnPrime->SetInner(true);
		btnPrime->UseInnerAlpha(false);
		btnPrime->SetSize(Vector2(183.f, 60.f));
		btnPrime->SetPos(Vector2(boxEditSquad->GetPos().x + 1
			, boxEditSquad->GetPos().y + boxEditSquad->GetSize().y - btnPrime->GetSize().y));
		btnPrime->SetInnerPos(Vector2(btnPrime->GetSize().x / 2 - btnPrime->GetInnerImage()->GetWidth() / 2
			, btnPrime->GetSize().y / 2 - btnPrime->GetInnerImage()->GetHeight() / 2));
		btnPrime->SetState(GameObject::STATE::Invisible);
		AddGameObject(btnPrime, LAYER_TYPE::FRONT_UI3);
		btnBrute = new Button(L"..\\Resources\\texture\\ui\\selectRobot\\brute_btn.bmp", A_BTN_BACK_2);
		btnBrute->SetInner(true);
		btnBrute->UseInnerAlpha(false);
		btnBrute->SetSize(Vector2(183.f, 60.f));
		btnBrute->SetPos(Vector2(btnPrime->GetPos().x + btnPrime->GetSize().x - 1
			, boxEditSquad->GetPos().y + boxEditSquad->GetSize().y - btnBrute->GetSize().y));
		btnBrute->SetInnerPos(Vector2(btnBrute->GetSize().x / 2 - btnBrute->GetInnerImage()->GetWidth() / 2
			, btnBrute->GetSize().y / 2 - btnBrute->GetInnerImage()->GetHeight() / 2));
		btnBrute->SetState(GameObject::STATE::Invisible);
		AddGameObject(btnBrute, LAYER_TYPE::FRONT_UI3);

		btnRange = new Button(L"..\\Resources\\texture\\ui\\selectRobot\\range_btn.bmp", A_BTN_BACK_2);
		btnRange->SetInner(true);
		btnRange->UseInnerAlpha(false);
		btnRange->SetSize(Vector2(183.f, 60.f));
		btnRange->SetPos(Vector2(btnBrute->GetPos().x + btnBrute->GetSize().x - 1
			, boxEditSquad->GetPos().y + boxEditSquad->GetSize().y - btnRange->GetSize().y));
		btnRange->SetInnerPos(Vector2(btnRange->GetSize().x / 2 - btnRange->GetInnerImage()->GetWidth() / 2
			, btnRange->GetSize().y / 2 - btnRange->GetInnerImage()->GetHeight() / 2));
		btnRange->SetState(GameObject::STATE::Invisible);
		AddGameObject(btnRange, LAYER_TYPE::FRONT_UI3);

		for (int i = 0; i < 3; i++)
		{
			Button* back = new Button(L"", A_BTN_BACK_2);
			back->SetSize(Vector2(110, 45));
			back->SetPos(Vector2(boxEditSquad->GetPos().x + 83.f + ((back->GetSize().x + 25) * i), 117.f));
			back->SetOSize(Vector2(110, 45));
			back->SetInnerMag(2);
			//back->SetInnerPos(Vector2(back->GetPos().x + back->GetSize().x / 2 - back->GetInnerImage()->GetSize().x / 2
			//	, back->GetPos().y + back->GetSize().y / 2 - back->GetInnerImage()->GetSize().y / 2));
			//back->SetResize(Vector2(110, 110));
			//back->SetResizeUnit(Vector2(30, 30));
			back->SetState(GameObject::STATE::Invisible);

			AddGameObject(back, LAYER_TYPE::FRONT_UI3);
			clickableMechs.push_back(back);
		}

		for (int i = 0; i < 3; i++)
		{
			Button* mechImage = new Button(MAKE_UNIT_PATH((MECHS)GameComp::mechInfos[i].unitNum, COMBAT_CONDITION_T::NO_SHADOW),
				NO_BACK);
			mechImage->SetItem(GameComp::mechInfos[i].unitNum);
			mechImage->SetInner(true);
			mechImage->SetInnerMag(2);
			mechImage->SetSize(mechImage->GetInnerImage()->GetSize() * 2);
			//mechImage->SetPos(Vector2(mechImage->GetInnerImage()->GetWidth() * i
			//	, squadPreview->GetPos().y + squadPreview->GetSize().y / 2 - mechImage->GetInnerImage()->GetHeight()));
			//mechImage->SetInnerPos(Vector2::Zero);
			mechImage->SetState(GameObject::STATE::Invisible);
			previewMechs.push_back(mechImage);
			AddGameObject(mechImage, LAYER_TYPE::FRONT_UI3);
		}

	}
	void SelectRobotScene::DrawMechInfos()
	{
		for (int i = 0; i < mechs.size(); i++)
		{
			mechs[i]->SetState(GameObject::STATE::Delete);
			skills[i]->SetState(GameObject::STATE::Delete);
			mechNames[i]->SetState(GameObject::STATE::Delete);
			mechMoves[i]->SetState(GameObject::STATE::Delete);
			mechHps[i]->SetState(GameObject::STATE::Delete);
			classNames[i]->SetState(GameObject::STATE::Delete);
			hpBacks[i]->SetState(GameObject::STATE::Delete);
		}
		for (int i = 0; i < hps.size(); i++) hps[i]->SetState(GameObject::STATE::Delete);
		mechs.clear();
		skills.clear();
		//mechClass.clear();
		mechNames.clear();
		mechMoves.clear();
		mechHps.clear();
		classNames.clear();
		hpBacks.clear();
		hps.clear();
		//for (int i = 0; i < 3; i++)
		//{
		//	hangarMechs[i]->SetTex(MAKE_UNIT_KEY((MECHS)GameComp::mechInfos[i].unitNum, COMBAT_CONDITION_T::NO_SHADOW), 
		//		MAKE_UNIT_PATH((MECHS)GameComp::mechInfos[i].unitNum, COMBAT_CONDITION_T::NO_SHADOW));
		//}
		for (int i = 0; i < 3; i++)
		{
			hangarMechs[i]->SetTex(MAKE_UNIT_KEY((MECHS)GameComp::mechInfos[i].unitNum, COMBAT_CONDITION_T::NO_SHADOW),
				MAKE_UNIT_PATH((MECHS)GameComp::mechInfos[i].unitNum, COMBAT_CONDITION_T::NO_SHADOW));
			shadows[i]->SetTex(MAKE_UNIT_KEY((MECHS)GameComp::mechInfos[i].unitNum, COMBAT_CONDITION_T::HOLO),
				MAKE_UNIT_PATH((MECHS)GameComp::mechInfos[i].unitNum, COMBAT_CONDITION_T::HOLO));
			//mechImage->SetPos(Vector2(500 - (i * 100), 205 + (i * (10 + (mechImage->GetSize().x * 2)))));
			Vector2 offset = MECHS_HANGAR_OFFSET[GameComp::mechInfos[i].unitNum];
			hangarMechs[i]->SetPos(Vector2(lights[i]->GetPos().x + lights[i]->GetSize().x - hangarMechs[i]->GetSize().x + offset.x,
				lights[i]->GetPos().y + lights[i]->GetSize().y - 55.f + offset.y));
			shadows[i]->SetPos(hangarMechs[i]->GetPos());
			shadows[i]->SetAlpha(true);
			shadows[i]->SetAlphaConstant(200);
		}
		for (int i = 0; i < 3; i++)
		{
			Background* mechImage = new Background(MAKE_UNIT_KEY((MECHS)GameComp::mechInfos[i].unitNum, COMBAT_CONDITION_T::NO_SHADOW),
				MAKE_UNIT_PATH((MECHS)GameComp::mechInfos[i].unitNum, COMBAT_CONDITION_T::NO_SHADOW), 2);
			mechImage->SetPos(Vector2(boxSquadInfo->GetPos().x + 10.f
				, boxSquadInfo->GetPos().y + 15.f + (i * 105.f)));
			mechs.push_back(mechImage);
			AddGameObject(mechImage, LAYER_TYPE::UI);

			Background* skillImage = new Background(WEAPON_IMAGES[(UINT)GameComp::mechInfos[i].weapons[0]]
				, WEAPON_IMAGES[(UINT)GameComp::mechInfos[i].weapons[0]]);
			skillImage->SetPos(Vector2(boxSquadInfo->GetPos().x + 100.f
				, boxSquadInfo->GetPos().y + 42.f + (105 * i)));
			skills.push_back(skillImage);
			AddGameObject(skillImage, LAYER_TYPE::UI);

			Background* mechName = new Background(MECH_NAMES_PATH[(UINT)GameComp::mechInfos[i].unitNum]
				, MECH_NAMES_PATH[(UINT)GameComp::mechInfos[i].unitNum]);
			mechName->SetPos(Vector2(boxSquadInfo->GetPos().x + 100.f
				, boxSquadInfo->GetPos().y + 10.f + (i * 105)));
			mechNames.push_back(mechName);
			AddGameObject(mechName, LAYER_TYPE::UI);

			Background* mechMove = new Background(BOLD_NUM_PATH[MECH_MOVE_RANGE[(UINT)GameComp::mechInfos[i].unitNum]]
				, BOLD_NUM_PATH[MECH_MOVE_RANGE[(UINT)GameComp::mechInfos[i].unitNum]]);
			mechMove->SetPos(Vector2(skillImage->GetPos().x + skillImage->GetSize().x + 35.f, skillImage->GetPos().y - 5.f));
			AddGameObject(mechMove, LAYER_TYPE::UI);
			mechMoves.push_back(mechMove);

			Background* mechHp = new Background(BOLD_NUM_PATH[MECH_HP[(UINT)GameComp::mechInfos[i].unitNum]]
				, BOLD_NUM_PATH[MECH_HP[(UINT)GameComp::mechInfos[i].unitNum]]);
			mechHp->SetPos(Vector2(mechMove->GetPos().x - 25.f
				, mechMove->GetPos().y));
			mechHps.push_back(mechHp);

			Background* mechHpBarBack = new Background(HP_BAR_2, HP_BAR_2);
			mechHpBarBack->SetSize(Vector2(mechHpBarBack->GetSize().x + ((MECH_HP[(UINT)GameComp::mechInfos[i].unitNum] - 2) * 2)
				, mechHpBarBack->GetSize().y));
			mechHpBarBack->SetPos(Vector2(mechHp->GetPos().x + mechHp->GetSize().x / 2 - mechHpBarBack->GetSize().x / 2
				, mechHp->GetPos().y + mechHp->GetSize().y - mechHpBarBack->GetSize().y / 2));
			AddGameObject(mechHpBarBack, LAYER_TYPE::UI);
			hpBacks.push_back(mechHpBarBack);
			AddGameObject(mechHp, LAYER_TYPE::UI);

			for (int _i = 0; _i < MECH_HP[(UINT)GameComp::mechInfos[i].unitNum]; _i++)
			{
				Background* hpTick = new Background(HP_BAR_BACK, HP_BAR_BACK);
				//hpTick->SetInner(true);
				float fWid = 17 / MECH_HP[(UINT)GameComp::mechInfos[i].unitNum];
				if (MECH_HP[(UINT)GameComp::mechInfos[i].unitNum] == 2) fWid -= 0.5f;
				hpTick->SetSize(Vector2((float)fWid, hpTick->GetSize().y - 2));
				hpTick->SetPos(Vector2(mechHpBarBack->GetPos().x + 2 + (hpTick->GetSize().x + 1) * _i
					, mechHpBarBack->GetPos().y + mechHpBarBack->GetSize().y / 2 - hpTick->GetSize().y / 2));
				hps.push_back(hpTick);
				AddGameObject(hpTick, LAYER_TYPE::UI);
			}

			Background* className = new Background(MECH_T_NAME_PATH[MECHS_T_HT[(UINT)GameComp::mechInfos[i].unitNum]]
				, MECH_T_NAME_PATH[MECHS_T_HT[(UINT)GameComp::mechInfos[i].unitNum]]);
			className->SetPos(Vector2(mechHp->GetPos().x
				, mechMove->GetPos().y + mechMove->GetSize().y + 10.f));
			AddGameObject(className, LAYER_TYPE::UI);
			classNames.push_back(className);
		}
	}
	void SelectRobotScene::Update()
	{
		Scene::Update();
		
		//if (btnStart->GetClicked())
		//{
		//	
		//}
		if (titleEndPlayed && titleEnd->GetStop())
		{
			titleEnd2->Play(false);
		}
		if (platformR[0]->GetOriginPos().y + 30.f <= platformR[0]->GetPos().y)
		{
			btnStart->SetClicked(false);
			hangarFront->SetTex(L"hangar_main3"
				, L"..\\Resources\\texture\\ui\\selectRobot\\hangar_main3.bmp");
			//for (int i = 0; i < 3; i++)
			//{
			//	ObjectGoFront(hangarMechs[i], LAYER_TYPE::UI);
			//	ObjectGoFront(shadows[i], LAYER_TYPE::UI);
			//}
			if (platformOpenIdx > -1)
			{
				platformR[platformOpenIdx]->SetPos(Vector2(platformR[platformOpenIdx]->GetPos().x + 200.f * Time::fDeltaTime()
					, platformR[platformOpenIdx]->GetPos().y));
				platformL[platformOpenIdx]->SetPos(Vector2(platformL[platformOpenIdx]->GetPos().x - 200.f * Time::fDeltaTime()
					, platformL[platformOpenIdx]->GetPos().y));
				if (platformR[platformOpenIdx]->GetOriginPos().x + 50.f < platformR[platformOpenIdx]->GetPos().x)
				{
					platformR[platformOpenIdx]->SetState(GameObject::STATE::Invisible);
					platformL[platformOpenIdx]->SetState(GameObject::STATE::Invisible);
					hangarMechs[platformOpenIdx]->SetPos(Vector2(hangarMechs[platformOpenIdx]->GetPos().x, hangarMechs[platformOpenIdx]->GetPos().y + 300.f * Time::fDeltaTime()));
					shadows[platformOpenIdx]->SetPos(Vector2(shadows[platformOpenIdx]->GetPos().x, shadows[platformOpenIdx]->GetPos().y + 300.f * Time::fDeltaTime()));

					if (shadows[platformOpenIdx]->GetPos().y > platformL[platformOpenIdx]->GetPos().y + 100)
					{
						lights[platformOpenIdx]->SetBlink(false);
						lights[platformOpenIdx]->SetAlphaConstant(255);
						if (platformOpenIdx == 0) moveScene = true;
						platformOpenIdx--;
					}
				}
			}

			if (!titleEnd2Played)
			{
				titleEnd2->Play(false);
				titleEnd2Played = true;

			}
			//if ((*titleEnd->GetSoundBufferStatus()) == DSBSTATUS_PLAYING)
			//{
			//	int a = 0;
			//}
		}
		if (moveScene)
		{
			Camera::SetMoveTime(1.f);
			Camera::SetLookAt(Vector2((float)application.GetResolutionWidth() / 2.f, (float)swapFake->GetPos().y + swapFake->GetHeight() / 2.f));
			moveScene = false;
		}
		if (Camera::GetCurPos() == Vector2((float)application.GetResolutionWidth() / 2.f, (float)swapFake->GetPos().y + swapFake->GetHeight() / 2.f))
		{
			SceneManager::LoadScene(SCENE_TYPE::SELECT_LAND);
		}
		if (btnStart->GetHover()) btnStart->SetTex(A_BTN_SELECT_BACK_2, A_BTN_SELECT_BACK_2);
		else btnStart->SetTex(A_BTN_BACK_2, A_BTN_BACK_2);
		if (btnStart->GetClicked())
		{
			btnStart->SetState(GameObject::STATE::Invisible);
			boxSquad->SetState(GameObject::STATE::Invisible);
			boxSquadInfo->SetState(GameObject::STATE::Invisible);
			btnChangeSquad->SetState(GameObject::STATE::Invisible);

			if (!titleEndPlayed)
			{
				titleEnd->Play(false);
				titleEndPlayed = true;
			}
			if (!startSoundPlayed)
			{
				Sound* startSound = Resources::Load<Sound>(L"start_game_", L"..\\Resources\\sound\\sfx\\ui_main_menu_start_game.wav");
				startSound->Play(false);
				startSoundPlayed = true;
			}
			for (int i = 0; i < mechs.size(); i++)
			{
				mechs[i]->SetState(GameObject::STATE::Delete);
				skills[i]->SetState(GameObject::STATE::Delete);
				mechNames[i]->SetState(GameObject::STATE::Delete);
				mechMoves[i]->SetState(GameObject::STATE::Delete);
				mechHps[i]->SetState(GameObject::STATE::Delete);
				classNames[i]->SetState(GameObject::STATE::Delete);
				hpBacks[i]->SetState(GameObject::STATE::Delete);
			}
			for (int i = 0; i < hps.size(); i++) hps[i]->SetState(GameObject::STATE::Delete);

			for (int i = 0; i < 3; i++)
			{
				lights[i]->SetTex(L"light_red", L"..\\Resources\\texture\\ui\\selectRobot\\hangar_lights_start.bmp");
				lights[i]->SetIdVar(20);
				reflectShadows[i]->CreateAnimationBack(L"reflectShadowAnim"
					, L"..\\Resources\\texture\\ui\\selectRobot\\hangar_platform_shadow.bmp", 13, 0.1f);
				platformL[i]->SetPos(Vector2(platformL[i]->GetPos().x, platformL[i]->GetPos().y + 15.f * Time::fDeltaTime()));
				platformR[i]->SetPos(Vector2(platformR[i]->GetPos().x, platformL[i]->GetPos().y + 15.f * Time::fDeltaTime()));

				hangarMechs[i]->SetPos(Vector2(hangarMechs[i]->GetPos().x, hangarMechs[i]->GetPos().y + 15.f * Time::fDeltaTime()));
				shadows[i]->SetPos(Vector2(shadows[i]->GetPos().x, shadows[i]->GetPos().y + 15.f * Time::fDeltaTime()));
			}
		}
		if (btnChangeSquad->GetHover()) btnChangeSquad->SetTex(A_BTN_SELECT_BACK_2, A_BTN_SELECT_BACK_2);
		else btnChangeSquad->SetTex(A_BTN_BACK_2, A_BTN_BACK_2);
		if (btnChangeSquad->GetClicked())
		{
			boxBlackFade->SetState(GameObject::STATE::Visible);
			boxEditSquad->SetState(GameObject::STATE::Visible);
			squadPreview->SetState(GameObject::STATE::Visible);
			btnEditConfirm->SetState(GameObject::STATE::Visible);
			btnBrute->SetState(GameObject::STATE::Visible);
			btnPrime->SetState(GameObject::STATE::Visible);
			btnRange->SetState(GameObject::STATE::Visible);
			btnPrime->SetClicked(true);
			for (int i = 0; i < previewMechs.size(); i++)
			{
				previewMechsUnitNum[i] = GameComp::mechInfos[i].unitNum;
				previewMechs[i]->ChangeInner(MAKE_UNIT_PATH((MECHS)GameComp::mechInfos[i].unitNum, COMBAT_CONDITION_T::NO_SHADOW));
				previewMechs[i]->SetInner(true);
				previewMechs[i]->SetState(GameObject::STATE::Visible);
			}
			for (int i = 0; i < clickableMechs.size(); i++)
			{
				clickableMechs[i]->SetState(GameObject::STATE::Visible);
			}
			btnChangeSquad->SetClicked(false);
		}
		bool all = true;
		for (int i = 0; i < previewMechs.size(); i++)
		{
			if (!previewMechs[i]->GetInner()) all = false;
		}
		if (all)
		{
			btnEditConfirm->ChangeInner(L"..\\Resources\\texture\\ui\\selectRobot\\select_squad_after_confirm.bmp");
			btnEditConfirm->SetInnerPos(Vector2(btnEditConfirm->GetSize().x / 2 - btnEditConfirm->GetInnerImage()->GetWidth() / 2
				, btnEditConfirm->GetSize().y / 2 - btnEditConfirm->GetInnerImage()->GetHeight() / 2));
			if (btnEditConfirm->GetHover())
			{
				btnEditConfirm->SetTex(A_BTN_SELECT_BACK_2, A_BTN_SELECT_BACK_2);
			}
			else btnEditConfirm->SetTex(A_BTN_BACK_2, A_BTN_BACK_2);
			if (btnEditConfirm->GetClicked())
			{
				boxBlackFade->SetState(GameObject::STATE::Invisible);
				boxEditSquad->SetState(GameObject::STATE::Invisible);
				squadPreview->SetState(GameObject::STATE::Invisible);
				btnEditConfirm->SetState(GameObject::STATE::Invisible);
				btnBrute->SetState(GameObject::STATE::Invisible);
				btnPrime->SetState(GameObject::STATE::Invisible);
				btnRange->SetState(GameObject::STATE::Invisible);
				btnEditConfirm->SetClicked(false);
				for (int i = 0; i < previewMechs.size(); i++) previewMechs[i]->SetState(GameObject::STATE::Invisible);
				for (int i = 0; i < clickableMechs.size(); i++) clickableMechs[i]->SetState(GameObject::STATE::Invisible);
				for (int i = 0; i < 3; i++)
				{
					GameComp::mechInfos[i].unitNum = previewMechs[i]->GetItem();
					GameComp::mechInfos[i].weapons[0] = BASIC_WEAPON_TYPE[previewMechs[i]->GetItem()];
				}
				DrawMechInfos();
				btnEditConfirm->SetClicked(false);
			}
		}
		else
		{
			btnEditConfirm->ChangeInner(L"..\\Resources\\texture\\ui\\selectRobot\\select_squad_before_confirm.bmp");
			btnEditConfirm->SetInnerPos(Vector2(btnEditConfirm->GetSize().x / 2 - btnEditConfirm->GetInnerImage()->GetWidth() / 2
				, btnEditConfirm->GetSize().y / 2 - btnEditConfirm->GetInnerImage()->GetHeight() / 2));
		}

		if (btnBrute->GetHover()) btnBrute->SetTex(A_BTN_SELECT_BACK_2, A_BTN_SELECT_BACK_2);
		else btnBrute->SetTex(A_BTN_BACK_2, A_BTN_BACK_2);

		if (btnPrime->GetHover()) btnPrime->SetTex(A_BTN_SELECT_BACK_2, A_BTN_SELECT_BACK_2);
		else btnPrime->SetTex(A_BTN_BACK_2, A_BTN_BACK_2);

		if (btnRange->GetHover()) btnRange->SetTex(A_BTN_SELECT_BACK_2, A_BTN_SELECT_BACK_2);
		else btnRange->SetTex(A_BTN_BACK_2, A_BTN_BACK_2);


		if (btnBrute->GetClicked())
		{
			int idx = 0;
			for (int i = 0; i < (int)BRUTE_T::END; i++)
			{
				if (MECH_NAMES_PATH[i + (int)PRIME_T::END] != L"")
				{
					clickableMechs[idx]->SetState(GameObject::STATE::Visible);
					clickableMechs[idx]->ChangeInner(MAKE_UNIT_PATH((MECHS)(i + (int)PRIME_T::END), COMBAT_CONDITION_T::NO_SHADOW));
					clickableMechs[idx]->SetInner(true);
					clickableMechs[idx]->SetItem(i + (int)PRIME_T::END);
					clickableMechs[idx]->SetInnerPos(Vector2(clickableMechs[idx]->GetSize().x / 2 - clickableMechs[idx]->GetInnerImage()->GetSize().x
						, clickableMechs[idx]->GetSize().y / 2 - clickableMechs[idx]->GetInnerImage()->GetSize().y));
					idx++;
				}
			}
			for (int i = idx; i < clickableMechs.size(); i++)
			{
				clickableMechs[i]->SetState(GameObject::STATE::Invisible);
			}
			boxEditSquad;
			btnBrute->SetClicked(false);
		}
		if (btnPrime->GetClicked())
		{
			int idx = 0;
			for (int i = 0; i < (int)PRIME_T::END; i++)
			{
				if (MECH_NAMES_PATH[i] != L"")
				{
					clickableMechs[idx]->SetState(GameObject::STATE::Visible);
					clickableMechs[idx]->ChangeInner(MAKE_UNIT_PATH((MECHS)i, COMBAT_CONDITION_T::NO_SHADOW));
					clickableMechs[idx]->SetInner(true);
					clickableMechs[idx]->SetItem(i);
					clickableMechs[idx]->SetInnerPos(Vector2(clickableMechs[idx]->GetSize().x / 2 - clickableMechs[idx]->GetInnerImage()->GetSize().x
						, clickableMechs[idx]->GetSize().y / 2 - clickableMechs[idx]->GetInnerImage()->GetSize().y));
					idx++;
				}
			}
			for (int i = idx; i < clickableMechs.size(); i++) { clickableMechs[i]->SetInner(false); }
			boxEditSquad;
			btnPrime->SetClicked(false);
		}
		if (btnRange->GetClicked())
		{
			int idx = 0;
			for (int i = 0; i < (int)RANGE_T::END; i++)
			{
				if (MECH_NAMES_PATH[i + (int)PRIME_T::END + (int)BRUTE_T::END] != L"")
				{
					clickableMechs[idx]->SetState(GameObject::STATE::Visible);
					clickableMechs[idx]->ChangeInner(MAKE_UNIT_PATH((MECHS)(i + (int)PRIME_T::END + (int)BRUTE_T::END), COMBAT_CONDITION_T::NO_SHADOW));
					clickableMechs[idx]->SetInner(true);
					clickableMechs[idx]->SetItem(i + (int)PRIME_T::END + (int)BRUTE_T::END);
					clickableMechs[idx]->SetInnerPos(Vector2(clickableMechs[idx]->GetSize().x / 2 - clickableMechs[idx]->GetInnerImage()->GetSize().x
						, clickableMechs[idx]->GetSize().y / 2 - clickableMechs[idx]->GetInnerImage()->GetSize().y));
					idx++;
				}
			}
			for (int i = idx; i < clickableMechs.size(); i++)
			{
				clickableMechs[i]->SetState(GameObject::STATE::Invisible);
			}
			boxEditSquad;
			btnRange->SetClicked(false);
		}
		for (int i = 0; i < clickableMechs.size(); i++)
		{
			bool bind = false;
			if (clickableMechs[i]->GetHover()) clickableMechs[i]->SetTex(A_BTN_SELECT_BACK_2, A_BTN_SELECT_BACK_2);
			else clickableMechs[i]->SetTex(A_BTN_BACK_2, A_BTN_BACK_2);

			if (clickableMechs[i]->GetClicked())
			{
				for (int _i = 0; _i < previewMechs.size(); _i++)
				{
					if (!previewMechs[_i]->GetInner())
					{
						previewMechs[_i]->SetItem(clickableMechs[i]->GetItem());
						previewMechs[_i]->ChangeInner(clickableMechs[i]->GetInnerImage()->GetPath());
						previewMechs[_i]->SetInner(true);
						bind = true;
						break;
					}
				}
				clickableMechs[i]->SetClicked(false);
				if (bind) break;
			}
		}
		for (int i = 0; i < previewMechs.size(); i++)
		{
			previewMechs[i]->SetPos(Vector2(squadPreview->GetPos().x + 20.f + ((previewMechs[i]->GetInnerImage()->GetWidth() + 10.f) * 2 * i)
				, squadPreview->GetPos().y + squadPreview->GetSize().y / 2 - previewMechs[i]->GetInnerImage()->GetHeight()));
			if (previewMechs[i]->GetClicked())
			{
				if (i == 2)
				{
					previewMechs[i]->SetInner(false);
					previewMechs[i]->SetItem(-1);
				}
					
				else
				{
					for (int _i = i; _i < 2; _i++)
					{
						if (previewMechs[_i + 1]->GetInner())
						{
							previewMechs[_i]->ChangeInner(previewMechs[_i + 1]->GetInnerImage()->GetPath());
							previewMechs[_i]->SetItem(previewMechs[_i + 1]->GetItem());
						}
						else
						{
							previewMechs[_i]->SetInner(false);
							previewMechs[_i]->SetItem(-1);
						}
					}
					previewMechs[2]->SetInner(false);
				}

				previewMechs[i]->SetClicked(false);
			}
			 
			/*	if (previewMechs[i]->GetClicked())
			{
				if (i + 1 < 3)
				{
					for (int _i = i; _i < 2; _i++)
					{
						if (previewMechs[_i + 1]->GetInner())
							previewMechs[_i]->ChangeInner(previewMechs[i + 1]->GetInnerImage()->GetPath());
						else
						{
							previewMechs[_i]->SetInner(false);
						}
					}
					if (previewMechs[2]->GetInner()) previewMechs[2]->SetInner(false);
				}
				else previewMechs[i]->SetInner(false);

				previewMechs[i]->SetClicked(false);
			}*/
		}
		for (int i = 0; i < 2; i++)
		{
			if (cloud[i]->GetPos().x > moon->GetPos().x + moon->GetWidth() * 2 + 40.f)
			{
				cloud[i]->SetPos(Vector2(moon->GetPos().x + 1 - cloudDiff - cloud[i]->GetWidth() * 2, cloud[i]->GetPos().y));
			}
			cloud[i]->SetPos(Vector2(cloud[i]->GetPos().x + 0.5f, cloud[i]->GetPos().y));
		}
		//for(int bright = 50; bright <= 255; bright++)

	}

	void SelectRobotScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void SelectRobotScene::Release()
	{
		Scene::Release();
	}
	void SelectRobotScene::OnEnter()
	{
		ambiousHangar = Resources::Load<Sound>(L"hangar_ambi", L"..\\Resources\\sound\\ambience\\amb_hanger.wav");
		ambiousHangar->SetVolume(10.f);
		ambiousHangar->Play(true);
		Camera::SetLookAt(Vector2((float)application.GetResolutionWidth() / 2, (float)application.GetResolutionHeight() / 2));
	}
	void SelectRobotScene::OnExit()
	{
		if(ambiousHangar)
			ambiousHangar->Stop(true);
		Camera::SetLookAt(Vector2((float)application.GetResolutionWidth() / 2, (float)application.GetResolutionHeight() / 2));
	}
}
