/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "invader.h"

SoundPlayer *SoundPlayer::singleton=NULL;
SoundPlayer::SoundData SoundPlayer::sound_data[MAX_PLAYING_SOUNDS];

void SoundPlayer::callbackAudio(void *_user_data, Uint8* stream, int len)
{
	UNUSUED_PARAM(_user_data);
	// clear stream
	memset(stream,0,len);

	for(int i = 0; i < MAX_PLAYING_SOUNDS; i++){
		if(sound_data[i].is_playing==true){ // some data to play...
			int length = (int)sound_data[i].audio_len<len?sound_data[i].audio_len:len;
			if((sound_data[i].audio_len-length)==0){
				if(sound_data[i].loop==true){
					sound_data[i].audio_len=sound_data[i].sound->wav_length;
					sound_data[i].audio_pos=sound_data[i].sound->wav_buffer;
					length = (int)sound_data[i].audio_len<len?sound_data[i].audio_len:len;
				}else{
					sound_data[i].is_playing=false;
				}
			}

			SDL_MixAudio(stream, sound_data[i].audio_pos, length, SDL_MIX_MAXVOLUME);
			sound_data[i].audio_len-=length;
			sound_data[i].audio_pos+=length;
		}
	}
}

SoundPlayer *SoundPlayer::getInstance(){
	if(singleton==NULL){
		memset(sound_data,0,sizeof(SoundData));
		singleton=new SoundPlayer();
	}
	return singleton;
}

void SoundPlayer::destroy(){
	if(singleton != NULL){
		delete singleton;
	}
	singleton = NULL;
}

SoundPlayer::SoundPlayer(){
	dev=0;
}

const char *SoundPlayer::getAudioFormatStr(SDL_AudioFormat _format){
	switch(_format){
	case AUDIO_U16SYS: return "AUDIO_U16SYS";
	case AUDIO_S16SYS: return "AUDIO_S16SYS";
	case AUDIO_S32SYS: return "AUDIO_S32SYS";
	case AUDIO_F32SYS: return "AUDIO_F32SYS";
	}

	return "unknown";
}

Uint8 SoundPlayer::getBytesPerSample(SDL_AudioFormat _format){
	switch(_format){
	case AUDIO_U16SYS: return 2;
	case AUDIO_S16SYS: return 2;
	case AUDIO_S32SYS: return 4;
	case AUDIO_F32SYS: return 4;
	}

	return 1;
}

void SoundPlayer::setup(SDL_AudioFormat _format, Uint16 _freq, Uint16 _samples, Uint8 _channels){

	if (SDL_WasInit(SDL_INIT_AUDIO) != SDL_INIT_AUDIO) {
		if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
			fprintf(stderr,"Unable to init sound subsystem: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
	}

	SDL_AudioSpec audio_obtained;

	SDL_memset(&audio_spec, 0, sizeof(audio_spec)); /* or SDL_zero(want) */
	audio_spec.userdata=NULL;
	audio_spec.freq=_freq;
	audio_spec.samples=_samples;
	audio_spec.channels=_channels;
	audio_spec.format=_format;
	audio_spec.callback = callbackAudio; /* you wrote this function elsewhere. */

// MAC fails to init SDL_OpenAudio (disable by default)
//#if !defined(__APPLE_CC__)

	if ( SDL_OpenAudio(&audio_spec, &audio_obtained) < 0 ){
	    fprintf(stderr,"SoundPlayer: '%s'", SDL_GetError());
	} else {
	    SDL_PauseAudio(0); // start audio playing.

	    audio_spec=audio_obtained;
	    audio_spec.callback=callbackAudio;

	    printf("Sound\n");
	    printf("-----\n");
	    printf("- Audio: %s\n"
	    	   "- Frequency :  %i(Hz)\n"
	    	   "- Channels : %i\n"
	    	   "- Samples : %i\n"
	    		,getAudioFormatStr(audio_spec.format)
	    		,audio_spec.freq
				,audio_spec.channels
				,audio_spec.samples

		);
	    printf("\n");
	}
//#endif

}

Uint16 SoundPlayer::getSamples(){
	return audio_spec.samples;
}

Uint16 SoundPlayer::getFrequency(){
	return audio_spec.freq;
}

Uint8 SoundPlayer::getChannels(){
	return audio_spec.channels;
}

SDL_AudioFormat SoundPlayer::getFormat(){
	return audio_spec.format;
}

void SoundPlayer::play(Sound *_sound, bool _loop){

	if(_sound == NULL){
		return;
	}

	for(int i = 0; i < MAX_PLAYING_SOUNDS; i++){
		if(sound_data[i].is_playing==false){ // is not playing.
			sound_data[i].audio_pos=_sound->wav_buffer;
			sound_data[i].audio_len=_sound->wav_length;
			sound_data[i].sound=_sound;
			sound_data[i].loop=_loop;
			sound_data[i].is_playing=true;
			return;
		}
	}
}

void SoundPlayer::stop(Sound *_sound){

	if(_sound == NULL){
		return;
	}

	for(int i = 0; i < MAX_PLAYING_SOUNDS; i++){
		if(sound_data[i].sound==_sound){
			sound_data[i].is_playing=false;
		}
	}
}

void SoundPlayer::stopAllSounds(){
	for(int i = 0; i < MAX_PLAYING_SOUNDS; i++){
		sound_data[i].is_playing=false;
	}
}

bool SoundPlayer::isPlaying(Sound *_sound){

	int count=0;

	if(_sound == NULL){
		return false;
	}

	for(int i = 0; i < MAX_PLAYING_SOUNDS; i++){
		if((sound_data[i].sound==_sound) && (sound_data[i].is_playing==true)){ // is not playing.
			count++;
		}
	}

	return count;
}

SoundPlayer::~SoundPlayer(){
	// stop audio...
	stopAllSounds();
	SDL_PauseAudio(1);
    SDL_CloseAudio();
}
