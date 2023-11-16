#pragma once


#define ALPHA_VALUE_TRANSPARENT		0
#define ALPHA_VALUE_SOLID			1


//class MaterialAnimation;
class Material{

public:
	enum{
		//---------------------------- Properties -----------------------------------
		 WITH_SHADELESS 		= 0x1 << 13, // Shadeless & no light means the same thing ...
	};

	typedef enum{
		COLOR_R		=0,
		COLOR_G		,
		COLOR_B		,
		ALPHA		,
		MAX_MATERIAL_COMPONENTS
	}MaterialComponent;


	//----------------------------
	// DON'T MOVE! THESE ORDER IS NEEDED FOR PASS ANIMATION COMPONENTS
	Color4f color;
	// DON'T MOVE!
	//----------------------------
	//float	 m_alpha;


	Material();

	~Material();



};

