/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

#define MAX_PLAYING_SOUNDS 20

class SoundPlayer{

public:

	static SoundPlayer * getInstance();
	static Uint8 getBytesPerSample(SDL_AudioFormat _format);
	static const char *getAudioFormatStr(SDL_AudioFormat _format);
	static void destroy();


	void setup(
		SDL_AudioFormat _format=AUDIO_S16SYS
		, Uint16 _frequency=22050
		, Uint16 _samples=256
		, Uint8 _channels=2
	);

	Uint16 getSamples();
	Uint16 getFrequency();
	Uint8 getChannels();
	SDL_AudioFormat getFormat();

	void play(Sound *snd, bool loop=false);
	void stop(Sound *snd);
	bool isPlaying(Sound *snd);
	void stopAllSounds();

private:
	SDL_AudioSpec audio_spec;

	typedef struct {
		Uint8 *audio_pos;
		int 	audio_len;
		Sound  *sound;
		bool	loop;
		bool	is_playing;
	}SoundData;

	static SoundData sound_data[MAX_PLAYING_SOUNDS];

	static SoundPlayer * singleton;
	SDL_AudioDeviceID dev;
	SoundPlayer();
	~SoundPlayer();

	static void callbackAudio(void *userdata, Uint8* stream, int len);



};
