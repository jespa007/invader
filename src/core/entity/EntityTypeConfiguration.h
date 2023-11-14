/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

class EntityTypeConfiguration{
public:

	//static const size_t npos=-1;

	typedef enum{
		ENTITY_TYPE_PROPERTY_DIE_FRAME_ANIMATION_ENDS=0x1 << 0
		//ENTITY_PROPERTY_DIE_TRANSFORM_ANIMATION_ENDS=0x1 << 1
	}EntityTypeProperty;

	size_t max;
	uint16_t properties;
	std::vector<EntityFrameAnimation> animations;
	Collider		*collider;
	size_t life_time;
	size_t move_time;
	std::function<void(Entity *)> *on_create;
	std::function<void(Entity *)> *on_update;

	EntityTypeConfiguration(){
		max=1;
		life_time=0;
		on_create=NULL;
		on_update=NULL;
		properties=0;
		collider=NULL;
		move_time=0;
	}

};
