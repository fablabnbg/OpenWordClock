# OpenWordClock

Simple wordclock project. Just flash files to your Arduino of choice (you'll need A6/A7). Code was tested on an ATmega328P and 168P (seperate branch!)

Connect LEDs with 150 ohm resistors directly to your Arduino pins:
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
