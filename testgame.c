#include "sense.h"
#include <string.h>
#include <stdlib.h>
#include "piece.h"
#include "outputtest.h"
#include <stdio.h>
#include <linux/input.h>

int running=1;
pi_i2c_t* gyro=NULL;
void callbackFunc(unsigned int code) {
  printf("code: %u\t",code);

  if(code == KEY_UP) {
    printf("can't move piece up");
    }else if(code == KEY_DOWN) {
      printf("move piece down");
    }else if(code == KEY_RIGHT) {
      printf("move piece right");
    }else if(code == KEY_LEFT) {
      printf("move piece left");
    }else if(code == KEY_ENTER) {
      printf("quit");
      running=0;
    }
    printf("\n");
}


void draw_piece(piece *p, pi_framebuffer_t *dev) {

        if (p->type == 0) {
                display_dot(dev, p->xpos, p->ypos);
        } else if (p->type == 1) {
                //ddisplay twoddots
        }
}

void delay(int time) {
        for (int i = 1; i <32767 * time; i++) {
        }
}

int main(void) {
  
        pi_framebuffer_t *dev = getFBDevice();
	pi_joystick_t *joystick = getJoystickDevice();

        int moved = 0;

        piece *first = NULL;
        first = malloc(sizeof(piece));

        first->xpos = 1;
        first->ypos = 1;
        first->type = 0;
	clearBitmap(dev->bitmap, 0);
        draw_piece(first, dev);

        int integer;

	while (1) {
	  //clearBitmap(dev->bitmap, 0);
	  first = move_piece_down(first);
	  delay(10000);
	  draw_piece(first, dev);
	  pollJoystick(joystick, callbackFunc, 1000);
	}
}
