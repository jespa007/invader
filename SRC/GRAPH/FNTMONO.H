#ifndef __FNTMONO_H__
#define __FNTMONO_H__


#define FNT_MONO_PROPERTY_BOLD      0x1<<0
#define FNT_MONO_PROPERTY_INVERTED  0x1<<1



void FntMono_PutChar(
    int _x
    ,int _y
    ,char _character
    ,uint8_t _texture
    ,uint16_t _properties
);

#endif