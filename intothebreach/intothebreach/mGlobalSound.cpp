#include "mGlobalSound.h"
#include "mSound.h"
#include "mResources.h"
namespace m
{
	Sound* GlobalSound::titleTheme;
	void GlobalSound::InitSound()
	{
		titleTheme = Resources::Load<Sound>(L"TitleTheme", L"..\\Resources\\sound\\music\\mus_title_A.wav");
	}
	void GlobalSound::AllStop()
	{
		titleTheme->Stop(true);
	}

}