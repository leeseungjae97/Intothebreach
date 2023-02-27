#pragma once
#include "yaGameObject.h"
#include "yaImage.h"
namespace ya
{
	class Mech : public GameObject
	{
	public:
		Mech(MECHS _mech);
		~Mech();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
		float mTime;
		int mIndx;
		MECHS mMech;
	};
}
