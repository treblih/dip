#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "const.h"
#include "type.h"
#include "proto.h"

void
smooth_avr_k(u8** index, int height, int width)
{
        int     i, j, k, m, n;
        int     total;
        K_AVR   trans;
        K_AVR   window[8];

        memset(window, 0, sizeof(K_AVR) << 3);
        memset(&trans, 0, sizeof(K_AVR));

	/* ignore the y-profiles */
        for (i = 1; i < height - 1; i++) {
		/* ignore the x-profiles */
                for (j = 1; j < width - 1; j++) {
                        k = 0;
                        total = 0;
                        memset(&trans, 0, sizeof(K_AVR));
                        for (m = -1; m < 2; m++) {
                                for (n = -1; n < 2; n++) {
                                        if (m || n) {
                                                window[k].val = index[i + m][j + n];
                                                window[k++].abs = abs( \
							index[i + m][j + n] - index[i][j]);
                                        }
                                }
                        }

			/*
			 * the FOR loop is a Buble-Sort, which just executes 2 times here
			 * to find the smallest 6 from 8
			 */
                        for (m = 0; m < 2; m++) {
                                /* now k = 9, not 8, so can't "n < k - 1 - m" */
                                for (n = 0; n < 8 - 1 - m; n++) {
                                        if (window[n].abs > window[n + 1].abs) {
                                                trans = window[n];
                                                window[n] = window[n + 1];
                                                window[n + 1] = trans;
                                        }
                                }
			}

			/* total of the nearest-6 */
                        for (m = 0; m < 6; m++) {
                                total  += (int)window[m].val;
                        }

			/* center-pixel-new = (center-pixel + nearest-6) / 7 */
                        index[i][j] = (total = (total + (int)index[i][j]) / 7) > 255 ? 255 : total;
                }
        }
}


void
smooth_avr_filter(u8** index, int height, int width)
{
        int     i, j, m, n;
        int     total;

        for (i = 1; i < height - 1; i++) {
                for (j = 1; j < width - 1; j++) {
                        total = 0;
                        for (m = -1; m < 2; m++) {
                                for (n = -1; n < 2; n++) {
                                        total += index[i + m][j + n];
                                }
                        }
                        index[i][j] = (total /= 9) > 255 ? 255 : total;
                }
        }
}

void
smooth_median_filter(u8** index, int height, int width)
{
        int     i, j, k, m, n, trans;
        int     total[9];

        for (i = 1; i < height - 1; i++) {
                for (j = 1; j < width - 1; j++) {
                        k = 0;
                        for (m = -1; m < 2; m++) {
                                for (n = -1; n < 2; n++) {
                                        total[k++] = index[i + m][j + n];
                                }
                        }

                        for (m = 0; m < 5; m++) {
                                for (n = 0; n < 9 - 1 - m; n++) {
                                        if (total[n] > total[n + 1]) {
                                                trans = total[n];
                                                total[n] = total[n + 1];
                                                total[n + 1] = trans;
                                        }
                                }
                        }
                        index[i][j] = total[4];
                }
        }
}
