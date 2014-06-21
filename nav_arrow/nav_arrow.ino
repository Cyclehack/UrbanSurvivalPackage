// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.

#include <Servo.h> 
#include <Serial.h>
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 90;    // variable to store the servo position 

const int directions_length = 12;

int incomingByte;
 
// Rotate from start to end
int rotate(Servo servo, int cur_pos, int start_p, int end_p) {

    int inc = 0;
    int delay_t = 20;

    if (start_p > end_p) {
        // Turn clockwise
        for(cur_pos; cur_pos >= end_p; cur_pos -= 1) {
            myservo.write(cur_pos);            
            // Give the Servo 30ms to move
            delay(delay_t);                     
        } 
        Serial.print("Turn clockwise\n");
    } else if (start_p <= end_p) {
        // Turn anti-clockwise
        for(cur_pos; cur_pos <= end_p ; cur_pos += 1) {
            myservo.write(cur_pos);            
            // Give the Servo n ms to move
            delay(delay_t);                     
        } 
        Serial.print("Anti-Clockwise\n");
    } 

    return cur_pos;
}

int goCenter(Servo servo, int cur_pos) {
    int new_pos; 

    new_pos = rotate(servo, cur_pos, cur_pos, 90);

    return new_pos;
}

int goLeft(Servo servo, int cur_pos) {
    if (cur_pos < 90) {
        // Reset if we're on the left
        cur_pos = goCenter(servo, cur_pos);
    }

    int new_pos = rotate(servo, cur_pos, cur_pos, 180);
    Serial.print("Turn left\n");
    return new_pos;
}

int goRight(Servo servo, int cur_pos) {
    if (cur_pos > 90) {
        // Reset if we're on the left
        cur_pos = goCenter(servo, cur_pos);
    }

    int new_pos = rotate(servo, cur_pos, cur_pos, 0);
    Serial.print("Turn Right\n");
    return new_pos;
}

void setup() 
{ 
    Serial.begin(4800);
    Serial.print("\n");
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 


void loop() { 

    // send data only when you receive data:
   if (Serial.available() > 0) {
       // read the incoming byte:
       incomingByte = Serial.read();

        Serial.print(incomingByte);

        // Parse R,L and S control bytes to drive servo
        if (incomingByte == 'R') {
           pos = goRight(myservo, pos);
        } else if (incomingByte == 'L') {
           pos = goLeft(myservo, pos);
        } else if (incomingByte == 'S') {
           pos = goCenter(myservo, pos);
        }
    }
} 

