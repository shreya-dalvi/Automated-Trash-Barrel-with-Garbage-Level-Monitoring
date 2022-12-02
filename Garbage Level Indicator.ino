#define BLYNK_PRINT SwSerial

#include <SoftwareSerial.h>
SoftwareSerial SwSerial(10, 11); // RX, TX

#include <BlynkSimpleStream.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

char auth[] = "Your Auth Token";

// Use Virtual pin 5 for uptime display
#define PIN_UPTIME V5
WidgetLED led1(V2);

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 // attach pin D3 Arduino to pin Trig of HC-SR04

long duration; //variable for the duration of sound wave travel
int distance;
int led = 13;

// This function tells Arduino what to do if there is a Widget
// which is requesting data for Virtual Pin (5)
BLYNK_READ(PIN_UPTIME)
{
  // This command writes Arduino's uptime in seconds to Virtual Pin (5)
  Blynk.virtualWrite(PIN_UPTIME, (22-(distance)));
}

BlynkTimer timer;

void emptydist() {
  Blynk.virtualWrite(V0,(distance));
}

void fulldist() {
  Blynk.virtualWrite(V1,(22-(distance)));
}

void setup()
{
  // Debug console
  SwSerial.begin(9600);

  pinMode(led,OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  Blynk.begin(Serial, auth);

  // Setup a function to be called every second
  timer.setInterval(1000L, emptydist);
  // Setup a function to be called every second
  timer.setInterval(1000L, fulldist);  
}

void loop()
{
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = (duration/2)/29.1; // Speed of sound wave divided by 2 (go and back)

  if(distance <= 5)
  {
    digitalWrite(led,HIGH);
    led1.on();
  }
  else
  {
    digitalWrite(led,LOW);  
    led1.off();
  }
  
  Blynk.run();
  timer.run();
}
