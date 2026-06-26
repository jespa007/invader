#ifndef __MODE13_H__
#define __MODE13_H__

#define VIDEO_SEGMENT 0xA000
#define VIDEO_OFFSET  0x0000
#define VGA_MEMORY ((unsigned char far *)MK_FP(VIDEO_SEGMENT, VIDEO_OFFSET))




#endif