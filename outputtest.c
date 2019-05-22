#include "project.h"

void display_dot(pi_framebuffer_t *dev, int x, int y) {
  uint16_t red = getColor(255, 0, 0);
  dev->bitmap->pixel[x][y]=red;
}

void display_two_dot(pi_framebuffer_t *dev, int x, int y, int rotate) {
  uint16_t green = getColor(0, 255, 0);
  dev->bitmap->pixel[x][y]=green;
  if (rotate == 0 || rotate == 2) {
    dev->bitmap->pixel[x][y+1]=green;
  } else {
    dev->bitmap->pixel[x-1][y]=green;
  }
}

void display_three_dot(pi_framebuffer_t *dev, int x, int y, int rotate) {
  uint16_t blue = getColor(0, 0, 255);
  dev->bitmap->pixel[x][y]=blue;
  if (rotate == 0 || rotate == 2) {
    dev->bitmap->pixel[x][y+1]=blue;
    dev->bitmap->pixel[x][y+2]=blue;
  } else {
    dev->bitmap->pixel[x-1][y]=blue;
    dev->bitmap->pixel[x-2][y]=blue;
  }
}

void display_z_piece(pi_framebuffer_t *dev, int x, int y, int rotate) {
  uint16_t yellow = getColor(255, 255, 51);
  dev->bitmap->pixel[x][y]=yellow;
  if (rotate == 0 || rotate == 2) {
    dev->bitmap->pixel[x-1][y]=yellow;
    dev->bitmap->pixel[x-1][y-1]=yellow;
    dev->bitmap->pixel[x][y+1]=yellow;
  } else {
    dev->bitmap->pixel[x-1][y]=yellow;
    dev->bitmap->pixel[x-1][y+1]=yellow;
    dev->bitmap->pixel[x-2][y+1]=yellow;
  }
}

void display_r_piece(pi_framebuffer_t *dev, int x, int y, int rotate) {
  uint16_t orange = getColor(255, 128, 0);
  dev->bitmap->pixel[x][y]=orange;
  dev->bitmap->pixel[x-1][y]=orange;
  if (rotate == 0) {
    dev->bitmap->pixel[x][y+1]=orange;
  } else if (rotate == 1) {
    dev->bitmap->pixel[x-1][y+1]=orange;
  } else if (rotate == 2) {
    dev->bitmap->pixel[x-1][y-1]=orange;
  } else if (rotate == 3) {
    dev->bitmap->pixel[x][y-1]=orange;
  }
}

void display_t_piece(pi_framebuffer_t *dev, int x, int y, int rotate) {
  uint16_t purple = getColor(255, 0, 255);
  dev->bitmap->pixel[x][y]=purple;
  dev->bitmap->pixel[x-1][y]=purple;
  if (rotate == 0) {
    dev->bitmap->pixel[x][y-1]=purple;
    dev->bitmap->pixel[x][y+1]=purple;
  } else if (rotate == 1) {
    dev->bitmap->pixel[x-2][y]=purple;
    dev->bitmap->pixel[x-1][y+1]=purple;
  } else if (rotate == 2) {
    dev->bitmap->pixel[x-1][y-1]=purple;
    dev->bitmap->pixel[x-1][y+1]=purple;
  } else if (rotate == 3) {
    dev->bitmap->pixel[x-2][y]=purple;
    dev->bitmap->pixel[x-1][y-1]=purple;
  }
}

int main(void) {
	pi_framebuffer_t *dev = getFBDevice();
	clearBitmap(dev->bitmap, 0);
	display_dot(dev, 1, 1);
	display_two_dot(dev, 1, 3, 0);
	display_three_dot(dev, 6, 1, 0);
	display_z_piece(dev, 3, 1, 0);
	display_r_piece(dev, 4, 4, 0);
	display_t_piece(dev, 6, 6, 0);
}
