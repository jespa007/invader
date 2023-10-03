/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

#include "EntityManagerLoadOptions.h"

class EntityManager{
public:
	typedef enum{
		ENTITY_PROPERTY_DIE_OUTSCREEN=0x1 << 0
	}EntityProperty;

	/*static EntityManager *newEntityManager(
			const std::string & _name
			, int _max_instances
			, const EntityManagerLoadOptions & _entity_manager_load_options
	);
	static EntityManager *get(const std::string & name);
	static void unloadAll();
	static void destroy();*/
	static void testCollision(
			EntityManager *_em1
			,EntityManager *_em2
			,const std::function<void (Entity *_e1, Entity *_e2)> & _on_collide
	);

	std::function<void (Entity *)> *on_update;
	std::function<void (Entity *)> *on_create;

	EntityManager();
	void setup(const EntityManagerLoadOptions & _entity_manager_load_options);

	Collider *getCollider();
	std::unordered_map<std::string, EntityAnimation *> *getAnimations();

	int getNumActiveEntities();
	int size();

	Entity *create(int _start_x, int _start_y, int _dx=0, int _dy=0);
	Entity	*getEntity(int _idx);

	void removeAll();


	//void testIntersection(_check_entities,std::function<std::vector<Entity *>()> *_onIntersection=NULL);

	void update();
	void remove(int idx_entity);
	void draw();

	~EntityManager();

private:

	static std::map<std::string,EntityManager *> 		*	s_entity_managers;
	static std::map<std::string, EntityManager *> 		*	getMap();

	Entity												*	entities;
	int														entities_len;
	uint16_t												properties;

	std::vector<int>										free_index;
	std::unordered_map<std::string, EntityAnimation *> 			animations;

	Collider 											*	collider;

	int														life_time;
	int														move_time;

	void addAnimation(const std::string & _id_animation, const EntityAnimationOptions & _entity_animation_options);
	void destroy();

};
