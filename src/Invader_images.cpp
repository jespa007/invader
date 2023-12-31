#include "Invader.h"

SDL_Surface *Invader::loadImage(
    const std::string _image_name
    , const std::string & _raw_image_file
    , int _image_width
    , int _image_height
    ,const std::string  & _raw_palette_file
){
    
    FILE *fp_raw_palette=fopen(_raw_palette_file.c_str(),"rb");
    FILE *fp_raw_image=NULL;
    SDL_Surface *srf_image=NULL;

    if(fp_raw_palette != NULL){
            Uint8 palette[INVADER_PALETTE_SIZE];

            fseek(fp_raw_palette, 0, SEEK_END);
		    long buf_size_palette = ftell(fp_raw_palette);
		    fseek(fp_raw_palette, 0, SEEK_SET);

            if(buf_size_palette == INVADER_PALETTE_SIZE){
            
                fp_raw_image=fopen(_raw_image_file.c_str(),"rb");

                if(fp_raw_image != NULL){

                    long expected_size=_image_width*_image_height;

                    fseek(fp_raw_image, 0, SEEK_END);
                    long buf_size_image = ftell(fp_raw_image);
                    fseek(fp_raw_image, 0, SEEK_SET);

                    if(buf_size_image == expected_size){
                    	srf_image=SDL_NewSurface(_image_width,_image_height,1);


                        fread(palette,1,INVADER_PALETTE_SIZE,fp_raw_palette);

                        SDL_Color sdl_colors[256];
                        Uint8 *dst_palette=(Uint8 *)&sdl_colors[0],*src_palette=palette;

						for(int i = 0; i < 256; i++) {
							*dst_palette++ = (*src_palette++)<<2; // R
							*dst_palette++ = (*src_palette++)<<2; // G
							*dst_palette++ = (*src_palette++)<<2; // B
							*dst_palette++=255;			 // A
						}

                        fread(srf_image->pixels,1,_image_width*_image_height,fp_raw_image);

                        // set palette
                        SDL_SetPaletteColors(srf_image->format->palette, sdl_colors, 0, 255);


                    }else{
                        fprintf(stderr,"loadImage : Error loading '%s'. Invalid image size. Expected %i bytes but it was %i bytes\n",_image_name.c_str(),(int)expected_size,(int)buf_size_image);    
                    }
                }else{
                   fprintf(stderr,"loadImage : Cannot open \"%s\"",_raw_image_file.c_str());
                }

            }else{
                fprintf(stderr,"loadImage : Error loading '%s'. Invalid palette size. Expected %i bytes but it was %i bytes\n"
                ,_image_name.c_str()
                ,(int)INVADER_PALETTE_SIZE
                ,(int)(buf_size_palette));
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

    return srf_image;
}

void Invader::loadImages(){
    typedef struct{
        std::string file_name;
        int width,height;
    }InvaderGraphicFile;
    std::vector<InvaderGraphicFile> image_files={
        {"BLOCS1.RAW",INVADER_WINDOW_WIDTH,INVADER_WINDOW_HEIGHT}
        ,{"Enemic.RAW",INVADER_WINDOW_WIDTH,INVADER_WINDOW_HEIGHT}
        //,{"FONTMT.RAW"} --> discarted because is a special mono font
        ,{"MEDFNT.RAW",INVADER_MED_FONT_LETTER_WIDTH*INVADER_FONT_NUM_LETTERS,INVADER_MED_FONT_LETTER_HEIGHT}
        ,{"BIGFNT.RAW",INVADER_BIG_FONT_LETTER_WIDTH*INVADER_FONT_NUM_LETTERS,INVADER_BIG_FONT_LETTER_HEIGHT}
        ,{"NAU00.RAW",206,97}
        ,{"NAUMARE0.RAW",230,200}
        ,{"Options.raw",INVADER_WINDOW_WIDTH,INVADER_WINDOW_HEIGHT}
        ,{"PANELL.RAW",96,192}
        ,{"SPACE0.RAW",INVADER_WINDOW_WIDTH,INVADER_WINDOW_HEIGHT}
        ,{"SPRITES1.RAW",INVADER_WINDOW_WIDTH,INVADER_WINDOW_HEIGHT}
        ,{"TERRA.RAW",110,100}
        ,{"TERRA0.RAW",INVADER_WINDOW_WIDTH,INVADER_WINDOW_HEIGHT}
        ,{"TERRA1.RAW",INVADER_WINDOW_WIDTH,INVADER_WINDOW_HEIGHT}
        ,{"TERRAD0.RAW",INVADER_WINDOW_WIDTH,INVADER_WINDOW_HEIGHT}
        ,{"TITUL.RAW",INVADER_WINDOW_WIDTH,INVADER_WINDOW_HEIGHT}
    };

    for(auto image_file:image_files){
        
        SDL_Surface *srf_image=loadImage(image_file.file_name
        ,"../../../assets/graphics/"+image_file.file_name
        ,image_file.width
        ,image_file.height
        ,"../../../assets/graphics/PALETA1.PAL"
        );

        // Set pink as color mask
		SDL_SetColorKey(
			srf_image
			,SDL_TRUE
			,SDL_MapRGB(srf_image ->format
				,0xFF
				,0x00
				,0xFF
			)
		);

        // block1.raw adds tiles starting from 14 up a copy of some tiles in the image inverted in Y
        if(image_file.file_name == "BLOCS1.RAW"){

        	// assign new surface with enough space for extra tiles
        	SDL_Surface *src_blocks=SDL_NewSurface(INVADER_WINDOW_WIDTH,INVADER_WINDOW_HEIGHT*2,1);

        	// copy pixels ...
      		memcpy(src_blocks->pixels, srf_image->pixels, INVADER_WINDOW_WIDTH * INVADER_WINDOW_HEIGHT);

            // copy palette ...
        	SDL_SetPaletteColors(src_blocks->format->palette, srf_image->format->palette->colors, 0, 255);
        	SDL_FreeSurface(srf_image);

        	// set old image
        	srf_image=src_blocks;
        	//SDL_SetPaletteColors(src_blocks->format->palette, srf_image->format->palette, 0, 255);

        	int tiles_per_row=INVADER_IMAGE_WIDTH/INVADER_TILE_WIDTH;
			int src_tile_id=14;
		    for(int dst_tile_id=48;dst_tile_id<INVADER_MAX_TILES;dst_tile_id++,src_tile_id++){
		    	// 1. set src and dst pointers
		    	int src_y=(src_tile_id/tiles_per_row)*INVADER_TILE_HEIGHT;
		    	int src_x=(src_tile_id%tiles_per_row)*INVADER_TILE_WIDTH;
		    	Uint8 *src_pointer=(Uint8 *)srf_image->pixels+src_y*INVADER_IMAGE_WIDTH+src_x;

		    	int dst_y=(dst_tile_id/tiles_per_row)*(INVADER_TILE_HEIGHT)+INVADER_TILE_HEIGHT-1;
		    	int dst_x=(dst_tile_id%tiles_per_row)*INVADER_TILE_WIDTH;
		    	Uint8 *dst_pointer=(Uint8 *)srf_image->pixels+dst_y*INVADER_IMAGE_WIDTH+dst_x;

		    	// 2. copy span
		    	for(int y=0; y < INVADER_TILE_HEIGHT;y++){

		    		memcpy(dst_pointer,src_pointer,INVADER_TILE_WIDTH);

		    		src_pointer+=(INVADER_IMAGE_WIDTH);
		    		dst_pointer-=(INVADER_IMAGE_WIDTH);
		    	}

		     }
        }

        Image::newImageFromSdlSurface(image_file.file_name,srf_image);

        SDL_FreeSurface(srf_image);
    }
}

int idx_current_image=0;
void Invader::iniTestImages(){
    idx_current_image=0;
    //current_image=Image::get(image_files[idx_current_image].file_name);
}

void Invader::updateTestImages(){

	const char * image_names[]={
	        "BLOCS1.RAW"
	        ,"Enemic.RAW"
	        //,{"FONTMT.RAW"} --> discarted because is a special mono font
	        ,"MEDFNT.RAW"
	        ,"BIGFNT.RAW"
	        ,"NAU00.RAW"
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

	size_t image_length=ARRAY_SIZE(image_names);

     if(T_RIGHT) {
       idx_current_image=(idx_current_image+1)%image_length;
     }

     Image *current_image=Image::get(image_names[idx_current_image]);
     Graphics::drawImage(current_image,current_image->getWidth()>>1,current_image->getHeight()>>1);

     /*Image *blocks_raw=Image::get("SPRITES1.RAW");
     Graphics::drawImage(blocks_raw,blocks_raw->getWidth()>>1,blocks_raw->getHeight()>>1);*/
}
