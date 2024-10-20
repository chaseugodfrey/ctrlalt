#pragma once
#include <math.h>	//For powf, power exponential
#include <string>	//For std::string
#include <map>		//For map
#include <vector>	//For vector
#include "fmod_core/inc/fmod.hpp"
#include "../Math/MathLib.h"

namespace Sounds {
	class AudioEngine {
	public:
		static void Init();
		static void Update();
		static void Shutdown();

		void LoadSound(const std::string& strSoundName, bool b3d = true, bool blooping = false, bool bStream = false);
		void UnLoadSound(const std::string& strSoundName);
		void Set3dListenerAndOrientation(const MathLib::vec3& vPos, const MathLib::vec3& vLook, const MathLib::vec3& vUp);
		int PlaySound(const std::string& strSoundName, const MathLib::vec3& vPos = MathLib::vec3{ 0,0,0 }, float fVolumedB = 0.0f);
		void StopChannel(int nChallenId);
		void StopAllChannels();
		void SetChannel3dPosition(int nChannelId, const MathLib::vec3& vPos);
		void SetChannelVolume(int nChannelId, float fVolumedB);
		bool IsPlaying(int nChannelId) const;
	};

	struct Implementation {
		Implementation();
		~Implementation();

		void Update();

		FMOD::System* mpSystem;

		int mnNextChannelId;

		typedef std::map<std::string, FMOD::Sound*> SoundMap;
		typedef std::map<int, FMOD::Channel*> ChannelMap;

		SoundMap mSounds;
		ChannelMap mChannels;
	};
}