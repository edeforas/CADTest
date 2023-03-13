#ifndef _Color_
#define _Color_

#define PIXELRGB(r,g,b) ((r<<16)+(g<<8)+b)

#define BLUE PIXELRGB(0xff,0,0)
#define GREEN PIXELRGB(0,0xff,0)
#define RED PIXELRGB(0,0,0xff)
#define BLACK PIXELRGB(0x0,0x0,0x0)
#define WHITE PIXELRGB(0xff,0xff,0xff)

#define GREY PIXELRGB(0x80,0x80,0x80)
#define DARK_GREY PIXELRGB(0x20,0x20,0x20)

#define DARK_GREEN PIXELRGB(0x20,0x80,0x20)

#define NOCOLOR (0xffffffff) //-1

#endif
