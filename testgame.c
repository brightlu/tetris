#include "sense.h"
#include <string.h>
#include <stdlib.h>
#include "piece.h"
#include "outputtest.h"
#include <stdio.h>

void draw_piece(piece *p, pi_framebuffer_t *dev) {

        if (p->type == 0) {
                display_dot(dev, p->xpos, p->ypos);
        } else if (p->type == 1) {
                //ddisplay twoddots
        }
}


int main(void) {

        pi_framebuffer_t *dev = getFBDevice();

        int moved = 0;

        piece *first = NULL;
        first = malloc(sizeof(piece));

        first->xpos = 1;
        first->ypos = 1;
        first->type = 0;

        draw_piece(first, dev);

        int integer;

        while (moved == 0) {

                int result = scanf("%d", &integer);

                if (result > 0) {
                        clearBitmap(dev->bitmap, 0);
                        first = move_piece_down(first);
                        moved = 1;
                        draw_piece(first, dev);
                }
        }
}
