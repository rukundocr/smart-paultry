int heating= 4;
int cooling1=5;
int cooling2 =6;
int lighting =7;
int incomingByte;      // a variable to read incoming serial data into
#include "DHT.h"
#define DHTPIN 2    
#define DHTPIN1 3  
#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
DHT dht1(DHTPIN1, DHTTYPE);
int mq_135 =A0;
void setup() {
  Serial.begin(9600);
  dht.begin();
  // initialize the LED pin as an output:
  pinMode(heating, OUTPUT);
  pinMode(cooling1, OUTPUT);
  pinMode(cooling2, OUTPUT);
  pinMode(lighting, OUTPUT);
  digitalWrite(heating, HIGH);
  digitalWrite(cooling1, HIGH);
  digitalWrite(cooling2, HIGH);
  digitalWrite(lighting, HIGH);
}

void loop() {
   //SERIAL COMMUNICATION FROM NODE-RED
   if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    //heating
    if (incomingByte == 'H') {
      digitalWrite(heating,LOW);
    }
    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'L') {
      digitalWrite(heating, HIGH);
    }
    // cooling 1
    if (incomingByte == 'C') {
      digitalWrite(cooling1, LOW);
    }
    if (incomingByte == 'D') {
      digitalWrite(cooling1, HIGH);
    }
    //COOLING 2
    if (incomingByte == 'K') {
      digitalWrite(cooling2, LOW);
    }
    if (incomingByte == 'U') {
      digitalWrite(cooling2,HIGH);
    }

    //LIGHTINH 

     if (incomingByte == 'R') {
      digitalWrite(lighting, LOW);
    }
    if (incomingByte == 'M') {
      digitalWrite(lighting,HIGH);
    }
  }
  
  delay(1000);
   //READING DT11 (1)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  
  //READING DT11 (2)
   float h1 = dht1.readHumidity();
  // Read temperature as Celsius (the default)
  float t1 = dht1.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f1 = dht1.readTemperature(true);

// Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  //READING MQ-135
    int co2 = analogRead(mq_135);
    
    // displaying data
 Serial.print("{\"Humidity1\":");
 Serial.print(h,3);
 Serial.print(",\"Temperature1\":");
 Serial.print(t);
 Serial.print(",\"Humidity2\":");
 Serial.print(h1);
 Serial.print(",\"Temperature2\":");
 Serial.print(t1);
 Serial.print(",\"CO2\":");
 Serial.print(co2);
 Serial.println("}");
    
  /*
  Serial.print(F("ROOM1 Humidity: "));
  Serial.println(h);
  Serial.print(F("ROOM1 Temperature: "));
  Serial.println(t);
  Serial.print(F("ROOM2 Humidity: "));
  Serial.println(h1);
  Serial.print(F("ROOM2  Temperature: "));
  Serial.println(t1);
  Serial.print(F("ROOM2 AIR QUALITY LEVEL: "));
  Serial.println(co2);
  */
  delay(1000);
}
