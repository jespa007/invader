/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

class EntityAnimationOptions{
public:
	std::vector<Frame> sprite_frames;

	EntityAnimationOptions(){

	}

	EntityAnimationOptions(
		const std::vector<Frame> & _sprite_frames
	){
		sprite_frames=_sprite_frames;
	}

	EntityAnimationOptions(const EntityAnimationOptions & _entity_animation_options){
		copy(_entity_animation_options);
	}

	EntityAnimationOptions & operator=(const EntityAnimationOptions & _entity_animation_options){
		copy(_entity_animation_options);
		return *this;
	}

private:
	void copy(const EntityAnimationOptions & _entity_animation_options){
		this->sprite_frames=_entity_animation_options.sprite_frames;
	}

};
