#include "Audio.h"

std::unordered_map<std::string, Mix_Chunk*> Audio::sAudioChunks;

Audio::Audio()
{
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
	int loops = loop ? -1 : 0;
	Mix_PlayChannel(channel, sAudioChunks[clipName], loops);
}

void Audio::HaltAudio(int channel)
{
	Mix_HaltChannel(channel);
}

void Audio::SetVolume(int channel, float volume)
{
	Mix_Volume(channel, static_cast<int>(volume));
}
