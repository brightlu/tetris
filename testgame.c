#include "sense.h"
#include <string.h>
#include <stdlib.h>
#include "piece.h"
#include "outputtest.h"
#include <stdio.h>
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


void draw_piece(piece *p, pi_framebuffer_t *dev) {
  clearBitmap(dev->bitmap, 0);
        if (p->type == 0) {
          display_dot(dev, p->xpos, p->ypos);
        } else if (p->type == 1) {
	  display_two_dot(dev, p->xpos, p->ypos, p->rotate);
	} else if (p->type == 2) {
	  display_three_dot(dev, p->xpos, p->ypos, p->rotate);
	} else if (p->type == 3) {
	  display_z_piece(dev, p->xpos, p->ypos, p->rotate);
	}
}

void delay(int time) {
        for (int i = 1; i <32767 * time; i++) {
        }
}

void rotate(piece *p, int data_x) {
  if (data_x > 30) {
    if (p->rotate == 3) {
      p->rotate = 0;
    } else {
      p->rotate = p->rotate + 1;
    }
  } else if (data_x < -30) {
    if (p->rotate == 0) {
      p->rotate = 3;
    } else {
      p->rotate = p->rotate - 1;
    }
  }
}

int main(void) {
  
        pi_framebuffer_t *dev = getFBDevice();
	pi_joystick_t *joystick = getJoystickDevice();
	gyro = geti2cDevice();
	configureAccelGyro(gyro);
	coordinate_t data;

        int moved = 0;

        first = malloc(sizeof(piece));
	//second = malloc(sizeof(piece));
	
        first->xpos = 1;
        first->ypos = 1;
        first->type = 3;
	first->rotate = 0;
	
	//second->xpos = 1;
	//second->ypos = 4;
	//second->type = 0;
	clearBitmap(dev->bitmap, 0);

        int integer;
	
	while (1) {
	  getMagData(gyro, &data);
	  rotate(first, data.x);
	  draw_piece(first, dev);
	  //draw_piece(second, dev);
	  pollJoystick(joystick, callbackFunc, 1000);
	  printf("%i\n", first->xpos);
	  if (first->xpos >= 7) {
	    first->xpos = 7;
	    break;
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
	    first = move_piece_down(first);
	    //second = move_piece_down(second);
	    delay(1000);
	    clearBitmap(dev->bitmap, 0);
	  }
        }
}
