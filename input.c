#include <string.h>
#include <stdlib.h>
#include "project.h"
//#include "piece.h"
//#include "outputtest.h"
#include <stdio.h>
#include <time.h>
#include <linux/input.h>

void destroy_lop(pixel **p) {
    pixel *current = *p;
    pixel *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    /* deref head_ref to affect the real head back
     in the caller. */
    *p = NULL;
}

int count(pixel *head, int search_x)
{
    pixel *current = head;
    int count = 0;
    while (current != NULL) {
        if (current->x == search_x)
            count++;
        current = current->next;
    }
    return count;
}

pixel *move_pixel_down(pixel *lop, int xpos) {
	pixel *p;
        p = lop;
        while(p->next != NULL) {
                if (p->x < xpos) {
                        p->x = p->x + 1;
                }
                p = p->next;
        }

	return p;
}

pixel *clearRow(pixel **lop, int xpos) {
	pixel *p = *lop;

	if (p->xpos == xpos) {
		pixel *next;
		next = p->next;
		free(p);
		p = next;
	}


        while(p->next != NULL) {
		pixel *next = p->next;
                if (p->x == xpos) {
                        free(p);
			p = next;
    		} else {
			p = p->next;
		}
        }

	return p;
}

int checkFullRows(pixel *lp) {
	for (int i = 7; i >= 0; i--) {
		if (count(lp, i) == 8) {
			lp = clearRow(&lp, i);
			lp = move_pixel_down(lp, i);
			return 1;
		}
	}

	return 0;
}

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
        } else if (p->type == 2) {
                head = lockPixel(p->xpos, p->ypos, p->type, head);
                if (p->rotate == 0 || p->rotate == 2) {
                        head = lockPixel(p->xpos, p->ypos + 1, p->type, head);
                        head = lockPixel(p->xpos, p->ypos + 2, p->type, head);
                } else {
                        head = lockPixel(p->xpos - 1, p->ypos, p->type, head);
                        head = lockPixel(p->xpos - 2, p->ypos, p->type, head);
                }
        } else if (p->type == 3) {
                head = lockPixel(p->xpos, p->ypos, p->type, head);
                if (p->rotate == 0 || p->rotate == 2) {
                        head = lockPixel(p->xpos - 1, p->ypos, p->type, head);
                        head = lockPixel(p->xpos - 1, p->ypos - 1, p->type, head);
                        head = lockPixel(p->xpos, p->ypos + 1, p->type, head);
                } else {
                        head = lockPixel(p->xpos - 1, p->ypos, p->type, head);
                        head = lockPixel(p->xpos - 1, p->ypos + 1, p->type, head);
                        head = lockPixel(p->xpos - 2, p->ypos + 1, p->type, head);
                }
        } else if (p->type == 4) {
                head = lockPixel(p->xpos, p->ypos, p->type, head);
                head = lockPixel(p->xpos - 1, p->ypos, p->type, head);
                if (p->rotate == 0) {
                        head = lockPixel(p->xpos, p->ypos + 1, p->type, head);
                } else if (p->rotate == 1) {
                        head = lockPixel(p->xpos - 1, p->ypos + 1, p->type, head);
                } else if (p->rotate == 2) {
                        head = lockPixel(p->xpos - 1, p->ypos - 1, p->type, head);
                } else {
                        head = lockPixel(p->xpos, p->ypos - 1, p->type, head);
                }
        } else {
                head = lockPixel(p->xpos, p->ypos, p->type, head);
                head = lockPixel(p->xpos - 1, p->ypos, p->type, head);

                if (p->rotate == 0) {
                        head = lockPixel(p->xpos, p->ypos + 1, p->type, head);
                        head = lockPixel(p->xpos, p->ypos - 1, p->type, head);
                } else if (p->rotate == 1) {
                        head = lockPixel(p->xpos - 1, p->ypos + 1, p->type, head);
                        head = lockPixel(p->xpos - 2, p->ypos, p->type, head);
                } else if (p->rotate == 2) {
                        head = lockPixel(p->xpos - 1, p->ypos - 1, p->type, head);
                        head = lockPixel(p->xpos - 1, p->ypos + 1, p->type, head);
                } else {
                        head = lockPixel(p->xpos - 1, p->ypos - 1, p->type, head);
                        head = lockPixel(p->xpos - 2, p->ypos, p->type, head);
                }
        }
        return head;
}

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
        } else if ((pi->ypos >= 6) && ((pi->rotate == 0) || (pi->rotate == 2)) && (pi->type == 1)) {
	  return pi;
	} else if ((pi->ypos >= 5) && ((pi->rotate == 0) || (pi->rotate == 2)) && (pi->type == 2)) {
          return pi;
	} else if ((pi->ypos >= 6) && (pi->type == 3)) {
	  return pi;
	} else if ((pi->ypos >= 6) && ((pi->rotate == 0) || (pi->rotate == 1)) && (pi->type == 4)) {
	  return pi;
	} else if ((pi->ypos >= 6) && (pi->rotate != 3) && (pi->type == 5)) {
	  return pi;
	} else {
          pi->ypos = pi->ypos + 1;
          return pi;
        }
}

piece *move_piece_left(piece *pi){
        if (pi->ypos <= 0) {
	  return pi;
	} else if ((pi->ypos <= 1) && ((pi->rotate == 0) || (pi->rotate == 2)) && (pi->type == 3)) {
          return pi;
        } else if ((pi->ypos <= 1) && ((pi->rotate == 2) || (pi->rotate == 3)) && (pi->type == 4)) {
          return pi;
        } else if ((pi->ypos <= 1) && (pi->rotate != 1) && (pi->type == 5)) {
          return pi;
        } else {
          pi->ypos = pi->ypos - 1;
          return pi;
        }
}

void rotate(piece *p, int data_x) {
	if ((p->type == 0) || (p->type == 4) || (p->type == 5) || ((p->type == 1) && (p->ypos <= 6)) || ((p->type == 2) && (p->ypos <= 5)) || ((p->type == 3) && (p->ypos >= 1) && (p->ypos <= 6))) {
		if (data_x < -30){
			if (p->type == 4) {
				if (((p->ypos == 0) && (p->rotate == 1)) || ((p->ypos == 7) && (p->rotate == 3))) {
				} else if (p->rotate == 3) {
					p->rotate = 0;
				} else {
					p->rotate = p->rotate + 1;
				}
			} else if (p->type == 5) {
				if (((p->ypos == 0) && (p->rotate == 2)) || ((p->ypos == 7) && (p->rotate == 3))) {
				} else if (p->rotate == 3) {
					p->rotate = 0;
				} else {
					p->rotate = p->rotate + 1;
				}
			} else {
				if (p->rotate == 3) {
					p->rotate = 0;
				} else {
					p->rotate = p->rotate + 1;
				}
			}
		} else if (data_x > 30) {
			if (p->type == 4) {
				if (((p->ypos == 0) && (p->rotate == 0)) || ((p->ypos == 7) && (p->rotate == 2))) {
				} else if (p->rotate == 0) {
					p->rotate = 3;
				} else {
					p->rotate = p->rotate - 1;
				}
			} else if (p->type == 5) {
				if (((p->ypos == 0) && (p->rotate == 1)) || ((p->ypos == 7) && (p->rotate == 3))) {
				} else if (p->rotate == 0) {
					p->rotate = 3;
				} else {
					p->rotate = p->rotate - 1;
				}
			} else {
				if (p->rotate == 0) {
					p->rotate = 3;
				} else {
				p->rotate = p->rotate - 1;
				}
			}
		}
	}
}

void draw_locked_pieces(pi_framebuffer_t *dev, pixel *lop) {
        pixel *p;
        p = lop;
        while(p != NULL) {
                if (p->color == 0) {
			//dot piece, red
                        dev->bitmap->pixel[p->x][p->y] = getColor(255, 0, 0);
                } else if (p->color == 1) {
			//two dot piece, green
                        dev->bitmap->pixel[p->x][p->y] = getColor(0, 255, 0);
                } else if (p->color == 2) {
			//three dot piece, blue
                        dev->bitmap->pixel[p->x][p->y] = getColor(0, 0, 255);
                } else if (p->color == 3) {
			//z piece, yellow
                        dev->bitmap->pixel[p->x][p->y] = getColor(255, 255, 51);
                } else if (p->color == 4) {
			//r piece, orange
                        dev->bitmap->pixel[p->x][p->y] = getColor(255, 128, 0);
                } else {
			//t piece, purple
                        dev->bitmap->pixel[p->x][p->y] = getColor(255, 0, 255);
                }
                p = p->next;
        }
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

int isLeftTo(int x, int y, pixel *top) {
	pixel *p;
	p = top;
	while(p != NULL){
		if ((y - 1 == p->y) && (x == p->x)) {
			return 1;
		}
		p = p->next;
	}
	return 0;
}

int isRightTo(int x, int y, pixel *top) {
	pixel *p;
	p = top;
	while(p != NULL){
		if ((y + 1 == p->y) && (x == p->x)) {
			return 1;
		}
		p = p->next;
	}
	return 0;
}

int checkOpenLeftTo(piece *pi, pixel *lop) {
	if (pi->type == 0) {
		return isLeftTo(pi->xpos, pi->ypos, lop);
	} else if (pi->type == 1) {
		if (pi->rotate == 0 || pi->rotate == 2) {
			return isLeftTo(pi->xpos, pi->ypos, lop);
		} else {
			return isLeftTo(pi->xpos, pi->ypos, lop) + isLeftTo(pi->xpos - 1, pi->ypos, lop);
		}
	} else if (pi->type == 2) {
		if (pi->rotate == 0 || pi->rotate == 2) {
			return isLeftTo(pi->xpos, pi->ypos, lop);
		} else {
			return isLeftTo(pi->xpos, pi->ypos, lop) + isLeftTo(pi->xpos - 1, pi->ypos, lop) + isLeftTo(pi->xpos -2, pi->ypos, lop);
		}
	} else if (pi->type == 3) {
		if (pi->rotate == 0 || pi->rotate == 2) {
			return isLeftTo(pi->xpos, pi->ypos, lop) + isLeftTo(pi->xpos - 1, pi->ypos - 1, lop);
		} else {
			return isLeftTo(pi->xpos, pi->ypos, lop) + isLeftTo(pi->xpos - 1, pi->ypos, lop) + isLeftTo(pi->xpos - 2, pi->ypos + 1, lop);
		}
	} else if (pi->type == 4) {
		if (pi->rotate == 0 || pi->rotate == 1) {
			return isLeftTo(pi->xpos, pi->ypos, lop) + isLeftTo(pi->xpos - 1, pi->ypos, lop);
		} else if (pi->rotate == 2) {
			return isLeftTo(pi->xpos, pi->ypos, lop) + isLeftTo(pi->xpos - 1, pi->ypos - 1, lop);
		} else {
			return isLeftTo(pi->xpos, pi->ypos - 1, lop) + isLeftTo(pi->xpos - 1, pi->ypos, lop);
		}
	} else if (pi->type == 5) {
		if (pi->rotate == 0) {
			return isLeftTo(pi->xpos, pi->ypos - 1, lop) + isLeftTo(pi->xpos - 1, pi->ypos, lop);
		} else if (pi->rotate == 1) {
			return isLeftTo(pi->xpos, pi->ypos, lop) + isLeftTo(pi->xpos - 1, pi->ypos, lop) + isLeftTo(pi->xpos - 2, pi->ypos, lop);
		} else if (pi->rotate == 2) {
			return isLeftTo(pi->xpos, pi->ypos, lop) + isLeftTo(pi->xpos - 1, pi->ypos - 1, lop);
		} else if (pi->rotate == 3) {
			return isLeftTo(pi->xpos, pi->ypos, lop) + isLeftTo(pi->xpos - 1, pi->ypos - 1, lop) + isLeftTo(pi->xpos - 2, pi->ypos, lop);
                }
	}
}

int checkOpenRightTo(piece *pi, pixel *lop) {
        if (pi->type == 0) {
                return isRightTo(pi->xpos, pi->ypos, lop);
        } else if (pi->type == 1) {
                if (pi->rotate == 0 || pi->rotate == 2) {
                        return isRightTo(pi->xpos, pi->ypos + 1, lop);
                } else {
                        return isRightTo(pi->xpos, pi->ypos, lop) + isRightTo(pi->xpos - 1, pi->ypos, lop);
                }
        } else if (pi->type == 2) {
                if (pi->rotate == 0 || pi->rotate == 2) {
                        return isRightTo(pi->xpos, pi->ypos + 2, lop);
                } else {
                        return isRightTo(pi->xpos, pi->ypos, lop) + isRightTo(pi->xpos - 1, pi->ypos, lop) + isRightTo(pi->xpos -2, pi->ypos, lop);
                }
        } else if (pi->type == 3) {
                if (pi->rotate == 0 || pi->rotate == 2) {
                        return isRightTo(pi->xpos, pi->ypos + 1, lop) + isRightTo(pi->xpos - 1, pi->ypos, lop);
                } else {
                        return isRightTo(pi->xpos, pi->ypos, lop) + isRightTo(pi->xpos - 1, pi->ypos + 1, lop) + isRightTo(pi->xpos - 2, pi->ypos + 1, lop);
                }
        } else if (pi->type == 4) {
                if (pi->rotate == 0) {
                        return isRightTo(pi->xpos, pi->ypos + 1, lop) + isRightTo(pi->xpos - 1, pi->ypos, lop);
                } else if (pi->rotate == 1) {
                        return isRightTo(pi->xpos, pi->ypos, lop) + isRightTo(pi->xpos - 1, pi->ypos + 1, lop);
                } else {
                        return isRightTo(pi->xpos, pi->ypos, lop) + isRightTo(pi->xpos, pi->ypos - 1, lop);
                }
        } else if (pi->type == 5) {
                if (pi->rotate == 0) {
                        return isRightTo(pi->xpos, pi->ypos + 1, lop) + isRightTo(pi->xpos - 1, pi->ypos, lop);
                } else if (pi->rotate == 1) {
                        return isRightTo(pi->xpos, pi->ypos, lop) + isRightTo(pi->xpos - 1, pi->ypos + 1, lop) + isRightTo(pi->xpos - 2, pi->ypos, lop);
                } else if (pi->rotate == 2) {
                        return isRightTo(pi->xpos, pi->ypos, lop) + isRightTo(pi->xpos - 1, pi->ypos + 1, lop);
                } else if (pi->rotate == 3) {
                        return isRightTo(pi->xpos, pi->ypos, lop) + isLeftTo(pi->xpos - 1, pi->ypos, lop) + isLeftTo(pi->xpos - 2, pi->ypos, lop);
                }
        }
}

int checkOpenBelow(piece *pi, pixel *lop) {
        if (pi->type == 0) {
		//single dot piece
                return isBelow(pi->xpos, pi->ypos, lop);
        } else if (pi->type == 1) {
		//two dot piece
                if (pi->rotate == 0 || pi->rotate == 2) {
                        return isBelow(pi->xpos, pi->ypos, lop) + isBelow(pi->xpos, pi->ypos + 1, lop);
                } else {
                        return isBelow(pi->xpos, pi->ypos, lop);
                }
        } else if (pi->type == 2) {
		//three dot piece
                if (pi->rotate == 0 || pi->rotate == 2) {
                        return isBelow(pi->xpos, pi->ypos, lop) + isBelow(pi->xpos, pi->ypos + 1, lop) + isBelow(pi->xpos, pi->ypos + 2, lop);
                } else {
                        return isBelow(pi->xpos, pi->ypos, lop);
                }
        } else if (pi->type == 3) {
		//z piece
                if (pi->rotate == 0 || pi->rotate == 2) {
                        return isBelow(pi->xpos, pi->ypos, lop) + isBelow(pi->xpos, pi->ypos + 1, lop) + isBelow(pi->xpos - 1, pi->ypos - 1, lop);
                } else {
                        return isBelow(pi->xpos, pi->ypos, lop) + isBelow(pi->xpos - 1, pi->ypos + 1, lop);
                }
        } else if (pi->type == 4) {
		//r piece
                if (pi->rotate == 0) {
                        return isBelow(pi->xpos, pi->ypos, lop) + isBelow(pi->xpos, pi->ypos + 1, lop);
                } else if (pi->rotate == 1) {
                        return isBelow(pi->xpos, pi->ypos, lop) + isBelow(pi->xpos - 1, pi->ypos + 1, lop);
                } else if (pi->rotate == 2) {
                        return isBelow(pi->xpos, pi->ypos, lop) + isBelow(pi->xpos - 1, pi->ypos - 1, lop);
                } else {
                        return isBelow(pi->xpos, pi->ypos, lop) + isBelow(pi->xpos, pi->ypos - 1, lop);
                }
        } else {
		//t piece
                if (pi->rotate == 0) {
                        return isBelow(pi->xpos, pi->ypos, lop) + isBelow(pi->xpos, pi->ypos + 1, lop) + isBelow(pi->xpos, pi->ypos - 1, lop);
                } else if (pi->rotate == 1) {
                        return isBelow(pi->xpos, pi->ypos, lop) + isBelow(pi->xpos - 1, pi->ypos + 1, lop);
                } else if (pi->rotate == 2) {
                        return isBelow(pi->xpos, pi->ypos, lop) + isBelow(pi->xpos - 1, pi->ypos - 1, lop) + isBelow(pi->xpos - 1, pi->ypos + 1, lop);
                } else {
                        return isBelow(pi->xpos, pi->ypos, lop) + isBelow(pi->xpos - 1, pi->ypos - 1, lop);
                }
        }
}

