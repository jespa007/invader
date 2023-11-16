#include "@graphics.h"

MaterialAnimation::MaterialAnimation(void){
	this->animation=new Animation(Material::MaterialComponent::MAX_MATERIAL_COMPONENTS);
}


void MaterialAnimation::startTween(
	 Material::MaterialComponent _material_component
	, EaseType _ease_type
	, float _from
	, float _to
	, uint32_t _duration
	, int _repeat
){
	this->animation->startTween(
		 SDL_GetTicks()
		, _material_component
		, _ease_type
		, _from
		, _to
		, _duration
		, _repeat
	);
}

void MaterialAnimation::update(Material *_material){
	this->animation->update(SDL_GetTicks());
	this->animation->copyChannelValues(&_material->color.r);

}

MaterialAnimation::~MaterialAnimation(){
	delete this->animation;
}


