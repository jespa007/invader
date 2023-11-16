#pragma once



class TransformAnimation{
public:
	// STATIC
	static Action 				*	newAction(void);


	// PUBLIC
	TransformAnimation(void);

	void	startTween(
		Transform::TransformComponent _transform_component
		, EaseType _ease_type
		, float _from
		, float _to
		, uint32_t _duration
		, int _repeat
	);
	void 	update(Transform *_transform);

	~TransformAnimation();
private:
	Animation *animation;
};


