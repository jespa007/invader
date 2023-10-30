/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

#define MAX_PLAYING_SOUNDS 20

class SoundPlayer{

public:

	static Uint8 getBytesPerSample(SDL_AudioFormat _format);
	static const char *getAudioFormatStr(SDL_AudioFormat _format);
	

	static void init(
		SDL_AudioFormat _format=AUDIO_S16SYS
		, Uint16 _frequency=22050
		, Uint16 _samples=256
		, Uint8 _channels=2
	);

	static Uint16 getSamples();
	static Uint16 getFrequency();
	static Uint8 getChannels();
	static SDL_AudioFormat getFormat();

	static void play(Sound *snd, bool loop=false);
	static void stop(Sound *snd);
	static bool isPlaying(Sound *snd);
	static void stopAllSounds();
	static void deInit();

private:


	static void callbackAudio(void *userdata, Uint8* stream, int len);



};
