#include "mScene.h"
#include "mLayer.h"
#include "mUnit.h"
#include "mTile.h"
#include "Building.h"
#include "Mech.h"
#include "Alien.h"
#include "mSkill.h"
#include "mSelectGDI.h"
#include "mApplication.h"
#include "mBackground.h"
#include "mCombatScene.h"
#include "mSelectLandScene.h"
#include "mInLandScene.h"
#include "mButton.h"
#include "func.h"
#include "mInput.h"
extern m::Application application;
namespace m
{
	Scene::Scene()
		: mMouseFollower(nullptr)
		, mAlphaFollower(nullptr)
		, playerTurn(false)
		, curTurnEnd(true)
		, firstUpdate(true)
		, curAttackAlien(0)
	{
		//mLayers.reserve((UINT)LAYER_TYPE::END);
		mLayers.resize((UINT)LAYER_TYPE::END);
	}
	Scene::~Scene()
	{

	}
	void Scene::Initialize()
	{
		//*(lmer)
		for (Layer& layer : mLayers)
		{
			layer.Initialize();
		}
	}
	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}
	void Scene::Destroy()
	{
		vector<GameObject*> deleteGameObjects = {};
		vector<Alien*>::iterator iter = GameComp::mAliens.begin();

		while (iter != GameComp::mAliens.end())
		{
			if ((*iter)->GetState() == GameObject::STATE::Death)
			{
				//deleteGameObjects.push_back((*iter));
				iter = GameComp::mAliens.erase(iter);
			}
			else
			{
				iter++;
			}
		}

		for (Layer& layer : mLayers)
		{
			vector<GameObject*>& gameObjects
				= layer.GetGameObjects();

			for (vector<GameObject*>::iterator iter = gameObjects.begin()
				; iter != gameObjects.end(); )
			{
				if ((*iter)->GetState() == GameObject::STATE::Death
					||
					(*iter)->GetState() == GameObject::STATE::Delete)
				{
					deleteGameObjects.push_back((*iter));
					iter = gameObjects.erase(iter);
				}
				else
				{
					iter++;
				}
			}
		}

		// 죽은 위치에서 충돌중인 다른 충돌체가 있었다면 Exit를
		// 호출 해준후에 삭제 해주어야한다.

		for (GameObject* deathObj : deleteGameObjects)
		{
			delete deathObj;
			deathObj = nullptr;
		}
	}
	void Scene::Render(HDC hdc)
	{
		for (Layer& layer : mLayers)
		{
			layer.Render(hdc);
		}
	}

	/// <summary>
	/// 타일 전체 생성 
	/// 나중에 타일을 저장하면 불러올때
	/// 각 타일에 대한 처리 해주어야됨
	/// </summary>
	/// <param name="iX">타일 x 크기</param>
	/// <param name="iY">타일 y 크기</param>
	/// <param name="_type">전체 타일의 땅 타입</param>
	/// <param name="_type2">전체 타일의 타입</param>
	void Scene::MakeTile(int iX, int iY, TILE_T _type, TILE_HEAD_T _type2)
	{
		mTiles.resize(iY, vector<Tile*>());
		mPosTiles.resize(iY, vector<Tile*>());
		mPosOutLineTiles.resize(iY, vector<Tile*>());
		mBoundaryTiles.resize(iY, vector<Tile*>());
		mArrowTiles.resize(iY, vector<Tile*>());
		//mEffectedTiles.resize(iY, vector<Tile*>());
		//mEnemyEmerge.resize(iY, vector<Tile*>());
		//mStruturesTiles.resize(iY, vector<Building*>());
		for (int y = 0; y < iY; y++)
		{
			mTiles[y].resize(iX);
			mPosTiles[y].resize(iX);
			mPosOutLineTiles[y].resize(iX);
			mBoundaryTiles[y].resize(iX);
			mArrowTiles[y].resize(iX);
			//mStruturesTiles[y].resize(iX);
			//mEffectedTiles[y].resize(iX);
			//mEnemyEmerge[y].resize(iX);
		}
		float fX, fY;
		float mX = (10.f * (TILE_SIZE_X / 2.f));
		float mY = TILE_SIZE_Y / 4.f;
		for (int y = 0; y < iY; y++)
		{
			for (int x = 0; x < iX; x++)
			{
				if (nullptr == mTiles[y][x])
				{
					Tile* tile = new Tile(Vector2((float)x, (float)y));
					fX = (float)((TILE_SIZE_X / TILE_X_DIVIDE_RECT) * (x - y) + mX);
					fY = (float)((TILE_SIZE_Y / TILE_Y_DIVIDE_RECT) * (x + y) + mY);
					tile->SetPos(Vector2(fX * 2, fY * 2));
					tile->SetTileType(_type);
					tile->SetTileTexture(MAKE_TILE_KEY(_type, _type2)
						, MAKE_TILE_PATH(_type, _type2));
					mTiles[y][x] = tile;
					AddGameObject(tile, LAYER_TYPE::TILE);
				}
				else
				{
					fX = (float)((TILE_SIZE_X / TILE_X_DIVIDE_RECT) * (x - y) + mX);
					fY = (float)((TILE_SIZE_Y / TILE_Y_DIVIDE_RECT) * (x + y) + mY);
					mTiles[y][x]->SetPos(Vector2(fX * 2, fY * 2));
					mTiles[y][x]->SetTileType(_type);
					mTiles[y][x]->SetTileTexture(MAKE_TILE_KEY(_type, _type2)
						, MAKE_TILE_PATH(_type, _type2));
				}
			}
		}
		MakeVariTile(iY, iX);

		SetMap();
	}
	/// <summary>
	/// 맵위의 오브젝트 표시를 위해 벡터 초기화.
	/// </summary>
	/// <param name="iX"></param>
	/// <param name="iY"></param>
	void Scene::MakeVariTile(int iX, int iY)
	{
		/*for (int y = iY - 1; y >= 0; y--) {
			for (int x = iX - 1; x >= 0; x--) {*/
		for (int y = 0; y < iY; y++)
		{
			for (int x = 0; x < iX; x++)
			{
				if (nullptr == mPosTiles[y][x])
				{
					Tile* posTile = new Tile(mTiles[y][x]->GetCoord());
					posTile->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
					posTile->SetPos(mTiles[y][x]->GetPos());
					mPosTiles[y][x] = posTile;
					AddGameObject(posTile, LAYER_TYPE::TILE);
				}
				if (nullptr == mBoundaryTiles[y][x])
				{
					Tile* etcTile = new Tile(mTiles[y][x]->GetCoord());
					etcTile->InitETCTiles(4);
					etcTile->SetPos(mTiles[y][x]->GetPos());
					mBoundaryTiles[y][x] = etcTile;
					AddGameObject(etcTile, LAYER_TYPE::TILE);
					
				}
				if (nullptr == mArrowTiles[y][x])
				{
					Tile* awTile = new Tile(mTiles[y][x]->GetCoord());
					awTile->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
					awTile->SetPos(mTiles[y][x]->GetPos());
					mArrowTiles[y][x] = awTile;
					AddGameObject(awTile, LAYER_TYPE::TILE);
				}
			}
		}
		for (int y = 0; y < iY; y++)
		{
			for (int x = 0; x < iX; x++)
			{
				if (nullptr == mPosOutLineTiles[y][x])
				{
					Tile* posLineTile = new Tile(mTiles[y][x]->GetCoord());
					posLineTile->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
					posLineTile->SetPos(mTiles[y][x]->GetPos());
					mPosOutLineTiles[y][x] = posLineTile;
					AddGameObject(posLineTile, LAYER_TYPE::TILE);
				}
				
			}
		}
	}
	void Scene::ClearMap()
	{
		for (int y = 0; y < mPosTiles.size(); y++)
		{
			for (int x = 0; x < mPosTiles[y].size(); x++)
			{
				map[y][x] = 0;
			}
		}
	}
	void Scene::ClearBackTiles()
	{
		if (mBackTiles.size() == 0) return;
		vector<Tile*>::iterator iter = mBackTiles.begin();
		while (iter != mBackTiles.end())
		{
			if (!(*iter)->GetComponent<Animator>()->GetStopAnimator())
			{
				iter++;
			}
			else if (!(*iter)->GetShown())
			{
				(*iter)->SetShown(true);
				iter++;
			}
			else
			{
				object::Destory((*iter));
				iter = mBackTiles.erase(iter);
			}
		}
		//for (int i = 0; i < mBackTiles.size();)
		//{
		//	if (!mBackTiles[i]->GetShown())
		//	{
		//		mBackTiles[i]->SetShown(true);
		//		continue;
		//	}
		//	object::Destory(mBackTiles[i]);
		//	
		//	//delete mBackTiles[i];
		//}
	}
	bool Scene::CheckMouseOutRange()
	{
		Vector2 bigRhombusPos(mPosTiles[7][0]->GetPos().x, mPosTiles[0][0]->GetPos().y);

		Vector2 bigRhombusDownPos(
			mPosTiles[0][7]->GetPos().x + mPosTiles[0][7]->GetScale().x,
			mPosTiles[7][7]->GetPos().y + mPosTiles[7][7]->GetScale().y);

		Vector2 bigRhombusScale(bigRhombusDownPos.x - bigRhombusPos.x, bigRhombusDownPos.y - bigRhombusPos.y);


		if (math::CheckRhombusPos(bigRhombusPos, bigRhombusScale, MOUSE_POS))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void Scene::OutOfMapRange()
	{
		if (!CheckMouseOutRange())
		{
			if (!mMouseFollower->GetMove())
			{
				mMouseFollower->GetCurAttackSkill()->SetStartRender(false);
			}
			mMouseFollower->SetCoord(mMouseFollower->GetFinalCoord());
			mMouseFollower->SetPos(mMouseFollower->GetFinalPos());
			SetAlphaState(GameObject::STATE::Invisible);
		}
		for (int y = 0; y < mPosTiles.size(); y++)
		{
			for (int x = 0; x < mPosTiles[y].size(); x++)
			{
				Tile* p = mPosTiles[y][x];
				if (math::CheckRhombusPos(p->GetPos(), p->GetScale(), MOUSE_POS))
				{
					// 마우스의 위치가 이동가능 범위가 아닐때
					// 원래 위치에 돌아감
					if (map[y][x] != MOVE)
					{
						mMouseFollower->SetCoord(mMouseFollower->GetFinalCoord());
						mMouseFollower->SetPos(mMouseFollower->GetFinalPos());
						mMouseFollower->GetDirectQue().clear();
					}
					// 마우스의 위치가 이동가능 범위일때
					// 마우스위치의 타일로 이동
					if (map[y][x] == MOVE)
					{
						mMouseFollower->SetCoord(mPosTiles[y][x]->GetCoord());
						mMouseFollower->SetPos(mPosTiles[y][x]->GetCenterPos());
					}
				}
			}
		}
	}


	/// <summary>
	/// 마우스 위치에 메카
	/// </summary>
	void Scene::RobotDrag()
	{
		for (int y = 0; y < mPosTiles.size(); y++)
		{
			for (int x = 0; x < mPosTiles[y].size(); x++)
			{
				// 마우스의 위치있는 메카 마우스에 따라오게
				Tile* p = mPosTiles[y][x];
				if (math::CheckRhombusPos(p->GetPos(), p->GetScale(), MOUSE_POS))
				{
					for (UINT _i = 0; _i < GameComp::mMechs.size(); _i++)
					{
						if (mPosTiles[y][x]->GetCoord() == GameComp::mMechs[_i]->GetCoord())
						{
							if (GameComp::mMechs[_i]->GetState() == GameObject::STATE::Broken) continue;
							//PlayerInfo::mMechs[_i]->SetMove(true);
							GameComp::mMechs[_i]->SetSelected(true);
							SetMouseFollower(GameComp::mMechs[_i]);
							SetAlphaFollower((Mech*)object::Instantiate(mMouseFollower->GetFinalCoord(), LAYER_TYPE::CLONE, mMouseFollower->GetUnitName()));
							break;
						}
					}
				}
			}
		}
	}
	void Scene::SetMap()
	{
		//for (int y = 0; y < mStruturesTiles.size(); y++)
		//{
		//	for (int x = 0; x < mStruturesTiles[y].size(); x++)
		//	{
		//		if (mStruturesTiles[y][x]->GetType() == STRUCTURES_T::Mountain)
		//		{
		//			map[y][x] = BUILDING;
		//		}
		//	}
		//}
		ClearMap();
		for (int i = 0; i < mStrutures.size(); i++)
		{
			Vector2 mp = mStrutures[i]->GetFinalCoord();
			if (mStrutures[i]->GetState() != GameObject::STATE::Explo)
				map[(int)mp.y][(int)mp.x] = BUILDING;
		}
		for (int i = 0; i < GameComp::mAliens.size(); i++)
		{
			Vector2 mp = GameComp::mAliens[i]->GetFinalCoord();

			if (GameComp::mAliens[i]->GetState() != GameObject::STATE::Emerge_loop)
				map[(int)mp.y][(int)mp.x] = ALIEN;
		}
		for (int i = 0; i < GameComp::mMechs.size(); i++)
		{
			Vector2 mp = GameComp::mMechs[i]->GetFinalCoord();
			map[(int)mp.y][(int)mp.x] = MECH;
		}
		if (nullptr != GameComp::bomb)
		{
			Vector2 mp = GameComp::bomb->GetFinalCoord();
			map[(int)mp.y][(int)mp.x] = MECH;
		}
	}
	void Scene::DrawFootTile()
	{
		for (UINT _i = 0; _i < GameComp::mAliens.size(); _i++)
		{
			if (nullptr == GameComp::mAliens[_i]
				|| GameComp::mAliens[_i]->GetFinalCoord() == Vector2::Zero
				/*|| GameComp::mAliens[_i]->GetState() == GameObject::STATE::Emerge*/
				|| GameComp::mAliens[_i]->GetState() == GameObject::STATE::Emerge_loop) continue;
			Vector2 mCoord = GameComp::mAliens[_i]->GetFinalCoord();
			mPosTiles[(int)mCoord.y][(int)mCoord.x]->SetTileType(TILE_T::MONSTER);
			mPosTiles[(int)mCoord.y][(int)mCoord.x]->SetSourceConstantAlpha(100);
			mPosTiles[(int)mCoord.y][(int)mCoord.x]->SetTileTexture(
				MAKE_TILE_KEY(MOVE_TILE_T::square_gy)
				, MAKE_TILE_PATH(MOVE_TILE_T::square_gy));
		}
		for (UINT _i = 0; _i < GameComp::mMechs.size(); _i++)
		{
			Vector2 mCoord = GameComp::mMechs[_i]->GetFinalCoord();
			mPosTiles[(int)mCoord.y][(int)mCoord.x]->SetTileType(TILE_T::PLAYER);
			mPosTiles[(int)mCoord.y][(int)mCoord.x]->SetSourceConstantAlpha(150);
			mPosTiles[(int)mCoord.y][(int)mCoord.x]->SetTileTexture(
				MAKE_TILE_KEY(MOVE_TILE_T::square_b)
				, MAKE_TILE_PATH(MOVE_TILE_T::square_b));
		}
	}
	/// <summary>
	/// 전체 타일 초기화.
	/// 나중에 맵위에 다른 타일의 정보에 대한 분기가 필요함
	/// </summary>
	/// <param name="_type">땅 종류</param>
	/// <param name="_hT">타일 타입</param>
	void Scene::ClearMTiles(TILE_T _type, TILE_HEAD_T _hT)
	{
		for (int y = 0; y < mPosTiles.size(); y++)
		{
			for (int x = 0; x < mPosTiles[y].size(); x++)
			{
				mBoundaryTiles[y][x]->ClearAddETCTiles();
				mArrowTiles[y][x]->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
				mPosTiles[y][x]->SetTileType(TILE_T::COMMON);
				mPosTiles[y][x]->SetSourceConstantAlpha(50);
				mPosTiles[y][x]->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
				mTiles[y][x]->SetTileType(mapType);
				mTiles[y][x]->SetTileTexture(MAKE_TILE_KEY(mapType, TILE_HEAD_T::ground)
					, MAKE_TILE_PATH(mapType, TILE_HEAD_T::ground));
			}
		}
		ClearBackTiles();
		ClearMap();
	}
	/// <summary>
	/// 마우스 위치의 타일 바꿈
	/// </summary>
	void Scene::HighlightTile()
	{
		for (int y = 0; y < mPosOutLineTiles.size(); y++)
		{
			for (int x = 0; x < mPosOutLineTiles[y].size(); x++)
			{
				Tile* p = mPosTiles[y][x];
				if (math::CheckRhombusPos(p->GetPos(), p->GetScale(), MOUSE_POS))
				{
					if (map[y][x] != MOVE) mPosOutLineTiles[y][x]->SetTileTexture(SQUARE_Y_LINE__KEY, SQUARE_Y_LINE__PATH);
				}
				else mPosOutLineTiles[y][x]->SetTileTexture(SQUARE__KEY, SQUARE__PATH);
			}
		}
	}
	void Scene::Release()
	{
		//Safe_Delete_X_Vec(mBacks);
		//Safe_Delete_X_Vec(mBackTiles);
		Safe_Delete_X_Vec(mStrutures);

		Safe_Delete_Y_Vec(mTiles);
		Safe_Delete_Y_Vec(mPosTiles);
		Safe_Delete_Y_Vec(mPosOutLineTiles);
		Safe_Delete_Y_Vec(mBoundaryTiles);
		Safe_Delete_Y_Vec(mArrowTiles);
		//Safe_Delete_Y_Vec(mEnemyEmerge);
		//Safe_Delete_Y_Vec(mEffectedTiles);
	}
	void Scene::CheckNumInput()
	{
		//if (nullptr == mMouseFollower) return;
		//if (KEY_DOWN(KEYCODE_TYPE::NUM_1)) { mMouseFollower->SetSkillIdx(0); }
		//if (KEY_DOWN(KEYCODE_TYPE::NUM_2)) { mMouseFollower->SetSkillIdx(1); }
		//if (KEY_DOWN(KEYCODE_TYPE::NUM_3)) { mMouseFollower->SetSkillIdx(2); }
		//if (KEY_DOWN(KEYCODE_TYPE::NUM_1)
		//	|| KEY_DOWN(KEYCODE_TYPE::NUM_2)
		//	|| KEY_DOWN(KEYCODE_TYPE::NUM_3))
		//{
		//	mMouseFollower->SetPos(mMouseFollower->GetFinalPos());
		//	mMouseFollower->SetCoord(mMouseFollower->GetFinalCoord());

		//	if (!mMouseFollower->GetMove()) // 공격이 취소되고 이동가능상태로
		//	{
		//		mMouseFollower->SetMove(true);
		//		mMouseFollower->GetCurAttackSkill()->SetStartRender(false);

		//		mMouseFollower->SetSkillIdx(-1);
		//	}
		//	else // 이동이 취소되고 공격가능상태로
		//	{
		//		mMouseFollower->SetCurAttackSkill();
		//		mMouseFollower->SetMove(false);
		//	}
		//}
	}
	void Scene::AlienAlgorithm()
	{
		if (playerTurn || curTurnEnd) return;
		//drawTile();
		//bool n = false;
		//for (int i = 0; i < PlayerInfo::mMechs.size(); i++)
		//	if (PlayerInfo::mMechs[i]->GetState() == GameObject::STATE::Idle) n = true;
		//if (!n) return;
		for (int i = 0; i < GameComp::mAliens.size(); i++)
		{
			if (GameComp::mAliens[i]->GetState() == GameObject::STATE::Broken
				||
				GameComp::mAliens[i]->GetState() == GameObject::STATE::Delete
				||
				GameComp::mAliens[i]->GetState() == GameObject::STATE::Death)
			{
				return;
			}
		}
		if (GameComp::mAliens.size() <= curAttackAlien)
		{
			((CombatScene*)SceneManager::GetActiveScene())->SetTextTurnNumber(
				((CombatScene*)SceneManager::GetActiveScene())->GetTextTurnNumber() + 1
			);
			playerTurn = true;
			curTurnEnd = true;
			SaveTurn();
			curAttackAlien = 0;
			((CombatScene*)SceneManager::GetActiveScene())->RandSpawnAlien(1);
			return;
		}
		Alien* curAlien = GameComp::mAliens[curAttackAlien];
		if (curAlien->GetState() == GameObject::STATE::Death) return;
		if (curAlien->GetState() == GameObject::STATE::Emerge_loop)
		{
			if (!SearchBlockUnit((int)curAlien->GetCoord().y, (int)curAlien->GetCoord().x))
			{
				curAlien->SetState(GameObject::STATE::Emerge);
			}
			else
			{
				HitAffectUnit((int)curAlien->GetCoord().y, (int)curAlien->GetCoord().x, 1);
				GameComp::iBlockCnt++;
				curAttackAlien++;
			}
			return;
		}
		if (curAlien->GetState() == GameObject::STATE::Emerge) return;

		if (nullptr != curAlien->GetCurAttackSkill()
			&& curAlien->GetCurAttackSkill()->GetStartRender())
		{
			curAlien->SetEndAttack(true);
			curAlien->GetCurAttackSkill()->SetStartFire(true);
			//curAlien->GetCurAttackSkill()->SetEndFire(false);
		}
		if (nullptr != curAlien->GetCurAttackSkill()
			&& curAlien->GetCurAttackSkill()->GetStartFire())
		{
			curAlien->GetCurAttackSkill()->CheckDirection();
		}

		if (curAlien->GetCurAttackSkill()->CheckSkillFiring()) return;

		//if (curAlien->GetEndAttack())
		//{
		//	curAlien->GetCurAttackSkill()->SetStartRender(false);
		//	curAlien->GetCurAttackSkill()->SetStartFire(false);
		//	curAlien->GetCurAttackSkill()->SetEndFire(false);
		//	curAlien->SetEndAttack(false);
		//	return;
		//}

		curAlien->AlienMapCheck(curAttackAlien);
		curAlien->AlienMoveCheck(curAttackAlien);

		//curAttackAlien++;
	}
	void Scene::MoveSkill()
	{
		if (!playerTurn || curTurnEnd) return;
		for (int i = 0; i < GameComp::mAliens.size(); i++)
		{
			if (GameComp::mAliens[i]->GetState() == GameObject::STATE::Broken
				||
				GameComp::mAliens[i]->GetState() == GameObject::STATE::Delete
				||
				GameComp::mAliens[i]->GetState() == GameObject::STATE::Death)
			{
				return;
			}
		}
		for (int i = 0; i < GameComp::mAliens.size(); i++)
		{
		//	//if (GameComp::mAliens[i]->GetFinalMoveCoord() != Vector2::Minus)
		//	//{
		//	//	SetPosTiles((int)GameComp::mAliens[i]->GetFinalMoveCoord().y, (int)GameComp::mAliens[i]->GetFinalMoveCoord().x
		//	//		, TILE_T::MOVE_RANGE, MOVE_TILE_T::square_g);
		//	//}
		//	//if (GameComp::mAliens[i]->GetCurAttackSkill()->CheckSkillFiring()) continue;
		//	//GameComp::mAliens[i]->AlienMoveToAttackCheck(GameComp::mAliens[i]->GetCoord());
			GameComp::mAliens[i]->ActiveSkill(GameComp::mAliens[i]->GetTargetCoord());
		}
		if (nullptr == mMouseFollower
			|| mMouseFollower->GetMove()
			|| nullptr == mMouseFollower->GetCurAttackSkill()) return;

		if (mMouseFollower->GetCurAttackSkill()->GetStartFire())
		{
			mMouseFollower->GetCurAttackSkill()->CheckDirection();
		}
		

		if (mMouseFollower->CheckSkillFiring()) return;

		mMouseFollower->ActiveSkill(MOUSE_POS);
		mMouseFollower->DrawSkillRangeTile();

		Scene::OutOfMapRange();

		if (KEY_DOWN(KEYCODE_TYPE::RBTN)
			&& !mMouseFollower->GetCurAttackSkill()->GetStartFire())
		{
			mMouseFollower->GetCurAttackSkill()->SetStartRender(false);
			mMouseFollower->SetMove(true);
			((CombatScene*)SceneManager::GetActiveScene())->SetWPBow(2);
		}

		if (KEY_DOWN(KEYCODE_TYPE::LBTN))
		{

			if (mMouseFollower->GetCurAttackSkill()->GetStartRender())
			{
				if (mMouseFollower->GetCurAttackSkill()->GetEndCoord() != Vector2::Zero)
				{
					// 공격.
					mMouseFollower->GetCurAttackSkill()->SetStartFire(true);
					//mMouseFollower->GetCurAttackSkill()->SetEndFire(false);
					moveSave.clear();
				}
			}
		}
	}
	void Scene::drawTile()
	{
		Scene::ClearMTiles(mapType, TILE_HEAD_T::ground);

		Scene::DrawFootTile();
		Scene::HighlightTile();
	}
	void Scene::SaveTurn()
	{
		saveGridPower = GameComp::gridPower;
		turnSave.clear();
		for (int i = 0; i < GameComp::mMechs.size(); i++)
		{
			turnSave.push_back(Vector2_3(
				GameComp::mMechs[i]->GetFinalCoord()
				, GameComp::mMechs[i]->GetFinalPos()
				, GameComp::mMechs[i]->GetMIdx()
				, (int)GameComp::mMechs[i]->GetState()
				, (int)GameComp::mMechs[i]->GetButtonType()
				, GameComp::mMechs[i]->GetCurHp()
			));
		}
		for (int i = 0; i < GameComp::mAliens.size(); i++)
		{
			turnSave.push_back(Vector2_3(
				GameComp::mAliens[i]->GetFinalCoord()
				, GameComp::mAliens[i]->GetFinalPos()
				, GameComp::mAliens[i]->GetMIdx()
				, (int)GameComp::mAliens[i]->GetState()
				, (int)GameComp::mAliens[i]->GetButtonType()
				, GameComp::mAliens[i]->GetCurHp()
			));
		}
		for (int i = 0; i < mStrutures.size(); i++)
		{
			turnSave.push_back(Vector2_3(
				mStrutures[i]->GetFinalCoord()
				, mStrutures[i]->GetFinalPos()
				, mStrutures[i]->GetMIdx()
				, (int)mStrutures[i]->GetState()
				, (int)mStrutures[i]->GetButtonType()
				, 0
			));
		}

	}
	void Scene::ResetTurn()
	{
		if (GameComp::resetTurn == 0) return;
		GameComp::resetTurn -= 1;

		moveSave.clear();
		if (saveGridPower != 0) GameComp::gridPower = saveGridPower;
		for (int i = 0; i < turnSave.size(); i++)
		{
			Vector2_3 info = turnSave[i];
			if (info.bType == (int)LAYER_TYPE::PLAYER)
			{
				GameComp::mMechs[info.idx]->SetCoord(info.coord);
				GameComp::mMechs[info.idx]->SetPos(info.pos);
				GameComp::mMechs[info.idx]->SetFinalCoord(info.coord);
				GameComp::mMechs[info.idx]->SetFinalPos(info.pos);
				GameComp::mMechs[info.idx]->SetCurHp(info.curHp);
				GameComp::mMechs[info.idx]->SetState((GameObject::STATE)info.state);
				GameComp::mMechs[info.idx]->SetEndMove(false);
				GameComp::mMechs[info.idx]->SetEndAttack(false);
				for (int i = 0; i < GameComp::mMechs[info.idx]->GetSkills().size(); i++)
				{
					GameComp::mMechs[info.idx]->GetSkills()[i]->Clear();
				}
			}
			if (info.bType == (int)LAYER_TYPE::MONSTER)
			{
				GameComp::mAliens[info.idx]->SetCoord(info.coord);
				GameComp::mAliens[info.idx]->SetPos(info.pos);
				GameComp::mAliens[info.idx]->SetFinalCoord(info.coord);
				GameComp::mAliens[info.idx]->SetFinalPos(info.pos);
				GameComp::mAliens[info.idx]->SetState((GameObject::STATE)info.state);
				GameComp::mAliens[info.idx]->SetCurHp(info.curHp);
				GameComp::mAliens[info.idx]->SetEndMove(false);
				GameComp::mAliens[info.idx]->SetEndAttack(false);
			}
			if (info.bType == (int)LAYER_TYPE::STRUCT)
			{
				mStrutures[info.idx]->SetCoord(info.coord);
				mStrutures[info.idx]->SetPos(info.pos);
				mStrutures[info.idx]->SetState((GameObject::STATE)info.state);
			}
		}
		ClearAffectUnit();
		turnSave.clear();
		for (int i = 0; i < GameComp::mMechs.size(); i++)
		{
			MoveAffectUnit(GameComp::mMechs[i]);
		}
		for (int i = 0; i < GameComp::mAliens.size(); i++)
		{
			MoveAffectUnit(GameComp::mAliens[i]);
		}
		for (int i = 0; i < mStrutures.size(); i++)
		{
			MoveAffectUnit(mStrutures[i]);
		}
		//for (int y = 0; y < TILE_Y; y++)
		//{
		//	for (int x = 0; x < TILE_X; x++)
		//	{
		//		ReSortAffectUnits(y, x);
		//	}
		//}
	}
	void Scene::UndoMove()
	{
		if (moveSave.size() != 0)
		{
			Vector2_2 moveBack = moveSave.back();
			Mech* mech = GameComp::mMechs[moveBack.mechIdx];
			mech->SetCoord(Vector2(moveBack.coord));
			mech->SetPos(Vector2(moveBack.pos));
			mech->SetEndMove(false);

			MoveAffectUnit(mech);

			mech->SetFinalCoord(mech->GetCoord());
			mech->SetFinalPos(mech->GetPos());
			moveSave.pop_back();
		}
	}
	void Scene::MoveMech()
	{
		//for (int i = 0; i < GameComp::mAliens.size(); i++)
		//{
		//	//if (GameComp::mAliens[i]->GetFinalMoveCoord() != Vector2::Minus)
		//	//{
		//	//	SetPosTiles((int)GameComp::mAliens[i]->GetFinalMoveCoord().y, (int)GameComp::mAliens[i]->GetFinalMoveCoord().x
		//	//		, TILE_T::MOVE_RANGE, MOVE_TILE_T::square_g);
		//	//}
		//	//if (GameComp::mAliens[i]->GetCurAttackSkill()->CheckSkillFiring()) continue;
		//	//GameComp::mAliens[i]->AlienMoveToAttackCheck(GameComp::mAliens[i]->GetCoord());
		//	GameComp::mAliens[i]->ActiveSkill(GameComp::mAliens[i]->GetTargetCoord());
		//}
		if (nullptr == mMouseFollower)
		{
			((CombatScene*)SceneManager::GetActiveScene())->ShowMechInfo(nullptr, false);
			((CombatScene*)SceneManager::GetActiveScene())->SetWPBow(2);
		}
		if (!playerTurn || curTurnEnd) return;
		drawTile();

		//((CombatScene*)SceneManager::GetActiveScene())->PlayerTurnBackground();
		//if (!((CombatScene*)SceneManager::GetActiveScene())->GetTurnBox1()->GetEndApDAp()) return;
		for (int i = 0; i < GameComp::mAliens.size(); i++)
		{
			if (GameComp::mAliens[i]->GetState() == GameObject::STATE::Broken)
			{
				return;
			}
		}
		if (KEY_UP(KEYCODE_TYPE::SPACE))
		{
			if (!playerTurn) playerTurn = true;
			else
			{
				//((CombatScene*)SceneManager::GetActiveScene())->SetTextTurnNumber(
				//	((CombatScene*)SceneManager::GetActiveScene())->GetTextTurnNumber() + 1
				//);
				playerTurn = false;
				if (nullptr != mMouseFollower)
				{
					mMouseFollower->SetPos(mMouseFollower->GetFinalPos());
					mMouseFollower->SetCoord(mMouseFollower->GetFinalCoord());

					if (nullptr != mMouseFollower->GetCurAttackSkill())
					{
						mMouseFollower->GetCurAttackSkill()->SetStartRender(false);
					}

					SetMouseFollower(nullptr);
				}
			}
			curTurnEnd = true;
			// TODO: TURN END
		}


		if (nullptr != mMouseFollower)
		{
			if (!mMouseFollower->GetMove()) return;
		}

		if (nullptr != mMouseFollower)
		{
			((CombatScene*)SceneManager::GetActiveScene())->ShowMechInfo(mMouseFollower, true);
			if (mMouseFollower->GetMove() && !mMouseFollower->GetEndMove())
			{
				mMouseFollower->DrawMoveRangeTile();
				mMouseFollower->DrawMoveDirectionTile();
			}
			Scene::OutOfMapRange();
		}
		else
		{
			((CombatScene*)SceneManager::GetActiveScene())->ShowMechInfo(nullptr, false);
		}

		if (KEY_DOWN(KEYCODE_TYPE::LSHIFT))
		{
			Scene::UndoMove();
		}

		if (KEY_DOWN(KEYCODE_TYPE::RBTN)
			&& nullptr != mMouseFollower)
		{
			mMouseFollower->SetPos(mMouseFollower->GetFinalPos());
			mMouseFollower->SetCoord(mMouseFollower->GetFinalCoord());
			((CombatScene*)SceneManager::GetActiveScene())->SetWPBow(2);
			SetMouseFollower(nullptr);
		}

		if (KEY_DOWN(KEYCODE_TYPE::LBTN))
		{

			if (nullptr != mMouseFollower)
			{
				//MoveEffectUnit(mMouseFollower);
				if (moveSave.size() == 0 || moveSave.back().mechIdx != mMouseFollower->GetMIdx())
				{
					moveSave.push_back(Vector2_2(mMouseFollower->GetFinalCoord(), mMouseFollower->GetFinalPos(), mMouseFollower->GetMIdx()));
				}

				mMouseFollower->SetEndMove(true);
				MoveAffectUnit(mMouseFollower, mMouseFollower->GetCoord());
				/*mMouseFollower->SetFinalPos(mMouseFollower->GetPos());
				mMouseFollower->SetFinalCoord(mMouseFollower->GetCoord());*/
				//SetMouseFollower(nullptr);
			}
			else
			{
				Scene::RobotDrag();
			}
		}
	}
	void Scene::ReSortAffectUnits(float y, float x)
	{
		int _y = (int)y;
		int _x = (int)x;
		if (affectUnits[_y][_x].size() == 0) return;
		for (int i = 0; i < affectUnits[_y][_x].size(); i++)
		{
			affectUnits[_y][_x][i]->SetAffectUnitVectorIdx(i);
		}
	}
	void Scene::ReSortAffectUnits(int y, int x)
	{
		if (affectUnits[y][x].size() == 0) return;
		for (int i = 0; i < affectUnits[y][x].size(); i++)
		{
			affectUnits[y][x][i]->SetAffectUnitVectorIdx(i);
		}
	}
	void Scene::MoveAffectUnit(Unit* unit, Vector2 _coord, bool push)
	{
		Vector2 idx = unit->GetFinalCoord();
		if (push)
		{
			float x = _coord.x - idx.x;
			float y = _coord.y - idx.y;
			((Alien*)unit)->SetTargetCoord(((Alien*)unit)->GetTargetCoord() + Vector2(x, y));
		}
		//if (effectUnits[(UINT)_coord.y][(UINT)_coord.x].size() == 0)
		//{
		//	effectUnits[(UINT)_coord.y][(UINT)_coord.x]->GetState() != GameObject::STATE::Emerge_loop) return;
		//}
		//if (idx == Vector2::Minus) return
			//effectUnits[(UINT)idx.y][(UINT)idx.x] = nullptr;
		RemoveAffectUnit(idx, unit);
		affectUnits[(UINT)_coord.y][(UINT)_coord.x].push_back(unit);
		ReSortAffectUnits(_coord.y, _coord.x);
		//unit->SetAffectUnitVectorIdx(affectUnits[(UINT)_coord.y][(UINT)_coord.x].size() - 1);
		//vector<Unit*>::iterator iter = effectUnits[(UINT)idx.y][(UINT)idx.x].begin();
		//for (int i = 0; i < effectUnits[(UINT)idx.y][(UINT)idx.x].size(); i++)
		//{
		//	if (effectUnits[(UINT)idx.y][(UINT)idx.x][i] == unit)
		//	{
		//		effectUnits[(UINT)idx.y][(UINT)idx.x].erase(iter + i);
		//		effectUnits[(int)_coord.y][(int)_coord.x].push_back(unit);
		//		unit->SetUnitIdx(effectUnits[(int)_coord.y][(int)_coord.x].size() - 1);
		//	}
		//}
		unit->SetPos(mPosTiles[(int)_coord.y][(int)_coord.x]->GetCenterPos());
		unit->SetCoord(_coord);
		unit->SetFinalCoord(unit->GetCoord());
		unit->SetFinalPos(unit->GetPos());
	}
	void Scene::MoveAffectUnit(Unit* unit)
	{
		Vector2 idx = unit->GetFinalCoord();
		Vector2 nIdx = unit->GetCoord();
		//if(idx != Vector2::Minus)
		//	effectUnits[(UINT)idx.y][(UINT)idx.x] = nullptr;
		RemoveAffectUnit(idx, unit);
		if (nIdx != Vector2::Minus)
		{
			affectUnits[(UINT)nIdx.y][(UINT)nIdx.x].push_back(unit);
			ReSortAffectUnits(nIdx.y, nIdx.x);
		}

		//vector<Unit*>::iterator iter = effectUnits[(UINT)idx.y][(UINT)idx.x].begin();
		//for (int i = 0; i < effectUnits[(UINT)idx.y][(UINT)idx.x].size(); i++)
		//{
		//	if (effectUnits[(UINT)idx.y][(UINT)idx.x][i] == unit)
		//	{
		//		effectUnits[(UINT)idx.y][(UINT)idx.x].erase(iter + i);
		//		effectUnits[(int)_coord.y][(int)_coord.x].push_back(unit);
		//		unit->SetUnitIdx(effectUnits[(int)_coord.y][(int)_coord.x].size() - 1);
		//	}
		//}
		//unit->SetPos(mPosTiles[(int)nIdx.y][(int)nIdx.x]->GetCenterPos());
		//unit->SetCoord(nIdx);
		//unit->SetFinalCoord(unit->GetCoord());
		//unit->SetFinalPos(unit->GetPos());
	}
	void Scene::HitAffectUnit(int y, int x, int damage)
	{
		if (GetAffectUnits(y, x).size() == 0) return;
		for (int i = 0; i < GetAffectUnits(y, x).size(); i++)
		{
			if (GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Explo
				|| GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Emerge_loop
				|| GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Death
				|| GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Invisible) continue;
			if (GetAffectUnits(y, x)[i]->GetButtonType() == LAYER_TYPE::MONSTER
				&& GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Broken) continue;

			if (GetAffectUnits(y, x)[i]->GetButtonType() == LAYER_TYPE::STRUCT) { 
				GameComp::saveTurnPeople -= 20; 
				GameComp::bStructureAlive = false;
				GameComp::iGridDamageCnt++;
				GameComp::iStructDesCnt++;
			}
			if (GetAffectUnits(y, x)[i]->GetButtonType() == LAYER_TYPE::PLAYER)
			{
				GameComp::iMechDamageCnt++;
			}

			GetAffectUnits(y, x)[i]->Hit(damage);
		}
	}
	bool Scene::SearchAffectUnitM(int y, int x, LAYER_TYPE type)
	{
		if (GetAffectUnits(y, x).size() == 0) return false;
		for (int i = 0; i < GetAffectUnits(y, x).size(); i++)
		{
			if (GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Explo
				|| GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Emerge_loop
				|| GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Death
				|| GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Invisible
				|| GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Broken) continue;
			//if (GetAffectUnits(y, x)[i]->GetLayerType() == LAYER_TYPE::MONSTER
			//	&& GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Broken) continue;

			if (GetAffectUnits(y, x)[i]->GetButtonType() != type
				&& GetAffectUnits(y, x)[i]->GetButtonType() != LAYER_TYPE::TERRAIN)
			{
				return true;
			}

		}
		return false;
	}
	bool Scene::SearchAffectUnit(int y, int x, LAYER_TYPE type)
	{
		if (GetAffectUnits(y, x).size() == 0) return false;
		for (int i = 0; i < GetAffectUnits(y, x).size(); i++)
		{
			if (GetAffectUnits(y, x)[i]->GetButtonType() == type)
			{
				return true;
			}

		}
		return false;
	}
	bool Scene::SearchAffectUnit(int y, int x, LAYER_TYPE type, GameObject::STATE state)
	{
		if (GetAffectUnits(y, x).size() == 0) return false;
		for (int i = 0; i < GetAffectUnits(y, x).size(); i++)
		{
			if (GetAffectUnits(y, x)[i]->GetState() == state
				&& GetAffectUnits(y, x)[i]->GetButtonType() == type)
			{
				return true;
			}

		}
		return false;
	}
	bool Scene::SearchAffectUnit(int y, int x, GameObject::STATE state, bool contain)
	{
		if (GetAffectUnits(y, x).size() == 0) return false;
		for (int i = 0; i < GetAffectUnits(y, x).size(); i++)
		{
			if (contain)
			{
				if (GetAffectUnits(y, x)[i]->GetState() == state)
				{
					return true;
				}
			}
			else
			{
				if (GetAffectUnits(y, x)[i]->GetState() != state)
				{
					return true;
				}
			}


		}
		return false;
	}
	bool Scene::SearchAffectUnit(int y, int x, GameObject::STATE state)
	{
		if (GetAffectUnits(y, x).size() == 0) return false;
		for (int i = 0; i < GetAffectUnits(y, x).size(); i++)
		{
			if (GetAffectUnits(y, x)[i]->GetState() == state)
			{
				return true;
			}
		}
		return false;
	}
	bool Scene::SearchAffectUnit(int y, int x)
	{
		vector<Unit*>::iterator iter = GetAffectUnits(y, x).begin();
		while (iter != GetAffectUnits(y, x).end())
		{
			if ((*iter)->GetState() == GameObject::STATE::NONE
				|| (*iter)->GetState() == GameObject::STATE::Explo
				|| (*iter)->GetState() == GameObject::STATE::Emerge_loop
				|| (*iter)->GetState() == GameObject::STATE::Emerge
				|| (*iter)->GetState() == GameObject::STATE::Death
				|| (*iter)->GetState() == GameObject::STATE::Invisible)
			{
				iter++;
				continue;
			}
			if ((*iter)->GetButtonType() == LAYER_TYPE::MONSTER
				&& (*iter)->GetState() == GameObject::STATE::Broken)
			{
				iter++;
				continue;
			}
			return true;
		}
		//for (int i = 0; i < GetAffectUnits(y, x).size(); i++)
		//{
		//	if (GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Explo
		//		|| GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Emerge_loop
		//		|| GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Emerge
		//		|| GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Death
		//		|| GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Invisible) continue;
		//	if (GetAffectUnits(y, x)[i]->GetLayerType() == LAYER_TYPE::MONSTER
		//		&& GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Broken) continue;
		return false;
	}
	bool Scene::SearchBlockUnit(int y, int x)
	{
		if (GetAffectUnits(y, x).size() == 0) return false;
		for (int i = 0; i < GetAffectUnits(y, x).size(); i++)
		{
			if (GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::NONE
				|| GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Broken
				|| GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Emerge_loop
				|| GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Death
				|| GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Emerge
				|| GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Invisible) continue;
			if (GetAffectUnits(y, x)[i]->GetButtonType() == LAYER_TYPE::MONSTER
				&& GetAffectUnits(y, x)[i]->GetState() == GameObject::STATE::Broken) continue;
			return true;
		}
		return false;
	}
	void Scene::SetPosTiles(int _y, int _x, TILE_T _type1, MOVE_TILE_T _type2)
	{
		mPosTiles[_y][_x]->SetTileType(_type1);
		mPosTiles[_y][_x]->SetTileTexture(MAKE_TILE_KEY(_type2)
			, MAKE_TILE_PATH(_type2));
	}
	void Scene::SetPosTiles(int _y, int _x, TILE_T _type1, COMBAT_ANIM_TILE_T _type2, BYTE fContant)
	{
		mPosTiles[_y][_x]->SetTileType(_type1);
		mPosTiles[_y][_x]->SetTileAnimator(_type2, fContant, true);
	}
	void Scene::SetPosTiles(int _y, int _x, TILE_T _type1, COMBAT_TILE_T _type2)
	{
		mPosTiles[_y][_x]->SetTileType(_type1);
		mPosTiles[_y][_x]->SetTileTexture(MAKE_TILE_KEY(_type2)
			, MAKE_TILE_PATH(_type2));
	}
	void Scene::SetBoundaryTiles(int y, int x, MOVE_TILE_T _type)
	{
		mBoundaryTiles[y][x]->SetETCTiles(MAKE_TILE_KEY(_type)
			, MAKE_TILE_PATH(_type));
	}
	void Scene::AddGameObject(GameObject* obj, LAYER_TYPE bType)
	{
		mLayers[(UINT)bType].AddGameObject(obj);
		if (bType == LAYER_TYPE::BACKGROUND)
			mBacks.push_back(dynamic_cast<Background*>(obj));

		if (nullptr != dynamic_cast<Unit*>(obj) && bType != LAYER_TYPE::CLONE)
		{
			Vector2 idx = ((Unit*)obj)->GetCoord();
			//if (idx == Vector2::Minus);
			//	effectUnits[0][0] = (dynamic_cast<Unit*>(obj));
			//else 
			//	effectUnits[(UINT)idx.y][(UINT)idx.x] = (dynamic_cast<Unit*>(obj));
			if (idx != Vector2::Minus)
			{
				affectUnits[(UINT)idx.y][(UINT)idx.x].push_back(dynamic_cast<Unit*>(obj));
				((Unit*)obj)->SetAffectUnitVectorIdx(affectUnits[(UINT)idx.y][(UINT)idx.x].size() - 1);
			}

			//((Unit*)obj)->SetUnitCoord(Vector2(idx.x, idx.y));
		}
	}
	void Scene::ClearAffectUnit()
	{
		for (int y = 0; y < TILE_Y; y++)
		{
			for (int x = 0; x < TILE_X; x++)
			{
				for (int i = 0; i < affectUnits[y][x].size(); i++)
				{
					affectUnits[y][x][i] = nullptr;
				}
				affectUnits[y][x].clear();
			}
		}
	}
	void Scene::ObjectGoFront(GameObject* obj, LAYER_TYPE bType)
	{
		mLayers[(UINT)bType].ObjectFront(obj);
	}
	void Scene::RemoveAffectUnit(Vector2 _coord)
	{
		ReSortAffectUnits(_coord.y, _coord.x);
		//effectUnits[(UINT)_coord.y][(UINT)_coord.x] = nullptr;
	}
	void Scene::RemoveAffectUnit(Vector2 _coord, Unit* unit)
	{
		vector<Unit*>::iterator iter = affectUnits[(UINT)_coord.y][(UINT)_coord.x].begin();
		while (iter != affectUnits[(UINT)_coord.y][(UINT)_coord.x].end())
		{
			if ((*iter) == unit)
			{
				iter = affectUnits[(UINT)_coord.y][(UINT)_coord.x].erase(iter);
			}
			else iter++;
		}
		ReSortAffectUnits(_coord.y, _coord.x);
	}
	void Scene::SetArrowTiles(int _y, int _x, MOVE_ARROW_T _type)
	{
		mArrowTiles[_y][_x]->SetTileTexture(MAKE_TILE_KEY(_type),
			MAKE_TILE_PATH(_type));
	}
	void Scene::SetAlphaState(GameObject::STATE state)
	{
		mAlphaFollower->SetState(state);
	}

	void Scene::SetAlphaFollower(Mech* _mM)
	{
		if (nullptr != mAlphaFollower)
		{
			SetAlphaState(GameObject::STATE::Death);
		}
		mAlphaFollower = _mM;
	}
	void Scene::SetMouseFollower(Mech* _mM)
	{
		if (nullptr == _mM)
		{
			if (nullptr != mMouseFollower)
				mMouseFollower->SetSelected(false);

			SetAlphaFollower(_mM);
		}
		mMouseFollower = _mM;
	}
}
