#include <Ethernet.h>
#include <SPI.h>
#include <ArduinoJson.h>

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 }; // RESERVED MAC ADDRESS
EthernetClient client;
IPAddress ip(192, 168, 1, 120);
int id = 90;
char server[] = "analyseroom.000webhostapp.com";


void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }
  Serial.println("Ethernet WebServer Example");
  Ethernet.begin(mac, ip);
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting to server ....");
  if(client.connect(server, 80)) Serial.println("Connected!!");
  else Serial.println("NOT connected!!");
}

void loop() {

  const size_t capacity = JSON_OBJECT_SIZE(1);
  DynamicJsonDocument doc(capacity);

  doc["id"] = 2;

  serializeJson(doc, Serial);
  
  if (client.connect(server, 80)) {
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
}
