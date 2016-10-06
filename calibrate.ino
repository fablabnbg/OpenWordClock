double calibrate(int timeperiod, int iterations){

  #define signalPin A2 //Pin of external clock signal
  
  unsigned long time1 = 0;
  unsigned long time2 = 0;
  long sum = 0;
  long add = 0;
  double average = 0;
  double factor = 0;
  long richtwert = timeperiod*1000000;

  pinMode(signalPin, INPUT);
  
  Serial.print("Intervall for measurement: ");
  Serial.println(timeperiod);
  Serial.print("Iterations: ");
  Serial.println(iterations);
  Serial.println();
  Serial.println("Start");
  Serial.println();


  for(int i = 0; i < iterations; i++){
    while(analogRead(signalPin) > 150){}
    while(analogRead(signalPin) < 150){}
    time1 = micros();
    for(int t = 0; t < timeperiod; t++){
      Serial.print(".");
      while(analogRead(signalPin) > 150){/*Serial.println(analogRead(signalPin));*/}
      while(analogRead(signalPin) < 150){}
    }
    time2 = micros();
    add = (time2-time1)-richtwert;
    sum += add; //sum up all iterations for later averaging
    Serial.print("Abweichung ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(add);
  }
  average = sum/iterations;
  factor = (richtwert/1000)/((richtwert + average)/1000);
  Serial.print("Durchschnittliche Abweichung: ");
  Serial.println(average);
  Serial.print("Faktor: ");
  Serial.println(factor, 10);
  Serial.println();
  
  
  return factor;
}
