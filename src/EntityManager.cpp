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


void EntityManager::setup(const std::string _name, const EntityType & _entity_type){
	//{
	//		set number of entities
	//		set animations and its sprite per animation
	//		set which entities by name will intersect and establish callback function
	// 		define onDie function (invader entity manager increments velocity after each kill)
	//}

	// set animations

	destroy();

	properties=_entity_manager_load_options.properties;
	entities_len=_entity_manager_load_options.max;
	entities=new Entity[entities_len];

	for(auto it=_entity_manager_load_options.entity_animations.begin(); it!=_entity_manager_load_options.entity_animations.end();it++){
		addAnimation(it->first,it->second);
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
}


void EntityManager::addAnimation(
	const std::string & _id_animation
	,const EntityAnimationOptions & _entity_animation_options

){
	EntityAnimation *eso;

	if(_id_animation == ""){
		fprintf(stderr,"Entity::addFrame: '_id_animation' cannot be empty\n");
		return;
	}

	if(animations.count(_id_animation)!=0){
		fprintf(stderr,"Entity::addFrame: '%s' animation already added\n",_id_animation.c_str());
		return;
	}

	eso=new EntityAnimation(_entity_animation_options);

	animations[_id_animation]=eso;

}

Collider *EntityManager::getCollider(){
	return collider;
}

std::unordered_map<std::string, EntityAnimation *> *EntityManager::getAnimations(){
	return &animations;
}

int EntityManager::getNumActiveEntities(){
	int num=0;

	for(int i = 0; i < this->entities_len; i++){
		if(this->entities[i].is_active){
			num++;
		}
	}
	return num;
}

int EntityManager::size(){
	return this->entities_len;
}

Entity *EntityManager::create(int _start_x, int _start_y, int _dx, int _dy){

	int index=0;
	Entity *entity=NULL;

	if(this->free_index.size()<=0){
		fprintf(stderr,"Cannot create more entities. (max is %i)\n",this->entities_len);
		return NULL;
	}

	// pops the last value and set entities as is_active ...
	index=free_index[free_index.size()-1];
	this->free_index.pop_back();
	entity=&this->entities[index];

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

	if(this->life_time>0){
		entity->life_time=System::getTime()+this->life_time;
	}

	if(on_create){
		(*this->on_create)(entity);
	}

	return entity;
}

Entity	*EntityManager::getEntity(int _idx){
	if(_idx < 0 || _idx >= this->entities_len){
		throw std::runtime_error("Entities out of bound");
	}

	return &this->entities[_idx];
}

void EntityManager::removeAll(){
	for(int i=0; i < this->entities_len; i++)
	{
		if((this->entities+i)->is_active==true){
			this->remove(i);
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
	for(int i=0; i < this->entities_len; i++)
	{
		Entity *entity=&this->entities[i];

		if(entity->is_active){

			entity->update();

			// if element has property to die when goes out of screen or life is 0, remove it
			if(

				(this->life_time>0 && entity->life_time<current_time)
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
				this->remove(i);

			}else{
				// update if there's a callback
				if(on_update){
					(*this->on_update)(entity);
				}
			}
		}
	}
}

void EntityManager::remove(int i){
	if(this->entities[i].is_active == false){
		throw std::runtime_error("EntityManager::remove: Expected entity as ACTIVE");
	}

	//if(this->entities[i].is_active==true){
	this->entities[i].is_active=false;
	this->free_index.push_back(i);
	//}
}

void EntityManager::draw(){
	for(int i=0; i < this->entities_len; i++)
	{
		if(this->entities[i].is_active){
			Graphics::drawEntity(&this->entities[i]);
		}
	}
}

void EntityManager::destroy(){
	entities_len=0;

	if(entities){
		delete [] entities;
		entities=NULL;
	}

	if(collider){
		delete collider;
	}

	for(auto it=animations.begin(); it != animations.end(); it++){
		delete it->second;
	}

	if(on_create){
		delete on_create;
		on_create=NULL;
	}

	if(on_update){
		delete on_update;
		on_update=NULL;
	}

	this->free_index.clear();
	this->animations.clear();

}

EntityManager::~EntityManager(){
	destroy();
}


