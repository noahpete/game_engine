#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include "SDL2/SDL.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "ApplicationState.h"

class Audio
{
public:
	Audio();
	static void PlayAudio(int channel, std::string clipName, bool loop);
	static void HaltAudio(int channel);
	static void SetVolume(int channel, float volume);

private:
	static std::unordered_map<std::string, Mix_Chunk*> sAudioChunks;

};

