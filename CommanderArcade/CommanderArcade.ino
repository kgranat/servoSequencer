/*
  Commander.ino - default firmware for arbotiX Commander (V1.1)
  Copyright (c) 2009-2012 Michael E. Ferguson.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/

const int UP_BUTTON = 2;
const int DOWN_BUTTON = 3;
const int RIGHT_BUTTON = 4; 
const int LEFT_BUTTON = 5;
const int BUT_LT = 6;
const int BUT_RT = 7;


#define USER      10

#define FRAME_LEN 33         // 30hz
unsigned long ltime;         // last time we sent data

int i;
void setup(){
    Serial.begin(38400);
    ltime = millis();
    pinMode(USER,OUTPUT);    // user LED
    pinMode(UP_BUTTON, INPUT_PULLUP);
    pinMode(DOWN_BUTTON, INPUT_PULLUP);
    pinMode(LEFT_BUTTON, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);
    pinMode(BUT_LT, INPUT_PULLUP);
    pinMode(BUT_RT, INPUT_PULLUP);
    
    i = 0;
}

void loop(){
    int right_V = 128;
    int right_H = 128;
    int left_V = 128;
    int left_H =  128;

  if(digitalRead(UP_BUTTON )== LOW)
  {
    right_V = 250;
  }
  else if(digitalRead(DOWN_BUTTON )== LOW)
  {
    
    right_V = 0;
  }
  else if(digitalRead(LEFT_BUTTON )== LOW)
  {
    right_H = 250;
  }
  else if(digitalRead(RIGHT_BUTTON )== LOW)
  {
    
    right_H = 0;
  }

    unsigned char buttons = 0;
 
  if(digitalRead(BUT_LT )== LOW)
  {
    buttons += 128;
  }

  
  if(digitalRead(BUT_RT) == LOW)
  {
    buttons += 64;
  }
  

 
    Serial.write(0xff);
    Serial.write((unsigned char) right_V);
    Serial.write((unsigned char) right_H);
    Serial.write((unsigned char) left_V);
    Serial.write((unsigned char) left_H);
    Serial.write(buttons);              // buttons
    Serial.write((unsigned char)0);     // extra
    Serial.write((unsigned char)(255 - (right_V+right_H+left_V+left_H+buttons)%256));
    
    if(i > 10){
      digitalWrite(10,HIGH-digitalRead(10));
      i=0;
    }
    i++;
    delay(FRAME_LEN);
}

/* Revisions 
 *  V1.2 - Feb 11, 2012 - Updated for Arduino 1.0
 *  V1.1 - Feb 19, 2010 - Replaced Walk/Look with Right/Left 
 *         (since apparently, I used something called "southpaw")
 *  V1.0 - Feb 10, 2010 - Firmware Finalized
 */

