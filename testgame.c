#include "sense.h"
#include <string.h>
#include <stdlib.h>
#include "piece.h"
#include "outputtest.h"
#include <stdio.h>
#include <linux/input.h>

typedef struct LockedPixel {
	int x;
	int y;
	int color;
	struct LockedPixel *next;
} pixel;

int running=1;
pi_i2c_t* gyro=NULL;
int pressed = 0;
int right = 0;
int left = 0;

piece *first = NULL;
piece *second = NULL;

pixel *lockPixel(int x, int y, int color, pixel *head) {
	pixel *temp;
	pixel *p;
    	temp = malloc(sizeof(pixel));
    	temp->x = x;
    	temp->y = y;
    	temp->color = color;
    	temp->next = NULL;

	if (head == NULL){
        	head = temp;
		printf("null");
    	} else {
        	p = head;
		printf("next");
        	while(p->next != NULL){
            		p = p->next;
        	}
        	p->next = temp;
    }
    return head;
}

pixel *createLockedPiece(piece *p, pixel *head) {
	if (p->type == 0) {
		head = lockPixel(p->xpos, p->ypos, p->type, head);
	} else if (p->type == 1) {
		head = lockPixel(p->xpos, p->ypos, p->type, head);
		if (p->rotate == 0 || p->rotate == 2) {
			head = lockPixel(p->xpos, p->ypos + 1, p->type, head);
		} else {
                        head = lockPixel(p->xpos - 1, p->ypos, p->type, head);
		}
	}
	return head;
}

void draw_locked_pieces(pi_framebuffer_t *dev, pixel *lop) {
	pixel *p;
	p = lop;
	while(p != NULL) {
		if (p->color == 0) {
			dev->bitmap->pixel[p->x][p->y] = getColor(255, 0, 0);
		} else if (p->color == 1) {
			dev->bitmap->pixel[p->x][p->y] = getColor(0, 255, 0);
		} 
		
		p = p->next;
	}
}


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
	} else if (p->type == 4) {
	  display_r_piece(dev, p->xpos, p->ypos, p->rotate);
	} else if (p->type == 5) {
	  display_t_piece(dev, p->xpos, p->ypos, p->rotate);
	}
}

void delay(int time) {
        for (int i = 1; i <32767 * time; i++) {
        }
}

void rotate(piece *p, int data_x) {
  if (data_x < -30) {
    if (p->rotate == 3) {
      p->rotate = 0;
    } else {
      p->rotate = p->rotate + 1;
    }
  } else if (data_x > 30) {
    if (p->rotate == 0) {
      p->rotate = 3;
    } else {
      p->rotate = p->rotate - 1;
    }
  }
}

int isBelow(int x, int y, pixel *top) {
	pixel *p;
	p = top;
	while(p != NULL){
	     if (x + 1 == p->x && y == p->y) {
		     return 1;
	     }
	     p = p->next;
	}

	return 0;
}

int checkOpen(piece *pi, pixel *lop) {
	if (pi->type == 0) {
		return isBelow(pi->xpos, pi->ypos, lop);
	} else if (pi->type == 1) {
		if (pi->rotate == 0 || pi->rotate == 2) {
			return isBelow(pi->xpos, pi->ypos, lop) + isBelow(pi->xpos, pi->ypos + 1, lop);
		} else {
			return isBelow(pi->xpos, pi->ypos, lop);
		}
	}
}

int main(void) {
  
        pi_framebuffer_t *dev = getFBDevice();
	pi_joystick_t *joystick = getJoystickDevice();
	gyro = geti2cDevice();
	configureAccelGyro(gyro);
	coordinate_t data;
	pixel *lp = NULL;
	
        int moved = 0;

        first = malloc(sizeof(piece));
	//second = malloc(sizeof(piece));
	
        first->xpos = 1;
        first->ypos = 1;
        first->type = 1;
	first->rotate = 0;
	
	//second->xpos = 1;
	//second->ypos = 4;
	//second->type = 0;
	clearBitmap(dev->bitmap, 0);

        int integer;
	int newType = 0;
	
	while (running) {
	  getMagData(gyro, &data);
	  rotate(first, data.x);
	  draw_piece(first, dev);
	  draw_locked_pieces(dev, lp);
	  //draw_piece(second, dev);
	  pollJoystick(joystick, callbackFunc, 1000);
	  printf("xpos: %i\n", first->xpos);
	  printf("rotate: %i\n", first->rotate);
	  if (first->xpos >= 7) {
	    first->xpos = 7;
	    lp = createLockedPiece(first, lp);

	    if (first->type == 0) {
		    newType = 1;
	    } else {
		    newType = 0;
	    }

	    free(first);

	    first = malloc(sizeof(piece));

	    first->xpos = 1;
	    first->ypos = 1;
	    first->type = newType;
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
	  } else {
	    if (checkOpen(first, lp) == 0) {
		    first = move_piece_down(first);
	    } else {
		    lp = createLockedPiece(first, lp);
		    free(first);
		    first = malloc(sizeof(piece));
            	    first->xpos = 1;
            	    first->ypos = 1;
            	    first->type = 0;
            	    first->rotate = 0;
	    }

	    //second = move_piece_down(second);
	    delay(1000);
	    clearBitmap(dev->bitmap, 0);
	  }
        }
}
