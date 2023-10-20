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
	current_frame_idx=0;
	next_time_change_frame=-1;
	//skip_frame=1;
	scale=1;
	current_animation_idx=0;
	width=0;
	height=0;
	is_active=false;
	current_animation=NULL;
	entity_manager=NULL;
	entity_type_id=0;
	animations=NULL;
	entity_id=-1;
	fix_frame=false;
	move_time=0;
	next_move_time=0;
	is_visible=true;
	//idx_fixed_frame=-1;
}

void Entity::setEntityManagerInfo(EntityManager *_entity_manager, size_t _entity_type_id, size_t _entity_id){
	entity_manager=_entity_manager;
	entity_id=_entity_id;
	entity_type_id=_entity_type_id;
	animations=entity_manager->getAnimations(entity_type_id);

	if(animations->size()>0){
		auto first_animation=animations[0];
	}
}

void Entity::setAnimation(
	size_t _animation_idx

){
	EntityAnimationOptions eso;

	if(_animation_idx==current_animation_idx){
		return;
	}

	if(_animation_idx >= animations->size()){
		fprintf(stderr,"Entity::setAnimation: animation_idx out of bounds\n");
		return;
	}

	current_frame_idx=0;
	next_time_change_frame=System::getTime()+current_animation->sprite.frames[current_frame_idx].time;
	current_animation_idx=_animation_idx;
	current_animation=(*animations)[_animation_idx];
	fix_frame=false;
	//idx_fixed_frame=-1;

}


void Entity::setFrame(size_t _idx_frame){

	if(current_animation==NULL){
		fprintf(stderr,"Entity::setFrame: no animation entries\n");
		return;
	}

	if(_idx_frame >= current_animation->sprite.frames.size()){
		fprintf(stderr,"Entity::setFrame: frame out of bounds (entry:%i max: %i)\n"
				,(int)_idx_frame
				,(int)current_animation->sprite.frames.size());
		return;
	}
	current_frame_idx=_idx_frame;
	fix_frame=true;
}

Frame * Entity::getCurrentFrameData(){
	if(current_animation != NULL){
	//EntityAnimationOptions eso =animations[current_animation_idx];
		return &current_animation->sprite.frames[current_frame_idx];
	}
	return NULL;
}

size_t Entity::getCurrentFrameIdx(){
	if(current_animation != NULL){
	//EntityAnimationOptions eso =animations[current_animation_idx];
		return current_frame_idx;
	}
	return Frame::npos;
}


size_t Entity::getCurrentAnimationIdx(){
	return this->current_animation_idx;
}

void Entity::deInit(){
	current_frame_idx=0;

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
	auto current_frame=this->getCurrentFrameData();
	if(current_frame!=NULL){
		if(current_frame->collider.collider_type!=Collider::COLLIDER_TYPE_NONE){
			return &current_frame->collider;
		}
	}
	return entity_manager->getCollider(entity_type_id);
}

EntityManager * Entity::getEntityManager(){
	return entity_manager;
}

void			Entity::die(){
	this->entity_manager->remove(this->entity_type_id,this->entity_id);
	this->deInit();
}

void Entity::update(){

	if(is_active == false){
		return;
	}

	// condition change frame animation
	if(	(current_animation!=NULL)
			&&
		(current_frame_idx<current_animation->sprite.frames.size())
			&&
		(current_animation->sprite.frames[current_frame_idx].time>0)
			&&
		fix_frame==false
	){


		int synch_time=System::getTime();

		// change frame
		if(next_time_change_frame<synch_time){

			current_frame_idx=(current_frame_idx+1);

			if(current_frame_idx>=current_animation->sprite.frames.size()){
				current_frame_idx=0;
			}

			next_time_change_frame=synch_time+current_animation->sprite.frames[current_frame_idx].time;//*skip_frame;
			Image *image=current_animation->sprite.frames[current_frame_idx].image;

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
