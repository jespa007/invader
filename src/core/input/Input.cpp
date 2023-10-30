/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "@input.h"

bool            g_key[DEF_KEY_LAST]={false};
bool            g_keyR[DEF_KEY_LAST]={false};


bool Input::getKey(DefKey _key_id){
	return g_key[_key_id];
}

bool Input::getKeyR(DefKey _key_id){
	return g_keyR[_key_id];
}


void Input::update(){

	memset(g_key,0,sizeof(g_key));
	Uint32 id_key=-1;
	EventKey event_key;
	SDL_Event sdl_event;

	while( SDL_PollEvent( &sdl_event ) )
	{
		memset(&event_key,0,sizeof(event_key));

		if(sdl_event.key.repeat == 0){ // one g_key g_key press at time...

			switch(sdl_event.type) {
			case SDL_KEYUP:
			case SDL_KEYDOWN:
				id_key = sdl_event.key.keysym.sym;

				//print_info_cr("UnPress");
				switch(sdl_event.key.keysym.sym){

					case SDLK_UP: id_key = DEF_KEY_UP; break;
					case SDLK_DOWN: id_key = DEF_KEY_DOWN; break;
					case SDLK_LEFT: id_key = DEF_KEY_LEFT; break;
					case SDLK_RIGHT:id_key = DEF_KEY_RIGHT; break;
					case SDLK_ESCAPE: id_key = DEF_KEY_ESCAPE;  break;
					case SDLK_F5: id_key = DEF_KEY_F5; break;
					case SDLK_F9: id_key = DEF_KEY_F9;break;
					case SDLK_F10: id_key = DEF_KEY_F10;break;
					case SDLK_BACKSPACE:id_key=DEF_KEY_SPACE;break;

					default:
						if(DEF_KEY_SPACE <= sdl_event.key.keysym.sym && sdl_event.key.keysym.sym <= DEF_KEY_z) {
							event_key.codeKey = sdl_event.key.keysym.sym;
						}

						break;
				}

				if(id_key<DEF_KEY_LAST) {

					g_keyR[id_key]=false;

					if(sdl_event.type == SDL_KEYDOWN) {
						g_key[id_key]=true;
						g_keyR[id_key]=true;

					}

				}

				break;

			}
		}
	}
}


