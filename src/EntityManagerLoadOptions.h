/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

class EntityTypeConfiguration{
public:
	int max;
	uint16_t properties;
	std::unordered_map<std::string, EntityAnimationOptions> entity_animations;
	Collider		*collider;
	int life_time;
	int move_time;
	std::function<void(Entity *)> *on_create;
	std::function<void(Entity *)> *on_update;

	EntityType(){
		max=1;
		life_time=0;
		on_create=NULL;
		on_update=NULL;
		properties=0;
		collider=NULL;
		move_time=0;

	}
};
