#include  <Servo.h>
#define RELAY_PIN 3 // RELAY_PIN is the pin the LED is attached to
#define RELAY_PIN2 3 // RELAY_PIN is the pin the LED is attached to
#define echoPin 11 // Echo Pin
#define trigPin 12 // Trigger Pin
//Need to add the naming and pin for the sonar sensor in here somehow
//Would the sonar defining or these LED strips need to be in that boolean open; below this comment? 
//NOPE -- open just tracks if the wings are open or not. Doesn't check any sonar state

boolean open;
Servo myservo1;
Servo myservo2;
//THESE RANGES ARE GONNA NEED TO BE PLAYED WITH, THIS DETERMINES HOW CLOSE
int maximumRange = 13; // Maximum range needed
int minimumRange = 5; // Minimum range needed
long duration, distance; // Duration used to calculate distance


void setup()
{
  myservo1.attach(9); // NOTE: now 9____ pin1 and pin2 are the number pin the servo is attached too Pin1
  myservo2.attach(6); // now____6 ___Pin2
  open = false;
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RELAY_PIN2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //Serial.begin(9600);
  
}

void loop()
{
  /* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
//Serial.println(distance); // 5 and 13 are min and max values...
 
  if(distance <= maximumRange || distance >= minimumRange) //This should be if they are greater than minimum range, and less than max range
  { 
     //Serial.println("Sonar triggered"); //This is a good way to test things. To check this, when you are starting your code, open up the serial monitor under tools.
    // write in the defined name for "(sonar fires)" instead of current writing here
  
    if(open) {
      digitalWrite(RELAY_PIN, HIGH); //turn light on
      digitalWrite(RELAY_PIN2, HIGH); //turn light on
      myservo1.write(90); // rotate servo1 90 degrees
      myservo2.write(180-90); // To move the opposite of myservo1 I think this should be
                              // 180 - n where n is the value in myservo1.write. I don't
                              // know if this will move in the opposite direction though
                              //THIS WILL ALL BE ABOUT TRIAL AND ERROR
    }
    else {
      digitalWrite(RELAY_PIN, LOW); // turn light off
      digitalWrite(RELAY_PIN2, LOW); // turn light off
      myservo1.write(0);
      myservo2.write(0); 
    }
    open = !open;
  }
  
}

