///////////////////////////////////////////////////////////
//  OliMid-U.ino                                         //
//                                                       //
//  https://github.com/oliou/OliMid-U                    //
//                                                       //
///////////////////////////////////////////////////////////

#include <MIDI.h>
#include <OneButton.h> // https://github.com/mathertel/OneButton
#include <Encoder_Polling.h> // https://github.com/frodofski/Encoder_Polling

MIDI_CREATE_DEFAULT_INSTANCE();

// PINOUT VARS
const int encPinA= 2; //the clk attach to pin 2
const int encPinB= 3; //the dt pin attach to pin 3
const int encSwPin= 4 ;//the sw pin attach to pin 4
const int ledPin = 13; 
const int recLedPin = A0; 
const int recPin = A1; 
const int shiftPin = A2; 
const int stopPin = A3; 
const int backwardPin = A4; 
const int forwardPin = A5; 
const int f1Pin = 8;
const int f2Pin = 7;
const int f3Pin = 6;
const int f4Pin = 5;
const int f5Pin = 12;
const int f6Pin = 11;
const int f7Pin = 10;
const int f8Pin = 9;        

OneButton shiftButton(shiftPin, true);

//PIN STATE VARS
bool recPinPrevState = false;
bool encSwPinPrevState = false;
bool shiftPinPrevState = false;
bool stopPinPrevState = false;
bool backwardPinPrevState = false;
bool forwardPinPrevState = false;

bool f1PinPrevState = false;
bool f2PinPrevState = false;
bool f3PinPrevState = false;
bool f4PinPrevState = false;
bool f5PinPrevState = false;
bool f6PinPrevState = false;
bool f7PinPrevState = false;
bool f8PinPrevState = false;

long previousMillis = 0; 
long interval = 500;
long midiClockPeriod = 1000;

//ENCODER VARS
unsigned long currentTime;
unsigned long loopTime;
byte encoder_A;
byte encoder_B;
byte encoder_A_prev=0;
int encCWNum=60;
int encCCWNum=60;
int defaultEncCWNum=50;
int defaultEncCCWNum=51;
unsigned char prevDir=0;

//synchro values
long number_of_received_clocks=0;
bool play_flag = false;
bool rec_flag = false;

int midiChannel=1;


void setup() 
{
  //set clkPin,dePin,swPin as INPUT

  encoder_begin(encPinB, encPinA);

  //PIN MODE
  pinMode(encPinA, INPUT);
  pinMode(encPinB, INPUT);
  pinMode(encSwPin, INPUT);

  pinMode(recLedPin, OUTPUT); 
  pinMode(recPin, INPUT); 
  pinMode(shiftPin, INPUT); 
  pinMode(stopPin, INPUT);
  pinMode(backwardPin, INPUT); 
  pinMode(forwardPin, INPUT); 

  pinMode(f1Pin, INPUT); 
  pinMode(f2Pin, INPUT); 
  pinMode(f3Pin, INPUT); 
  pinMode(f4Pin, INPUT); 
  pinMode(f5Pin, INPUT); 
  pinMode(f6Pin, INPUT); 
  pinMode(f7Pin, INPUT); 
  pinMode(f8Pin, INPUT); 

  shiftButton.attachDoubleClick(shiftBtnDoubleclick);
  //shiftButton.attachLongPressStart(shiftBtnLongPress);

  //INIT PIN VALUE
  digitalWrite(encSwPin, HIGH);
  digitalWrite(recPin, HIGH);
  digitalWrite(shiftPin, HIGH);
  digitalWrite(stopPin, HIGH);
  digitalWrite(backwardPin, HIGH);
  digitalWrite(forwardPin, HIGH);

  digitalWrite(f1Pin, HIGH);
  digitalWrite(f2Pin, HIGH);
  digitalWrite(f3Pin, HIGH);
  digitalWrite(f4Pin, HIGH);
  digitalWrite(f5Pin, HIGH);
  digitalWrite(f6Pin, HIGH);
  digitalWrite(f7Pin, HIGH);
  digitalWrite(f8Pin, HIGH);
  
  pinMode(ledPin, OUTPUT); 
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.turnThruOff();
}

void loop() 
{
  if(!rec_flag && !play_flag){
    digitalWrite(recLedPin, LOW);
  } 
  
  // keep watching the push buttons:
  shiftButton.tick();
  
  //BUTTONS
  shiftPinPrevState = setButtonHandler(shiftPin, shiftPinPrevState, 0); //70 
  stopPinPrevState = setButtonHandler(stopPin, stopPinPrevState, 93); 

  if(!shiftPinPrevState){ // SHIFT NOT PRESSED
    encCWNum=defaultEncCWNum;
    encCCWNum=defaultEncCCWNum;
    
    backwardPinPrevState = setButtonHandler(backwardPin, backwardPinPrevState, 91); 
    forwardPinPrevState = setButtonHandler(forwardPin, forwardPinPrevState, 92); 
    f1PinPrevState = setButtonHandler(f1Pin, f1PinPrevState, 54); 
    f2PinPrevState = setButtonHandler(f2Pin, f2PinPrevState, 55); 
    f3PinPrevState = setButtonHandler(f3Pin, f3PinPrevState, 56); 
    f4PinPrevState = setButtonHandler(f4Pin, f4PinPrevState, 57); 
    f5PinPrevState = setButtonHandler(f5Pin, f5PinPrevState, 58); 
    f6PinPrevState = setButtonHandler(f6Pin, f6PinPrevState, 59); 
    f7PinPrevState = setButtonHandler(f7Pin, f7PinPrevState, 60); 
    f8PinPrevState = setButtonHandler(f8Pin, f8PinPrevState, 61); 
    encSwPinPrevState = setButtonHandler(encSwPin, encSwPinPrevState, 94);
    recPinPrevState = setButtonHandler(recPin, recPinPrevState, 95);

  }else{ // SHIFT PRESSED
    encCWNum=52;
    encCCWNum=53;
    
    backwardPinPrevState = setButtonHandler(backwardPin, backwardPinPrevState, 96); 
    forwardPinPrevState = setButtonHandler(forwardPin, forwardPinPrevState, 97); 
    f1PinPrevState = setButtonHandler(f1Pin, f1PinPrevState, 62); 
    f2PinPrevState = setButtonHandler(f2Pin, f2PinPrevState, 63); 
    f3PinPrevState = setButtonHandler(f3Pin, f3PinPrevState, 64); 
    f4PinPrevState = setButtonHandler(f4Pin, f4PinPrevState, 65); 
    f5PinPrevState = setButtonHandler(f5Pin, f5PinPrevState, 66); 
    f6PinPrevState = setButtonHandler(f6Pin, f6PinPrevState, 67); 
    f7PinPrevState = setButtonHandler(f7Pin, f7PinPrevState, 68); 
    f8PinPrevState = setButtonHandler(f8Pin, f8PinPrevState, 69); 
    encSwPinPrevState = setButtonHandler(encSwPin, encSwPinPrevState, 0); //custom state to switch jogwheel to defaut MCU mode
    recPinPrevState = setButtonHandler(recPin, recPinPrevState, 98);
  }
  
  //ENCODER
  int direction = encoder_data(); // Check for rotation
  if(direction == 1){       // If its forward...
    MIDI.sendControlChange(encCWNum, 1, midiChannel);  
  }else if(direction == -1){ // If its backward...
    MIDI.sendControlChange(encCCWNum, 65, midiChannel);  
  }  

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis; 
  }
  
  if (MIDI.read())                // Is there a MIDI message incoming ?
  {   
      switch(MIDI.getType())      // Get the type of the message we caught
      {
          case midi::NoteOn:
              if(MIDI.getData1()==95){
                 rec_flag = true;  
              }
              break;  
          case midi::Start:  
              number_of_received_clocks=0;
              play_flag = true;
              break;
          case midi::Continue:
              play_flag = true;
              break;    
          case midi::Stop:
              play_flag = false;
              rec_flag = false;
              number_of_received_clocks=0;
              break;
          case midi::Clock:     
              if(play_flag) { 
                number_of_received_clocks++;
                //Serial.println(number_of_received_clocks);
                if(number_of_received_clocks%24==0) //see MIDI specification: the clock is sent 24 times for quarter note, && 120BMP=120 quarter notes for minute => BPM value= 60/time to receive 24 clocks
                {
                  updateLeds();
                }
              } 
              break;
          // See the online reference for other message types
          default:
              break;
      }
  }
}

// Switch between normal and customs MCU jogwheel mode
void shiftBtnDoubleclick() {
  toggleNonMCUWheelMode();
} 

void toggleNonMCUWheelMode(){
  if(defaultEncCWNum == 50 && defaultEncCCWNum == 51){ // Set Custom values set in Reaper to "Move cursor to grid division"
    defaultEncCWNum=54;
    defaultEncCCWNum=55;
    flashLed(ledPin,100,2);
  }else{  // Set Custom values set in Reaper to "Move cursor forward/backwward one mesure"
    defaultEncCWNum=50;
    defaultEncCCWNum=51;
    flashLed(ledPin,300,1);
  }
}

void toggleMCUWheelMode(){
  if(defaultEncCWNum != 60 && defaultEncCCWNum != 60){ //Set MCU mode
    defaultEncCWNum=60;
    defaultEncCCWNum=60;
    digitalWrite(ledPin, HIGH);
    flashLed(ledPin,100,3); 
  }
  else{
    toggleNonMCUWheelMode();
  }     
}

//void shiftBtnLongPress(){ //Default MCU Mode, cancel with double click
//    defaultEncCWNum=60;
//    defaultEncCCWNum=60;
//    digitalWrite(ledPin, HIGH);
//    flashLed(ledPin,100,3);
//}


void flashLed(int pin, int duration, int repeat) {
  for (int i=0; i < repeat; i++){  
    digitalWrite(pin, HIGH);
    delay(duration);  
    digitalWrite(pin, LOW);
    delay(duration); 
  }    
}

void updateLeds() {
    if(rec_flag){
      digitalWrite(ledPin, HIGH);
      digitalWrite(recLedPin, HIGH);
      delay(50); //high part of the clock square wave.
      digitalWrite(ledPin, LOW);
      digitalWrite(recLedPin, LOW);
    }else{
      digitalWrite(ledPin, HIGH);
      delay(50); //high part of the clock square wave.
      digitalWrite(ledPin, LOW);
    }
}

bool setButtonHandler(int pinId, bool buttonPressed, int noteNumber){
  byte pinState = digitalRead(pinId);
  if(pinState == LOW && !buttonPressed){
    if(noteNumber != 0 ){
      MIDI.sendNoteOn(noteNumber, 127,  midiChannel);
    } 
    if(noteNumber == 93){ // Stop Button
      play_flag = false;
      rec_flag = false;
      updateLeds();
    }
    if(noteNumber == 93){ // Play Button
      play_flag = true;
      number_of_received_clocks=0;
    }
    if(pinId == encSwPin && noteNumber == 0){ // Shift + Play 
      toggleMCUWheelMode();
    }
    if(noteNumber == 95){ // Rec Button
      play_flag = true;
      rec_flag = true;
      number_of_received_clocks=0;
      digitalWrite(recLedPin, HIGH);
    }
    buttonPressed=true;
    delay(100);
  }
  if(pinState == HIGH && buttonPressed ){
    if(noteNumber != 0){
      MIDI.sendNoteOff(noteNumber, 0,  midiChannel);
    }
    buttonPressed=false;
    delay(100);
  }
  return buttonPressed;
}

