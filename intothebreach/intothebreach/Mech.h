#pragma once
#include "mUnit.h"
namespace m
{
	class Image;
	class Mech : public Unit
	{
	public:
		Mech(int unitValue, Vector2 _coord, int _range, int _hp, size_t idx);
		Mech(Mech& _origin);
		~Mech();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void idle() override;
		virtual void broken() override;
		virtual void water() override;
		void noMove();

		void MechMove();
		void CheckNumInput();
		void SetDeploy(bool _b) { 
			_b ? (bDeploy = _b, bSwap = false, bCancelDeploy = false) : (bDeploy = _b);

		}
		void SetSwap(bool _b) { 
			_b ? (bDeploy = false, bSwap = _b, bCancelDeploy = false) : (bSwap = _b);
		}
		void SetCancelDeploy(bool _b) { 
			_b ? (bDeploy = false, bSwap = false, bCancelDeploy = _b) : (bCancelDeploy = _b);
		}
		bool GetDeploy() { return bDeploy; }
	private:
		int moveCnt;
		bool bDeploy;
		bool bSwap;
		bool bCancelDeploy;
		Image* deployArrow;
	};
}
