# OliMid-U

![OliMid-U](https://github.com/oliou/OliMid-U/blob/master/OliMid-U%20small.JPG?raw=true)


## Presentation

OliMid-U is a partially MCU compliant MIDI/USB controller built around an Arduino Uno Board, a rotary encoder, several momentary buttons and the lid of a small Vegemite jar. 
The primary reason for that project is Firewire being obsolete (and not included in my future laptop), forcing me to plan for the replacement of my Tascam Fireone audio interface which includes a very convenient MIDI controller built around a huge jog-wheel. And to use that Arduino board taking the dust for a long time.

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

## Manual

![Panel](https://github.com/oliou/OliMid-U/blob/master/panel.jpg?raw=true)

### Wheel Modes


### Midi Mapping

Button       | Shift Released| Shift Pressed
------------ | ------------- | -------------
Play / Pause | | 
Stop | |
Rec | |  
> | | 
< | | 
F1 | | 
F2 | | 
F3 | | 
F4 | | 
F5 | | 
F6 | | 
F7 | | 
F8 | | 


## What else?

To add a setup mode to assign controller/note numbers on the fly? (See https://www.arduino.cc/en/Reference/EEPROM )
