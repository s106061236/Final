/*---------In this Project, my stragety is saving the whole map in my K66F---------*/

#include "mbed.h"
#include "bbcar.h"

Ticker servo_ticker; 
PwmOut pin9(D9), pin8(D8);
BBCar car(pin8, pin9, servo_ticker); 
Serial pc(USBTX,USBRX); // tx,rx 
Serial uart(D1,D0); // tx,rx OpenMV
DigitalInOut pin10(D10); // Ping
Serial xbee(D12, D11); // Xbee

float data[50]; // the array to save the ping data in Mission 2

/*--------------------------------Main Function--------------------------------*/

int main() {

    xbee.printf("start!\n\r"); // to check if Xbee is connected or not
    parallax_ping  ping1(pin10);
    int i=0;

/*--------------------Normal  way--------------------*/

    // Go straight 130cm
    wait(3);
    car.goStraight(75); 
    wait(9.5);
    car.stop();
    wait(0.5);

    // turn left 90
    car.turn(50,1);
    wait(1);
    car.stop();
    wait(0.5);

    // Straight 50cm, go into Mission 1
    wait(1);
    car.goStraight(75);
    wait(3);
    car.stop();
    wait(0.5);

/*---------------------Mission 1---------------------*/

/*---------Parking---------*/

    // turn right 90
    car.turn(50,-1);
    wait(1);
    car.stop();
    wait(0.5);

    // Back 55 cm
    wait(1);
    car.goStraight(-75);
    wait(3);
    car.stop();
    wait(0.5);

/*-------Take Picture-------*/

    // Straight 30 cm
    car.goStraight(75);
    wait(2.5);
    car.stop();
    wait(1);
    
    // turn left 90
    car.turn(50,1);
    wait(1);
    car.stop();
    wait(0.5);

    // Straight 10 cm
    car.goStraight(75);
    wait(1.2);
    car.stop();
    wait(1);

    // turn right 90
    car.turn(50,-1);
    wait(0.9);
    car.stop();
    wait(1);

    // take picture
    wait(1);
    char s[21];
    sprintf(s,"image_classification"); // sent the command to OpenMV for taking picture
    uart.puts(s); // sent the command by UART
    wait(1);

    // turn right 90
    car.turn(50,-1);
    wait(0.9);
    car.stop();
    wait(1);

    // Straight 10 cm
    car.goStraight(75);
    wait(3.1);
    car.stop();
    wait(1);

    // turn right 90, exit Mission 1
    car.turn(50,-1);
    wait(1);
    car.stop();
    wait(1);

/*--------------------Normal  way--------------------*/

    // Straight 120 cm
    car.goStraight(75);
    wait(8.9);
    car.stop();
    wait(1);

    // turn right 90
    car.turn(50,-1);
    wait(1);
    car.stop();
    wait(1);
    
    // Straight 10 cm, go into Mission 2
    car.goStraight(75);
    wait(2);
    car.stop();
    wait(1);

/*---------------------Mission 2---------------------*/

    // turn right 90
    car.turn(50,-1);
    wait(1);
    car.stop();
    wait(1);
    
    // Straight 10 cm
    car.goStraight(75);
    wait(1.8);
    car.stop();
    wait(1);

    // save the ping data
    for(i=0;i<50;i++)
    {
        data[i] = ping1;
        wait(0.02);
    }

    // back 10 cm
    car.goStraight(-75);
    wait(1.6);
    car.stop();
    wait(1);

    // turn left 90
    car.turn(50,1);
    wait(1.2);
    car.stop();
    wait(1);

    // Straight 70 cm
    car.goStraight(75);
    wait(5.5);
    car.stop();
    wait(1);

    // turn right 90, exit Mission 2
    car.turn(50,-1);
    wait(1);
    car.stop();
    wait(1);
    
/*--------------------Normal  way--------------------*/

    // Straight 150 cm
    car.goStraight(75);
    wait(10);
    car.stop();

/*----------Finally, send the data by XBee-----------*/ 

    int flag = 0;
    for(i=0;i<50;i++)
    {
        xbee.printf("%f\n\r",data[i]);
        wait(0.1);
        if(data[i]>14) flag=1;
    }
    if(!flag) xbee.printf("rectengle.")
    
}