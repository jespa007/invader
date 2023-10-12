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

void loadImage(const std::string _image_name, const std::string & _raw_image_file, const std::string  & _raw_palette_file){
    
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
                        Image *image=Image::newImage(_image_name,INVADER_IMAGE_WIDTH,INVADER_IMAGE_HEIGHT);

                        Color last_color;
                        image->begin();
                        image->setColor3i(0,0,0);
                        for(int y=0; y < INVADER_IMAGE_HEIGHT; y++){
                            for(int x=0; x < INVADER_IMAGE_WIDTH; x++){
                                int paletter_idx=fgetc(fp_raw_image);
                                Color current_color=palette[paletter_idx];
                                if(last_color != current_color){
                                    image->setColor3i(current_color.r<<2,current_color.g<<2,current_color.b<<2);
                                    last_color=current_color;
                                }
                                image->putPoint(x,y);
                            }
                        }
                        image->end();

                        //printf("- Loaded image '%s'\n",_image_name.c_str());

                    }else{
                        fprintf(stderr,"loadImage : Error loading '%s'. Invalid image size. Expected %i bytes but it was %i bytes\n",_image_name.c_str(),INVADER_IMAGE_SIZE,(int)buf_size_image);    
                    }
                }else{
                   fprintf(stderr,"loadImage : Cannot open \"%s\"",_raw_image_file.c_str());
                }

            }else{
                fprintf(stderr,"loadImage : Error loading '%s'. Invalid palette size. Expected %i bytes but it was %i bytes\n",_image_name.c_str(),INVADER_PALETTE_SIZE,(int)buf_size_palette);
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


}

void deInit(){
	
	// destroy managers...
	Font::destroy();
	Image::destroy();
	Sound::destroy();


	Graphics::deInit();
	SoundPlayer::deInit();

	// unload SDL
	SDL_Quit();
}

int main(int argc, char *argv[]){
    Graphics::createWindow(INVADER_WINDOW_WIDTH,INVADER_WINDOW_HEIGHT);

    SoundPlayer::init();


    std::vector<std::string> image_files={
        "BIGFNT.RAW"
        ,"BLOCS1.RAW"
        ,"Enemic.RAW"
        ,"FONTMT.RAW"
        ,"MEDFNT.RAW"
        ,"NAU00.RAW"
        ,"NAUINT.RAW"
        ,"NAUMARE0.RAW"
        ,"Options.raw"
        ,"PANELL.RAW"
        ,"SPACE0.RAW"
        ,"SPRITES1.RAW"
        ,"TERRA.RAW"
        ,"TERRA0.RAW"
        ,"TERRA1.RAW"
        ,"TERRAD0.RAW"
        ,"TITUL.RAW"
    };

    for(auto image_file:image_files){
        loadImage(image_file,"../../../assets/graphics/"+image_file,"../../../assets/graphics/PALETA1.PAL");
    }

    std::vector<std::string> sample_files={
        "ALARMA.WAV"
        ,"BOMBOUT.WAV"
        ,"BOSSEX.WAV"
        ,"C_OK.WAV"
        ,"C_OPTION.WAV"
        ,"EXPLOS1.WAV"
        ,"FEBLE.WAV"
        ,"LAMEVAEX.WAV"
        ,"MECANIC.WAV"
        ,"NAUMARE0.WAV"
        ,"SHOT0.WAV"
        ,"SHOT1.WAV"
        ,"SHOT2.WAV"
        ,"TRO.WAV"
        ,"TURBO.WAV"
        ,"ATTENTIO.WAV"
        ,"BOMBERUP.WAV"
        ,"HUMET.WAV"
        ,"POWERUP.WAV"
        ,"ROBOT.WAV"

    };

    for(auto sample_file:sample_files){
        Sound::newSound(sample_file,"../../../assets/sounds/"+sample_file);
    }
  


    int idx_current_image=0;
    Image *current_image=Image::get(image_files[idx_current_image]);

    do{

        // clear screen...
		Graphics::clear(0,0,0);

        if(current_image!=NULL){
            Graphics::drawImage(current_image,current_image->getWidth()>>1,current_image->getHeight()>>1);
        }

        // update input
        Input::update();

        if(T_RIGHT) {
            idx_current_image=(idx_current_image+1)%image_files.size();
            current_image=Image::get(image_files[idx_current_image]);
        }



        // toggle fullscreen
		if(T_F9) {
			Graphics::toggleFullscreen();
		}

        // update screen...
		Graphics::update();
    }while(!T_ESC);

    deInit();

    return 0;
}