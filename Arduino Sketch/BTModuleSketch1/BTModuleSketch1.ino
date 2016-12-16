/*
 * Derek Prince
 * Wireless Quadcopter Remote Sketch
 * 
 * I'm just bored and have a final in 4 hours so I can;t do much else.
 * Weeee
 * 
 * Date Created:   Dec. 15th, 2016
 * Last Modified:  Dec. 15th, 2016
 * 
 */
/*
MIT License

Copyright (c) 2016 Derek Prince

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

//Begin
#define UD_LEFT_STICK_PIN A0
#define LR_LEFT_STICK_PIN A1
#define UD_RIGHT_STICK_PIN A2
#define LR_RIGHT_STICK_PIN A3
#define LEFT_SELECT_PIN 7
#define RIGHT_SELECT_PIN 8    //might as well use the non-PWM pins
#define CENTER_PIN 7          //temporarily the same as left select

// This code is - at least for now - a test to see what parameters these cheap-o analog thumbsticks have.
// They're probably not centered on the pots and may not even have uniform readings throughout the range.
// But. It'll be fun regardless. I wanted to do this for our EDL robot but ran out of time.
// I should put a big red button on it. Emphasis on *big*.

// The 328p I'm using is on a Arduino Mini Pro clocked at 18MHz so we'll have to see if the thing ever fights me 
// on timings since the thumb sticks should be very responsive. Callback functions probably a must so transmit and
// analogReads can share the load as Samwise Gamgee would say.

// For testing I'll probably just connect to a bluetooth terminal on my phone rather than another arduino.
// This way I won't have to delve into the master-slave relationship and addresses business yet.

   //analog reads are unsigned 10-bit values. 16 will have to do, I don't really want a byte array. Space is fine. 
  unsigned int UD_leftStick = 0;         //left stick
  unsigned int LR_leftStick = 0;
  unsigned int UD_rightStick = 0;         //right stick
  unsigned int LR_rightStick = 0;
  unsigned int UpDownCenterValue_Left;     //used for centering the left stick
  unsigned int LeftRightCenterValue_Left;
  unsigned int UpDownCenterValue_Right;     //used for centering the right stick
  unsigned int LeftRightCenterValue_Right;
  bool leftSelect = 0;    //can probably eschew these for functional read conditions
  bool rightSelect = 0;   //I'll keep them if I need to create a hierarchy tree of things to do
  
  //I keep wanting to write this program like it's Verilog. Bleh.

void setup() {
  pinMode(CENTER_PIN, INPUT);
  
  Serial.begin(115200); //default Bluetooth baud rate of my module
  
  UpDownCenterValue_Left = analogRead(UD_LEFT_STICK_PIN);       //grab initials. Only works if user isn't effing w/
  LeftRightCenterValue_Left = analogRead(LR_LEFT_STICK_PIN);    // the sticks on startup.
  UpDownCenterValue_Right = analogRead(UD_RIGHT_STICK_PIN);
  LeftRightCenterValue_Right = analogRead(LR_RIGHT_STICK_PIN);
  
}

void loop() {
  if (digitalRead(CENTER_PIN))
    center();
  if (digitalRead(LEFT_SELECT_PIN))
    Serial.print("To the left!\n");
  if (digitalRead(RIGHT_SELECT_PIN))
    Serial.print("Riiiiiight...\n");

  readLeft();
  readRight();
  Serial.print("Left (UD-LR): ");
  Serial.print(UD_leftStick, DEC);
  Serial.print("-");
  Serial.print(LR_leftStick, DEC);
  Serial.print("\nRight (UD-LR): ");
  Serial.print(UD_rightStick, DEC);
  Serial.print("-");
  Serial.print(LR_rightStick, DEC);
  //gross print block
  
  //should I collect a bunch of things in a buffer to serial print at the end of every loop?
  //that would control the max time betwee signals at least
  //Could also callback to the buffer
  //Create stack?
  //Maybe I should stop overthinking it and see if I even need to do these things.
  //They sound fun though. 
}

void center() {
  UpDownCenterValue_Left = analogRead(UD_LEFT_STICK_PIN);
  LeftRightCenterValue_Left = analogRead(LR_LEFT_STICK_PIN);
  UpDownCenterValue_Right = analogRead(UD_RIGHT_STICK_PIN);
  LeftRightCenterValue_Right = analogRead(LR_RIGHT_STICK_PIN);
}

//I kinda fancy the idea of these returning things but...
//I don't want 4 functions. I'm not sure if I want to make an array to store
//the values in an easy-to-return format either. Probs forget whap maps to what in a week
//I will want to do that if I bundle this in a header file later.
void readLeft() { 
  UD_leftStick = analogRead(UD_LEFT_STICK_PIN);
  LR_leftStick = analogRead(LR_LEFT_STICK_PIN);
}

void readRight() {
  UD_rightStick = analogRead(UD_RIGHT_STICK_PIN);
  LR_rightStick = analogRead(LR_RIGHT_STICK_PIN);
}

