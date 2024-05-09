#include "Audio.h"
#include <iostream>
std::unordered_map<std::string, Mix_Chunk*> Audio::sAudioChunks;

Audio::Audio()
{
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	std::string audioPath = "assets/audio";
	if (std::filesystem::exists(audioPath))
	{
		auto audioFiles = std::filesystem::directory_iterator(audioPath);
		for (const auto& audioFile : audioFiles)
		{
			std::string chunkName = audioFile.path().stem().string();
			std::string filePath = "assets/audio/" + audioFile.path().filename().string();
			sAudioChunks[chunkName] = Mix_LoadWAV(filePath.c_str());
		}
	}
}

void Audio::PlayAudio(int channel, std::string clipName, bool loop)
{
	if (!State::sGameRunning) return;
	int loops = loop ? -1 : 0;
	Mix_PlayChannel(channel, sAudioChunks[clipName], loops);
	std::cout << "playing " + clipName << std::endl;
}

void Audio::HaltAudio(int channel)
{
	if (!State::sGameRunning) return;
	Mix_HaltChannel(channel);
}

void Audio::SetVolume(int channel, float volume)
{
	if (!State::sGameRunning) return;
	Mix_Volume(channel, static_cast<int>(volume));
}
