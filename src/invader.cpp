#include "System.cpp"
#include "Graphics.cpp"
#include "Input.cpp"
#include "Collider.cpp"
#include "Image.cpp"
#include "Sprite.cpp"
#include "Entity.cpp"
#include "EntityAnimation.cpp"
#include "EntityManager.cpp"
#include "Tilemap.cpp"
#include "Font.cpp"
#include "Sound.cpp"
#include "SoundPlayer.cpp"

Image *loadImage(const std::string & _raw_image_file, const std::string  & _raw_palette_file){
    
    FILE *fp_raw_palette=fopen(_raw_palette_file.c_str(),"rb");
    FILE *fp_raw_image=NULL;
    Image *image=NULL;

    if(fp_raw_palette != NULL){
            Color palette[INVADER_PALETTE_COLORS];

            fseek(fp_raw_palette, 0, SEEK_END);
		    long buf_size_palette = ftell(fp_raw_palette);
		    fseek(fp_raw_palette, 0, SEEK_SET);

            if(buf_size_palette == INVADER_PALETTE_SIZE){
            
                fp_raw_image=fopen(_raw_image_file.c_str(),"rb");

                if(fp_raw_image != NULL){

                    fseek(fp_raw_image, 0, SEEK_END);
                    long buf_size_image = ftell(fp_raw_image);
                    fseek(fp_raw_image, 0, SEEK_SET);

                    if(buf_size_image == INVADER_IMAGE_SIZE){
                        fread(palette,1,INVADER_PALETTE_SIZE,fp_raw_palette);
                        Image *image=Image::newImage(_raw_image_file,INVADER_IMAGE_WIDTH,INVADER_IMAGE_HEIGHT);

                        Color last_color;
                        image->begin();
                        image->setColor3i(0,0,0);
                        for(int y=0; y < INVADER_IMAGE_HEIGHT; y++){
                            for(int x=0; x < INVADER_IMAGE_WIDTH; x++){
                                int paletter_idx=fgetc(fp_raw_image);
                                Color current_color=palette[paletter_idx];
                                if(last_color != current_color){
                                    image->setColor3i(current_color.r,current_color.g,current_color.b);
                                    last_color=current_color;
                                }
                                image->putPoint(x,y);
                            }
                        }
                        image->end();

                    }else{
                        fprintf(stderr,"loadImage : Invalid image size. Expected %i bytes but it was %i bytes\n",INVADER_IMAGE_SIZE,(int)buf_size_image);    
                    }
                }else{
                   fprintf(stderr,"loadImage : Cannot open \"%s\"",_raw_image_file.c_str());
                }

            }else{
                fprintf(stderr,"loadImage : Invalid palette size. Expected %i bytes but it was %i bytes\n",INVADER_PALETTE_SIZE,(int)buf_size_palette);
            }
    }else{
        fprintf(stderr,"loadImage : Cannot open \"%s\"\n",_raw_palette_file.c_str());
    }
    
    if(fp_raw_image != NULL){
        fclose(fp_raw_image);
    }

    if(fp_raw_palette != NULL){
        fclose(fp_raw_palette);
    }

    return image;
}

void destroy(){
	
	// destroy managers...
	Font::destroy();
	Image::destroy();
	Sound::destroy();
	Graphics::deInit();
	SoundPlayer::destroy();

	// unload SDL
	SDL_Quit();
}

int main(int argc, char *argv[]){
    Graphics::createWindow(INVADER_WINDOW_WIDTH,INVADER_WINDOW_HEIGHT);

    do{

        // clear screen...
		Graphics::clear(0,0,0);

        // update input
        Input::update();

        // toggle fullscreen
		if(T_F9) {
			Graphics::toggleFullscreen();
		}

        // update screen...
		Graphics::update();
    }while(!T_ESC);

    destroy();

    return 0;
}