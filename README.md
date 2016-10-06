# OpenWordClock

Simple project for building your own Wordclock with Arduino. 
The wordclock frame is based on the well known Ikea Ribba frame 25x25cm.
The front and the inserts are made with a lasercutter. Compared to other projects this version doesn´t need any other components or pcb.
the 42 LEDS are directly connected to the atmega chip.
Just flash files to your Arduino of choice (you'll need A6/A7). Code was tested on an ATmega328P and 168P(seperate branch!)

Connect LEDs with appropriate resistor directly to your Arduino pins:
* Eins: D1
* [...]
* Zwölf: D12
* EsIst: D0
* Uhr: 13
* Vor: A0
* Nach: A1
* Viertel: A2
* Halb: A3
* Zehn: A4
* Fünf: A5

Buttons:
* Button_hour: A6
* Button_min: A7 
