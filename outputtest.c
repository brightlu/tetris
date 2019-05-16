#include "framebuffer.h"
#include "sense.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void display_dot(pi_framebuffer_t *dev) {
  uint16_t white = getColor(255, 255, 255);
  dev->bitmap->pixel[1][1]=white;
}

void display_twodot(pi_framebuffer_t *dev) {
  uint16_t blue = getColor(0, 0, 255);
  dev->bitmap->pixel[1][3]=blue;
  dev->bitmap->pixel[1][4]=blue;
}

int main(void) {
  pi_framebuffer_t *dev = getFBDevice();
  display_dot(dev);
  display_twodot(dev);
  //clearBitmap(dev->bitmap,0);  
}
#include "framebuffer.h"
#include "sense.h"
#include <stdio.h>

void display_dot(pi_framebuffer_t *dev) {
  uint16_t white = getColor(255, 255, 255);
  dev->bitmap->pixel[i][j]=white;
}

int main(void) {
  display_dot(pi_framebuffer_t *dev);
}
