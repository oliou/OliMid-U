///////////////////////////////////////////////////////////
//  OliMid-U.ino                                         //
//                                                       //
//  https://github.com/oliou/OliMid-U                    //
//                                                       //
///////////////////////////////////////////////////////////

#include <MIDI.h>
#include <OneButton.h> // https://github.com/mathertel/OneButton
#include <Encoder_Polling.h> // https://github.com/frodofski/Encoder_Polling
#include <EEPROM.h>


MIDI_CREATE_DEFAULT_INSTANCE();

// PINOUT VARS
const int encAPin= 2; //the clk attach to pin 2
const int encBPin= 3; //the dt pin attach to pin 3
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

//Default note/CC values
int encCwMCUDefNum=60;
int encCcwMCUDefNum=60;
int encCwMode1DefNum=50;
int encCcwMode1DefNum=51;
int encCwMode2DefNum=52;
int encCcwMode2DefNum=53;


const int ledDefNum = 13; 
const int recLedDefNum = A0; 
const int recDefNum = A1; 
const int shiftDefNum = 0; 
const int stopDefNum = 93; 

const int encSwDefNumA = 94;
const int backwardDefNumA = 91; 
const int forwardDefNumA = 92; 
const int f1DefNumA = 54;
const int f2DefNumA = 55;
const int f3DefNumA = 56;
const int f4DefNumA = 57;
const int f5DefNumA = 58;
const int f6DefNumA = 59;
const int f7DefNumA = 60;
const int f8DefNumA = 61; 

const int encSwDefNumB = 0;
const int backwardDefNumB = 96; 
const int forwardDefNumB = 97; 
const int f1DefNumB = 62;
const int f2DefNumB = 63;
const int f3DefNumB = 64;
const int f4DefNumB = 65;
const int f5DefNumB = 66;
const int f6DefNumB = 67;
const int f7DefNumB = 68;
const int f8DefNumB = 69; 

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

unsigned char prevDir=0;

//synchro values
long number_of_received_clocks=0;
bool play_flag = false;
bool rec_flag = false;

int midiChannel=1;

bool setMode = false;

void setup() 
{
  //set clkPin,dePin,swPin as INPUT

  encoder_begin(encBPin, encAPin);

  //PIN MODE
  pinMode(encAPin, INPUT);
  pinMode(encBPin, INPUT);
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
  
  //BUTTONS ASSIGNEMENT
  shiftPinPrevState = setButtonHandler(shiftPin, shiftPinPrevState, 0); //70 
  stopPinPrevState = setButtonHandler(stopPin, stopPinPrevState, stopDefNum); 
  recPinPrevState = setButtonHandler(recPin, recPinPrevState, 95);

  if(!shiftPinPrevState){ // SHIFT NOT PRESSED; MODE A
    encCwMCUDefNum=encCwMode1DefNum;
    encCcwMCUDefNum=encCcwMode1DefNum;
    
    backwardPinPrevState = setButtonHandler(backwardPin, backwardPinPrevState, backwardDefNumA); 
    forwardPinPrevState = setButtonHandler(forwardPin, forwardPinPrevState, forwardDefNumA); 
    f1PinPrevState = setButtonHandler(f1Pin, f1PinPrevState, f1DefNumA); 
    f2PinPrevState = setButtonHandler(f2Pin, f2PinPrevState, f2DefNumA); 
    f3PinPrevState = setButtonHandler(f3Pin, f3PinPrevState, f3DefNumA); 
    f4PinPrevState = setButtonHandler(f4Pin, f4PinPrevState, f4DefNumA); 
    f5PinPrevState = setButtonHandler(f5Pin, f5PinPrevState, f5DefNumA); 
    f6PinPrevState = setButtonHandler(f6Pin, f6PinPrevState, f6DefNumA); 
    f7PinPrevState = setButtonHandler(f7Pin, f7PinPrevState, f7DefNumA); 
    f8PinPrevState = setButtonHandler(f8Pin, f8PinPrevState, f8DefNumA); 
    encSwPinPrevState = setButtonHandler(encSwPin, encSwPinPrevState, encSwDefNumA);

  }else{ // SHIFT PRESSED; MODE B
    encCwMCUDefNum=encCwMode2DefNum;
    encCcwMCUDefNum=encCcwMode2DefNum;
    
    backwardPinPrevState = setButtonHandler(backwardPin, backwardPinPrevState, backwardDefNumB); 
    forwardPinPrevState = setButtonHandler(forwardPin, forwardPinPrevState, forwardDefNumB); 
    f1PinPrevState = setButtonHandler(f1Pin, f1PinPrevState, f1DefNumB); 
    f2PinPrevState = setButtonHandler(f2Pin, f2PinPrevState, f2DefNumB); 
    f3PinPrevState = setButtonHandler(f3Pin, f3PinPrevState, f3DefNumB); 
    f4PinPrevState = setButtonHandler(f4Pin, f4PinPrevState, f4DefNumB); 
    f5PinPrevState = setButtonHandler(f5Pin, f5PinPrevState, f5DefNumB); 
    f6PinPrevState = setButtonHandler(f6Pin, f6PinPrevState, f6DefNumB); 
    f7PinPrevState = setButtonHandler(f7Pin, f7PinPrevState, f7DefNumB); 
    f8PinPrevState = setButtonHandler(f8Pin, f8PinPrevState, f8DefNumB); 
    encSwPinPrevState = setButtonHandler(encSwPin, encSwPinPrevState, encSwDefNumB); //custom state to switch jogwheel to defaut MCU mode
  }
  
  //ENCODER
  int direction = encoder_data(); // Check for rotation
  if(direction == 1){       // If its forward...
    MIDI.sendControlChange(encCwMCUDefNum, 1, midiChannel);  
  }else if(direction == -1){ // If its backward...
    MIDI.sendControlChange(encCcwMCUDefNum, 65, midiChannel);  
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
  if(encCwMode1DefNum == 50 && encCcwMode1DefNum == 51){ // Set Custom values set in Reaper to "Move cursor to grid division"
    encCwMode1DefNum=54;
    encCcwMode1DefNum=55;
    flashLed(ledPin,100,2);
  }else{  // Set Custom values set in Reaper to "Move cursor forward/backwward one mesure"
    encCwMode1DefNum=50;
    encCcwMode1DefNum=51;
    flashLed(ledPin,300,1);
  }
}

void toggleMCUWheelMode(){
  if(encCwMode1DefNum != 60 && encCcwMode1DefNum != 60){ //Set MCU mode
    encCwMode1DefNum=60;
    encCcwMode1DefNum=60;
    digitalWrite(ledPin, HIGH);
    flashLed(ledPin,100,3); 
  }
  else{
    toggleNonMCUWheelMode();
  }     
}

//void shiftBtnLongPress(){ //Default MCU Mode, cancel with double click
//    encCwMode1DefNum=60;
//    encCcwMode1DefNum=60;
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

