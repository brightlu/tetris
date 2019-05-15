#include "sense.h"
#include <linux/input.h>
#include <stdio.h>

int running=1;
pi_i2c_t* gyro=NULL;
void callbackFunc(unsigned int code) {
    printf("code: %u\t",code);
    if(code == KEY_UP) {
        printf("can't move piece up");
    }else if(code == KEY_DOWN) {
        printf("move piece down");
    }else if(code == KEY_RIGHT) {
        printf("move piece right");
    }else if(code == KEY_LEFT) {
        printf("move piece left");
    }else if(gyro) {
        coordinate_t data;
        getMagData(gyro,&data);
        printf("%f %f %f\n",data.x,data.y,data.z);
    } else if(code == KEY_ENTER) {
        printf("quit");
        running=0;	
    }
    printf("\n");
}

int main(void) {
    pi_joystick_t* joystick=getJoystickDevice();
    gyro=geti2cDevice();
    configureAccelGyro(gyro);
    while(running){
        pollJoystick(joystick,callbackFunc,1000);
    }
    printf("Looks like 'running' is zero!\n");
    freeJoystick(joystick);
}
