#include "piece.h"
#include <stdio.h>
#include <time.h>

piece *move_piece_down(piece *pi){
	if (pi->xpos > 7) {
	  return pi;
	} else { 
	  pi->xpos = pi->xpos + 1;
	  return pi;
	}
}
