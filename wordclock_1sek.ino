/*
MINI WORDCLOCK
 
 Simple wordclock sketch that uses the arduino pins for the words directly.
 v02: now supports dimming
 v03: store things in eeprom and added serial-mode for config
 
 By Kilian Bock
 */
#define ver 3

////////////
//LIBRARIES
////////////
#include <SoftPWM.h>
#include <EEPROMex.h>

/////////////////
//DEFINITIONS
/////////////////
#define EsIst 0
#define Fuenf A5
#define Zehn A4
#define Vor A0
#define Nach A1
#define Viertel A2
#define Halb A3
#define Eins 1
#define Zwei 2
#define Drei 3
#define Vier 4
#define Fuenf_z 5
#define Sechs 6
#define Sieben 7
#define Acht 8
#define Neun 9
#define Zehn_z 10
#define Elf 11
#define Zwoelf 12
#define Uhr 13
#define Button_hour A6
#define Button_min A7

//dimming settings
//clock initializes at 00:00
byte dim_night = 15; //value between 0 and 255
byte dim_day = 255; //value between 0 and 255
byte night_start = 23; //hour in 24 hour format (no comma please! Keep start > end!!!)
byte night_end = 6; //hour in 24 hour format (no comma please! Keep start > end!!!)

int fadetime = 500;

double factor = 1;

int sekunden = 0;
int minuten = 0;
int stunde = 0;
int add = 0;
int state = 0;
int hour_display = 0;
int dim = 255;
boolean nightmode = false;
boolean smode = false;

int stunden[] = {
  Zwoelf, Eins, Zwei, Drei, Vier, Fuenf_z, Sechs, Sieben, Acht, Neun, Zehn_z, Elf, Zwoelf};

unsigned long time = 0;
unsigned long timeadd = 0;


byte vercheck = 0;






//////////////////
//SETUP
//////////////////
void setup() {

  //only read values if version numbers match
  vercheck = EEPROM.read(0);
  if (vercheck == ver){
    readValues();
  }

  //serial-mode?
  if(analogRead(Button_hour) > 512 && analogRead(Button_min) > 512 ){
    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);
    delay(500);
    digitalWrite(6, LOW);
    delay(500);
    serialmode();
  }

  //initial calibrate?
  if(EEPROM.read(84) != 42){
    Serial.begin(9600);
    
    factor = calibrate(15, 2);
    EEPROM.writeDouble(1, factor);
    EEPROM.update(84, 42);
    
    Serial.end();
  } else {
    factor = EEPROM.readDouble(1);
  }

  SoftPWMBegin();

  SoftPWMSet(EsIst, 0); // Es Ist
  SoftPWMSet(Fuenf, 0); // Fünf
  SoftPWMSet(Zehn, 0); // Zehn
  SoftPWMSet(Vor, 0); //Vor
  SoftPWMSet(Nach, 0); //Nach
  SoftPWMSet(Viertel, 0); //Viertel
  SoftPWMSet(Halb, 0); //Halb
  SoftPWMSet(Eins, 0); // EINS
  SoftPWMSet(Zwei, 0); // ZWEI
  SoftPWMSet(Drei, 0); //DREI
  SoftPWMSet(Vier, 0); //VIER
  SoftPWMSet(Fuenf_z, 0); //FÜNF
  SoftPWMSet(Sechs, 0); //SECHS
  SoftPWMSet(Sieben, 0); // SIEBEN
  SoftPWMSet(Acht, 0); // ACHT
  SoftPWMSet(Neun, 0); // NEUN
  SoftPWMSet(Zehn_z, 0); // ZEHN
  SoftPWMSet(Elf, 0); // ELF
  SoftPWMSet(Zwoelf, 0); // ZWÖLF
  SoftPWMSet(Uhr, 0); // UHR
  //pinMode(Button_hour, INPUT_PULLUP);
  //pinMode(Button_min, INPUT_PULLUP);

  SoftPWMSetFadeTime(ALL, fadetime, fadetime);

  SoftPWMSet(EsIst, dim); // Es Ist initialisieren

} //end setup

//////////////////
//LOOP
//////////////////
void loop() {


  //ZEIT Einstellen

  if(analogRead(Button_hour) > 512){
    delay(200);
    timeadd += (60*60);
  }
  else if(analogRead(Button_min) > 512){
    delay(200);
    timeadd += 60;
  }

  //ZEIT

  time = millis()*factor;
  sekunden = second();
  minuten = minute();
  stunde = hour();

  //Nightmode?
  if(stunde >= night_start || stunde < night_end) {
    if(!nightmode){
      dim = dim_night;
      state = 0;
      SoftPWMSet(EsIst, dim); // Es Ist
      nightmode = true;
    }
  }
  else {
    if (nightmode){
      dim = dim_day;
      state = 0;
      SoftPWMSet(EsIst, dim); // Es Ist
      nightmode = false;
    }
  }


  if((minuten < 2) || (minuten == 2 && sekunden <= 30)){             // GANZ
    if(state != 1 || stunde + add == 1){
      allow();
      SoftPWMSet(Uhr, dim);
      add = 0;
      state = 1;
    }
  }
  else if((minuten < 7) || (minuten == 7 && sekunden <= 30)){        // Fuenf
    if(state != 2){
      allow();
      SoftPWMSet(Fuenf, dim);
      SoftPWMSet(Nach, dim);
      add = 0;
      state = 2;
    }
  }
  else if((minuten < 12) || (minuten == 12 && sekunden <= 30)){       // Zehn
    if(state != 3){
      allow();
      SoftPWMSet(Zehn, dim);
      SoftPWMSet(Nach, dim);
      add = 0;
      state = 3;
    }
  }
  else if((minuten < 17) || (minuten == 17 && sekunden <= 30)){       // Viertel
    if(state != 4){
      allow();
      SoftPWMSet(Viertel, dim);
      add = 1;
      state = 4;
    }
  }
  else if((minuten < 22) || (minuten == 22 && sekunden <= 30)){       // Zehn vor Halb
    if(state != 5){
      allow();
      SoftPWMSet(Zehn, dim);
      SoftPWMSet(Vor, dim);
      SoftPWMSet(Halb, dim);
      add = 1;
      state = 5;
    }
  }
  else if((minuten < 27) || (minuten == 27 && sekunden <= 30)){       // Fuenf vor Halb
    if(state != 6){
      allow();
      SoftPWMSet(Fuenf, dim);
      SoftPWMSet(Vor, dim);
      SoftPWMSet(Halb, dim);
      add = 1;
      state = 6;
    }
  }
  else if((minuten < 32) || (minuten == 32 && sekunden <= 30)){       // Halb
    if(state != 7){
      allow();
      SoftPWMSet(Halb, dim);
      add = 1;
      state = 7;
    }
  }
  else if((minuten < 37) || (minuten == 37 && sekunden <= 30)){       // Fuenf nach Halb
    if(state != 8){
      allow();
      SoftPWMSet(Fuenf, dim);
      SoftPWMSet(Nach, dim);
      SoftPWMSet(Halb, dim);
      add = 1;
      state = 8;
    }
  }
  else if((minuten < 42) || (minuten == 42 && sekunden <= 30)){       // Zehn nach Halb
    if(state != 9){
      allow();
      SoftPWMSet(Zehn, dim);
      SoftPWMSet(Nach, dim);
      SoftPWMSet(Halb, dim);
      add = 1;
      state = 9;
    }
  }
  else if((minuten < 47) || (minuten == 47 && sekunden <= 30)){       // Viertel vor
    if(state != 10){
      allow();
      SoftPWMSet(Viertel, dim);
      SoftPWMSet(Vor, dim);
      add = 1;
      state = 10;
    }
  }
  else if((minuten < 52) || (minuten == 52 && sekunden <= 30)){       // Zehn vor
    if(state != 11){
      allow();
      SoftPWMSet(Zehn, dim);
      SoftPWMSet(Vor, dim);
      add = 1;
      state = 11;
    }
  }
  else if((minuten < 57) || (minuten == 57 && sekunden <= 30)){       // Fuenf vor
    if(state != 12){
      allow();
      SoftPWMSet(Fuenf, dim);
      SoftPWMSet(Vor, dim);
      add = 1;
      state = 12;
    }
  }
  else if((minuten < 60) || (minuten == 60 && sekunden <= 60)){       // GANZ
    if(state != 13 || stunde + add == 1){
      allow();
      SoftPWMSet(Uhr, dim);
      add = 1;
      state = 13;
    }
  }
  else {
    while (true){
      SoftPWMSet(13, dim);
      delay(1000);
      SoftPWMSet(13, dim);
      delay(1000);
    }
  }

  display_hour(add);

  //reset?
  if((time + timeadd*1000) >= 2592000000){
    softReset();
  }

} //end loop






///////////
//METHODS
///////////
byte second(){
  byte ret = (time/1000 + timeadd) % 60;
  return ret;
}

byte minute(){
  byte ret = ((time/1000 + timeadd) / 60) % 60;
  return ret;
}
byte hour(){
  byte ret = ((time/1000 + timeadd) / 60 / 60) % 24;
  return ret;
}

void display_hour(int next){
  hour_display = stunden[(stunde%12) + next];
  for(int i = 0; i <= 12; i++){
    if(hour_display == stunden[i]){
      SoftPWMSet(stunden[i], dim);
    } 
    else {
      SoftPWMSet(stunden[i], 0);
    }
  }
}

void allow(){
  SoftPWMSet(Fuenf, 0);
  SoftPWMSet(Zehn, 0);
  SoftPWMSet(Vor, 0);
  SoftPWMSet(Nach, 0);
  SoftPWMSet(Viertel, 0);
  SoftPWMSet(Halb, 0);
  SoftPWMSet(Uhr, 0);
}

void softReset(){
  allow();
  timeadd = 0;
  asm volatile ("  jmp 0");
}

void readValues(){
  factor = EEPROM.readDouble(1);  //factor
  dim_night = EEPROM.read(10);  //dim_night
  dim_day = EEPROM.read(11);  //dim_day
  night_start = EEPROM.read(12);  //night_start
  night_end = EEPROM.read(13);  //night_end
  fadetime = EEPROM.readInt(14);  //fadetime
}
