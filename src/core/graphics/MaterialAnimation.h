#pragma once



class MaterialAnimation{
public:

   // PUBLIC
	MaterialAnimation(void);

	void					startTween(
		 Material::MaterialComponent _material_component
		, EaseType _ease_type
		, float _from
		, float _to
		, uint32_t _duration
		, int _repeat
	);

	void 					update( Material *_material);

	~MaterialAnimation();

private:
	Animation *animation;
};


