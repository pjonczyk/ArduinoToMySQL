#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);


void setup() {

Serial.begin(9600);

SPI.begin();

mfrc522.PCD_Init();
}

void loop() {
if( ! mfrc522.PICC_IsNewCardPresent()) {
  return;
}

if( ! mfrc522.PICC_ReadCardSerial()) {
  return;
}

Serial.print("Die ID des RFID-Tags lautet: ");

for(byte i= 0; i < 32; i++) {
  Serial.print(mfrc522.uid.uidByte[i], HEX);
  Serial.print(" ");
}

Serial.println();

}
