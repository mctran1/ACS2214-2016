#include <PID_v1.h>
#define START_CMD_CHAR '*'
#define CMD_ANALOGWRITE 11

const int photores = A0; // Photo resistor input
const int pot = A1; // Potentiometer input
const int led = 9; // LED output
double lightLevel; //variable that stores the incoming light level

// Tuning parameters
float Kp=10; //Initial Proportional Gain 
float Ki=0; //Initial Integral Gain 
float Kd=0;  //Initial Differential Gain 

    int ledPin = 11; 
    double state = 0;
    double out = 0;


double Setpoint, Input, Output;  //These are just variables for storing values
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT); // This sets up our PDID Loop
//Input is our PV
//Output is our u(t)
//Setpoint is our SP
const int sampleRate = 1; // Variable that determines how fast our PID loop runs

// Communication setup
const long serialPing = 500; //This determines how often we ping our loop
// Serial pingback interval in milliseconds
unsigned long now = 0; //This variable is used to keep track of time
// placehodler for current timestamp
unsigned long lastMessage = 0; //This keeps track of when our loop last spoke to serial
// last message timestamp.

void setup(){

  
  lightLevel = analogRead(photores); //Read in light level
  Input = map(lightLevel, 0, 1024, 0, 255); //Change read scale to analog out scale
  Setpoint = map(analogRead(pot), 0, 1024, 0, 255);  //get our setpoint from our pot
  Serial.begin(9600); //Start a serial session
    Serial.flush();
  myPID.SetMode(AUTOMATIC);  //Turn on the PID loop
  myPID.SetSampleTime(sampleRate); //Sets the sample rate
  

  lastMessage = millis(); // timestamp
}

void loop(){
 Serial.flush();
  int ard_command = 0;
  int pin_num = 0;
  int pin_value = 0;

  char get_char = ' ';  //read serial

  if (Serial.available() < 1) return; // if serial empty, return to loop().

  // parse incoming command start flag 
  get_char = Serial.read();
  if (get_char != START_CMD_CHAR) return; // if no command start flag, return to loop().

  // parse incoming command type
  ard_command = Serial.parseInt(); // read the command
  
  // parse incoming pin# and value  
  pin_num = Serial.parseInt(); // read the pin
  pin_value = Serial.parseInt();  // read the value

  // 3) GET analogWrite DATA FROM ARDUDROID
  if (ledPin == CMD_ANALOGWRITE) {  
    analogWrite(  pin_num, pin_value ); 


  Setpoint = map(analogRead(pot), 0, 1024, 0, 255); //Read our setpoint
  lightLevel = analogRead(photores); //Get the light level
  Input = map(lightLevel, 0, 900, 0, 255); //Map it to the right scale
  myPID.Compute();  //Run the PID loop
  analogWrite(led, Output);  //Write out the output from the PID loop to our LED pin
  
  now = millis(); //Keep track of time
  if(now - lastMessage > serialPing) {  //If its been long enough give us some info on serial
    // this should execute less frequently
    // send a message back to the mother ship


    
    lastMessage = now; 
    //update the time stamp. 
  }

    return;  // Done. return to loop();
    
  }

  delay (100);
    
}
