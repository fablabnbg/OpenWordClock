void serialmode(){
  smode = true;
  String command = "";
  String buf = "test";
  char next;
  boolean finishedc = false;
  boolean finishedaa = false;
  boolean finishedab = false;
  String arga = "";
  String argb = "";
  Serial.begin(9600);
  
  //check version
  if (vercheck != ver){
    Serial.println("EEPROM VALUES:");
    Serial.print("factor: ");
    Serial.println(EEPROM.readDouble(1), 20);  //factor
    Serial.print("dim_night: ");
    Serial.println(EEPROM.read(10));  //dim_night
    Serial.print("dim_day: ");
    Serial.println(EEPROM.read(11));  //dim_day
    Serial.print("night_start: ");
    Serial.println(EEPROM.read(12));  //night_start
    Serial.print("night_end: ");
    Serial.println(EEPROM.read(13));  //night_end
    Serial.print("fadetime: ");
    Serial.println(EEPROM.readInt(14));  //fadetime
    Serial.println();
    Serial.println("DEFAULT VALUES:");
    printData();
    
    boolean answered = false;
    while(!answered){
      Serial.println("Version numbers don't match! Restore default Values? Y/N ('K' to keep factor)");
      while(Serial.available() <= 0){}
      next = Serial.read();
      if (next == 'Y') {
        answered = true;
        EEPROM.writeDouble(1, factor);  //factor
        EEPROM.write(10, dim_night);  //dim_night
        EEPROM.write(11, dim_day);  //dim_day
        EEPROM.write(12, night_start);  //night_start
        EEPROM.write(13, night_end);  //night_end
        EEPROM.writeInt(14, fadetime);  //fadetime
      } else if(next == 'K'){
        answered = true;
        EEPROM.write(10, dim_night);  //dim_night
        EEPROM.write(11, dim_day);  //dim_day
        EEPROM.write(12, night_start);  //night_start
        EEPROM.write(13, night_end);  //night_end
        EEPROM.writeInt(14, fadetime);  //fadetime
      } else if(next == 'N'){
        answered = true;
        readValues();
      } else {
        Serial.println("Please answer my question first!");
      }
      EEPROM.update(0, ver);
      EEPROM.update(84, 42);
    }
  }

  while(smode){
    
    Serial.println("Type help; for help.");
    printData();

    //get command
    buf = "";
    while (!finishedc){
      if (Serial.available() > 0) {
        next = Serial.read();
        if (next == ' ' || next == ';' || next == '\n'){
          if(next == ';' || next == '\n'){
            finishedaa = true;
            finishedab = true;
          }
          command = buf;
          finishedc = true;
        }
        else {
          buf += next;
          //Serial.println(next);
          //Serial.println(buf);
        }
      }
    }
    //Serial.println(command);

    //get arga
    buf = "";
    while (!finishedaa){
      while (Serial.available() <= 0) {}
      next = Serial.read();
      if (next == ' ' || next == ';' || next == '\n'){
        if(next == ';' || next == '\n'){
          finishedab = true;
        }
        arga = buf;
        finishedaa = true;
      }
      else {
        buf += next;
      }
    }
    //Serial.println(arga);

    //get argb
    buf = "";
    while (!finishedab){
      while (Serial.available() <= 0) {}
      next = Serial.read();
      if (next == ' ' || next == ';' || next == '\n'){
        //throw anything away after argb until the ; comes
        while(next != ';' && next != '\n'){
          next = Serial.read();
        }
        argb = buf;
        finishedab = true;
      }
      else {
        buf += next;
      }
    }
    //Serial.println(argb);

    if (command == "$1"){    // calibrate
      //if ((arga.toInt()%2) != 0) {
      //  Serial.println("Time must be multiple of 2!");
      //} else {
        factor = calibrate(arga.toInt(), argb.toInt());
        EEPROM.writeDouble(1, factor);
        Serial.println("Factor succesfully updated!");
      //}
    }

    else if (command == "$2") {    //set factor
      char temp[arga.length()];
      arga.toCharArray(temp, arga.length()+1);
      double writefactor = atof(temp);
      if(arga != "" && writefactor != factor) {
        factor = writefactor;
        EEPROM.writeDouble(1, factor);
        Serial.println("Factor succesfully updated!");
      } else {
        Serial.println("Error!");
      }
    }

    else if (command == "$3") {    //set dim_night
      if (arga != "" && arga.toInt() != dim_night && arga.toInt() >= 0 && arga.toInt() <= 255){
        dim_night = arga.toInt();
        EEPROM.write(10, dim_night);  //dim_night
        Serial.println("dim_night succesfully updated!");
      } 
      else {
        Serial.println("dim_night: Illegal argument! Type help; for more information.");
      }
    }

    else if (command == "$4") {    //set dim_day
      if (arga != "" && arga.toInt() != dim_day && arga.toInt() >= 0 && arga.toInt() <= 255){
        dim_day = arga.toInt();
        EEPROM.write(11, dim_day);  //dim_day
        Serial.println("dim_day succesfully updated!");
      } 
      else {
        Serial.println("dim_day: Illegal argument! Type help; for more information.");
      }
    }

    else if (command == "$5") {    //set night_start
      if (arga != "" && arga.toInt() != night_start && arga.toInt() > night_end && arga.toInt() < 24){
        night_start = arga.toInt();
        EEPROM.write(12, night_start);  //night_start
        Serial.println("night_start succesfully updated!");
      } 
      else {
        Serial.println("night_start: Illegal argument! Type help; for more information.");
      }
    }

    else if (command == "$6") {    //set night_end
      if (arga != "" && arga.toInt() != night_end && arga.toInt() < night_start && arga.toInt() < 24){
        night_end = arga.toInt();
        EEPROM.write(13, night_end);  //night_end
        Serial.println("night_end succesfully updated!");
      } 
      else {
        Serial.println("night_end: Illegal argument! Type help; for more information.");
      }
    }

    else if (command == "$7") {    //set fadetime
      if (arga != "" && arga.toInt() != fadetime && arga.toInt() >= 0 && arga.toInt() <= 500){
        fadetime = arga.toInt();
        EEPROM.writeInt(14, fadetime);  //fadetime
        Serial.println("fadetime succesfully updated!");
      } 
      else {
        Serial.println("fadetime: Illegal argument! Type help; for more information.");
      }
    }

    else if (command == "help") {
      //printHelp();            //TODO!!!
      Serial.println("Sorry! Can't help you yet.");
    }
    
    else if (command == "exit") {
      smode = false;
    }

    else {
      Serial.print("How do I ");
      Serial.print(command);
      Serial.println("?");
    }

    finishedc = false;
    finishedaa = false;
    finishedab = false;
    arga = "";
    argb = "";
    command = "";
    
    Serial.println();
    
  } //end while(smode)

  Serial.end();
} //end serialmode

void printData(){
  Serial.print("$2 Factor: ");
  Serial.println(factor, 20);
  Serial.print("$3 dim_night: ");
  Serial.println(dim_night);
  Serial.print("$4 dim_day: ");
  Serial.println(dim_day);
  Serial.print("$5 night_start: ");
  Serial.println(night_start);
  Serial.print("$6 night_end: ");
  Serial.println(night_end);
  Serial.print("$7 fadetime: ");
  Serial.println(fadetime);
  Serial.println();
  delay(500);
}
