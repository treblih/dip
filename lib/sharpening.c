#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "const.h"
#include "type.h"
#include "proto.h"


void
sharp_laplacian(u8** index, int height, int width)
{
        int     i, j, trans;
        for (i = 1; i < height - 1; i++) {
                for (j = 1; j < width - 1; j++) {
                        trans = 0;
                        trans = ((int)index[i - 1][j] + (int)index[i][j - 1] + (int)index[i + 1][j] + \
                                 (int)index[i][j + 1] - 4 * (int)index[i][j]);
                        trans = trans < 0 ? abs(trans) : trans;
                        trans = trans > 255 ? 255 : trans;
                        index[i][j] = (u8)trans;
                }
        }
}

void
sharp_hpass_filter(u8** index, int height, int width)
{
        int     i, j, m, n, trans;
        for (i = 1; i < height - 1; i++) {
                for (j = 1; j < width - 1; j++) {

                        trans = 9 * (int)index[i][j];
                        for (m = -1; m < 2; m++) {
                                for (n = -1; n < 2; n++) {
                                        if (m || n) {
                                                trans -= (int)index[i + m][j + n];
                                        }
                                }
                        }
                        trans = trans < 0 ? abs(trans) : trans;
                        trans = trans > 255 ? 255 : trans;
                        index[i][j] = (u8)trans;
                }
        }
}

void
sharp_ladder(u8** index, int height, int width)
{
        int     i, j, trans;
        for (i = 1; i < height - 1; i++) {
                for (j = 1; j < width - 1; j++) {
                        trans = abs((int)index[i - 1][j - 1] - (int)index[i][j]) + abs((int)index[i - 1][j] - \
                                 (int)index[i][j - 1]) + 100;
                        trans = trans < 0 ? abs(trans) : trans;
                        trans = trans > 255 ? 255 : trans;
                        index[i][j] = (u8)trans;
                }
        }
}
