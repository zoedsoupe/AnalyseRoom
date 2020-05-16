#include <Adafruit_Fingerprint.h>

SoftwareSerial mySerial(10, 11);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()  
{
  Serial.begin(9600);
  while (!Serial); 
  delay(100);
  Serial.println("\n\nApagando todos os templates das digitais!");
  Serial.println("Digite 'Y' para confirmar!");
  while (1) {
    if (Serial.available() && (Serial.read() == 'Y')) {
      break;
    }
  }
  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Sensor reconhecido!");
  } else {
    Serial.println("Sensor não encontrado :(");
    while (1);
  }
  
  finger.emptyDatabase();

  Serial.println("A database foi apagada :)");
}

void loop() {
}
