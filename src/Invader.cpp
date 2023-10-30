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

void Invader::iniTestImages(){
    /*idx_current_image=0;
    current_image=Image::get(image_files[idx_current_image].file_name);*/
}

void Invader::updateTestImages(){
     /*if(T_RIGHT) {
       idx_current_image=(idx_current_image+1)%image_files.size();
       current_image=Image::get(image_files[idx_current_image].file_name);
     }*/
     Image *blocks_raw=Image::get("BLOCS1.RAW");
     Graphics::drawImage(blocks_raw,blocks_raw->getWidth()>>1,blocks_raw->getHeight()>>1);
}

void Invader::update(){
    Invader::updateTestImages();
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


