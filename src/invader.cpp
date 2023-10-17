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

#include "invader_images.cpp"
#include "invader_sounds.cpp"
#include "Stage1.cpp"


void deInit(){
	
	// destroy managers...
	Font::destroy();
	Image::destroy();
	Sound::destroy();
    Tilemap::destroy();
    EntityManager::destroy();


	Graphics::deInit();
	SoundPlayer::deInit();

	// unload SDL
	SDL_Quit();
}

int main(int argc, char *argv[]){
    Graphics::createWindow(INVADER_WINDOW_WIDTH,INVADER_WINDOW_HEIGHT);
    Stage1 stage1;

    SoundPlayer::init();

    loadImages();
    loadSounds();
    
    stage1.load();
    

    do{

        // clear screen...
		Graphics::clear(0,0,0);

        /*if(current_image!=NULL){
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
        }*/



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