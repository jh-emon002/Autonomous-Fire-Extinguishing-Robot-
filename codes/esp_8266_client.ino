#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include<Servo.h>
Servo mys;
const char* ssid = "OPPO A15";
const char* password = "emon0002";

const char * udpAddress = "192.168.43.250"; 
WiFiUDP udp;
unsigned int udpPort = 1234;  
int ledR1 = D2;
int ledR2 = D4;
int buzzer = D7;

char pktbuf1[10];
char rx_val;

void setup() {
  mys.attach(D5);
  mys.write(90);
  pinMode(ledR1, OUTPUT);
  pinMode(ledR2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(D6, INPUT);
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  Serial.println(WiFi.localIP());
  Serial.println("Status: Connected");

  udp.begin(udpPort);
  Serial.println("UDP Port: " + String(udpPort));
}

void loop() {
  int packetSize = udp.parsePacket();

  if (!packetSize) {
    if (Serial.available() > 0) {
      rx_val = Serial.read();
      Serial.print("udp_send: ");
      Serial.println(rx_val);
      udp.beginPacket(udpAddress, udpPort);
      udp.write(rx_val);
      udp.endPacket();
    }
  } else {
    udp.read(pktbuf1, sizeof(pktbuf1) - 1);
    pktbuf1[packetSize] = '\0'; 

    Serial.print("Packet from " + String(udpAddress) + ": ");
    Serial.println(pktbuf1);

    if (pktbuf1[0] == '1') {
      digitalWrite(ledR1, HIGH);
      digitalWrite(ledR2, LOW);
      digitalWrite(buzzer, HIGH);
    } 
    else if(pktbuf1[0] == '2') {
      digitalWrite(ledR1, LOW);
      digitalWrite(ledR2, HIGH);
      digitalWrite(buzzer, HIGH);
          }
    else {
      digitalWrite(ledR1, LOW);
      digitalWrite(ledR2, LOW);
      digitalWrite(buzzer, LOW);
    }

    //delay(1000);
  }

  if(digitalRead(D6)==LOW){
  // for(int k=0; k<1001; k++){
    for (int pos = 0; pos <= 180; pos += 5) {  
      mys.write(pos);
      delay(30);  
    }
    for (int pos = 180; pos >= 0; pos -= 5) { 
      mys.write(pos);
      delay(30); 
    }
      }
  //}
  delay(100);
}
