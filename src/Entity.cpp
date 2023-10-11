/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "invader.h"



bool Entity::testCollision(
	Entity * _e1
	, Entity * _e2
){

	return Collider::testIntersection(
		 _e1->x
		,_e1->y
		,_e1->getCollider()
		,_e2->x
		,_e2->y
		,_e2->getCollider()
	);
}


Entity::Entity(){
	y=0;
	x=0;
	dx=0;
	dy=0;
	life_time=0;
	idx_current_frame=0;
	next_time_change_frame=-1;
	//skip_frame=1;
	scale=1;
	id_current_animation="";
	width=0;
	height=0;
	is_active=false;
	current_animation=NULL;
	entity_manager=NULL;
	animations=NULL;
	entity_id=-1;
	fix_frame=false;
	move_time=0;
	next_move_time=0;
	is_visible=true;
	//idx_fixed_frame=-1;
}

void Entity::setEntityManagerInfo(EntityManager *_entity_manager, int _entity_id){
	entity_manager=_entity_manager;
	entity_id=_entity_id;
	animations=entity_manager->getAnimations();

	if(animations->size()>0){
		auto first_animation=animations->begin();
		id_current_animation=first_animation->first;
		current_animation=first_animation->second;
	}
}

void Entity::setAnimation(
	const std::string & _id_animation

){
	EntityAnimationOptions eso;

	if(_id_animation==id_current_animation){
		return;
	}

	if(animations->count(_id_animation)==0){
		fprintf(stderr,"Entity::setFrame: '%s' animation not found\n",_id_animation.c_str());
		return;
	}

	idx_current_frame=0;
	next_time_change_frame=System::getTime()+current_animation->sprite.frames[idx_current_frame].time;
	id_current_animation=_id_animation;
	current_animation=(*animations)[_id_animation];
	fix_frame=false;
	//idx_fixed_frame=-1;

}


void Entity::setFrame(int _idx_frame){

	if(current_animation==NULL){
		fprintf(stderr,"Entity::setFrame: no animation entries\n");
		return;
	}

	if(_idx_frame < 0 || _idx_frame >= (int)current_animation->sprite.frames.size()){
		fprintf(stderr,"Entity::setFrame: frame out of bounds (entry:%i max: %i)\n"
				,_idx_frame
				,(int)current_animation->sprite.frames.size());
		return;
	}
	idx_current_frame=_idx_frame;
	fix_frame=true;
}

Frame * Entity::getFrame(){
	if(current_animation != NULL){
	//EntityAnimationOptions eso =animations[id_current_animation];
		return &current_animation->sprite.frames[idx_current_frame];
	}
	return NULL;
}



std::string Entity::getAnimation(){
	return this->id_current_animation;
}

void Entity::deInit(){
	idx_current_frame=0;

	x=0;
	y=0;
	dx=0;
	dy=0;
	life_time=0;
	is_active=false;

}

/*
void Entity::setSkipFrame(float _skip_frame){

	if(_skip_frame == 0){
		fprintf(stderr,"Entity::setSkipFrame: _skip_frame should be > 0\n");
		_skip_frame=1;
	}

	skip_frame=1.0/_skip_frame;

}*/

Collider * Entity::getCollider(){
	auto current_frame=this->getFrame();
	if(current_frame!=NULL){
		if(current_frame->collider.collider_type!=Collider::COLLIDER_TYPE_NONE){
			return &current_frame->collider;
		}
	}
	return entity_manager->getCollider();
}

EntityManager * Entity::getEntityManager(){
	return entity_manager;
}

void			Entity::die(){
	this->entity_manager->remove(this->entity_id);
	this->deInit();
}

void Entity::update(){

	if(is_active == false){
		return;
	}

	// condition change frame animation
	if(	(current_animation!=NULL)
			&&
		(idx_current_frame<current_animation->sprite.frames.size())
			&&
		(current_animation->sprite.frames[idx_current_frame].time>0)
			&&
		fix_frame==false
	){


		int synch_time=System::getTime();

		// change frame
		if(next_time_change_frame<synch_time){

			idx_current_frame=(idx_current_frame+1);

			if(idx_current_frame>=current_animation->sprite.frames.size()){
				idx_current_frame=0;
			}

			next_time_change_frame=synch_time+current_animation->sprite.frames[idx_current_frame].time;//*skip_frame;
			Image *image=current_animation->sprite.frames[idx_current_frame].image;

			if(image!=NULL){
				width = image->getWidth();
				height = image->getHeight();
			}
		}
	}

	if(next_move_time<SDL_GetTicks()){
		x+=dx;
		y+=dy;
		next_move_time=SDL_GetTicks()+move_time;
	}
}

Entity::~Entity(){



	//frame.clear();
}