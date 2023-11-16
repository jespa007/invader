#pragma once



class Color4f{
public:
	static Color4f BLACK;
	static Color4f WHITE;
	static Color4f RED;
	static Color4f YELLOW;
	static Color4f GREEN;
	static Color4f GRAY;

	static Color4f fromHtmlHexStr(const std::string & hex_color);
	static Color4f fromColor3i(int r, int g, int b);

	float r,g,b,a;

	Color4f(){ // black by default
		set(0
		    ,0
			,0
			,1
		);
	}

	Color4f(const Color4f & _color){ // black by default
		set(_color.r
		    ,_color.g
			,_color.b
			,_color.a
		);
	}

	Color4f(Uint32 color){
		setColorHtml(color);
	}

	Color4f(float _r, float _g, float _b, float _a);

	Color4f & operator=(const Color4f & _color){
		set(_color.r
		    ,_color.g
			,_color.b
			,_color.a
		);
		return *this;
	}

	void set(float _r, float _g, float _b, float _a){
		this->r=_r;
		this->g=_g;
		this->b=_b;
		this->a=_a;
	}

	void setColorHtml(Uint32 hex_color){
		//SDL_Color c;
		//SDL_html2rgb(hexcolor,c);
		this->r=((hex_color>>16)  & 0xFF)*ONE_OVER_256;
		this->g=((hex_color>>8)  & 0xFF)*ONE_OVER_256;
		this->b=((hex_color>>0) & 0xFF)*ONE_OVER_256;
		this->a=((hex_color>>24) & 0xFF)*ONE_OVER_256;

		if(this->a==0){
			this->a=1;
		}
	}



};



