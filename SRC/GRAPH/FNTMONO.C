#include "SRC\GRAPH\@GRAPH.H"

#define FNT_MONO_MAX_CHARACTERS     48
#define FNT_MONO_CHAR_HEIGHT        8
#define FNT_MONO_TEXTURE_WIDTH      8
#define FNT_MONO_TEXTURE_HEIGHT     8
#define FNT_MONO_TEXTURE_RESOLUTION FNT_MONO_TEXTURE_WIDTH*FNT_MONO_TEXTURE_HEIGHT
#define FNT_MONO_NUM_TEXTURES       4

static char g_fnt_mono_char[FNT_MONO_CHAR_HEIGHT*FNT_MONO_MAX_CHARACTERS] = {
    0,126,114,114,114,114,126,0, /* 0 */
    0,120,56,56,56,56,56,0,      /* 1 */
    0,124,28,124,112,124,124,0,  /* 2 */
    0,124,28,124,28,124,124,0,   /* 3 */
    0,116,116,124,28,28,28,0,    /* 4 */
    0,124,112,124,28,124,124,0,  /* 5 */
    0,124,112,124,116,124,124,0, // 6 */
    0,124,28,60,28,28,28,0,      //* 7 */
    0,124,116,124,116,124,124,0, //* 8 */
    0,124,92,124,28,28,28,0,     //* 9 */
    0,0,0,0,0,24,24,0,           //* . */
    0,0,0,0,0,24,48,0,           //* , */
    0,0,24,24,0,24,24,0,         //* : */
    0,0,24,24,0,24,48,0,         //* ; */
    24,60,60,24,24,0,24,0,       //* ! */
    24,0,24,24,60,60,24,0,       //* � */
    28,38,6,12,16,0,16,0,        //* ? */
    8,0,8,48,96,100,56,0,        //* � */
    0,48,96,96,96,96,48,0,       //* ( */
    0,24,12,12,12,12,24,0,       //* ) */
    0,60,102,94,94,102,60,0,     //* Copyright */
    0,60,102,102,126,126,102,0,  //* A */
    0,124,116,126,114,114,126,0, //* B */
    0,126,114,112,112,114,126,0, //* C */
    0,124,114,114,114,114,124,0, //* D */
    0,126,112,124,112,112,126,0, //* E */
    0,126,112,124,112,112,112,0, //* F */
    0,126,114,112,118,114,126,0, //* G */
    0,114,114,126,114,114,114,0, //* H */
    0,126,24,24,24,24,126,0,     //* I */
    0,14,14,14,78,78,126,0,      //* J */
    0,116,120,120,116,114,114,0, //* K */
    0,112,112,112,112,112,126,0, //* L */
    0,102,126,90,66,66,66,0,     //* M */
    0,98,114,122,110,102,98,0,   //* N */
    0,60,102,102,102,102,60,0,   //* O */
    0,124,114,114,124,112,112,0, //* P */
    0,56,100,100,100,100,58,0,   //* Q */
    0,124,114,114,124,126,114,0, //* R */
    0,62,112,56,28,30,124,0,     //* S */
    0,124,24,24,24,24,24,0,      //* T */
    0,114,114,114,114,126,60,0,  //* U */
    0,114,114,114,118,60,24,0,   //* V */
    0,66,90,90,90,126,102,0,     //* W */
    0,102,36,24,24,36,102,0,     //* X */
    0,98,98,60,24,24,24,0,       //* Y */
    0,126,14,28,56,112,126,0,    //* Z */
    0,0,0,0,0,0,0,0              //*   */
};            

static uint8_t g_fnt_mono_texture[FNT_MONO_NUM_TEXTURES*FNT_MONO_TEXTURE_RESOLUTION] = {
    15,15,15,15,15,15,15,15, // Textura 5
    15,15,15,15,15,15,15,15, // Textura 5
    15,15,15,15,15,15,15,15, // Textura 5
    15,15,15,15,15,15,15,15, // Textura 5
    15,15,15,15,15,15,15,15, // Textura 5
    15,15,15,15,15,15,15,15, // Textura 5
    15,15,15,15,15,15,15,15, // Textura 5
    15,15,15,15,15,15,15,15, // Textura 5

    0,0,0,0,0,0,0,0, // Textura 2
    0,255,15,15,15,15,15,0,
    0,15,15,15,15,15,15,0,
    0,15,15,15,15,15,15,0,
    0,15,15,15,15,15,15,0,
    0,15,15,15,15,15,15,0,
    0,15,15,15,15,15,15,0,
    0,0,0,0,0,0,0,0,

    15,15,30,28,26,26,53,53,
    15,30,28,26,26,53,53,50,
    30,28,26,26,53,53,50,50,
    28,26,26,53,53,50,50,13,
    26,26,53,53,50,50,13,13,
    26,53,53,50,50,13,13,8,
    53,53,50,50,13,13,8,8,
    53,50,50,13,13,8,8,8,


    15,15,27,27,27,27,27,55, // Textura 4
    15,15,27,27,27,27,55,55, 
    27,27,27,27,27,55,55,55,
    27,27,27,27,55,55,55,83,
    27,27,27,55,55,55,83,83,
    27,27,55,55,55,83,83,83,
    27,55,55,55,83,83,83,111,
    55,55,55,83,83,83,111,111

};


uint8_t FntMono_getCharCode(char _char_code) {

 switch(_char_code) {
  case '0':return 0;
  case '1':return 1;
  case '2':return 2;
  case '3':return 3;
  case '4':return 4;
  case '5':return 5;
  case '6':return 6;
  case '7':return 7;
  case '8':return 8;
  case '9':return 9;
  case '.':return 10;
  case ',':return 11;
  case ':':return 12;
  case ';':return 13;
  case '!':return 14;
  //case '�':return 15;
  case '?':return 16;
  //case '�':return 17;
  case '(':return 18;
  case ')':return 19;
  case '-':return 20;
  case 'A':return 21;
  case 'B':return 22;
  case 'C':return 23;
  case 'D':return 24;
  case 'E':return 25;
  case 'F':return 26;
  case 'G':return 27;
  case 'H':return 28;
  case 'I':return 29;
  case 'J':return 30;
  case 'K':return 31;
  case 'L':return 32;
  case 'M':return 33;
  case 'N':return 34;
  case 'O':return 35;
  case 'P':return 36;
  case 'Q':return 37;
  case 'R':return 38;
  case 'S':return 39;
  case 'T':return 40;
  case 'U':return 41;
  case 'V':return 42;
  case 'W':return 43;
  case 'X':return 44;
  case 'Y':return 45;
  case 'Z':return 46;
  default:return 47;
 }

}

void FntMono_PutChar(
    int _x
    ,int _y
    ,char _character
    ,uint8_t _texture
    ,uint16_t _properties
){
    int offset,by;
    uint8_t getbyte;
    uint8_t offset_texture;
    bool is_bold = (_properties & FNT_MONO_PROPERTY_BOLD) == FNT_MONO_PROPERTY_BOLD;
    bool is_inverted = (_properties & FNT_MONO_PROPERTY_INVERTED) == FNT_MONO_PROPERTY_INVERTED;

    uint8_t char_code = FntMono_getCharCode(_character);

    offset_texture = _texture*FNT_MONO_TEXTURE_RESOLUTION;
    offset = char_code*FNT_MONO_CHAR_HEIGHT;

 
    if(!is_inverted){
          for(by=0;by<FNT_MONO_CHAR_HEIGHT;by++,offset++)
          {
           getbyte = g_fnt_mono_char[offset];
           if ((getbyte&128)!=0)
           {
            Graphics_PutPixel(_x,_y+by,g_fnt_mono_texture[offset_texture]);
            if(is_bold) Graphics_PutPixel(_x+1,_y+by+1,g_fnt_mono_texture[offset_texture]);
           }
           offset_texture++;
           getbyte = g_fnt_mono_char[offset];
           if ((getbyte&64)!=0) 
           {
            Graphics_PutPixel(_x+1,_y+by,g_fnt_mono_texture[offset_texture]);
            if(is_bold) Graphics_PutPixel(_x+2,_y+by+1,g_fnt_mono_texture[offset_texture]);
           }
           offset_texture++;
           getbyte = g_fnt_mono_char[offset];
           if ((getbyte&32)!=0) 
           { 
            Graphics_PutPixel(_x+2,_y+by,g_fnt_mono_texture[offset_texture]);
            if(is_bold) Graphics_PutPixel(_x+3,_y+by+1,g_fnt_mono_texture[offset_texture]);
           }
           offset_texture++;
           getbyte = g_fnt_mono_char[offset];
           if ((getbyte&16)!=0) 
           { 
            Graphics_PutPixel(_x+3,_y+by,g_fnt_mono_texture[offset_texture]);
            if(is_bold) Graphics_PutPixel(_x+4,_y+by+1,g_fnt_mono_texture[offset_texture]);
           }
           offset_texture++;
           getbyte = g_fnt_mono_char[offset];
           if ((getbyte&8)!=0) 
           { 
            Graphics_PutPixel(_x+4,_y+by,g_fnt_mono_texture[offset_texture]);
            if(is_bold) Graphics_PutPixel(_x+5,_y+by+1,g_fnt_mono_texture[offset_texture]);
           }
           offset_texture++;
           getbyte = g_fnt_mono_char[offset];
           if ((getbyte&4)!=0) 
           { 
            Graphics_PutPixel(_x+5,_y+by,g_fnt_mono_texture[offset_texture]);
            if(is_bold) Graphics_PutPixel(_x+6,_y+by+1,g_fnt_mono_texture[offset_texture]);
           }
           offset_texture++;
           getbyte = g_fnt_mono_char[offset];
           if ((getbyte&2)!=0) 
           { 
            Graphics_PutPixel(_x+6,_y+by,g_fnt_mono_texture[offset_texture]);
            if(is_bold) Graphics_PutPixel(_x+7,_y+by+1,g_fnt_mono_texture[offset_texture]);
           }
           offset_texture++;
           getbyte = g_fnt_mono_char[offset];
           if ((getbyte&1)!=0) 
           {
            Graphics_PutPixel(_x+7,_y+by,g_fnt_mono_texture[offset_texture]);
            if(is_bold) Graphics_PutPixel(_x+8,_y+by+1,g_fnt_mono_texture[offset_texture]);
           }
           offset_texture++;
          }
         }
         else
         {
          for(by=0;by<FNT_MONO_CHAR_HEIGHT;by++,offset++)
          {
           getbyte = g_fnt_mono_char[offset];
           if ((getbyte&1)!=0) 
           {
            Graphics_PutPixel(_x,_y+by,g_fnt_mono_texture[offset_texture]);
            if(is_bold) Graphics_PutPixel(_x+7,_y+by+1,g_fnt_mono_texture[offset_texture]);
           }
           offset_texture++;
           getbyte = g_fnt_mono_char[offset];
           if ((getbyte&2)!=0) 
           { 
            Graphics_PutPixel(_x+1,_y+by,g_fnt_mono_texture[offset_texture]);
            if(is_bold) Graphics_PutPixel(_x+7,_y+by+1,g_fnt_mono_texture[offset_texture]);
           }
           offset_texture++;
           getbyte = g_fnt_mono_char[offset];
           if ((getbyte&4)!=0) 
           { 
            Graphics_PutPixel(_x+2,_y+by,g_fnt_mono_texture[offset_texture]);
            if(is_bold) Graphics_PutPixel(_x+7,_y+by+1,g_fnt_mono_texture[offset_texture]);
           }
           offset_texture++;
           getbyte = g_fnt_mono_char[offset];
           if ((getbyte&8)!=0) 
           { 
            Graphics_PutPixel(_x+3,_y+by,g_fnt_mono_texture[offset_texture]);
            if(is_bold) Graphics_PutPixel(_x+7,_y+by+1,g_fnt_mono_texture[offset_texture]);
           }
           offset_texture++;
           getbyte = g_fnt_mono_char[offset];
           if ((getbyte&16)!=0) 
           { 
            Graphics_PutPixel(_x+4,_y+by,g_fnt_mono_texture[offset_texture]);
            if(is_bold) Graphics_PutPixel(_x+7,_y+by+1,g_fnt_mono_texture[offset_texture]);
           }
           offset_texture++;
           getbyte = g_fnt_mono_char[offset];
           if ((getbyte&32)!=0) 
           {
            Graphics_PutPixel(_x+5,_y+by,g_fnt_mono_texture[offset_texture]);
            if(is_bold) Graphics_PutPixel(_x+7,_y+by+1,g_fnt_mono_texture[offset_texture]);
           }
           offset_texture++;
           getbyte = g_fnt_mono_char[offset];
           if ((getbyte&64)!=0) 
           {
            Graphics_PutPixel(_x+6,_y+by,g_fnt_mono_texture[offset_texture]);
            if(is_bold) Graphics_PutPixel(_x+7,_y+by+1,g_fnt_mono_texture[offset_texture]);
           }
           offset_texture++;
           getbyte = g_fnt_mono_char[offset];
           if ((getbyte&128)!=0) 
           { 
            Graphics_PutPixel(_x+7,_y+by,g_fnt_mono_texture[offset_texture]);
            if(is_bold) Graphics_PutPixel(_x+7,_y+by+1,g_fnt_mono_texture[offset_texture]);
           }
           offset_texture++;
        
          }
        
        }
    }
