#include "Invader.h"


Image *Invader::loadImage(
    const std::string _image_name
    , const std::string & _raw_image_file
    , int _image_width
    , int _image_height
    ,const std::string  & _raw_palette_file
){
    
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

                    long expected_size=_image_width*_image_height;

                    fseek(fp_raw_image, 0, SEEK_END);
                    long buf_size_image = ftell(fp_raw_image);
                    fseek(fp_raw_image, 0, SEEK_SET);

                    if(buf_size_image == expected_size){
                        fread(palette,1,INVADER_PALETTE_SIZE,fp_raw_palette);
                        Image *image=Image::newImage(_image_name,_image_width,_image_height);
                        bool is_tilemap=_image_name == "BLOCK1.RAW";
                        float one_over_image_width=1.0f/INVADER_TILE_WIDTH;
                        float one_over_image_height=1.0f/INVADER_TILE_HEIGHT;

                        Color last_color;
                        image->begin();
                        image->setColor3i(0,0,0);
                        for(int y=0; y < _image_height; y++){
                            for(int x=0; x < _image_width; x++){
                                int paletter_idx=fgetc(fp_raw_image);
                                Color current_color=palette[paletter_idx];
                                if(last_color != current_color){
                                    image->setColor3i(current_color.r<<2,current_color.g<<2,current_color.b<<2);
                                    last_color=current_color;
                                }
                                image->putPoint(x,y);

                                if(is_tilemap){
                                    int src_tile=y*one_over_image_width+one_over_image_width*x;
                                    if(src_tile >= 14){
                                        int dst_tile = 48 + (src_tile-14);
                                        int y_dst_tile=48/10;
                                        int x_dst_tile=48%10;
                                        
                                        int offset =(y_dst_tile)*_image_width*31 + x_dst_tile*_image_width + (INVADER_TILE_WIDTH)*(INVADER_TILE_HEIGHT-1) - y*(INVADER_TILE_WIDTH) + x;
                                        image->putPoint(x,y);
                                    }
                                }
                            }
                        }

                        // Particular case! If image is the tiles it has to build aditional tiles flipped horizontally and vertically
                        if(){
                            fseek(fp_raw_image, 0, SEEK_SET);
                            image->setColor3i(0,0,0);
                            for(k=48;k<INVADER_MAX_TILES;k++)
                                fseek(fp_raw_image, 0, SEEK_SET);{
                                for(int y=0; y < _image_height; y++){
                                    for(int x=0; x < _image_width; x++){
                                        // BLOCINVERS[y*INVADER_TILE_WIDTH+x]
                                        int offset = (INVADER_TILE_WIDTH)*(INVADER_TILE_HEIGHT-1) - y*(INVADER_TILE_WIDTH) + x;
                                        Blocs[k][j] = Blocs[k-48+14][BLOCINVERS[j]];
                                        image->setColor3i(current_color.r<<2,current_color.g<<2,current_color.b<<2);
                                        last_color=current_color;
                                    }
                                }
                            }
                        }

                        image->end();

                        //printf("- Loaded image '%s'\n",_image_name.c_str());

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

    return image;
}

void Invader::loadImages(){
    typedef struct{
        std::string file_name;
        int width,height;
    }InvaderGraphicFile;
    std::vector<InvaderGraphicFile> image_files={
        {"BLOCS1.RAW",INVADER_WINDOW_WIDTH,INVADER_WINDOW_HEIGHT}
        ,{"Enemic.RAW",INVADER_WINDOW_WIDTH,INVADER_WINDOW_HEIGHT}
        //,{"FONTMT.RAW"} --> discarted becasue is mono font
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
        
        Image *image=loadImage(image_file.file_name
        ,"../../../assets/graphics/"+image_file.file_name
        ,image_file.width
        ,image_file.height
        ,"../../../assets/graphics/PALETA1.PAL"
        );

        // from block 48 and upper are inverted 
        if(image_file.file_name == "BLOCK1.RAW"){

                
                for(k=48;k<INVADER_MAX_TILES;k++){
                    for(j=0;j<=((INVADER_TILE_WIDTH)*(INVADER_TILE_HEIGHT)-1);j++){
                        image->copy();
                        SDL_RenderCopy(SDL_Renderer * renderer,
                            SDL_Texture * texture,
                            const SDL_Rect * srcrect,
                            const SDL_Rect * dstrect
                        )
                        SDL_FLIP_HORIZONTAL|SDL_FLIP_VERTICAL
                        image->getColor3i(current_color.r<<2,current_color.g<<2,current_color.b<<2);
                        int offsetBLOCINVERS[y*AMPLADA_BLOC+x] = (AMPLADA_BLOC)*(AMPLADA_BLOC-1) - y*(AMPLADA_BLOC) + x;
                        Blocs[k][j] = Blocs[k-48+14][BLOCINVERS[j]];
                        image->setColor3i(current_color.r<<2,current_color.g<<2,current_color.b<<2);

                    }
                }

                    for(int y=0; y < _image_height; y++){
                        for(int x=0; x < _image_width; x++){
                            int paletter_idx=fgetc(fp_raw_image);
                            Color current_color=palette[paletter_idx];
                            if(last_color != current_color){
                                image->setColor3i(current_color.r<<2,current_color.g<<2,current_color.b<<2);
                                last_color=current_color;
                            }
                            image->putPoint(x,y);
                        }
                    }
                }
                image->end();            


                // may be an special flag the flips horizontally, or set properties for blocs or hardcode flip the image 

        }
    }

}