/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "invader.h"

Input *Input::input=NULL;

Input * Input::getInstance(){
	if(input == NULL){
		input = new Input();
	}
	return input;
}

void Input::destroy(){
	if(input){
		delete input;
	}
	input = NULL;
}

void Input::update(){

	memset(key,0,sizeof(key));
	Uint32 m_idxKey=-1;
	EventKey event_key;
	SDL_Event sdl_event;

	while( SDL_PollEvent( &sdl_event ) )
	{
		memset(&event_key,0,sizeof(event_key));

		if(sdl_event.key.repeat == 0){ // one key key press at time...

			switch(sdl_event.type) {
			case SDL_KEYUP:
			case SDL_KEYDOWN:
				m_idxKey = sdl_event.key.keysym.sym;

				//print_info_cr("UnPress");
				switch(sdl_event.key.keysym.sym){

					case SDLK_UP: m_idxKey = DEF_KEY_UP; break;
					case SDLK_DOWN: m_idxKey = DEF_KEY_DOWN; break;
					case SDLK_LEFT: m_idxKey = DEF_KEY_LEFT; break;
					case SDLK_RIGHT:m_idxKey = DEF_KEY_RIGHT; break;
					case SDLK_ESCAPE: m_idxKey = DEF_KEY_ESCAPE;  break;
					case SDLK_F5: m_idxKey = DEF_KEY_F5; break;
					case SDLK_F9: m_idxKey = DEF_KEY_F9;break;
					case SDLK_F10: m_idxKey = DEF_KEY_F10;break;
					case SDLK_BACKSPACE:m_idxKey=DEF_KEY_SPACE;break;

					default:
						if(DEF_KEY_SPACE <= sdl_event.key.keysym.sym && sdl_event.key.keysym.sym <= DEF_KEY_z) {
							event_key.codeKey = sdl_event.key.keysym.sym;
						}

						break;
				}

				if(m_idxKey<DEF_KEY_LAST) {

					keyR[m_idxKey]=false;

					if(sdl_event.type == SDL_KEYDOWN) {
						key[m_idxKey]=true;
						keyR[m_idxKey]=true;

					}

				}

				break;

			}
		}
	}
}
