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
		void SetSelected(bool _b) { bSelected = _b; }
		void EndDeploy()
		{
			bDeploy = false;
			bCancelDeploy = false;
			bSwap = false;
			bDeployed = false;
		}
		void SetDeploy(bool _b)
		{
			_b ? (bDeploy = _b, bSwap = false, bCancelDeploy = false) : (bDeploy = _b);
		}
		void SetSwap(bool _b)
		{
			_b ? (bDeploy = false, bSwap = _b, bCancelDeploy = false) : (bSwap = _b);
		}
		void SetCancelDeploy(bool _b)
		{
			_b ? (bDeploy = false, bSwap = false, bCancelDeploy = _b) : (bCancelDeploy = _b);
		}
		void SetMakeDeployAlpha(bool _b) { bMakeDeployAlpha = _b; }
		void SetDeployConstant(float _c) { fDeployConstant = _c; }
		void SetDeployed(bool _b) { bDeployed = _b; }

		bool GetSelected() { return bSelected; }
		bool GetDeployed() { return bDeployed; }
		bool GetMakeDeployAlpha() { return bMakeDeployAlpha; }
		bool GetDeploy() { return bDeploy; }
		bool GetCancelDeploy() { return bCancelDeploy; }
		bool GetSwap() { return bSwap; }
	private:
		int moveCnt;
		bool bSelected;
		bool bDeploy;
		bool bSwap;
		bool bCancelDeploy;
		bool bMakeDeployAlpha;
		bool bDeployed;
		float fDeployConstant;
		Image* deployArrow;
	};
}
