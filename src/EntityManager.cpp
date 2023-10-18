/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "invader.h"

//-------
// Static

void EntityManager::testCollision(
		EntityManager *_em1
		,EntityManager *_em2
		,const std::function<void (Entity *_e1, Entity *_e2)> & _on_collide){
	for(int i=0; i < _em1->entities_len; i++){
		Entity *e1=_em1->entities+i;
		if(e1->is_active){
			for(int j=0; j < _em2->entities_len; j++){
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
	entities_len=0;
	entities=NULL;
	this->life_time = 0;
	on_update=NULL;
	on_create=NULL;
	collider=NULL;
	properties=0;
	move_time=0;
}


size_t EntityManager::newType(const EntityTypeConfiguration & _entity_type_configuration){
	//{
	//		set number of entities
	//		set animations and its sprite per animation
	//		set which entities by name will intersect and establish callback function
	// 		define onDie function (invader entity manager increments velocity after each kill)
	//}

	// set animations
	size_t type_id=this->entity_types.size();

	EntityType *entity_type=new EntityType();

	entity_types.push_back(entity_type);

	entity_type->properties=_entity_manager_load_options.properties;
	entity_type->entities_len=_entity_manager_load_options.max;
	entity_type->entities=new Entity[entities_len];

	for(auto it=_entity_manager_load_options.entity_animations.begin(); it!=_entity_manager_load_options.entity_animations.end();it++){
		addAnimation(type_id,it->first,it->second);
	}

	for(int i=0; i < _entity_manager_load_options.max; i++){
		entities[i].setEntityManagerInfo(this,i);
		this->free_index.push_back(i);
	}

	this->life_time=_entity_manager_load_options.life_time;
	this->move_time=_entity_manager_load_options.move_time;
	this->collider=_entity_manager_load_options.collider;

	on_create=_entity_manager_load_options.on_create;
	on_update=_entity_manager_load_options.on_update;

	return type_id;
}


void EntityManager::addAnimation(
	size_t _entity_type_id
	,const std::string & _id_animation
	,const EntityAnimationOptions & _entity_animation_options

){
	if(_entity_type_id >= entity_types.size()){
		return;		
	}

	EntityAnimation *eso;

	if(_id_animation == ""){
		fprintf(stderr,"Entity::addFrame: '_id_animation' cannot be empty\n");
		return;
	}

	if(entity_types[_entity_type_id]->animations.count(_id_animation)!=0){
		fprintf(stderr,"Entity::addFrame: '%s' animation already added\n",_id_animation.c_str());
		return;
	}

	eso=new EntityAnimation(_entity_animation_options);

	entity_types[_entity_type_id]->animations[_id_animation]=eso;

}

Collider *EntityManager::getCollider(size_t _entity_type_id){
	if(_entity_type_id >= entity_types.size()){
		return;		
	}
		
	return entity_types[_entity_type_id]->collider;
}

std::unordered_map<std::string, EntityAnimation *> *EntityManager::getAnimations(size_t _entity_type_id){
	if(_entity_type_id >= entity_types.size()){
		return;		
	}
	
	return &entity_types[_entity_type_id]->animations;
}

int EntityManager::getNumActiveEntities(size_t _entity_type_id){

	if(_entity_type_id >= entity_types.size()){
		return;		
	}
	
	int num=0;
	int entities_len=entity_types[_entity_type_id]->entities_len;
	auto entities=entity_types[_entity_type_id]->entities;

	for(int i = 0; i < entities_len; i++){
		if(entities[i].is_active){
			num++;
		}
	}
	return num;
}

int EntityManager::size(size_t _entity_type_id){

	if(_entity_type_id >= entity_types.size()){
		return;		
	}
	
	return this->entities_len;
}

Entity *EntityManager::create(size_t _entity_type_id,int _start_x, int _start_y, int _dx, int _dy){

	if(_entity_type_id >= entity_types.size()){
		return;		
	}
	
	EntityType *entity_type=entity_types[_entity_type_id];
	int index=0;
	Entity *entity=NULL;

	if(entity_type->free_index.size()<=0){
		fprintf(stderr,"Cannot create more entities. (max is %i)\n",entity_type->entities_len);
		return NULL;
	}

	// pops the last value and set entities as is_active ...
	index=entity_type->free_index[free_index.size()-1];
	entity_type->free_index.pop_back();
	entity=&entity_type->entities[index];

	if(entity->is_active == true){
		throw std::runtime_error("EntityManager::create: Expected entity as NOT is_active");
	}

	entity->deInit();
	entity->setMoveTime(this->move_time);
	entity->x= _start_x;
	entity->y=_start_y;
	entity->dy=_dy;
	entity->dx=_dx;
	entity->is_active=true;
	entity->is_visible=true;

	if(entity_type->life_time>0){
		entity->life_time=System::getTime()+this->life_time;
	}

	if(on_create){
		(*entity_type->on_create)(entity);
	}

	return entity;
}

Entity	*EntityManager::getEntity(size_t _entity_type_id, size_t _entity_idx){

	if(_entity_type_id >= entity_types.size()){
		return;		
	}

	EntityType *entity_type=entity_types[_entity_type_id];

	if(_entity_idx >= entity_type->entities_len){
		throw std::runtime_error("Entities out of bound");
	}

	return &entity_type->entities[_idx];
}

void EntityManager::removeAll(size_t _entity_type_id){

	if(_entity_type_id >= entity_types.size()){
		return;		
	}

	EntityType *entity_type=entity_types[_entity_type_id];

	for(int i=0; i < entity_type->entities_len; i++)
	{
		if((entity_type->entities+i)->is_active==true){
			entity_type->remove(_entity_type_id,i);
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
		for(int i=0; i < t->entities_len; i++)
		{
			Entity *entity=&entity_type->entities[i];

			if(entity->is_active){

				entity->update();

				// if element has property to die when goes out of screen or life is 0, remove it
				if(

					(entity_type->life_time>0 && entity->life_time<current_time)
											||

					((properties & ENTITY_PROPERTY_DIE_OUTSCREEN)
										&&
						(
								(entity->getY()<-entity->getHeight() || entity->getY()>Graphics::getHeight())
															||
								(entity->getX()<-entity->getWidth()   || entity->getX()> Graphics::getWidth())
						)
					)
				){
					entity_type->remove(entity_type->id,i);

				}else{
					// update if there's a callback
					if(on_update){
						(*entity_type->on_update)(entity);
					}
				}
			}
		}
	}
}

void EntityManager::remove(size_idx _entity_type_idx, size_idx _entity_id){
	if(_entity_type_id >= entity_types.size()){
		return;		
	}

	EntityType *entity_type=entity_types[_entity_type_id];

	if(_entity_idx >= entity_type->entities_len){
		throw std::runtime_error("Entities out of bound");
	}


	if(entity_type->entities[_entity_id].is_active == false){
		throw std::runtime_error("EntityManager::remove: Expected entity as ACTIVE");
	}

	entity_type->entities[_entity_id].is_active=false;
	entity_type->free_index.push_back(i);
}

void EntityManager::draw(){
	for(auto entity_type:entity_types){
		for(size_t i=0; i < entity_type->entities_len; i++)
		{
			if(entity_type->entities[i].is_active){
				Graphics::drawEntity(&entity_type->entities[i]);
			}
		}
	}
}

void EntityManager::destroy(size_idx _entity_type_idx){

	if(_entity_idx >= entity_type->entities_len){
		throw std::runtime_error("Entities out of bound");
	}

	EntityType *entity_type=entity_types[_entity_type_id];

	entity_type->entities_len=0;


	if(entity_type->entities){
		delete [] entity_type->entities;
		entity_type->entities=NULL;
	}

	if(entity_type->collider){
		delete entity_type->collider;
	}

	for(auto it=entity_type->animations.begin(); it != entity_type->animations.end(); it++){
		delete it->second;
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

	entity_types[_entity_type_id]=NULL;

}

EntityManager::~EntityManager(){
	for(auto entity_type:entity_types){
		destroy(entity_type->id);
	}
}


