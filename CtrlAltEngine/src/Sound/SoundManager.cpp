#include "SoundManager.h"

namespace Sounds{
	float dBToVolume(float dB) {
		return powf(10.0f, 0.05f * dB);
	}

	float VolumeTodB(float volume) {
		return 20.0f * log10(volume); 
	}

	Implementation* sgpImplementation = nullptr;

	void AudioEngine::Init() {
		sgpImplementation = new Implementation;
	}

	void AudioEngine::Update() {
		sgpImplementation->Update();
	}

	void AudioEngine::Shutdown() {
		delete sgpImplementation;
	}

	void Implementation::Update() {
		std::vector<ChannelMap::iterator> pStoppedChannels;
		for (auto it = mChannels.begin(), itEnd = mChannels.end(); it != itEnd; ++it) {
			bool bIsPlaying = false;
			it->second->isPlaying(&bIsPlaying);
			if (!bIsPlaying) {
				pStoppedChannels.push_back(it);
			}
		}

		for (auto& it : pStoppedChannels) {
			mChannels.erase(it);
		}
		mpSystem->update();
	}

	void AudioEngine::LoadSound(const std::string& strSoundName, bool b3d, bool bLooping, bool bStream) {
		auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
		if (tFoundIt != sgpImplementation->mSounds.end())
			return;
		FMOD_MODE eMode = FMOD_DEFAULT;
		eMode |= b3d ? FMOD_3D : FMOD_2D;
		eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
		eMode |= bStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;
		FMOD::Sound* pSound = nullptr;
		sgpImplementation->mpSystem->createSound(strSoundName.c_str(), nullptr, &pSound);
		if (pSound) {
			sgpImplementation->mSounds[strSoundName] = pSound;
		}
	}

	void AudioEngine::UnLoadSound(const std::string& strSoundName) {
		auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
		if (tFoundIt == sgpImplementation->mSounds.end())
			return;
		tFoundIt->second->release();
		sgpImplementation->mSounds.erase(tFoundIt);
	}

	int AudioEngine::PlaySound(const std::string& strSoundName, const MathLib::vec3& vPos, float fVolumedB) {
		int nChannelId = sgpImplementation->mnNextChannelId++;
		auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
		if (tFoundIt == sgpImplementation->mSounds.end()) {
			LoadSound(strSoundName);
			tFoundIt = sgpImplementation->mSounds.find(strSoundName);
			if (tFoundIt == sgpImplementation->mSounds.end()) {
				return nChannelId;
			}
		}
		FMOD::Channel* pChannel = nullptr;
		sgpImplementation->mpSystem->playSound(FMOD_CHANNEL_FREE, tFoundIt->second, true, &pChannel);
		if (pChannel) {
			FMOD_VECTOR position = VectorToFmod(Vposition);
			pChannel->set3DAttributes(&position, nullptr);
			pChannel->setVolume(dBToVolume(fVolumedb));
			pChannel->setPaused(false);
			sgpImplementation->mChannels[nChannelId] = pChannel;
		}
		return nChannelId;
	}

	void SetChannel3dPosition(int nChannelId, const MathLib::vec3& vPos) {
		auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
		if (tFoundIt == sgpImplementation->mChannels.end())
			return;
		tFoundIt->second->set3dPosition(vPos);
	}

	void SetChannelVolume(int nChannelId, float fVolumedB) {
		auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
		if (tFoundIt == sgpImplementation->mChannels.end())
			return;
		tFoundIt->second->setVolume(dBToVolume(fVolumedB));
	}
}
