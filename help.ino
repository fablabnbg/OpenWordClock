void printHelp(){
  /*
  Serial.println("$1: Calibrate your clock:");
  Serial.println("     This uses one impuls every 2 seconds for easy use with an electrical clockwork.");
  Serial.println("     Connect the electric signal from the clockwork to pin A2 which is the >VIERTEL< segment");
  Serial.println("     This automatically sets your correction-factor to the measured value!");
  Serial.println("   Syntax: $1 timeperiod iterations;");
  Serial.println("           timeperiod: numerical value. Duration of one measurement-cycle in seconds.");
  Serial.println("                       IMPORTANT!: This must be a multiple of 2 since we only see a pulse every 2 seconds from a clockwork");
  Serial.println("           iterations: numerical value. Number of measurement-cycles. The measured variances are averaged over all cycles.The factor is calculated over the average.");
  Serial.println("");
  Serial.println("$2: Set correction factor to compensate for inaccurate clock speeds.");
  Serial.println("    Syntax: $2 factor;");
  Serial.println("            factor: Double-value. The time of your clock is multiplied by this factor. If your clock is running fast set this < 1.0 and vice versa.");
  Serial.println("");
  Serial.println("$3: Set brightness when your clock is in nightmode.");
  Serial.println("    Syntax: $3 brightness;");
  Serial.println("            brightness: numerical value between 0 and 255. This directly sets the PWM duty-cycle. 0 is off and 255 is always on.");
  Serial.println("");
  Serial.println("$4: Set brightness when your clock is NOT in nightmode. -> daymode");
  Serial.println("    Syntax: $4 brightness;");
  Serial.println("            brightness: numerical value between 0 and 255. This directly sets the PWM duty-cycle. 0 is off and 255 is always on.");
  Serial.println("");
  Serial.println("$5: Set hour for nightmode to start.");
  Serial.println("    Syntax: $5 hour;");
  Serial.println("            hour: numerical value between 0 and 24. This is the hour to which your nightmode starts.");
  Serial.println("                  IMPORTANT!: This has to be greater than your nightmode-end! Nightmode is only available for timeperiods through midnight! If you don't want your nightmode to be somewhen over midnight - just use nightmode as your daymode an set the brightnes settings accordingly. If you don't want any nightmode at all - just set both brightnes settings equal.");
  Serial.println("");
  Serial.println("$6: Set hour for nightmode to end.");
  Serial.println("    Syntax: $6 hour;");
  Serial.println("            hour: numerical value between 0 and 24. This is the hour to which your nightmode ends.");
  Serial.println("                  IMPORTANT!: This has to be greater than your nightmode-start! See above for more information.");
  Serial.println("");
  Serial.println("$7: Set fading speed.");
  Serial.println("    Syntax: $7 time;");
  Serial.println("            time: numerical value between 0 and 500. Sets the time it takes to fade over to the next time-display. The brighter your brightness-settings the better this feature works!");
  Serial.println("");
  Serial.println("exit: Exit programming-mode");
  Serial.println("");
  Serial.println("For command termination you have the choice between EITHER ; OR \n!");
  Serial.println("");
  */
}
