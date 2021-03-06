#ifndef         _TYPE_H
#define         _TYPE_H


typedef         unsigned char           u8;
typedef         unsigned short          u16;
typedef         unsigned int            u32;

typedef struct {
   u16      file_type;
   u32      file_size;
   int      reserved;
   u32      bm_offset;

   u32      bminfo_size;
   int      width;
   int      height;
   u16      planes;
   u16      bits_per_pixel;
   u32      compress;
   u32      bm_size;
   u32      horzres;
   u32      vertres;
   u32      color_used;
   u32      color_imp;
} BMP_HEADER;


#if 0
typedef struct {
        BMP_HEADER      header;
        char            color_buf[0];
} BMP;
#endif

typedef struct {
        u8      val;
        u8      abs;
} K_AVR;


#endif
