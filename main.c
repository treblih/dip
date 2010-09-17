#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "const.h"
#include "type.h"
#include "proto.h"


/* take STDIN under my control */
/*
 * it can't b a local-var
 * 'cause can't b destroyed with MAIN func
 */
char buf_input[BUFSIZ];
char *bp = buf_input;

int main(int argc, char *argv[])
{
	/* Line-Buf */
	setvbuf(stdin, buf_input, _IOLBF, BUFSIZ);

	int i;
	if (argc != 2) {
		printf("\nUSEAGE: \"dip + your_pic_name\" TRY AGIAN !\n\n");
		exit(EXIT_FAILURE);
	}

	char in_name[16] = { 0 };
	strcpy(in_name, argv[1]);

	BMP_HEADER *p_header = calloc(BMP_HEADER_SIZE, sizeof(u8));

	FILE *fd = fopen(in_name, "rb");
	if (!fd) {
		printf("\nread failure!\n");
		exit(EXIT_FAILURE);
	}

	read_bmp_header(p_header, fd);

	int color_len = p_header->bm_offset - BMP_HEADER_SIZE;
	int image_len = p_header->file_size - p_header->bm_offset;
	int width = p_header->width;
	int height = p_header->height;
	u8 color_buf[color_len];
	u8 image_buf[image_len];
	u8 *index[height];

	fread(color_buf, color_len, 1, fd);
	fread(image_buf, image_len, 1, fd);
	fclose(fd);

	/* pointer-array, namely 2D array */
	for (i = 0; i < height; i++) {
		index[i] = &image_buf[i * width];
	}

	print_header(p_header);

	image_proc(index, image_buf, color_buf, width, height, p_header);

	/* printf("addr: %x\n", &((BMP_HEADER *)0)); */
	/* can not arrive here */
	return 0;
}

inline int
image_proc(u8 ** index, u8 * image_buf, u8 * color_buf, int width,
	   int height, BMP_HEADER * p_header)
{
	char interact = 0;
	int char_test = 0;

	while (1) {
		printf("\n\nDIP has already held your image, what's next?\n"
		       "type:\n"
		       "[s] -> smooth\n"
		       "[h] -> sharp\n"
		       "[l] -> enlarge / shrink\n"
		       "[r] -> rotate\n" "[e] -> exit\n\n");
		while ((char_test = getchar()) != '\n' && char_test != EOF) {
			interact = char_test;

			/* 
			 * so significant here
			 * we need just a char, if user inputs such as 'sel',
			 * so the final char which installed in the var is
			 * 'l', not 's'
			 */
			while ((char_test = getchar()) != '\n'
			       && char_test != EOF) ;
			break;
		}

		switch (interact) {
		case 's':
			printf("which algorithm u wanna use?\n"
			       "type:\n"
			       "[k] -> k_near_average\n"
			       "[a] -> average_filter \t[1, 1, 1, 1, 1, 1, 1, 1, 1]\n"
			       "[m] -> median_filter\n");
			__asm__ __volatile__("2:");
			while ((char_test = getchar()) != '\n'
			       && char_test != EOF) {
				interact = char_test;
				while ((char_test = getchar()) != '\n'
				       && char_test != EOF) ;
				break;
			}

			switch (interact) {
			case 'k':
				smooth_avr_k(index, height, width);
				break;
			case 'a':
				smooth_avr_filter(index, height, width);
				break;
			case 'm':
				smooth_median_filter(index, height, width);
				break;
			default:
				printf("\nhey bro, type \"k\" or \"9\"\n");
				__asm__ __volatile__("jmp 2b");
				break;
			}
			if (write_bmp(p_header, color_buf, image_buf)) {
				printf("Sorry, Failure!\n");
			}
			printf("Well Done!\n");
			break;
		case 'h':
			printf("which algorithm u wanna use?\n"
			       "type:\n"
			       "[l] -> laplacian \t[0, 1, 0; 1, -4, 1; 0, 1, 0]\n"
			       "[f] -> high pass filter [-1, -1, -1; -1, 9, -1; -1, -1, -1]\n"
			       "[a] -> ladder \t\t[-1, 1; -1, 1]\n");
			__asm__ __volatile__("3:");
			while ((char_test = getchar()) != '\n'
			       && char_test != EOF) {
				interact = char_test;
				while ((char_test = getchar()) != '\n'
				       && char_test != EOF) ;
				break;
			}

			switch (interact) {
			case 'a':
				sharp_ladder(index, height, width);
				break;
			case 'l':
				sharp_laplacian(index, height, width);
				break;
			case 'f':
				sharp_hpass_filter(index, height, width);
				break;
			default:
				printf("\nhey bro, type \"l\" or \"f\"\n");
				__asm__ __volatile__("jmp 3b");
				break;
			}
			if (write_bmp(p_header, color_buf, image_buf)) {
				printf("Sorry, Failure!\n");
			}
			printf("Well Done!\n");
			break;
		case 'l':
			stretch(index, p_header, color_buf, width, height);
			break;
		case 'r':
			rotate(index, p_header, color_buf, width, height);
			break;
		case 'e':
			{
				int i = 0;
				for (; i < 10; i++) {
					printf("%x %c\n", *bp, *bp);
					bp++;
				}
				free(p_header);
				/* to avoid accessing freed memory */
				p_header = NULL;
			}
			return 0;
		default:
			printf("\nHey bro, please follow the rule\n");
			break;
		}
	}
}
