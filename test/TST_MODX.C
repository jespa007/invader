/* tst_modx.c - Minimal Mode X graphics API + test
 *
 * Target: MS-DOS real mode, Turbo C/Borland C.
 * Mode: Mode X 320x240x256 (planar), 64KB window.
 *
 * Build (Turbo C):  tcc -mc modex_min.c
 */

#include <dos.h>
#include <mem.h>
#include <stdlib.h>
#include <conio.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long  u32;

#define VGA_SEG 0xA000
static u8 far* const VGA = (u8 far*)MK_FP(VGA_SEG, 0);

#define SC_INDEX  0x3C4
#define SC_DATA   0x3C5
#define GC_INDEX  0x3CE
#define GC_DATA   0x3CF
#define CRTC_INDEX 0x3D4
#define CRTC_DATA  0x3D5
#define MISC_OUT   0x3C2
#define INPUT_STATUS_1 0x3DA
#define OUTP(p,v) ((void)outp((p),(v)))


static int g_scrollX = 0;
static int g_scrollY = 0;

/* ---------- Low-level port helpers ---------- */
static void outw_(u16 port, u16 value) {
  OUTP(port, value & 0xFF);
  OUTP(port + 1, value >> 8);
}
static void wait_vsync(void) {
  /* wait for not in vblank */
  while (inp(INPUT_STATUS_1) & 8) { }
  /* wait for vblank */
  while (!(inp(INPUT_STATUS_1) & 8)) { }
}

/* ---------- Mode setting ---------- */

/* Enter BIOS mode 13h first (320x200x256), then tweak to Mode X 320x240 */
static void bios_set_mode(u8 mode) {
  union REGS r;
  r.h.ah = 0x00;
  r.h.al = mode;
  int86(0x10, &r, &r);
}

static void modeX_set(void)
{
    bios_set_mode(0x13);

    /* turn off chain-4 */
    OUTP(SC_INDEX, 0x04);
    OUTP(SC_DATA,  0x06);

    /* enable all planes */
    OUTP(SC_INDEX, 0x02);
    OUTP(SC_DATA,  0x0F);

    /* graphics controller */
    OUTP(GC_INDEX, 0x05);
    OUTP(GC_DATA,  0x40);
    OUTP(GC_INDEX, 0x06);
    OUTP(GC_DATA,  0x05);

    /* unprotect CRTC */
    OUTP(CRTC_INDEX, 0x11);
    OUTP(CRTC_DATA,  INP(CRTC_DATA) & 0x7F);

    /* logical width = 320 pixels => 80 bytes */
    OUTP(CRTC_INDEX, 0x13);
    OUTP(CRTC_DATA,  80);

    /* byte mode */
    OUTP(CRTC_INDEX, 0x14);
    OUTP(CRTC_DATA,  INP(CRTC_DATA) | 0x40);

    g_scrollX = 0;
    g_scrollY = 0;
}


/* Back to text mode */
static void modeX_text(void) {
  bios_set_mode(0x03);
}

/* ---------- Mode X primitives ---------- */

/* Select which plane(s) to write (0..3 => 1<<plane) */
static void set_plane_mask(u8 mask) {
  OUTP(SC_INDEX, 0x02);
  OUTP(SC_DATA,  mask);
}

/* Set CRTC start address (in words) + fine horizontal panning (0..7) */
static void modeX_setScroll(int x, int y) {
  /* x,y in pixels for the “world” offset */
  int start;
  int fine = x & 7;          /* fine pan: 0..7 */
  int byteX = x >> 2;        /* 4 pixels per byte across planes => /4 */
  int byteY = y * 80;        /* 80 bytes per scanline (per plane) */
  int addr  = byteY + byteX; /* byte address into planar memory */

  /* CRTC start address uses WORD address => /2 */
  start = addr >> 1;

  g_scrollX = x;
  g_scrollY = y;

  /* Start Address High/Low */
  OUTP(CRTC_INDEX, 0x0C); OUTP(CRTC_DATA, (start >> 8) & 0xFF);
  OUTP(CRTC_INDEX, 0x0D); OUTP(CRTC_DATA, (start     ) & 0xFF);

  /* Horizontal Panning (Attribute Controller index 0x13) */
  /* Read input status to reset flip-flop */
  (void)inp(INPUT_STATUS_1);
  OUTP(0x3C0, 0x13);
  OUTP(0x3C0, fine);
  OUTP(0x3C0, 0x20); /* enable display */
}

/* Clear screen to a color (full 320x240) */
static void modeX_clear(u8 color) {
  int plane;
  u16 offset;
  /* Each plane stores 320x240/4 = 19200 bytes */
  for (plane = 0; plane < 4; plane++) {
    set_plane_mask(1 << plane);
    _fmemset(VGA, color, 19200);
  }
  set_plane_mask(0x0F);
}

/* Plot pixel (slow; for debugging only) */
static void modeX_putPixel(int x, int y, u8 color) {
  u16 off = (u16)(y * 80 + (x >> 2));
  u8  plane = (u8)(x & 3);
  set_plane_mask(1 << plane);
  VGA[off] = color;
  set_plane_mask(0x0F);
}

/* Draw solid filled rectangle */
static void modeX_drawBlock(int x, int y, int w, int h, u8 color) {
  int yy, plane;
  for (plane = 0; plane < 4; plane++) {
    set_plane_mask(1 << plane);
    for (yy = 0; yy < h; yy++) {
      int px = x + plane; /* only pixels matching this plane */
      //int len = w;
      u16 off = 0;
      int countPixels = 0;

      if (px < x) px += 4;
      if (px >= x + w) continue;

      /* first byte index for this scanline */
      off = (u16)((y + yy) * 80 + (px >> 2));

      /* number of pixels for this plane = ceil((w - (px-x))/4) */
      countPixels = (w - (px - x) + 3) >> 2; /* /4 rounded up */
      /* countPixels bytes correspond 1 byte each for this plane */
      _fmemset(VGA + off, color, countPixels);
    }
  }
  set_plane_mask(0x0F);
}

/* Draw masked sprite (w,h) where:
   - src is 1 byte per pixel (color)
   - mask is 1 byte per pixel (0=transparent, 1=draw)
   This is not the fastest possible but is clean and works.
*/
static void modeX_drawSpriteMasked(int x, int y, int w, int h,
                                  const u8* src, const u8* mask) {
  int yy, xx;
  for (yy = 0; yy < h; yy++) {
    int sy = y + yy;
    for (xx = 0; xx < w; xx++) {
      int sx = x + xx;
      if (mask[yy * w + xx]) {
        u16 off = (u16)(sy * 80 + (sx >> 2));
        u8 plane = (u8)(sx & 3);
        set_plane_mask(1 << plane);
        VGA[off] = src[yy * w + xx];
      }
    }
  }
  set_plane_mask(0x0F);
}

/* ---------- Save/restore region ---------- */

typedef struct {
  int w, h;
  /* Planar storage: plane0 bytes, then plane1, plane2, plane3.
     Each plane needs ceil(w/4) bytes per scanline. */
  u8* data;
} ModeXRegion;

/* bytes per scanline per plane for a given width */
static int region_pitch(int w) {
  return (w + 3) >> 2; /* ceil(w/4) */
}

static ModeXRegion* modeX_createRegion(int w, int h) {
  ModeXRegion* r = (ModeXRegion*)malloc(sizeof(ModeXRegion));
  int pitch = region_pitch(w);
  int planeBytes = pitch * h;
  r->w = w; r->h = h;
  r->data = (u8*)malloc(planeBytes * 4);
  return r;
}

static void modeX_freeRegion(ModeXRegion* r) {
  if (!r) return;
  if (r->data) free(r->data);
  free(r);
}

/* Read VRAM region into buffer */
static void modeX_saveRegion(int x, int y, ModeXRegion* r) {
  int pitch = region_pitch(r->w);
  int plane, yy;
  for (plane = 0; plane < 4; plane++) {
    u8* dst = r->data + plane * (pitch * r->h);
    for (yy = 0; yy < r->h; yy++) {
      int sy = y + yy;
      /* For each plane, the byte offset uses x>>2, but we must align x to plane.
         We capture bytes starting at floor(x/4). */
      u16 off = (u16)(sy * 80 + (x >> 2));
      /* Set read map select */
      OUTP(GC_INDEX, 0x04);
      OUTP(GC_DATA,  plane);
      _fmemcpy(dst + yy * pitch, VGA + off, pitch);
    }
  }
}

/* Write region buffer back to VRAM */
static void modeX_restoreRegion(int x, int y, const ModeXRegion* r) {
  int pitch = region_pitch(r->w);
  int plane, yy;
  for (plane = 0; plane < 4; plane++) {
    const u8* src = r->data + plane * (pitch * r->h);
    set_plane_mask(1 << plane);
    for (yy = 0; yy < r->h; yy++) {
      int sy = y + yy;
      u16 off = (u16)(sy * 80 + (x >> 2));
      _fmemcpy(VGA + off, src + yy * pitch, pitch);
    }
  }
  set_plane_mask(0x0F);
}

/* ---------- Simple demo data ---------- */

static void make_test_sprite(u8* src, u8* m, int w, int h, u8 baseColor) {
  int x, y;
  for (y = 0; y < h; y++) for (x = 0; x < w; x++) {
    int dx = x - w/2;
    int dy = y - h/2;
    int r2 = dx*dx + dy*dy;
    if (r2 <= (w*w)/6) {
      m[y*w+x] = 1;
      src[y*w+x] = baseColor + (u8)((x + y) & 15);
    } else {
      m[y*w+x] = 0;
      src[y*w+x] = 0;
    }
  }
}

/* ---------- Bonus test ---------- */

int main(void)
{
	modeX_set();
	modeX_setScroll(0,0);
	modeX_clear(12); /* bright color */
	
	getch();
    modeX_text();
    
    return 0;
}

int main_old(void) {
  const int SW = 320, SH = 240;
  int t = 0;

  /* sprite */
  const int SPW = 32, SPH = 32;
  u8* spr  = (u8*)malloc(SPW * SPH);
  u8* mask = (u8*)malloc(SPW * SPH);
  ModeXRegion * back = NULL;
  make_test_sprite(spr, mask, SPW, SPH, 40);

  /* region for save/restore behind sprite */
  back = modeX_createRegion(SPW, SPH);

  modeX_set();
  modeX_clear(0);

  /* draw some static “world” blocks bigger than screen area
     We’ll fake a world by redrawing blocks at shifted positions occasionally.
     In a real game, you’d have a tilemap and render edges.
  */
  while (!kbhit()) {
    int scrollX = (t * 1) & 255;      /* 0..255 */
    int scrollY = (t * 1) & 127;      /* 0..127 */

    /* Smooth scroll: do during vblank to reduce tearing */
    wait_vsync();
    modeX_setScroll(scrollX, scrollY);

    /* Occasionally refresh background pattern (cheap fake “map”) */
    if ((t & 31) == 0) {
      /* clear full screen (if you want true scrolling without full redraw,
         you’d draw only newly revealed columns/rows instead) */
      modeX_clear(0);

      /* big blocks pattern */
      modeX_drawBlock(10, 10, 120, 40, 10);
      modeX_drawBlock(180, 30, 90, 60, 20);
      modeX_drawBlock(60, 120, 200, 30, 30);
      modeX_drawBlock(20, 190, 70, 40, 12);

      /* some stripes */
      modeX_drawBlock(0, 0, 320, 2, 15);
      modeX_drawBlock(0, 238, 320, 2, 15);
    }

    /* moving sprite position in screen coordinates */
    {
      int sx = (SW/2 - SPW/2) + (int)( (t & 63) - 32 );
      int sy = (SH/2 - SPH/2) + (int)( ((t>>1) & 63) - 32 );

      /* Save background under sprite, draw sprite, then restore previous sprite area:
         For correct restore, we need to restore *last frame* position.
         We'll track last position and restore it before saving new one. */
      static int lastx = -1, lasty = -1;
      static int first = 1;

      if (!first) {
        modeX_restoreRegion(lastx, lasty, back);
      } else {
        first = 0;
      }

      modeX_saveRegion(sx, sy, back);
      modeX_drawSpriteMasked(sx, sy, SPW, SPH, spr, mask);

      lastx = sx;
      lasty = sy;
    }

    t++;
  }

  getch(); /* consume key */
  modeX_text();

  modeX_freeRegion(back);
  free(spr);
  free(mask);
  return 0;
}

