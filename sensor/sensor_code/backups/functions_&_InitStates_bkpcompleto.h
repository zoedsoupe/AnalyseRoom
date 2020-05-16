#include <Adafruit_Fingerprint.h>
#include <Servo.h>
#include <Ethernet.h>
#include <SPI.h>
#include <ArduinoJson.h>

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 }; // RESERVED MAC ADDRESS
EthernetClient client;
int id = 90;
char server[] = "analyseroom.000webhostapp.com";
IPAddress ip(192, 168, 1, 120);

SoftwareSerial mySerial(11, 12);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

const int pinoServo = 8;
int fingerPrintID = 0;

Servo motor;
bool found = false;

void initSetup() {
  motor.attach(pinoServo); 

  Serial.begin(9600);

  Ethernet.begin(mac, ip);
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting to server ....");
  if(client.connect(server, 80)) Serial.println("Connected!!");
  else Serial.println("NOT connected!!");
  delay(2000);
  while (!Serial);
  delay(100);
  Serial.println("\n\nTeste de autorização por digital!");
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Sensor reconhecido!");
  } else {
    Serial.println("Não foi possível encontrar o sensor :(");
    while (1) { delay(1); }
  }
  finger.getTemplateCount();
  Serial.print("Existem "); Serial.print(finger.templateCount); Serial.println(" templates no sensor!");
  Serial.println("Esperando por uma digital válida...");
}

void open_close_door() {
  if (found) {
    motor.write(128);
    found = false;
    delay(8000);
  }
  else {
    motor.write(45);
  }
}

void post() {
  const size_t capacity = JSON_OBJECT_SIZE(1);
  DynamicJsonDocument doc(capacity);

  doc["id"] = fingerPrintID;

  serializeJson(doc, Serial);
    
  if (client.connect(server, 80)) {
    Serial.print("Connected to server on: ");
    Serial.println(client.remoteIP());
    client.println("POST /index.php HTTP/1.1");
    client.println("Host: analyseroom.000webhostapp.com"); 
    client.println("User-Agent: Arduino/Mega");
    client.println("Content-Type: application/json");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(measureJsonPretty(doc));
    client.println();
    serializeJsonPretty(doc, client);
    delay(100);
  }
  Serial.println(client.connect(server, 80)); 
}


uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagem tirada");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("Nenhuma digital detectada");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Erro de comunicação");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Erro na imagem");
      return p;
    default:
      Serial.println("Erro desconhecido");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagem convertida");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Imagem irreconhecível");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Erro de comunicação");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Informações da digital inexistentes");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Informações da digital inexistentes");
      return p;
    default:
      Serial.println("Erro desconhecido");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Digital reconhecida!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Erro de comunicação");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Digital não reconhecida :(");
    return p;
  } else {
    Serial.println("Erro de comunicação");
    return p;
  }   
  
  // found a match!
  Serial.print("ID encontrado: #"); Serial.print(finger.fingerID); 
  Serial.print(" com número de série "); Serial.println(finger.confidence); 
  fingerPrintID = finger.fingerID;
  post();
  found = true;
  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) {
    Serial.println("Digital não válida!");
    found = false;
    return -1;
  }
  
  // found a match!
  Serial.print("ID encontrado: #"); Serial.print(finger.fingerID); 
  Serial.print(" com número de série "); Serial.println(finger.confidence);
  fingerPrintID = finger.fingerID;
  post();
  found = true;
  return finger.fingerID; 
}
