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
int servoPosition;


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
  servoPosition = 0;
}

void loop()
{
  // Make a change to the wingspan only every 50 milliseconds (1/20th of a second)
  if (millis() % 50 == 0) {
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
     
     // AND is represented as && not || (which represents OR)
     open = (distance <= maximumRange && distance >= minimumRange);
   
    if (open) {
      digitalWrite(RELAY_PIN, HIGH); //turn light on
      digitalWrite(RELAY_PIN2, HIGH); //turn light on
      if (servoPosition < 90) {
        servoPosition += 1;
      }
    }
    else {
      digitalWrite(RELAY_PIN, LOW); // turn light off
      digitalWrite(RELAY_PIN2, LOW); // turn light off
      
      if (servoPosition > 0) {
        servoPosition -= 1;
      }
    }
    
    myservo1.write(servoPosition); // servo to position
    myservo2.write(180-servoPosition); // opposite of other servo position
  }
}

