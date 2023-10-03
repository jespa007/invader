/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "Invader.h"

Uint32 System::synch_time = 0;

void System::synchTime(){
	synch_time = SDL_GetTicks();
}

/*
Uint32 System::getSynchTime(){
	return synch_time;
}*/


Uint32 System::getTime(){
	return synch_time;
}
