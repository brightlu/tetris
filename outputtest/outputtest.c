#include "framebuffer.h"
#include "sense.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void display_dot(pi_framebuffer_t *dev, int x, int y) {
  uint16_t red = getColor(255, 0, 0);
  dev->bitmap->pixel[x][y]=red;
}

void display_two_dot(pi_framebuffer_t *dev, int x, int y) {
  uint16_t green = getColor(0, 255, 0);
  dev->bitmap->pixel[y][x]=green;
  dev->bitmap->pixel[y][x+1]=green;
}

void display_three_dot(pi_framebuffer_t *dev, int x, int y) {
  uint16_t blue = getColor(0, 0, 255);
  dev->bitmap->pixel[y][x]=blue;
  dev->bitmap->pixel[y][x-1]=blue;
  dev->bitmap->pixel[y][x+1]=blue;
}

void display_z_piece(pi_framebuffer_t *dev, int x, int y) {
  uint16_t yellow = getColor(51, 255, 255);
  dev->bitmap->pixel[x][y]=yellow;
  dev->bitmap->pixel[x-1][y]=yellow;
  dev->bitmap->pixel[x][y-1]=yellow;
  dev->bitmap->pixel[x+1][y-1]=yellow;
}

void display_r_piece(pi_framebuffer_t *dev, int x, int y) {
  uint16_t orange = getColor(255, 128, 0);
  dev->bitmap->pixel[y][x]=orange;
  dev->bitmap->pixel[y][x-1]=orange;
  dev->bitmap->pixel[y+1][x-1]=orange;
  dev->bitmap->pixel[y-1][x]=orange;
}

int main(void) {
  pi_framebuffer_t *dev = getFBDevice();
  char input;
  while (!input) {
    display_dot(dev, 1, 1);
    display_two_dot(dev, 3, 1);
    display_three_dot(dev, 3, 2);
    display_z_piece(dev, 6, 6);
    display_r_piece(dev, 6, 1);
    scanf("%c", &input);
  }
  clearBitmap(dev->bitmap, 0);
  return 0;
}
