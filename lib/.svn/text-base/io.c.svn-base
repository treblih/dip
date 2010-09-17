#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "const.h"
#include "type.h"
#include "proto.h"

void
read_bmp_header(BMP_HEADER* p_header, FILE* fd)
{
        fread(&p_header->file_type,           2, 1, fd);
        fread(&p_header->file_size,           4, 1, fd);
        fread(&p_header->reserved,            4, 1, fd);
        fread(&p_header->bm_offset,           4, 1, fd);
        fread(&p_header->bminfo_size,         4, 1, fd);
        fread(&p_header->width,               4, 1, fd);
        fread(&p_header->height,              4, 1, fd);
        fread(&p_header->planes,              2, 1, fd);
        fread(&p_header->bits_per_pixel,      2, 1, fd);
        fread(&p_header->compress,            4, 1, fd);
        fread(&p_header->bm_size,             4, 1, fd);
        fread(&p_header->horzres,             4, 1, fd);
        fread(&p_header->vertres,             4, 1, fd);
        fread(&p_header->color_used,          4, 1, fd);
        fread(&p_header->color_imp,           4, 1, fd);
}

int
write_bmp(BMP_HEADER* p_header, u8* color_buf, u8* image_buf)
{
        getchar();
        char    out_name[16] = {0};
        printf("\n\n\nI have done as u said\ngive a name to the image output(15 chars max)\n");
        scanf("%s", out_name);

        FILE*                   fd              = fopen(out_name, "wb");
        if (!fd) {
                printf("write failure!\n");
                return -1;
        }

        write_bmp_header(p_header, fd);

        int             color_len         = p_header->bm_offset - BMP_HEADER_SIZE;
        int             image_len         = p_header->file_size - p_header->bm_offset;
        fwrite(color_buf, color_len, 1, fd);
        fwrite(image_buf, image_len, 1, fd);
        fclose(fd);

        return 0;
}

void
write_bmp_header(BMP_HEADER* p_header, FILE* fd)
{
        fwrite(&p_header->file_type,           2, 1, fd);
        fwrite(&p_header->file_size,           4, 1, fd);
        fwrite(&p_header->reserved,            4, 1, fd);
        fwrite(&p_header->bm_offset,           4, 1, fd);
        fwrite(&p_header->bminfo_size,         4, 1, fd);
        fwrite(&p_header->width,               4, 1, fd);
        fwrite(&p_header->height,              4, 1, fd);
        fwrite(&p_header->planes,              2, 1, fd);
        fwrite(&p_header->bits_per_pixel,      2, 1, fd);
        fwrite(&p_header->compress,            4, 1, fd);
        fwrite(&p_header->bm_size,             4, 1, fd);
        fwrite(&p_header->horzres,             4, 1, fd);
        fwrite(&p_header->vertres,             4, 1, fd);
        fwrite(&p_header->color_used,          4, 1, fd);
        fwrite(&p_header->color_imp,           4, 1, fd);
}

void
print_header(BMP_HEADER* p_header)
{
        printf("\nyour BMP file info:\n\n");
        printf("file_type: \t0x%x\n", p_header->file_type);
        printf("file_size: \t0x%x\n", p_header->file_size);
        printf("bm_offset: \t0x%x\n", p_header->bm_offset);
        printf("bminfo_size \t0x%x\n\n", p_header->bminfo_size);
        printf("width \t\t0x%x\n", p_header->width);
        printf("height \t\t0x%x\n", p_header->height);
        printf("planes \t\t0x%x\n", p_header->planes);
        printf("bits_per_pixel \t0x%x\n", p_header->bits_per_pixel);
        printf("compress \t0x%x\n", p_header->compress);
        printf("bm_size \t0x%x\n", p_header->bm_size);
        printf("colorsused \t0x%x\n", p_header->color_used);
        printf("colorsimp \t0x%x\n", p_header->color_imp);

#if 0
        printf("\nwidth * height: 0x%x\n", p_header->width * p_header->height);
        printf("width * height: %d\n", p_header->width * p_header->height);
        printf("width-Dec: \t%d\n", p_header->width);
        printf("height-Dec: \t%d\n", p_header->height);
        printf("bm_size \t%d\n", p_header->bm_size);
        printf("file_size: \t%d\n", p_header->file_size);
#endif
}

int
write_bmp_calloc(u8** image, u8* color_buf, int width, int height, BMP_HEADER* p_header)
{
	int		char_test;
        BMP_HEADER      header;
        memcpy(&header, p_header, BMP_HEADER_SIZE);
        p_header                =       &header;

        int  i;
        int  color_len          =        p_header->bm_offset - BMP_HEADER_SIZE;
        p_header->bm_size       =        width * height;
        p_header->width         =        width;
        p_header->height        =        height;
        p_header->file_size     =        p_header->bm_size + p_header->bm_offset;

        char    out_name[16] = {0};
        printf("\n\n\nI have done as u said\ngive a name to the image output(15 chars max)\n");
        scanf("%s", out_name);
	while ((char_test = getchar()) != '\n' && char_test != EOF) ; /* essential ';' */

        FILE*  fd              =        fopen(out_name, "wb");
        if (!fd) {
                printf("Write Failure!\n");
                return -1;
        }

        write_bmp_header(p_header, fd);
        fwrite(color_buf, color_len, 1, fd);
        for (i = 0; i < height; i++) {
                fwrite(image[i], width, 1, fd);
        }
        fclose(fd);

        return 0;
}

void
width_pad(int* width)
{
        int     rem;

        /* BMP's width should MOD 4 == 0, other wise we fill it ourselves */
        if ((rem = *width % 4)) {
                *width       =       *width + 4 - rem;
        }
}

void
calloc_buf(u8** image, int width, int height)
{
        int     i       =       0;
        for (; i < height; i++) {
                image[i]       =       (u8*)calloc(width, sizeof (u8));
                if (image[i] == NULL) {
                        printf("Calloc Failure!\n");
                        exit(EXIT_FAILURE);
                }
        }
}

void
free_buf(u8** image, int width, int height)
{
        int     i       =       0;
        for (; i < height; i++) {
                free(image[i]);
        }
}
