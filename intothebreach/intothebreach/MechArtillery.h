#pragma once
#include "yaGameObject.h"
#include "yaImage.h"
namespace ya
{
	class MechArtillery : public GameObject
	{
	public:
		MechArtillery();
		~MechArtillery();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
		float mTime;
		int mIndx;
	};
}
