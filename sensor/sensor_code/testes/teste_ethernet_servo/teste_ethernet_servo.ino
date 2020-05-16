#include <Ethernet.h>
#include <SPI.h>
#include <Servo.h>
#include <ArduinoJson.h>

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 }; // RESERVED MAC ADDRESS
EthernetClient client;
int id = 9, id1 = 10;
char server[] = "analyseroom.000webhostapp.com";

const int pinoServo = 8; 
 
Servo motor; 
int pos = 45; 

void setup() {
  motor.attach(pinoServo);
  motor.write(0);
  Serial.begin(9600);

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
  }

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); 
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }
}

void loop() {
  if(pos == 45) {
    delay(5000);
    const size_t capacity = JSON_OBJECT_SIZE(1);
  DynamicJsonDocument doc(capacity);

  doc["id"] = id;

  serializeJson(doc, Serial);
  
  if (client.connect(server, 80)) {
    motor.write(pos);
    Serial.print("Connected to server on: ");
      Serial.println(client.remoteIP());
    client.println("POST /index.php HTTP/1.1");
    client.println("Host: analyseroom.000webhostapp.com"); // or generate from your server variable to not hardwire
    client.println("User-Agent: Arduino/Mega");
    client.println("Content-Type: application/json");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(measureJsonPretty(doc));
    client.println();
    serializeJsonPretty(doc, client);
  }
  Serial.println(client.connect(server, 80));
  pos = 128;
  if(client.connect(server, 80)) client.stop();
  } else {
    const size_t capacity = JSON_OBJECT_SIZE(1);
  DynamicJsonDocument doc(capacity);

  doc["id"] = id1;

  serializeJson(doc, Serial);
  
  if (client.connect(server, 80)) {
    motor.write(pos);
    Serial.print("Connected to server on: ");
      Serial.println(client.remoteIP());
    client.println("POST /index.php HTTP/1.1");
    client.println("Host: analyseroom.000webhostapp.com"); // or generate from your server variable to not hardwire
    client.println("User-Agent: Arduino/Mega");
    client.println("Content-Type: application/json");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(measureJsonPretty(doc));
    client.println();
    serializeJsonPretty(doc, client);
  }
  Serial.println(client.connect(server, 80));
  pos = 45;
  if(client.connect(server, 80)) client.stop();
  }

}
