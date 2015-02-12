//Temperature sensitivity = 10 mV/ºC
//Output Voltage = 500 mV for 0 ºC.

int arrayTemperature[5];
float avarageTemperature = 0;

void TemperatureMeasure()
{

  //Converting analog input to voltage. Max voltage = 5V, Analog resolution = 10 bits,
  //Which means 1024 values. Analog input = analogRead value * Voltage / 1024 (1 step of
  //analogRead). To make this a floating point operation instead of integer we add .0 to
  //1024.
  temperature = analogRead(tempIn)*5/1024.0;

  //To calibrate to 0 ºC the difference between the voltage read and 500mV is
  // linearily dependent on the temperature.
  temperature = temperature - 0.5;

  //This difference is divided by 10mV/step which results in temperature.
  temperature = temperature / 0.01;

  // To convert to body measurements.
  temperature = temperature + 4;
  
  // To make sure the measurement outcome is above 0
  temperature = (temperature * temperature);
  temperature = sqrt(temperature);

  //Serial.println(temperature);
  delay(500);    
}

void Temperature()
{
  unsigned long startedAt = millis();
  while(millis() - startedAt < 10000)
  {    
    TemperatureMeasure();
    avarageTemperature = 0;

    for(int i=0; i<4; i++){
      arrayTemperature[i] = arrayTemperature[i+1];
      avarageTemperature += arrayTemperature[i];  
    } 
    arrayTemperature[4] = temperature;    
    avarageTemperature += arrayTemperature[4];
    avarageTemperature = avarageTemperature /= 5; 

  }
  String string1 = "#TEMPERATURE:";          // Because of interrupts the message has to be send from within this code
  String string2 = "%";                      // and not from the communication code.
  String string3 = string1 + avarageTemperature + string2;
  Serial.println(string3);
  pulsiRun = 3;  
}





