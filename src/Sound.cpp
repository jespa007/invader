/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "Invader.h"

//-------
// Static
std::map<std::string, Sound *> *Sound::s_sounds=NULL;

std::map<std::string, Sound *> *Sound::getMap(){
	if(s_sounds == NULL){
		s_sounds=new std::map<std::string,Sound *>;
	}

	return s_sounds;
}


Sound *Sound::newSound(const std::string & _name, const std::string & _file){

	Sound *sound=Sound::get(_name);

	if(sound != NULL){
		fprintf(stderr,"Sound::newSound: Sound '%s' already exists\n",_name.c_str());
		return NULL;
	}


	sound=new Sound();
	if(!sound->load(_file)){
		delete sound;
		return NULL;
	}

	(*s_sounds)[_name]=sound;

	return sound;
}

Sound *Sound::get(const std::string & _name){
	auto sounds=getMap();
	if(sounds->count(_name)!=0){
		return (*sounds)[_name];
	}

	return NULL;
}

void Sound::unloadAll(){
	auto sounds=getMap();
	for(auto v=sounds->begin(); v != sounds->end(); v++){
		delete v->second;
	}

	sounds->clear();
}

void Sound::destroy(){
	unloadAll();

	if(s_sounds != NULL){
		delete s_sounds;
		s_sounds=NULL;
	}
}

//-------
// Member
Sound::Sound(){

	wav_buffer=0;
	wav_length=0;
	duration=0;

}

bool Sound::convertAudio(SDL_AudioSpec * wav_spec, Uint8 **wav_buffer,	Uint32 *wav_length) {
	// PRE: wav_buffer is loaded by SDL_LoadWav
	SoundPlayer *sound_player=SoundPlayer::getInstance();

	SDL_AudioCVT cvt;
	int ret;
	ret = SDL_BuildAudioCVT(
			&cvt
			, wav_spec->format
			, wav_spec->channels
			, wav_spec->freq
			, sound_player->getFormat()
			, sound_player->getChannels()
			, sound_player->getFrequency()
	);

	if(ret == -1){
		fprintf(stderr,"SDL_BuildAudioCVT: %s", SDL_GetError());
		return false;
	}else{
		cvt.buf = (Uint8 *)malloc(*wav_length*cvt.len_mult);
		memcpy(cvt.buf, *wav_buffer, *wav_length);
		cvt.len = *wav_length;
		if(SDL_ConvertAudio(&cvt)==-1){
			fprintf(stderr,"SDL_ConvertAudio : %s", SDL_GetError());
		}

		// deallocates previous
		SDL_FreeWAV(*wav_buffer);

		// update new wave data
		SDL_LockAudio();
		*wav_buffer = cvt.buf;
		*wav_length = cvt.len_cvt;
		SDL_UnlockAudio();
	}
	return true;
}


bool Sound::load(const std::string & _file){
	SDL_AudioSpec wav_spec;


	if(SDL_LoadWAV(_file.c_str(),
					&wav_spec,
					 &wav_buffer,
					  &wav_length) ==NULL){
		fprintf(stderr, "%s\n", SDL_GetError());
		return false;
	}

	Uint32 sample_size = SDL_AUDIO_BITSIZE(wav_spec.format) / 8;
	Uint32 sample_count = wav_length / sample_size;
	duration=(sample_count*1000)/(wav_spec.freq*wav_spec.channels);

	// convert to current audio format
	if(convertAudio(&wav_spec, &wav_buffer, &wav_length) == false){
		return false;
	}

	return true;
}


long Sound::getDuration(){
	return duration;
}

Sound::~Sound(){

	if(wav_buffer!=NULL){
		free(wav_buffer);
	}
}
