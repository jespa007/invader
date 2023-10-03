/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

class Sound{

public:

	static Sound *newSound(const std::string & name, const std::string & file);
	static Sound *get(const std::string & name);
	static void unloadAll();
	static void destroy();


	Uint32 wav_length;
	Uint8 *wav_buffer;

	long getDuration();


private:

	static std::map<std::string,Sound *> *s_sounds;
	static std::map<std::string, Sound *> *getMap();

	long duration;

	Sound();

	bool convertAudio(SDL_AudioSpec * wav_spec, Uint8 **wav_buffer,	Uint32 *wav_length);

	bool load(const std::string & _file);


	~Sound();

};

