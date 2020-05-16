#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Ethernet.h>
//Connection via LAN
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "analyseroom.000webhostapp.com";
IPAddress ip(192, 168, 1, 120);// give your Ip in the same Class
EthernetClient client;
String data;
int getFingerprintIDez();
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino (WHITE wire)
SoftwareSerial mySerial(11, 12);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
// On Leonardo/Micro or others with hardware serial, use those! #0 is green wire, #1 is white
//Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);
void setup()
{
while (!Serial); // For Yun/Leo/Micro/Zero/...
data = "";
Serial.begin(9600);
// start the Ethernet connection:
// try to congifure using IP address instead of DHCP:
Ethernet.begin(mac, ip);
// give the Ethernet shield a second to initialize:
delay(1000);
Serial.println("connecting to server ....");
if(client.connect(server, 80)) Serial.println("Connected!!");
else Serial.println("NOT connected!!");
delay(2000);
Serial.println("Adafruit finger detect test");
// set the data rate for the sensor serial port
finger.begin(57600);
if (finger.verifyPassword()) {
Serial.println("Found fingerprint sensor!");
} else {
Serial.println("Did not find fingerprint sensor :(");
while (1);
}
Serial.println("Waiting for valid finger...");
}
void loop() // run over and over again
{
getFingerprintIDez();
delay(50); //don't ned to run this at full speed.
}
uint8_t getFingerprintID() {
uint8_t p = finger.getImage();
switch (p) {
case FINGERPRINT_OK:
Serial.println("Image taken");
break;
case FINGERPRINT_NOFINGER:
Serial.println("No finger detected");
return p;
case FINGERPRINT_PACKETRECIEVEERR:
Serial.println("Communication error");
return p;
case FINGERPRINT_IMAGEFAIL:
Serial.println("Imaging error");
return p;
default:
Serial.println("Unknown error");
return p;
}
// OK success!
p = finger.image2Tz();
switch (p) {
case FINGERPRINT_OK:
Serial.println("Image converted");
break;
case FINGERPRINT_IMAGEMESS:
Serial.println("Image too messy");
return p;
case FINGERPRINT_PACKETRECIEVEERR:
Serial.println("Communication error");
return p;
case FINGERPRINT_FEATUREFAIL:
Serial.println("Could not find fingerprint features");
return p;
case FINGERPRINT_INVALIDIMAGE:
Serial.println("Could not find fingerprint features");
return p;
default:
Serial.println("Unknown error");
return p;
}
// OK converted!
p = finger.fingerFastSearch();
if (p == FINGERPRINT_OK) {
Serial.println("Found a print match!");
} else if (p == FINGERPRINT_PACKETRECIEVEERR) {
Serial.println("Communication error");
return p;
} else if (p == FINGERPRINT_NOTFOUND) {
Serial.println("Did not find a match");
return p;
} else {
Serial.println("Unknown error");
return p;
}
// found a match!
data = "userId=" + (String)finger.fingerID;
Serial.print(data);
Serial.print("Found ID #"); Serial.print(finger.fingerID);
if (client.connect(server, 80)) {
Serial.println("connected");
// Make a HTTP request:
client.println("POST /Arduino/index.php HTTP/1.1");
client.println("Host: 192.168.10.1");
client.println("Content-Type: application/x-www-form-urlencoded");
client.print("Content-Length: ");
client.println(data.length());
client.println();
client.print(data);
// client.println("Connection: close");
client.println();
} else {
// if you didn't get a connection to the server:
Serial.println("connection failed");
}
Serial.print(" with confidence of "); Serial.println(finger.confidence);
}
// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
uint8_t p = finger.getImage();
if (p != FINGERPRINT_OK) return -1;
p = finger.image2Tz();
if (p != FINGERPRINT_OK) return -1;
p = finger.fingerFastSearch();
if (p != FINGERPRINT_OK) return -1;
data = "userId=" + (String)finger.fingerID;
// found a match!
Serial.print("Found ID #"); Serial.print(finger.fingerID);
Serial.print(data);
client.stop();
if (client.connect(server, 80)) {
Serial.println("connected");
// Make a HTTP request:
client.println("POST /Arduino/index.php HTTP/1.1");
client.println("Host: PHP Server IP Address");
client.println("Content-Type: application/x-www-form-urlencoded");
client.print("Content-Length: ");
client.println(data.length());
client.println();
client.print(data);
//client.println("Connection: close");
client.println();
} else {
// if you didn't get a connection to the server:
Serial.println("connection failed");
}
Serial.print(" with confidence of "); Serial.println(finger.confidence);
return finger.fingerID;
}
