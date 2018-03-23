#include <ESP8266WiFi.h>

const char *ssid =  "SSID";   // cannot be longer than 32 characters!
const char *pass =  "PASSWORD";    //password for the network
int red = 12; // red LED Pin
int yellow = 13; // Yellow LED Pin
int green = 15; // Green LED Pin
int alreadySwitchedToGreen = 0;

void setup() {
  // Setup console
  Serial.begin(115200);
  delay(10);
  Serial.println();
  
  WiFi.mode(WIFI_STA); // to prevent module from showing up in wireless network list
// set the three control pins to output
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

// set all pins to LOW irrespective of current state
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);  
}

void cycle(){ 
// .....red.....yellow.....green.....
  digitalWrite(red, HIGH);
  delay(500);
  digitalWrite(red, LOW);
  digitalWrite(yellow, HIGH);
  delay(500);
  digitalWrite(yellow, LOW);
  digitalWrite(green, HIGH);
  delay(500);
  digitalWrite(green, LOW);
}

void wifiConnected(){
  if(!alreadySwitchedToGreen){ // check if green LED is already on to prevent multiple digitalWrite
   Serial.println("WiFi connected");
   Serial.println(ssid);
// turn off all LED's
   digitalWrite(red, LOW);
   digitalWrite(yellow, LOW);
   digitalWrite(green, LOW);
// turn on green LED
   digitalWrite(green, HIGH);
   alreadySwitchedToGreen = 1; //set green LED to on
  }
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println("...");
    WiFi.begin(ssid, pass);
    alreadySwitchedToGreen = 0; //in case wifi disconnects after successful connection
    cycle();
     if (WiFi.waitForConnectResult() != WL_CONNECTED)
      return;
    }

  if (WiFi.status() == WL_CONNECTED) {
    wifiConnected();
  }
}
