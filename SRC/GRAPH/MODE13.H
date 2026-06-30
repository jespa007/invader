#ifndef __MODE13_H__
#define __MODE13_H__

#define VIDEO_SEGMENT 0xA000
#define VIDEO_OFFSET  0x0000
#define VGA_MEMORY ((unsigned char far *)MK_FP(VIDEO_SEGMENT, VIDEO_OFFSET))


void Mode13_Init();
void Mode13_PutBlock(
    int _x
    ,int _y
    ,uint8_t far * _block
    ,uint16_t _block_width
    ,uint16_t _block_height
    ,uint16_t MIN_AMPLADA
    ,uint16_t MIN_ALTURA
    ,uint16_t MAX_AMPLADA
    ,uint16_t MAX_ALTURA
    ,uint16_t SEGMENT
);

void Mode13_DeInit();


#endif