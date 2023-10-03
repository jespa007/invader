/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "Invader.h"

EntityAnimation::EntityAnimation(){

}

EntityAnimation::EntityAnimation(const EntityAnimationOptions & _entity_state_options){
	sprite.frames=_entity_state_options.sprite_frames;

}


