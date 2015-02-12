//Pins
int pulsePin = A0;                // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat

// Runs all the Pulsi programs
int pulsiRun = 3;

//Temperature
//float because we want to use a decimal point. - slower than int
int tempIn = A1;
float temperature;
int teperatureValue = 0;
int temperatureCsharp = 0;

//Heartbeat
volatile int BPM;                   // used to hold the pulse rate
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // holds the time between beats, must be seeded! 
volatile boolean Pulse = false;     // true when pulse wave is high, false when it's low
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

volatile int pulseCounter = 0;      // Counter for Heartbeat value to C#

//Communication
String message = "";
String command = "";
String comValues= "";

void setup(){
  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  Serial.begin(9600);               // we agree to talk fast!
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 
}

void loop(){
  
  if(pulsiRun == 1)        // This mode measures the heartbeat.
  {
    Heartbeat();
  }
  else if(pulsiRun == 2)  // This mode measures the Temperature.
  {
    Temperature();    
  }
  else if(pulsiRun == 3)  // This mode can accept and receive Commands (heartbeat will still be shown with the LED).
  {
      Commands();  
  }
}



