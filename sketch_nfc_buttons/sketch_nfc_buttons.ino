#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
const int buttonLanguage = 6;
const int buttonLogout = 5;
const int ledR = A0;
const int ledG = A1;
const int ledB = A2;

void rgb(int r, int g, int b) {
  analogWrite(ledR, r*4);
  analogWrite(ledG, g*4);
  analogWrite(ledB, b*4);
  
}

void setup() {

  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  
  pinMode(buttonLanguage, INPUT);
  pinMode(buttonLogout, INPUT);
  
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  
  rgb(255,0,0);
}

void loop() {
  //Serial.print("blablabla\n");
  if(Serial.available() > 0) {
    rgb(0,255,0);
    String input = "";
    input = Serial.readString();
    Serial.print(input);
    if(input == "This is just a test") {
        rgb(0,0,255);
        Serial.print("I received the following text: " + input + ";");
        Serial.print("Testing read from the other side 1;");
        Serial.print("Testing read from the other side 2;");

        Serial.print("Testing read from the other side 3;");

        Serial.print("Testing read from the other side 4;");

        Serial.print("Testing read from the other side 5;");

    }
    delay(1000);
    rgb(255,0,0);
  }

  
  int buttonStateLanguage = digitalRead(buttonLanguage);
  int buttonStateLogout = digitalRead(buttonLogout);

  if (buttonStateLanguage == HIGH) {
    Serial.println("Language Button pressed");
  }
  if (buttonStateLogout == HIGH) {
      Serial.println("Logout Button pressed");
  }
  
  if( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  
  if( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  
  Serial.print("Die ID des RFID-Tags lautet: ");
  String uid = "";
  for(byte i= 0; i < mfrc522.uid.size; i++) {
    String part = String(mfrc522.uid.uidByte[i], HEX);
    //Serial.print(mfrc522.uid.uidByte[i], HEX);
    //Serial.print(" ");
    uid += part;
    
  }
  
  //Serial.print(uid);
  Serial.println(uid);
  Serial.println();

}
