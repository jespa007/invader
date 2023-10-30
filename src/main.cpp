#include "Invader.h"

int main(int argc, char *argv[]){


    Invader::init();
    //invader.load();


    //int idx_current_image=0;
   //Image *current_image=Image::get(image_files[idx_current_image].file_name);

    //int idx_current_sound=0;
    //Sound *current_sound=Sound::get(sound_files[idx_current_sound]);
     Invader::iniTestImages();

    do{

        // clear screen...
		Graphics::clear(0,0,0);

        /*if(current_image!=NULL){
            Graphics::drawImage(current_image,current_image->getWidth()>>1,current_image->getHeight()>>1);
        }*/


        // update input
        Input::update();

        Invader::update();

        /*if(T_RIGHT) {
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

    Invader::deInit();

    return 0;
}
