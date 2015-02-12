void Commands()
{
  if (Serial.available() > 0) {
    // read the incoming byte:
    int incomingByte = Serial.read();

    // say what you got:
    //Serial.print("I received: ");
    char receivedCharacter = (char) incomingByte;
    //Serial.println(receivedCharacter);
    message += receivedCharacter;

    int commandStart = message.indexOf("#");
    int commandEnd = message.indexOf(":");
    int commandValue = message.indexOf("%");

    if (commandStart != -1 && commandEnd != -1 && commandValue != -1)
    {
      int commandLengte = commandEnd - commandStart + 1;
      command = message.substring(commandStart, commandLengte);

      int valueLength = commandValue - commandStart + 1;
      comValues = message.substring(commandEnd + 1, valueLength);

      // CATCHES C# COMMAND TO MEASURE THE BPM (WHICH IS BASED ON 1 MINUTE DIVIDED TO THE AVARAGE OF 10 IBI VALUES)
      if(command == "#SHOW:" && comValues == "BPM%")
      {
        message = "";
        pulsiRun = 1;
        // Because of interrupts the message to C# has to be send from the Heartbeat_interrupt code
      }
      // CATCHES C# COMMAND TO MEASURE TEMPERATURE.
      if(message == "#SHOW:temperature%")
      {
        message = "";
        pulsiRun = 2;
      }
     // Because of interrupts the message to C# has to be send from the Temperature code   
    }
  }
}

void Heartbeat()
{
  if (QS == true){                     // Quantified Self flag is true when arduino finds a heartbeat
    QS = false;                        // reset the Quantified Self flag for next time    
  } 
  delay(20);                           //  take a break
}


