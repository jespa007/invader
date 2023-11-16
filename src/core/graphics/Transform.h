#pragma once

class Transform{

public:

	typedef enum{
		POSITION_X	=0,
		POSITION_Y	,
		ROTATE  	,
		DIMENSION_X ,
		DIMENSION_Y  ,
		MAX_TRANSFORM_COMPONENTS
	}TransformComponent;

	//----------------------------
	// DON'T MOVE! THESE ORDER IS NEEDED FOR PASS ANIMATION COMPONENTS
	Point2f position;
	float rotate;
	Point2f dimension;
	// DON'T MOVE!
	//----------------------------

	Transform();



};

