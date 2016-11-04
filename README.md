# OliMid-U

![OliMid-U](https://github.com/oliou/OliMid-U/blob/master/OliMid-U%20small.JPG?raw=true)


## Presentation

OliMid-U is a partially MCU compliant MIDI/USB controller built around an Arduino Uno Board, a rotary encoder, several momentary buttons and the lid from a small Vegemite jar. 
The primary reason for that project is Firewire being obsolete (and probably not included in my future laptop), pushing me to plan for the replacement of my Tascam Fireone audio interface, which includes a very convenient MIDI controller built around a huge jog-wheel. And to use that Arduino board, which has been sleeping on the shelf for too long.

## Pre-requisite 

The Arduino requires to be flashed with the HIDUINO firmware.

https://github.com/ddiakopoulos/hiduino

http://www.instructables.com/id/Recompile-Rename-and-Flash-HIDUINO-with-ISP-to-tur/  

You will need an [ISP Programmer Module](http://www.ebay.com.au/itm/AVR-USB-Tiny-ISP-Programmer-Module-USB-Download-Interface-Board-For-Arduino-OK-/281823675251?hash=item419e000373:g:2z8AAOSw9mFWGKyc).

## External Libraries

[OneButton](https://github.com/mathertel/OneButton) for handling long and double press

[Encoder Polling](https://github.com/frodofski/Encoder_Polling) for handling encoder direction


## Components

x1 [Arduino Uno](http://www.ebay.com.au/itm/Arduino-UNO-R3-Arduino-Clone-Compatible-Uno-R3-USB-Cable-AU-Stock-/131606915147?hash=item1ea462284b:g:BBgAAOSwpLNYADtu)

x1 [rotary encoder](http://www.ebay.com.au/itm/Rotary-Encoder-Module-Brick-Sensor-Development-Board-Test-For-Arduino-New-OG-/281937129178?hash=item41a4c32eda:g:S~IAAOSwFNZWwqfc)

x1 [158x90x60mm project enclosure](http://www.ebay.com.au/itm/Plastic-Waterproof-Cover-Clear-Electronic-Project-Box-Enclosure-Case-158x90x60mm-/282179016699?hash=item41b32e17fb:g:AWEAAOSwAuZX1qnb)

x1 [momentary button with red led](http://www.ebay.com.au/itm/2-Pcs-4-Terminals-Red-LED-Lamp-Momentary-Push-Button-Switch-DC-3V-DW-/291688533314?hash=item43e9fdcd42:g:OjoAAOSwKtVWxs7V)

x12 momentary buttons

x1 green led

x1 lid from a small Vegemite jar


## Manual

![Panel](https://github.com/oliou/OliMid-U/blob/master/panel.png?raw=true)

### Midi Mapping
Button       | Shift Released| Shift Pressed
------------ | ------------- | -------------
Play / Pause | Note 94 | Green flash twice: Set the wheel in MCU mode: CW*: CC60 val:1, CCW**: CC***60 val:65;  Green flash once: back to regular mode
Stop | Note 93 | /
Rec | Note 95 |  Note 98 
Wheel CW, mode 1 (Default)|CC: 50 val:1  | CC: 52 val:1
Wheel CCW, mode 1 (Default)|CC: 51 val:65 | CC: 53 val:65
Wheel CW, mode 2 (Double press on shift)|CC: 54 val:1  | CC: 52 val:1
Wheel CCW, mode 2 (Double press on shift)|CC: 55 val:65 | CC: 53 val:65
Wheel CW, MCU mode (shift+Play)|CC: 60 val:1  | CC: 52 val:1
Wheel CCW, MCU mode (Shift+Play)|CC: 60 val:65 | CC: 53 val:65
> | Note 92| Note 97
< | Note 91| Note 96 
F1 | Note 54| Note 62
F2 | Note 55| Note 63
F3 |Note 56 | Note 64
F4 |Note 57 | Note 65
F5 | Note 58| Note 66
F6 | Note 59| Note 67
F7 | Note 60| Note 68
F8 | Note 61| Note 69

*CW: Clock-Wise
**CCW: Counter Clock-Wise
***CC: Control Change

### Wheel Modes
Modes       | Command | Visual feedback
------------ | ------------- | -------------
Mode 1 (Default) |Shift double-press from mode 2, shift + play from MCU mode |x1 long Green flash
Mode 2 |Double-press on shift to enter,  double-press to revert to mode 1 | x2 short Green flash
MCU |shift + play to enter,  shift + play to revert to mode 1 | x3 short Green flash


### Visual feedback
 Context  | Green Led | Red Led
------------ | ------------- | -------------
Play | Flash in sync with MIDI BPM |  /
Record |  Flash in sync with MIDI BPM |  Flash in sync with MIDI BPM
Switch to mode 1 |  x1 long Green flash |  /
Switch to mode 2 |  x2 short Green flash |  /
Switch to MCU mode |  x3 short Green flash |  /

## What's Next?

To add a setup mode to assign controller/note numbers on the fly and offline persistence? (See https://www.arduino.cc/en/Reference/EEPROM )

