/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#include "font_8x8.bmp.c"
#include "@graphics.h"


//-------
// Static
Font *Font::default_font=NULL;
std::map<std::string, Font *> *Font::s_fonts=NULL;


Font *Font::getDefaultFont(){
	if(default_font ==NULL){
		default_font=new Font();
		default_font->load(font_8x8_bmp,font_8x8_bmp_len,8,8);
	}
	return default_font;
}

std::map<std::string, Font *> *Font::getMap(){
	if(s_fonts == NULL){
		s_fonts=new std::map<std::string,Font *>;
	}

	return s_fonts;
}


Font *Font::newFont(
		const std::string & _name
		,const std::string & _file
		,int _char_width
		,int _char_height
		,const FontLoadOptions & _font_load_options
){

	Font *font=Font::get(_name);

	if(font != NULL){
		fprintf(stderr,"Font::newFont: Font '%s' already exists\n",_name.c_str());
		return NULL;
	}


	font=new Font();
	if(!font->load(_file
			,_char_width
			,_char_height
			,_font_load_options
	)){
		delete font;
		return NULL;
	}

	(*s_fonts)[_name]=font;

	return font;
}

Font *Font::get(const std::string & _name){
	auto fonts=getMap();
	if(fonts->count(_name)!=0){
		return (*fonts)[_name];
	}

	return NULL;
}

void Font::unloadAll(){
	auto fonts=getMap();
	for(auto v=fonts->begin(); v != fonts->end(); v++){
		delete v->second;
	}

	fonts->clear();
}

void Font::destroy(){
	unloadAll();

	if(s_fonts != NULL){
		delete s_fonts;
		s_fonts=NULL;
	}

	if(default_font !=NULL){
		delete default_font;
		default_font=NULL;
	}
}

//------------
// Member

Font::Font(){

	char_width=char_height=totalchars=totalchars_x=totalchars_y=0;
}



bool Font::load(unsigned char *buf, size_t buf_size,int _char_width,int _char_height,const FontLoadOptions &_font_load_options){
	SDL_Surface *srf=SDL_LoadBMP_RW(SDL_RWFromMem(buf,buf_size),1);
	if(srf!=NULL){

		if(_font_load_options.color_key!=-1){
			SDL_SetColorKey(
					srf
					,SDL_TRUE
					,SDL_MapRGB(srf ->format
						,SDL_COLOR32B_TO_RED8B(_font_load_options.color_key)
						,SDL_COLOR32B_TO_GREEN8B(_font_load_options.color_key)
						,SDL_COLOR32B_TO_BLUE8B(_font_load_options.color_key)
					)
			);
		}

		if((sdl_texture=Image::convertSurfaceToTexture(srf)) !=NULL){
			/*SDL_QueryTexture(image,
					NULL,
					NULL,
					&this->mWidth,
					&this->mHeight);*/
			this->width=srf->w;
			this->height=srf->h;
			this->char_width=_char_width;
			this->char_height=_char_height;
			totalchars_x=this->width/_char_width;
			totalchars_y=this->height/_char_height;
			totalchars=totalchars_x*totalchars_y;

			return true;
		}
		else{
			fprintf(stderr,"SurfaceToTexture:%s\n",SDL_GetError());
		}
	}
	else{
		fprintf(stderr,"SDL_LoadBMP:%s\n",SDL_GetError());
	}

	return false;
}

bool Font::load(
		 const std::string & _file
		,int _char_width
		,int _char_height
		,const FontLoadOptions &_font_load_options
){
	bool ok=false;
	FILE *fp=fopen(_file.c_str(),"rb");
	if(fp!=NULL){
		fseek(fp, 0, SEEK_END);
		long buf_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		unsigned char *buf=(unsigned char *)malloc(buf_size);

		long n=fread(buf,1,buf_size,fp);

		if(n!=buf_size){
			fprintf(stderr,"Cannot read font '%s'\n",_file.c_str());
		}else{

			ok=Font::load(buf, buf_size, _char_width, _char_height,_font_load_options);

			if(ok){
				printf("Loaded font %s (%ix%i). Font size: %ix%i. wc:%i hc:%i\n"
						,_file.c_str()
						,this->width
						,this->height
						,this->char_width
						,this->char_height
						,this->totalchars_x
						,this->totalchars_y
				);
			}
		}

		free(buf);
	}else{
		fprintf(stderr,"Cannot open:%s\n",_file.c_str());
	}
	return ok;
}

int Font::getCharWidth(){
	return char_width;
}
int Font::getCharHeight(){
	return char_height;
}

int Font::getTextWith(const std::string & str, const FontDrawOptions &_font_draw_options){

	float scale=1;

	if(_font_draw_options.font_height>0){
		if(_font_draw_options.font_height!=char_height){
			scale=_font_draw_options.font_height/((float)char_height);
		}
	}

	int total_width=0;

	for(unsigned i=0; i < str.size(); i++){
		total_width+=char_width;
	}
	return total_width*scale;
}

SDL_Rect Font::getRectChar(char c){
	m_aux_rect={0,0,char_width,char_height};
	if(c<totalchars){
		int x=c%totalchars_x;
		int y=c/totalchars_x;

		m_aux_rect.x=x*char_width;
		m_aux_rect.y=y*char_height;
	}

	return m_aux_rect;
}

Font::~Font(){

}
