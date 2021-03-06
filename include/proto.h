#ifndef         _PROTO_H
#define         _PROTO_H


void    read_bmp_header(BMP_HEADER*, FILE*);
int     write_bmp(BMP_HEADER*, u8*, u8*);
void    write_bmp_header(BMP_HEADER*, FILE*);
void    print_header(BMP_HEADER*);

void    smooth_avr_k(u8**, int, int);
void    smooth_avr_filter(u8**, int, int);
void    smooth_median_filter(u8**, int, int);

void    sharp_laplacian(u8**, int, int);
void    sharp_hpass_filter(u8**, int, int);
void    sharp_ladder(u8**, int, int);
void    stretch(u8**, BMP_HEADER*, u8*, int, int);
void    rotate(u8**, BMP_HEADER*, u8*, int, int);
int	bilinear_interposition(u8**, float, float, int, int);

void    width_pad(int*);
void    calloc_buf(u8**, int, int);
void    free_buf(u8**, int, int);
int     write_bmp_calloc(u8**, u8*, int, int, BMP_HEADER*);

inline int image_proc(u8 **, u8 *, u8 *, int, int, BMP_HEADER *)
	__attribute__((__always_inline__));


#endif
