// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 90;    // variable to store the servo position 

const int directions_length = 12;

// -1 left, 1 right
// Second value is the distance
int directions[directions_length] = {
    -1, 100,
    -1, 80,
    -1, 60,
    -1, 40,
    -1, 20,
    -1, 5
};

 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 

// Rotate from start to end
int rotate(Servo servo, int cur_pos, int start_p, int end_p) {

    int inc = 0;
    int delay_t = 30;

    if (start_p > end_p) {
        // Turn clockwise
        for(cur_pos; cur_pos >= end_p; cur_pos -= 1) {
            myservo.write(cur_pos);            
            // Give the Servo 30ms to move
            delay(delay_t);                     
        } 
    } else if (start_p <= end_p) {
        // Turn anti-clockwise
        for(cur_pos; cur_pos <= end_p ; cur_pos += 1) {
            myservo.write(cur_pos);            
            // Give the Servo n ms to move
            delay(delay_t);                     
        } 
    } 

    return cur_pos;
}

int goCenter(Servo servo, int cur_pos) {
    int new_pos; 

    new_pos = rotate(servo, cur_pos, cur_pos, 90);

    return new_pos;
}

int goRight(Servo servo, int cur_pos) {
    if (cur_pos < 90) {
        // Reset if we're on the left
        goCenter(servo, cur_pos);
    }

    int new_pos = rotate(servo, cur_pos, 90, 180);
    return new_pos;
}

int goLeft(Servo servo, int cur_pos) {
    if (cur_pos > 90) {
        // Reset if we're on the left
        goCenter(servo, cur_pos);
    }

    int new_pos = rotate(servo, cur_pos, 90, 0);
    return new_pos;
}

int run = 0;
 
void loop() { 

    if (run < 1) {
        pos = goCenter(myservo, pos);
        delay(1000);
        run++;
    }

   // pos = goRight(myservo, pos);
   // delay(1000);
   // pos = goLeft(myservo, pos);
   // delay(1000);
} 
