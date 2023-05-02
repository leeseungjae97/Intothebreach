#pragma once
#include "mUnit.h"

namespace m
{
	class Image;
	class Animator;
	class Building :
		public Unit
	{
	public:
		Building(STRUCTURES _type, Vector2 _coord, int mIdx, TILE_T mapType, int hp = 0);
		~Building();

		/*       void SetCoord(Vector2 _coord) { mCoord = _coord; }
			   void SetFinalPos(Vector2 _pos) { mFinalPos = _pos; }
			   void SetFinalCoord(Vector2 _coord) { mFinalCoord = _coord; }

			   Vector2 GetFinalPos() { return mFinalPos; }
			   Vector2 GetCoord() { return mCoord; }
			   Vector2 GetFinalCoord() { return mFinalCoord; }*/

		STRUCTURES GetType() { return mType; }
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void idle() override;
		virtual void broken() override;
		virtual void water() override;

		virtual void Hit(int damage) override;
		void SetBlink(bool _b) { bBlink = _b;}

		bool GetBombExplosive() { return bBombExplosive; }
		bool GetBlink() { return bBlink; }
		int GetBlinkCnt() { return iBlinkCnt; }
		float GetIdVar() { return iDVar; }

		void SetIdVar(float _i) { iDVar = _i; }
		void SetBombExplosive(bool _b) { bBombExplosive = _b; }
		void explo();
		void SetMapType(TILE_T _type) { mapType = _type; }
	private:
		//Animator* mAnimator;
		//Image* mImage;
		//Vector2 mCoord;
		//Vector2 mFinalCoord;
		//Vector2 mFinalPos;
		bool bBombExplosive;
		bool bBlink;
		int iBlinkCnt;
		TILE_T mapType;
		Vector2 mOffset;
		STRUCTURES mType;
		Image* gridIcon;
		float iDVar;
		int iDir;
		int iConstant;
	};
}

