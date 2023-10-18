/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

#include "EntityTypeConfiguration.h"

class EntityManager{
public:
	typedef enum{
		ENTITY_PROPERTY_DIE_OUTSCREEN=0x1 << 0
	}EntityProperty;

	EntityManager();
	size_t newType(const EntityTypeConfiguration & _entity_type_configuration);

	Collider *getCollider(size_t _entity_type_idx);
	std::unordered_map<std::string, EntityAnimation *> *getAnimations(size_t _entity_type_id);

	int getNumActiveEntities(size_t _entity_type_id);
	int size(size_t _entity_type_id);

	size_t create(size_t _entity_type_ix, int _start_x, int _start_y, int _dx=0, int _dy=0);
	Entity	*getEntity(size_t _entity_type_id,size_t _entity_id);

	void removeAll(size_t _entity_type_id);


	//void testIntersection(_check_entities,std::function<std::vector<Entity *>()> *_onIntersection=NULL);

	void update();
	void remove(size_t _entity_type_id,size_t _entity_id);
	void draw();

	~EntityManager();

private:

	struct{
		Entity													*entities;
		Entity													entities_len;
		uint16_t												properties;
		std::vector<int>										free_index;
		std::unordered_map<std::string, EntityAnimation *>		animations;
		Collider 											*	collider;
		int														life_time;
		int														move_time;
		std::function<void (Entity *)> 						*	on_update;
		std::function<void (Entity *)> 						*	on_create;
	}EntityType;

	std::vector<EntityType *>										entity_types;
	

	static void testCollision(
			EntityType *_em1
			,EntityType *_em2
			,const std::function<void (Entity *_e1, Entity *_e2)> & _on_collide
	);


	void addAnimation(size_t _entity_type_id,const std::string & _id_animation, const EntityAnimationOptions & _entity_animation_options);
	void destroy(size_t _entity_type_id);

};
