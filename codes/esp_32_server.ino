#include <WiFi.h>
#include <WiFiUdp.h>


const char* ssid = "OPPO A15"; 
const char* password = "emon0002";


const char * udpAddress = "192.168.43.23"; 
WiFiUDP udp;
unsigned int udpPort=1234; 
int sensor1= 13;
int sensor2= 12;

char pktbuf[10]; 
char rx_val;
void setup() {
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
Serial.begin(115200);
WiFi.begin(ssid, password);
while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  Serial.println(WiFi.localIP());
  Serial.println("Status: Connected");


  udp.begin(udpPort);
  Serial.println(udpPort);
}

void loop() { 
 int rp=udp.parsePacket(); 
 if(!rp)
 { 
   if (digitalRead(sensor1)==LOW)
   {
     rx_val= 'R1';
     Serial.print("udp_send: ");
     Serial.println(rx_val);
     udp.beginPacket(udpAddress,udpPort);
     udp.write(rx_val);
     udp.endPacket();

   }
   else if (digitalRead(sensor2)==LOW)
   {
     rx_val= 'R2';
     Serial.print("udp_send: ");
     Serial.println(rx_val);
     udp.beginPacket(udpAddress,udpPort);
     udp.write(rx_val);
     udp.endPacket();

   } 
   else{
    rx_val= 'S';
     Serial.print("udp_send: ");
     Serial.println(rx_val);
     udp.beginPacket(udpAddress,udpPort);
     udp.write(rx_val);
     udp.endPacket();
   }
 }
 else
 {    
    udp.read(pktbuf,1);
    Serial.print("Packet from "+String(udpAddress)+": ");
    Serial.println(pktbuf);
    delay(1000);
 }
 delay(1000);
 }
