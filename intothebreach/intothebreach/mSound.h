#pragma once
#include "mResources.h"
namespace m
{
    class Sound :
        public Resource
    {
    public:
        virtual HRESULT Load(const std::wstring& path) override;
        bool LoadWavFile(const std::wstring& path);
        void Play(bool loop);
        void Stop(bool reset);
        bool GetStop() { return bStop; }
        void SetPosition(float position, bool loop);
        void SetVolume(float volume);
        void SetSpeed(DWORD speed);
        int GetDecibel(float volume);
        LPDWORD GetSoundBufferStatus();
    private:
        LPDIRECTSOUNDBUFFER		mSoundBuffer;
        DSBUFFERDESC			mBufferDesc;
        int mVolume;
        bool bStop;
    };
}


