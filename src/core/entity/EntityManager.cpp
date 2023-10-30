/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "@entity.h"

//-------
// Static

void EntityManager::testCollision(
		EntityType *_em1
		,EntityType *_em2
		,const std::function<void (Entity *_e1, Entity *_e2)> & _on_collide){
	for(size_t i=0; i < _em1->entities_len; i++){
		Entity *e1=_em1->entities+i;
		if(e1->is_active){
			for(size_t j=0; j < _em2->entities_len; j++){
				Entity *e2=_em2->entities+j;

				if(e2->is_active){
					if(Entity::testCollision(e1,e2)){
						_on_collide(e1,e2);
					}
				}
			}
		}
	}
}


//----
// Members
// Entities are build with only one frame
EntityManager::EntityManager(){
}


size_t EntityManager::newType(const EntityTypeConfiguration & _entity_type_configuration){
	//{
	//		set number of entities
	//		set animations and its sprite per animation
	//		set which entities by name will intersect and establish callback function
	// 		define onDie function (invader entity manager increments velocity after each kill)
	//}

	// set animations
	size_t entity_type_id=this->entity_types.size();

	EntityManager::EntityType *entity_type=new EntityManager::EntityType();
	entity_type->id=entity_types.size();

	entity_types.push_back(entity_type);

	entity_type->properties=_entity_type_configuration.properties;
	entity_type->entities_len=_entity_type_configuration.max;
	entity_type->entities=new Entity[_entity_type_configuration.max];

	for(auto animation:_entity_type_configuration.entity_animations){
		addAnimation(entity_type_id,animation);
	}

	for(size_t entity_idx=0; entity_idx < _entity_type_configuration.max; entity_idx++){
		entity_type->entities[entity_idx].setEntityManagerInfo(this,entity_type_id,entity_idx);
		entity_type->free_index.push_back(entity_idx);
	}

	entity_type->life_time=_entity_type_configuration.life_time;
	entity_type->move_time=_entity_type_configuration.move_time;
	entity_type->collider=_entity_type_configuration.collider;

	entity_type->on_create=_entity_type_configuration.on_create;
	entity_type->on_update=_entity_type_configuration.on_update;

	return entity_type_id;
}


size_t EntityManager::addAnimation(
	size_t _entity_type_id
	,const EntityAnimationOptions & _entity_animation_options

){
	if(_entity_type_id >= entity_types.size()){
		fprintf(stderr,"EntityManager::addAnimation : _entity_type_id out of bounds\n");
		return EntityAnimation::npos;		
	}

	EntityAnimation *eso;

	size_t animation_idx=entity_types[_entity_type_id]->animations.size();
	eso=new EntityAnimation(_entity_animation_options);

	entity_types[_entity_type_id]->animations.push_back(eso);

	return animation_idx;

}

Collider *EntityManager::getCollider(size_t _entity_type_id){
	if(_entity_type_id >= entity_types.size()){
		fprintf(stderr,"EntityManager::getCollider : _entity_type_id out of bounds\n");
		return NULL;		
	}
		
	return entity_types[_entity_type_id]->collider;
}

std::vector<EntityAnimation *> *EntityManager::getAnimations(size_t _entity_type_id){
	if(_entity_type_id >= entity_types.size()){
		fprintf(stderr,"EntityManager::getAnimations : _entity_type_id out of bounds\n");
		return NULL;		
	}
	
	return &entity_types[_entity_type_id]->animations;
}

size_t EntityManager::getNumActiveEntities(size_t _entity_type_id){

	if(_entity_type_id >= entity_types.size()){
		fprintf(stderr,"EntityManager::getNumActiveEntities : _entity_type_id out of bounds\n");
		return npos;		
	}
	
	size_t num=0;
	auto entities_type=entity_types[_entity_type_id];

	for(size_t i = 0; i < entities_type->entities_len; i++){
		if(entities_type->entities[i].is_active){
			num++;
		}
	}
	return num;
}

size_t EntityManager::size(size_t _entity_type_id){

	if(_entity_type_id >= entity_types.size()){
		fprintf(stderr,"EntityManager::size : _entity_type_id out of bounds\n");
		return npos;		
	}
	
	auto entities_type=entity_types[_entity_type_id];
	return entities_type->entities_len;
}

size_t EntityManager::create(size_t _entity_type_id,int _start_x, int _start_y, int _dx, int _dy){

	if(_entity_type_id >= entity_types.size()){
		fprintf(stderr,"EntityManager::create : _entity_type_id out of bounds\n");
		return npos;		
	}
	
	EntityManager::EntityType *entity_type=entity_types[_entity_type_id];
	size_t entity_idx=0;
	Entity *entity=NULL;

	if(entity_type->free_index.size()<=0){
		fprintf(stderr,"Cannot create more entities. (max is %i)\n",(int)entity_type->entities_len);
		return npos;
	}

	// pops the last value and set entities as is_active ...
	entity_idx=entity_type->free_index[entity_type->free_index.size()-1];
	entity_type->free_index.pop_back();
	entity=&entity_type->entities[entity_idx];

	if(entity->is_active == true){
		throw std::runtime_error("EntityManager::create: Expected entity as NOT is_active");
	}

	entity->deInit();
	entity->setMoveTime(entity_type->move_time);
	entity->x= _start_x;
	entity->y=_start_y;
	entity->dy=_dy;
	entity->dx=_dx;
	entity->is_active=true;
	entity->is_visible=true;

	if(entity_type->life_time>0){
		entity->life_time=System::getTime()+entity_type->life_time;
	}

	if(entity_type->on_create){
		(*entity_type->on_create)(entity);
	}

	return entity_idx;
}

Entity	*EntityManager::getEntityData(size_t _entity_type_id, size_t _entity_idx){

	if(_entity_type_id >= entity_types.size()){
		fprintf(stderr,"EntityManager::getEntityData : _entity_type_id out of bounds\n");
		return NULL;		
	}

	EntityType *entity_type=entity_types[_entity_type_id];

	if(_entity_idx >= entity_type->entities_len){
		throw std::runtime_error("Entities out of bound");
	}

	return &entity_type->entities[_entity_idx];
}

void EntityManager::removeAll(size_t _entity_type_id){

	if(_entity_type_id >= entity_types.size()){
		fprintf(stderr,"EntityManager::removeAll : _entity_type_id out of bounds\n");
		return;		
	}

	EntityManager::EntityType *entity_type=entity_types[_entity_type_id];

	for(size_t i=0; i < entity_type->entities_len; i++)
	{
		if((entity_type->entities+i)->is_active==true){
			this->remove(_entity_type_id,i);
		}
	}
}
/*
bool EntityManager::testIntersection(EntityManager *_check_entities,std::function<void(Entity *, Entity *)> *_onIntersection=NULL){


	for(int i=0; i<this->entities_len; i++){
			Entity *src_entity=&this->entities[i];
			if(src_entity->is_active){

				// check all entities
				for(int check_entity_id=0;check_entity_id<_check_entities->){

					if(check_entity.is_active){

						// check intersection
						if(Entity::testIntersection(
								check_entity
								,src_entity
						)
						){

							if(_onIntersection!=null){
								_onIntersection(check_entity,src_entity)
							}
						}
					}
			}
		}
	}
}

*/

void EntityManager::update(){
	// update its positions
	int current_time=System::getTime();
	for(auto entity_type:entity_types){
		for(size_t entity_idx=0; entity_idx < entity_type->entities_len; entity_idx++)
		{
			Entity *entity=&entity_type->entities[entity_idx];

			if(entity->is_active){

				entity->update();

				// if element has property to die when goes out of screen or life is 0, remove it
				if(

					(entity_type->life_time>0 && entity->life_time<current_time)
											||

					((entity_type->properties & ENTITY_PROPERTY_DIE_OUTSCREEN)
										&&
						(
								(entity->getY()<-entity->getHeight() || entity->getY()>Graphics::getHeight())
															||
								(entity->getX()<-entity->getWidth()   || entity->getX()> Graphics::getWidth())
						)
					)
				){
					this->remove(entity_type->id,entity_idx);

				}else{
					// update if there's a callback
					if(entity_type->on_update){
						(*entity_type->on_update)(entity);
					}
				}
			}
		}
	}
}

void EntityManager::remove(size_t _entity_type_idx, size_t _entity_idx){
	if(_entity_type_idx >= entity_types.size()){
		fprintf(stderr,"EntityManager::remove : _entity_type_id out of bounds\n");
		return;		
	}

	EntityType *entity_type=entity_types[_entity_type_idx];

	if(_entity_idx >= entity_type->entities_len){
		throw std::runtime_error("Entities out of bound");
	}


	if(entity_type->entities[_entity_idx].is_active == false){
		throw std::runtime_error("EntityManager::remove: Expected entity as ACTIVE");
	}

	entity_type->entities[_entity_idx].is_active=false;
	entity_type->free_index.push_back(_entity_idx);
}

void EntityManager::draw(){
	for(auto entity_type:entity_types){
		for(size_t entity_idx=0; entity_idx < entity_type->entities_len; entity_idx++)
		{
			if(entity_type->entities[entity_idx].is_active){
				Graphics::drawEntity(&entity_type->entities[entity_idx]);
			}
		}
	}
}

void EntityManager::destroy(size_t _entity_type_idx){

	if(_entity_type_idx >= entity_types.size()){
		fprintf(stderr,"EntityManager::destroy : _entity_type_id out of bounds\n");
		return;
	}

	EntityType *entity_type=entity_types[_entity_type_idx];

	entity_type->entities_len=0;


	if(entity_type->entities){
		delete [] entity_type->entities;
		entity_type->entities=NULL;
	}

	if(entity_type->collider){
		delete entity_type->collider;
	}

	for(auto animation:entity_type->animations){
		delete animation;
	}

	if(entity_type->on_create){
		delete entity_type->on_create;
		entity_type->on_create=NULL;
	}

	if(entity_type->on_update){
		delete entity_type->on_update;
		entity_type->on_update=NULL;
	}

	entity_type->free_index.clear();
	entity_type->animations.clear();

	delete entity_type;

	entity_types[_entity_type_idx]=NULL;

}

EntityManager::~EntityManager(){
	for(auto entity_type:entity_types){
		destroy(entity_type->id);
	}
}


