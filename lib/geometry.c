#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "const.h"
#include "type.h"
#include "proto.h"
#include "global.h"



void
stretch(u8** image, BMP_HEADER* p_header, u8* color_buf, int width, int height)
{
	char	flag_bilinear, char_test;
        int     i, j;
        float   x_ratio, y_ratio, x, y;
        printf("Give a float ratio to X-stretch (must > 0)\n");

	/* 
	 * no matter whether it's a '\n' in input-buf, SCANF ignores it
	 * except SCANF needs %c
	 */
	scanf("%f", &x_ratio);
	/* eat the '\n' which user has typed follow a useful num */
	while ((char_test = getchar()) != '\n' && char_test != EOF) ;

        printf("Give a float ratio to Y-stretch (must > 0)\n");
	scanf("%f", &y_ratio);
	while ((char_test = getchar()) != '\n' && char_test != EOF) ;

        printf("Choose one algorithm\n"
		"[a] -> adjacent pixel\n"
		"[b] -> bilinear interposition\n");
	__asm__ __volatile__("4:");
	while ((char_test = getchar()) != '\n' && char_test != EOF) {
		flag_bilinear = char_test;

		/* not *++bp, bp is a global-var */
		*bp	 = '\n';
	}

	/* algorithm bilinear-interposition */
	switch (flag_bilinear) {
		case 'b':
			flag_bilinear = 1;
			break;
		case 'a':
			flag_bilinear = 0;
			break;
		default:
			printf("Hey bro, type 'a' or 'b'\n");
			__asm__ __volatile__("jmp 4b");
			break;
	}

        int     width_new   =       (int)(width * x_ratio);
        int     height_new  =       (int)(height * y_ratio);
        u8*     image_new[height_new];

        width_pad(&width_new);

        calloc_buf(image_new, width_new, height_new);

	if (!flag_bilinear) {
		int x_int, y_int;
		for (i = 0; i < height_new; i++) {
			y_int	=	(int)((float)i / y_ratio);
			for (j = 0; j < width_new; j++) {
				x_int	=	(int)((float)j / x_ratio);
				if (x_int >= width)
					/* why minus 1? see below */
					x_int = width - 1;
				if (y_int >= height)
					y_int = height - 1;
				/* here is the answer */
				image_new[i][j] =       image[y_int][x_int];
			}
		}
	}
	else {
		for (i = 0; i < height_new; i++) {
			y       =       ((float)i / y_ratio);
			for (j = 0; j < width_new; j++) {
				x       =       ((float)j / x_ratio);
				if ((int)x >= width)
					/* the same reason here */
					x = width - 1;
				if ((int)y >= height)
					y = height - 1;
				/* the same answer here */
				image_new[i][j] = x - floor(x) || y - floor(y) ? \
						  bilinear_interposition(image, x, y, width, height) : \
						  image[(int)y][(int)x];
			}
		}
	}

        if (write_bmp_calloc(image_new, color_buf, width_new, height_new, p_header)) {
                printf("Sorry, Stretch Failure!\n");
                exit(EXIT_FAILURE);
        }

        free_buf(image_new, width_new, height_new);
        printf("\nStretch Done!\tWhat's more?\n");
}

void
rotate(u8** image, BMP_HEADER* p_header, u8* color_buf, int width, int height)
{
	char	char_test;
        int     i, j, flag_rotate;
        float   angle, x, y;

        printf("Give a rotate angle (whatever >0 or <0)\n");
	scanf("%f", &angle);
	while ((char_test = getchar()) != '\n' && char_test != EOF) ;

        printf("Choose one algorithm\n"
		"[a] -> adjacent pixel\n"
		"[b] -> bilinear interposition\n");
	__asm__ __volatile__("5:");
	while ((char_test = getchar()) != '\n' && char_test != EOF) {
		flag_rotate = char_test;

		/* not *++bp, bp is a global-var */
		*bp	 = '\n';
	}

	switch (flag_rotate) {
		case 'b':
			flag_rotate = 1;
			break;
		case 'a':
			flag_rotate = 0;
			break;
		default:
			printf("Hey bro, type 'a' or 'b'\n");
			__asm__ __volatile__("jmp 5b");
			break;
	}

        float   radian  =       RADIAN(angle);
        float   sina    =       sin(radian);
        float   cosa    =       cos(radian);

	/* 
	 * y	Original Image -- regard (x1, y1) as (0, 0)
	 *
	 * ^
	 * |
	 * |
	 * |
	 * |
	 * |(x2, y2)			      (x4, y4)
	 * ..................................
	 * .				    .
	 * .				    .
	 * .				    .
	 * .				    .
	 * .				    .
	 * .(x1, y1) -- axis		    . (x3, y3)
	 * ..................................----------> x */

	/* after anti-clock-wise rotation */
        float   x1      =       0;
        float   x2      =       0 - height * sina;
        float   x3      =       0 + width * cosa;
        float   x4      =       0 + width * cosa - height * sina;

        float   y1      =       0;
        float   y2      =       0 + height * cosa;
        float   y3      =       0 + width * sina;
        float   y4      =       0 + width * sina + height * cosa;

	/* 
	 * make sure that the image always locate 
	 * in active-x-axis'n active-y-axis
	 * so we need to know how far they get away
	 */
        float   x_offset =      MAX(MAX(-x2, -x3), -x4);
        float   y_offset =      MAX(MAX(-y2, -y3), -y4);
        x_offset        =       x_offset > 0 ? x_offset : 0;
        y_offset        =       y_offset > 0 ? y_offset : 0;

        int     width_new       =       ceil(MAX(fabs(x1 - x4), fabs(x2 - x3)));
        int     height_new      =       ceil(MAX(fabs(y1 - y4), fabs(y2 - y3)));

        u8*     image_new[height_new];

	/* fill up */
        width_pad(&width_new);

	/* everything for making a new image has done, now calloc */
        calloc_buf(image_new, width_new, height_new);

	/* control every pixels in image new, not image original */
        for (i = 0; i < height_new; i++) {
                for (j = 0; j < width_new; j++) {
			/* it's image new here, so clock-wise */
                        x       =       (  (j - x_offset) * cosa + (i - y_offset) * sina);
                        y       =       (- (j - x_offset) * sina + (i - y_offset) * cosa);

			/* 
			 * if the pixel in image new has the corresponding pixel in
			 * image original, we evaluate it, other wise, next one
			 */
			/* no equals */
			if (y >= 0 && y < height && x >= 0 && x < width) {
				image_new[i][j] = flag_rotate ? \
						  bilinear_interposition(image, x, y, width, height) : \
						  image[(int)y][(int)x];
			}
                }
        }

        if (write_bmp_calloc(image_new, color_buf, width_new, height_new, p_header)) {
                printf("Sorry, Failure!\n");
                exit(EXIT_FAILURE);
        }

        free_buf(image_new, width_new, height_new);
        printf("\nRotate Done!\tWhat's more?\n");
}

int
bilinear_interposition(u8** image, float x, float y, int width, int height)
{
	int	x_floor		=	floor(x);
	int	y_floor		=	floor(y);
	int	x_ceil		=	ceil(x);
	int	y_ceil		=	ceil(y);
	float	x_fraction	=	x - floor(x);
	float	y_fraction	=	y - floor(y);

	if (x_floor < 0)
		x_floor	= 0;
	if (y_floor < 0)
		y_floor	= 0;

	/*
	 * assume that width == 256, x == 255.5
	 * => x_ceil == 256
	 * assert *_ceil < width/height
	 */
	if (x_ceil >= width)
		x_ceil	= width - 1;
	if (y_ceil >= height)
		y_ceil	= height - 1;


	/* assert *_ceil < width/height */
	return (int)
	       (image[y_floor][x_floor] * (1 - x_fraction) * (1 - y_fraction) + \
		image[y_floor][x_ceil]  * (1 - x_fraction) * (y_fraction)     + \
		image[y_ceil][x_floor]  * (x_fraction)     * (1 - y_fraction) + \
		image[y_ceil][x_ceil]   * (x_fraction)     * (y_fraction));
	/* don't b worried, it's just a fomula, not too difficult */
}
