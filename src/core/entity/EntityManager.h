/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

#include "EntityTypeConfiguration.h"

class EntityManager{
public:
	const static size_t npos=-1;

	EntityManager();
	size_t newType(const EntityTypeConfiguration & _entity_type_configuration);

	Collider *getCollider(size_t _entity_type_idx);
	std::vector<EntityFrameAnimation> *getFrameAnimations(size_t _entity_type_id);

	size_t getNumActiveEntities(size_t _entity_type_id);
	size_t size(size_t _entity_type_id);

	size_t create(size_t _entity_type_ix, int _start_x, int _start_y, int _dx=0, int _dy=0);
	Entity	*getEntityData(size_t _entity_type_id,size_t _entity_id);

	void removeAll(size_t _entity_type_id);


	//void testIntersection(_check_entities,std::function<std::vector<Entity *>()> *_onIntersection=NULL);

	void update();
	void remove(size_t _entity_type_id,size_t _entity_id);
	void draw();

	~EntityManager();

private:

	struct EntityType{
		size_t													id;
		Entity													*entities;
		size_t													entities_len;
		uint16_t												properties;
		std::vector<int>										free_index;
		std::vector<EntityFrameAnimation>						frame_animations;
		Collider 											*	collider;
		int														life_time;
		int														move_time;
		std::function<void (Entity *)> 						*	on_update;
		std::function<void (Entity *)> 						*	on_create;

		EntityType(){
			entities=NULL;
			entities_len=0;
			properties=0;
			collider=NULL;
			life_time=0;
			move_time=0;
			on_update=NULL;
			on_create=NULL;
			id=-1;
		}
	};

	std::vector<EntityType *>										entity_types;
	

	static void testCollision(
			EntityType *_em1
			,EntityType *_em2
			,const std::function<void (Entity *_e1, Entity *_e2)> & _on_collide
	);


	size_t addAnimation(size_t _entity_type_id,const EntityFrameAnimation & _entity_animation_options);
	void destroy(size_t _entity_type_id);

};
