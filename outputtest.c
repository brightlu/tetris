#include "sense.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "piece.h"

void display_dot(pi_framebuffer_t *dev, int x, int y) {
  uint16_t red = getColor(255, 0, 0);
  dev->bitmap->pixel[x][y]=red;
}

void display_two_dot(pi_framebuffer_t *dev, int x, int y) {
  uint16_t green = getColor(0, 255, 0);
  dev->bitmap->pixel[x][y]=green;
  dev->bitmap->pixel[x][y+1]=green;
}

void display_three_dot(pi_framebuffer_t *dev, int x, int y) {
  uint16_t blue = getColor(0, 0, 255);
  dev->bitmap->pixel[x][y]=blue;
  dev->bitmap->pixel[x][y+1]=blue;
  dev->bitmap->pixel[x][y+2]=blue;
}

void display_z_piece(pi_framebuffer_t *dev, int x, int y) {
  uint16_t yellow = getColor(255, 255, 51);
  dev->bitmap->pixel[x][y]=yellow;
  dev->bitmap->pixel[x-1][y]=yellow;
  dev->bitmap->pixel[x-1][y-1]=yellow;
  dev->bitmap->pixel[x][y+1]=yellow;
}

void display_r_piece(pi_framebuffer_t *dev, int x, int y) {
  uint16_t orange = getColor(255, 128, 0);
  dev->bitmap->pixel[y][x]=orange;
  dev->bitmap->pixel[y][x-1]=orange;
  dev->bitmap->pixel[y+1][x-1]=orange;
  dev->bitmap->pixel[y-1][x]=orange;
}

