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

#include "Invader_images.cpp"
#include "Invader_sounds.cpp"
#include "Invader_entities.cpp"
#include "Invader_stage1.cpp"

Tilemap *Invader::background=NULL;
EntityManager *Invader::entity_manager=NULL;
bool Invader::initialized=false;

void Invader::init(){
    if(Invader::initialized == true){
        fprintf(stderr, "Invader::init : Invader already initialized!");
        return;
    }

    Invader::background = new Tilemap();
    Invader::entity_manager = new EntityManager();

    Graphics::createWindow(INVADER_WINDOW_WIDTH,INVADER_WINDOW_HEIGHT);
    SoundPlayer::init();
    loadImages();
    loadSounds();

    Invader::initialized = true;
    
}

void Invader::deInit(){
    if(Invader::initialized == false){
        fprintf(stderr, "Invader::deInit : Invader not initialized!");
        return;
    }


    delete Invader::background;
    delete Invader::entity_manager;

	// destroy managers...
	Font::destroy();
	Image::destroy();
	Sound::destroy();
	Graphics::deInit();
	SoundPlayer::deInit();

	// unload SDL
	SDL_Quit();

    Invader::initialized = false;
}

int main(int argc, char *argv[]){


    Invader::init();

    Stage1 stage1;
    stage1.load();
    

    int idx_current_image=0;
    Image *current_image=Image::get(image_files[idx_current_image].file_name);

    int idx_current_sound=0;
    Sound *current_sound=Sound::get(sound_files[idx_current_sound]);

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
            current_image=Image::get(image_files[idx_current_image].file_name);
        }

        if(T_LEFT) {
            if(current_sound != NULL){
                SoundPlayer::play(current_sound);
            }
            idx_current_sound=(idx_current_sound+1)%sound_files.size();            
            current_sound=Sound::get(sound_files[idx_current_sound]);
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