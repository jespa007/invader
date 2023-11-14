/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

#include "Frame.h"
class EntityFrameAnimation{
public:

	std::vector<Frame> frames;
	bool loop=true; // by default

	EntityFrameAnimation(){

	}

	EntityFrameAnimation(
		const std::vector<Frame> & _frames
		,bool _loop=false
	){
		frames=_frames;
		loop=_loop;
	}

	EntityFrameAnimation(const EntityFrameAnimation & _entity_frame_animation){
		copy(_entity_frame_animation);
	}

	EntityFrameAnimation & operator=(const EntityFrameAnimation & _entity_frame_animation){
		copy(_entity_frame_animation);
		return *this;
	}

private:
	void copy(const EntityFrameAnimation & _entity_frame_animation){
		this->frames=_entity_frame_animation.frames;
		this->loop=_entity_frame_animation.loop;
	}

};
