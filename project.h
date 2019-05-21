#include "sense.h"

typedef struct Piece {
        int xpos;
        int ypos;
        int type;
        int rotate;
} piece;

typedef struct LockedPixel {
        int x;
        int y;
        int color;
        struct LockedPixel *next;
} pixel;


piece *move_piece_down(piece *pi);
piece *move_piece_right(piece *pi);
piece *move_piece_left(piece *pi);
piece *rotate_piece(piece *pi, int data_x);

void display_dot(pi_framebuffer_t *dev, int x, int y);
void display_two_dot(pi_framebuffer_t *dev, int x, int y, int rotate);
void display_three_dot(pi_framebuffer_t *dev, int x, int y, int rotate);
void display_z_piece(pi_framebuffer_t *dev, int x, int y, int rotate);
void display_r_piece(pi_framebuffer_t *dev, int x, int y, int rotate);
void display_t_piece(pi_framebuffer_t *dev, int x, int y, int rotate);

pixel *lockPixel(int x, int y, int color, pixel *head);
pixel *createLockedPiece(piece *p, pixel *head);
void draw_locked_pieces(pi_framebuffer_t *dev, pixel *lop);
void callbackFunc(unsigned int code);
void draw_piece(piece *p, pi_framebuffer_t *dev);
void delay(int time);
void rotate(piece *p, int data_x);
int isBelow(int x, int y, pixel *top);
int checkOpen(piece *pi, pixel *lop);

