#include "piece.h"
#include <stdio.h>
#include <time.h>

piece *move_piece_down(piece *pi){
	piece *trans;
	if (trans->ypos < 0) {
	  return trans;
	} else { 
	  trans->xpos = pi->xpos + 1;
	  trans->type = pi->type;
	  trans->ypos = pi->ypos;
	}
}
