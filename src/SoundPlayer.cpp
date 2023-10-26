/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "Invader.h"


SDL_AudioSpec g_audio_spec;

typedef struct {
	Uint8 *audio_pos;
	int 	audio_len;
	Sound  *sound;
	bool	loop;
	bool	is_playing;
}SoundData;

SoundData g_sound_data[MAX_PLAYING_SOUNDS];
SDL_AudioDeviceID g_sound_device=0;

void SoundPlayer::callbackAudio(void *_user_data, Uint8* stream, int len)
{
	UNUSUED_PARAM(_user_data);
	// clear stream
	memset(stream,0,len);

	for(int i = 0; i < MAX_PLAYING_SOUNDS; i++){
		if(g_sound_data[i].is_playing==true){ // some data to play...
			int length = (int)g_sound_data[i].audio_len<len?g_sound_data[i].audio_len:len;
			if((g_sound_data[i].audio_len-length)==0){
				if(g_sound_data[i].loop==true){
					g_sound_data[i].audio_len=g_sound_data[i].sound->wav_length;
					g_sound_data[i].audio_pos=g_sound_data[i].sound->wav_buffer;
					length = (int)g_sound_data[i].audio_len<len?g_sound_data[i].audio_len:len;
				}else{
					g_sound_data[i].is_playing=false;
				}
			}

			SDL_MixAudio(stream, g_sound_data[i].audio_pos, length, SDL_MIX_MAXVOLUME);
			g_sound_data[i].audio_len-=length;
			g_sound_data[i].audio_pos+=length;
		}
	}
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

void SoundPlayer::init(SDL_AudioFormat _format, Uint16 _freq, Uint16 _samples, Uint8 _channels){

	if (SDL_WasInit(SDL_INIT_AUDIO) != SDL_INIT_AUDIO) {
		if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
			fprintf(stderr,"Unable to init sound subsystem: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
	}

	SDL_AudioSpec audio_obtained;

	SDL_memset(&g_audio_spec, 0, sizeof(g_audio_spec)); /* or SDL_zero(want) */
	g_audio_spec.userdata=NULL;
	g_audio_spec.freq=_freq;
	g_audio_spec.samples=_samples;
	g_audio_spec.channels=_channels;
	g_audio_spec.format=_format;
	g_audio_spec.callback = callbackAudio; /* you wrote this function elsewhere. */

// MAC fails to init SDL_OpenAudio (disable by default)
//#if !defined(__APPLE_CC__)

	if ( SDL_OpenAudio(&g_audio_spec, &audio_obtained) < 0 ){
	    fprintf(stderr,"SoundPlayer: '%s'", SDL_GetError());
	} else {
	    SDL_PauseAudio(0); // start audio playing.

	    g_audio_spec=audio_obtained;
	    g_audio_spec.callback=callbackAudio;

	    printf("Sound\n");
	    printf("-----\n");
	    printf("- Audio: %s\n"
	    	   "- Frequency :  %i(Hz)\n"
	    	   "- Channels : %i\n"
	    	   "- Samples : %i\n"
	    		,getAudioFormatStr(g_audio_spec.format)
	    		,g_audio_spec.freq
				,g_audio_spec.channels
				,g_audio_spec.samples

		);
	    printf("\n");
	}
//#endif

}

Uint16 SoundPlayer::getSamples(){
	return g_audio_spec.samples;
}

Uint16 SoundPlayer::getFrequency(){
	return g_audio_spec.freq;
}

Uint8 SoundPlayer::getChannels(){
	return g_audio_spec.channels;
}

SDL_AudioFormat SoundPlayer::getFormat(){
	return g_audio_spec.format;
}

void SoundPlayer::play(Sound *_sound, bool _loop){

	if(_sound == NULL){
		return;
	}

	for(int i = 0; i < MAX_PLAYING_SOUNDS; i++){
		if(g_sound_data[i].is_playing==false){ // is not playing.
			g_sound_data[i].audio_pos=_sound->wav_buffer;
			g_sound_data[i].audio_len=_sound->wav_length;
			g_sound_data[i].sound=_sound;
			g_sound_data[i].loop=_loop;
			g_sound_data[i].is_playing=true;
			return;
		}
	}
}

void SoundPlayer::stop(Sound *_sound){

	if(_sound == NULL){
		return;
	}

	for(int i = 0; i < MAX_PLAYING_SOUNDS; i++){
		if(g_sound_data[i].sound==_sound){
			g_sound_data[i].is_playing=false;
		}
	}
}

void SoundPlayer::stopAllSounds(){
	for(int i = 0; i < MAX_PLAYING_SOUNDS; i++){
		g_sound_data[i].is_playing=false;
	}
}

bool SoundPlayer::isPlaying(Sound *_sound){

	int count=0;

	if(_sound == NULL){
		return false;
	}

	for(int i = 0; i < MAX_PLAYING_SOUNDS; i++){
		if((g_sound_data[i].sound==_sound) && (g_sound_data[i].is_playing==true)){ // is not playing.
			count++;
		}
	}

	return count;
}

void SoundPlayer::deInit(){
	// stop audio...
	stopAllSounds();
	SDL_PauseAudio(1);
    SDL_CloseAudio();
}
