#include "@graphics.h"

TransformAnimation::TransformAnimation(void){
	this->animation=new Animation(Transform::MAX_TRANSFORM_COMPONENTS);
}

void TransformAnimation::update(Transform *_transform){
	this->animation->update(SDL_GetTicks());
	this->animation->copyChannelValues(&_transform->position.x);
}


void TransformAnimation::startTween(
		 Transform::TransformComponent _transform_component
		, EaseType _ease_type
		, float _from
		, float _to
		, uint32_t _duration
		, int _repeat
){
	this->animation->startTween(
		 SDL_GetTicks()
		, _transform_component
		, _ease_type
		, _from
		, _to
		, _duration
		, _repeat
	);
}

TransformAnimation::~TransformAnimation(){

	delete this->animation;
}


