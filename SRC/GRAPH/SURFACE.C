#include "@GRAPH.H"


typedef struct Surface
{
    SurfaceType type;

    uint16_t width;
    uint16_t height;
    uint16_t pitch;

    bool owns_pixels;

    union
    {
        uint8_t far *pixels;

        struct
        {
            uint16_t segment;
            uint16_t offset;
        } video;
    } data;
} SurfaceData;



Surface  * Surface_New( uint16_t _width, uint16_t _height){
    unit8_t *pixels = FARNEW_LENGTH(unit8_t,_width*_height);
    Surface * surface = MALLOC(Surface);
    SurfaceData * data = MALLOC(SurfaceData);

    if(!pixels || !surface || !data){
        if(pixels){
            FARFREE(pixels);
        }

        if(surface){
            FREE(surface);
        }
        return NULL;
    }


    surface->data = data;

    data->type = SURFACE_MEMORY;
    data->owns_pixels = true;
    data->width = _width;
    data->height = _height;
    data->pixels = pixels;

    return surface;

}

void Surface_Clear(Surface * _this, uint8_t color){

}


bool Surface_LoadRaw(
    Surface * _this,
    const char *filename,
    uint16_t width,
    uint16_t height
){
    // load raw file

    // create surface according widt, height
}

static void Surface_BlitMemToMem(
    Surface * _this,
    int16_t _x,
    int16_t _y,
    const Surface *_src,
    const Rect *_src_rect
){

}

static void Surface_BlitMemToMode13(
    Surface * _this,
    int16_t _x,
    int16_t _y,
    const Surface *_src,
    const Rect *_src_rect    
){

}

static void Surface_BlitMemToModeX(    
    Surface * _this,
    int16_t _x,
    int16_t _y,
    const Surface *_src,
    const Rect *_src_rect
){

}

bool Surface_Blit(
    Surface *_this,
    int16_t _x,
    int16_t _y,
    const Surface * _src,
    const Rect * _src_rect
){

    if (_src->type != SURFACE_MEMORY)
    {
        return false;
    }    

    switch (dst->type)
    {
        case SURFACE_MEMORY:
            Surface_BlitMemToMem(
                dst,
               _x,
               _y,
                _src,
                _src_rect
            );
            break;

        case SURFACE_MODE13:
            Surface_BlitMemToMode13(
                dst,
               _x,
               _y,
                _src,
                _src_rect
            );
            break;

        case SURFACE_MODEX:
            Surface_BlitMemToModeX(
                dst,
               _x,
               _y,
                _src,
                _src_rect
            );
            break;

        default:
            return false;
    }

    return true;
}

void Surface_Delete(Surface * _this){
    if(_this == NULL){
        return;
    }

    SurfaceData *data = _this->data;

    if(data->owns_pixels){
        FARFREE(data->pixels);
    }


    FREE(data);
    FREE(_this);
}