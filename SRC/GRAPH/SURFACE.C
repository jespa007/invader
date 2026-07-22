#include "GRAPH/@GRAPH.H"


typedef struct
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
    Surface * surface = NULL;
    SurfaceData * data = NULL;
    uint8_t far * pixels = NULL;
    uint32_t pixel_count = 0;
    
    if ( _width == 0 || _height == 0){
        LOG_ERROR("Surface_New : _width == 0 || _height == 0");
        return NULL;
    }

    pixel_count = (uint32_t)_width * (uint32_t)_height;

    if ( pixel_count > 65535UL){
        LOG_ERROR("Surface_New : pixel_count > 65535");
        return NULL;
    }    

    pixels = FARNEW_LENGTH(uint8_t,pixel_count);
    surface = NEW(Surface);
    data = NEW(SurfaceData);

    if(!pixels || !surface || !data){
        if(pixels){
            FARFREE(pixels);
        }

        if (data != NULL){
            FREE(data);
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
    data->pitch = _width;
    data->data.pixels = pixels;

    return surface;
}

Surface  * Surface_NewFromPixels( uint8_t far * _pixels, uint16_t _width, uint16_t _height){
    Surface * surface = NULL;
    SurfaceData * data = NULL;
    uint32_t pixel_count = 0;
    
    if (_pixels == NULL || _width == 0 || _height == 0){
        LOG_ERROR("Surface_NewFromPixels : _pixels == NULL || _width == 0 || _height == 0");
        return NULL;
    }

    pixel_count = (uint32_t)_width * (uint32_t)_height;

    if ( pixel_count > 65535UL){
        LOG_ERROR("Surface_NewFromPixels : pixel_count > 65535");
        return NULL;
    }    


    surface = NEW(Surface);
    data = NEW(SurfaceData);

    if(!surface || !data){

        if(data){
            FREE(data);
        }

        if(surface){
            FREE(surface);
        }
        return NULL;
    }


    surface->data = data;

    data->type = SURFACE_MEMORY;
    data->owns_pixels = false;
    data->width = _width;
    data->height = _height;
    data->pitch = _width;
    data->data.pixels = _pixels;

    return surface;

}

static Surface *Surface_NewVideo(
    SurfaceType _type,
    uint16_t _segment,
    uint16_t _offset,
    uint16_t _width,
    uint16_t _height,
    uint16_t _pitch
)
{
    Surface *surface;
    SurfaceData *data;

    surface = Surface_NewFromPixels(
        (uint8_t far *)MK_FP(_segment, _offset),
        _width,
        _height
    );

    if (surface == NULL)
    {
        return NULL;
    }

    data = surface->data;

    data->type  = _type;
    data->pitch = _pitch;

    return surface;
}

Surface *Surface_NewMode13(
    uint16_t _segment,
    uint16_t _offset,
    uint16_t _width,
    uint16_t _height,
    uint16_t _pitch
)
{
    return Surface_NewVideo(
        SURFACE_MODE13,
        _segment,
        _offset,
        _width,
        _height,
        _pitch
    );
}

Surface *Surface_NewModeX(
    uint16_t _segment,
    uint16_t _offset,
    uint16_t _width,
    uint16_t _height,
    uint16_t _pitch
)
{
    return Surface_NewVideo(
        SURFACE_MODEX,
        _segment,
        _offset,
        _width,
        _height,
        _pitch
    );
}

Surface *Surface_NewFromRaw(
    const char *_filename,
    uint16_t _width,
    uint16_t _height
)
{
    Buffer *buffer;
    Surface *surface;
    SurfaceData *surface_data;
    uint32_t pixel_count;

    if (_filename == NULL || _width == 0 || _height == 0)
    {
        return NULL;
    }

    pixel_count = (uint32_t)_width * (uint32_t)_height;

    /*
     * Surface_New currently supports at most one 64 KB segment.
     */
    if (pixel_count > 65535UL)
    {
        LOG_ERROR(
            "Surface_NewFromRaw: image '%s' is too large",
            _filename
        );

        return NULL;
    }

    buffer = File_Read(_filename);

    if (buffer == NULL)
    {
        LOG_ERROR(
            "Surface_NewFromRaw: file '%s' does not exist",
            _filename
        );

        return NULL;
    }

    if ((uint32_t)buffer->len != pixel_count)
    {
        LOG_ERROR(
            "Surface_NewFromRaw: raw file '%s' has length %lu, expected %lu",
            _filename,
            (unsigned long)buffer->len,
            (unsigned long)pixel_count
        );

        Buffer_Delete(buffer);
        return NULL;
    }

    surface = Surface_New(_width, _height);

    if (surface == NULL)
    {
        LOG_ERROR(
            "Surface_NewFromRaw: cannot allocate surface for '%s'",
            _filename
        );

        Buffer_Delete(buffer);
        return NULL;
    }

    surface_data = surface->data;

    FARMEMCPY(
        surface_data->data.pixels,
        buffer->ptr,
        (size_t)pixel_count
    );

    Buffer_Delete(buffer);

    return surface;
}

void Surface_Clear(Surface * _this, uint8_t color){

}



static bool Surface_BlitMemToLinear(
    Surface *_this,
    int _x,
    int _y,
    const Surface *_src,
    const Rect *_src_rect
)
{
    SurfaceData *dst_data;
    SurfaceData *src_data;
    uint8_t far *dst;
    uint8_t far *src;
    uint16_t row;

    dst_data = _this->data;
    src_data = _src->data;

    dst =
        dst_data->data.pixels +
        ((uint32_t)_y * dst_data->pitch) +
        _x;

    src =
        src_data->data.pixels +
        ((uint32_t)_src_rect->y * src_data->pitch) +
        _src_rect->x;

    for (row = 0; row < _src_rect->height; ++row)
    {
        _fmemcpy(
            dst,
            src,
            _src_rect->width
        );

        dst += dst_data->pitch;
        src += src_data->pitch;
    }

    return true;
}

static bool Surface_BlitMemToMode13(
    Surface * _this,
    int _x,
    int _y,
    const Surface *_src,
    const Rect *_src_rect    
){

/*word Segment(byte *VSbuffer)
{
 return FP_SEG(VSbuffer);
}*/

}

static bool Surface_BlitMemToModeX(    
    Surface * _this,
    int _x,
    int _y,
    const Surface *_src,
    const Rect *_src_rect
){

}

bool Surface_Blit(
    Surface *_this,
    int _x,
    int _y,
    const Surface * _src,
    const Rect * _src_rect
){
    SurfaceData * dst_data = NULL;
    SurfaceData * src_data = NULL;
    Rect          src_rect = {0};

    if(_this == NULL || _src == NULL){
        return false;
    }

     dst_data = _this->data;
     src_data = _src->data;

    if (src_data->type != SURFACE_MEMORY){
        return false;
    }


    if (_src_rect != NULL){
        src_rect = *_src_rect;
    }else{
        src_rect.x      = 0;
        src_rect.y      = 0;
        src_rect.width  = src_data->width;
        src_rect.height = src_data->height;
    }    

    switch (dst_data->type){
    case SURFACE_MEMORY:
    case SURFACE_MODE13:
        return Surface_BlitMemToLinear(
            _this,
            _x,
            _y,
            _src,
            _src_rect
        );

        case SURFACE_MODEX:
            return Surface_BlitMemToModeX(
                _this,
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

    SurfaceData *data = NULL;

    if(_this == NULL){
        return;
    }

    data = _this->data;

    if(data->owns_pixels){
        FARFREE(data->data.pixels);
    }

    FREE(data);
    FREE(_this);
}