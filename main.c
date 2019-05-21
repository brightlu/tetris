#include "sense.h"
#include <string.h>
#include <stdlib.h>
#include "project.h"
//#include "piece.h"
//#include "outputtest.h"
#include <stdio.h>
#include <time.h>
#include <linux/input.h>

int running=1;
pi_i2c_t* gyro=NULL;
int pressed = 0;
int right = 0;
int left = 0;

piece *first = NULL;
piece *second = NULL;

void callbackFunc(unsigned int code) {
  printf("code: %u\t",code);

  if(code == KEY_UP) {
    printf("can't move piece up");
    }else if(code == KEY_DOWN) {
      printf("move piece down");
    }else if(code == KEY_RIGHT) {
      printf("move piece right");
      right = 1;
    }else if(code == KEY_LEFT) {
      printf("move piece left");
      left = 1;
    }else if(code == KEY_ENTER) {
      printf("quit");
      running=0;
      free(first);
      //free(second);
    }
    printf("\n");
}

int main(void) {

        pi_framebuffer_t *dev = getFBDevice();
        pi_joystick_t *joystick = getJoystickDevice();
        gyro = geti2cDevice();
        configureAccelGyro(gyro);
        coordinate_t data;
        pixel *lp = NULL;

        int moved = 0;
        srand48(time(NULL));

        first = malloc(sizeof(piece));
        //second = malloc(sizeof(piece));

        int choice;
        choice = (int)(drand48() * 6);
        if (choice == 6) {
                choice == 5;
        }

        first->xpos = 1;
        first->ypos = 3;
        first->type = choice;
        first->rotate = 0;

        //second->xpos = 1;
        //second->ypos = 4;
        //second->type = 0;
        clearBitmap(dev->bitmap, 0);

        int choicet;
        int integer;

        while (running) {
          getMagData(gyro, &data);
          rotate(first, data.x);
          draw_piece(first, dev);
          draw_locked_pieces(dev, lp);
          //draw_piece(second, dev);
          pollJoystick(joystick, callbackFunc, 1000);
          printf("xpos: %i\n", first->xpos);
          printf("rotate: %i\n", first->rotate);
	  choicet = (int)(drand48() * 6);
	  if (choicet == 6) {
	    choicet == 5;
	  }
          if (first->xpos >= 7) {
            first->xpos = 7;
            lp = createLockedPiece(first, lp);

            free(first);

            first = malloc(sizeof(piece));

            first->xpos = 1;
            first->ypos = 3;
            first->type = choicet;
            first->rotate = 0;
            clearBitmap(dev->bitmap, 0);

          } else if (right) {
            //rotate(first, 35);
            first = move_piece_right(first);
            right = 0;
            clearBitmap(dev->bitmap, 0);
          } else if (left) {
            first = move_piece_left(first);
            left = 0;
            clearBitmap(dev->bitmap, 0);
          } else if (right) {
            //rotate(first, 35);
            first = move_piece_right(first);
            right = 0;
            clearBitmap(dev->bitmap, 0);
          } else if (left) {
            first = move_piece_left(first);
            left = 0;
            clearBitmap(dev->bitmap, 0);
          } else {
            if (checkOpen(first, lp) == 0) {
                    first = move_piece_down(first);
            } else {
                    lp = createLockedPiece(first, lp);
                    free(first);
                    first = malloc(sizeof(piece));
                    first->xpos = 1;
                    first->ypos = 3;
                    first->type = choicet;
                    first->rotate = 0;
            }

            //second = move_piece_down(second);
            delay(1000);
            clearBitmap(dev->bitmap, 0);
          }
        }
}
