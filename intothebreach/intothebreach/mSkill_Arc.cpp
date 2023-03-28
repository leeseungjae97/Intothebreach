#include "mSkill_Arc.h"
#include "mTime.h"
#include "mResources.h"
#include "mUnit.h"
#include "mImage.h"
#include "func.h"
namespace m
{
	Skill_Arc::Skill_Arc(SKILL_T _type)
		: Skill(_type)
	{
	}
	Skill_Arc::~Skill_Arc()
	{
	}
	void Skill_Arc::Initialize()
	{
		object::Visible(this);
		fTime = 0.f;
		fMaxTime = 0.4f;
		fDistance = (mFinalEdPos - mStPos).Length();
		offsetHeight = mFinalEdPos.y - mStPos.y;
		fHeight = 100.f - mStPos.y;

		// ���Ͽ� �ɸ��� �ð�
		// ������ �߷°��ӵ� = 2 * �Ÿ� / �ð�^2
		gravityAccel = 2 * fHeight / (fMaxTime * fMaxTime);

		// ���� ���� �ð� == �ӵ�
		velocityY = sqrtf(2.f * fHeight * gravityAccel);

		float a = gravityAccel;

		// �ӵ� == �ְ� ���̿��� �������� ��.
		// ����¥�� �� 2�� ����.
		float b = -2 * velocityY;
		float c = offsetHeight;

		// ����
		// ���� ���Ŀ� ���� �ΰ��� (-, +)x�� ����.
		maxTheta = (-b + sqrtf(b * b - 4 * a * c)) / (2 * a);
		minTheta = (-b - sqrtf(b * b - 4 * a * c)) / (2 * a);

		// x�� �ӵ�
		// �ӵ� = �Ÿ� / ����.
		velocityX = -(mStPos.x - mFinalEdPos.x) / maxTheta;
	}
	void Skill_Arc::Update()
	{
		GameObject::Update();
		Vector2 mPos = GetPos();
		if (stFire)
		{
			fTime += Time::fDeltaTime();
			Vector2 prevMPos = mPos;
			mPos.x = (mStPos.x - velocityX * fTime) /** Time::fDeltaTime()*/;
			mPos.y = (mStPos.y - velocityY * fTime - (0.5f * gravityAccel * fTime * fTime)) /** Time::fDeltaTime()*/;
			Vector2 diff = prevMPos - mPos;
			arcTheta = atan2(diff.y, diff.x);
		}
		CalEndFire();
		SetPos(mPos);

		if (endFire)
		{
			object::Invisible(this);
		}
	}
	void Skill_Arc::Render(HDC hdc)
	{
		if (!startRender) return;
		if (endFire) stFire = false;
		if (stFire)
		{
			Active(hdc);
		}
		else
		{
			GuideWire(hdc);
		}
	}
	void Skill_Arc::Release()
	{
	}
	void Skill_Arc::ReInit(Vector2 stPos, Vector2 enPos)
	{
		Skill::ReInit(stPos, enPos);
		this->Initialize();
	}
	void Skill_Arc::Active(HDC hdc)
	{
		Vector2 mPos = GetPos();
		Image* im = Resources::Load<Image>(L"missile", L"..\\Resources\\texture\\effect\\shotup_tribomb_missile_L.bmp");

		bitmap::RotateBitmap(hdc, mPos, im->GetBitmap(),
			arcTheta, im->GetHdc());
	}
	void Skill_Arc::GuideWire(HDC hdc)
	{
		Vector2 mPos = mStPos;
		Image* im = Resources::Load<Image>(L"line", L"..\\Resources\\texture\\combat\\artillery_dot.bmp");

		Vector2 vec = mStPos;
		float absD = abs(mFinalEdPos.x - mStPos.x);
		float absMD = abs(vec.x - mStPos.x);
		float diff = absD - absMD;

		float t = 0;
		while (diff > 0.f)
		{
			t += 0.05f;
			mPos.x = (mStPos.x - velocityX * t);
			mPos.y = (mStPos.y - velocityY * t - (0.5f * gravityAccel * t * t));

			TransparentBlt(hdc,
				(int)(mPos.x),
				(int)(mPos.y),
				(int)(im->GetWidth() * 2),
				(int)(im->GetHeight() * 2),
				im->GetHdc(),
				0, 0,
				im->GetWidth(),
				im->GetHeight(),
				RGB(255, 0, 255));

			vec = Vector2(mPos.x, mPos.y);
			absD = abs(mFinalEdPos.x - mStPos.x);
			absMD = abs(vec.x - mStPos.x);
			diff = absD - absMD;
		}
	}
	void Skill_Arc::CheckDirection()
	{
		Vector2 pos = GetPos();
		Scene* scene = SceneManager::GetActiveScene();
		// right, up, down, left
		int direct[4][2] = { {0, 1},{-1, 0} ,{1, 0},{0, -1} };
		if (endFire && scene->GetEffectUnit((int)GetEndCoord().y, (int)GetEndCoord().x).size() != 0)
		{
			for (int i = 0; i < scene->GetEffectUnit((int)GetEndCoord().y, (int)GetEndCoord().x).size(); i++)
			{
				scene->GetEffectUnit((int)GetEndCoord().y, (int)GetEndCoord().x)[i]->Hit(1);
				
			}
			SetEndFire(false);
			SetStartFire(false);
			PushUnit(scene);
		}
		else if (endFire)
		{
			SetEndFire(false);
			SetStartFire(false);
			PushUnit(scene);
			/*for (int i = 0; i < 4; i++)
			{
				int dy = GetEndCoord().y + direct[i][0];
				int dx = GetEndCoord().x + direct[i][1];

				if (dx < 0 || dy < 0 || dx >= TILE_X - 1 || dy >= TILE_Y - 1) continue;
				if (scene->GetEffectUnit(dy, dx).size() == 0)continue;
				for (int i = 0; i < scene->GetEffectUnit(dy, dx).size(); i++)
				{
					Unit* unit = scene->GetEffectUnit(dy, dx)[i];
					int _dy = dy + direct[i][0];
					int _dx = dx + direct[i][1];
					if (_dx < 0 || _dy < 0 || _dx >= TILE_X - 1 || _dy >= TILE_Y - 1) continue;
					scene->MoveEffectUnit(unit, Vector2((float)_dy, (float)_dx));
				}
			}*/
		}
	}
}