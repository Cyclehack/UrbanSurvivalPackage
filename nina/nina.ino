// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.

#include <Servo.h> 
#include <Serial.h>
#include "pitches.h"

/**
 * Horn stuff
 */

#define melodyPin 8

float def_note_ratio = 2.0;
float note_ratio = 2.0;

//Mario main theme melody
int melody[] = {
    NOTE_B6, 0, 0, 0
};
//Mario main them tempo
int tempo[] = {
    12, 6, 12, 6
};

/**
 * Servo stuff
 */
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

int playedLast = 0;

void playSong() {
  
    // The longer the song is played the faster it should play
    if (playedLast > 0) {
      if (note_ratio > 0.4) {
        note_ratio -= 0.2;
      }
    } else {
      // Reset the note speed
      note_ratio = def_note_ratio;
    }
    
    int number_of_melody_notes = 3;
    for (int thisNote = 0; thisNote < number_of_melody_notes; thisNote++) {

        int noteDuration = 1000/tempo[thisNote];
        tone(8, melody[thisNote],noteDuration);

        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * note_ratio;
        delay(pauseBetweenNotes);
        // stop the tone playing:
        noTone(8);
    }
    playedLast += 1;
}

void setup() 
{ 
    Serial.begin(9600);
    Serial.print("\n"); 
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 


void loop() { 

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    if (digitalRead(2)) {
        Serial.print("Button pushed");
        playSong();
        delay(200);
    } else {
        
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
        
        // Reset the played last
        playedLast = 0;
    } 
}
