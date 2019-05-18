#include "piece.h"
#include <stdio.h>
#include <time.h>

piece *move_piece_down(piece *pi){
	if (pi->xpos >= 7) {
	  return pi;
	} else { 
	  pi->xpos = pi->xpos + 1;
	  return pi;
	}
}

piece *move_piece_right(piece *pi){
        if (pi->ypos >= 7) {
          return pi;
        } else {
          pi->ypos = pi->ypos + 1;
          return pi;
        }
}

piece *move_piece_left(piece *pi){
        if (pi->ypos < 1) {
          return pi;
        } else {
          pi->ypos = pi->ypos - 1;
          return pi;
        }
}
