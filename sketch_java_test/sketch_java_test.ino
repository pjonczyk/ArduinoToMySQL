#include <SPI.h>
#include <MFRC522.h>
#include <mysql.h>
#define SS_PIN 10
#define RST_PIN 9


char  *host = (char*)"localhost";
char  *user = (char*)"root";
char  *pass = (char*)"";
char  *db   = (char*)"nfcscheduler";
int isconnected = 0;


String result_query(String query, String field){
  String res = "";
  String q = query + "&field=" + field;
  Serial.println(q);
  //delay(3000);
  res = Serial.readString();
  //Serial.println("reading result: " + res);
  if(res == "-")
  return 0;
  while(res.length() <= 0){
  res = Serial.readString();  
  if(res == "-")
  return 0;
  }
  Serial.println("reading result: " + res);
  Serial.println("second: " + Serial.readString());
  return res;
}

MFRC522 mfrc522(SS_PIN, RST_PIN);
const int buttonLanguage = 6;
const int buttonLogout = 5;
const int ledR = A0;
const int ledG = A1;
const int ledB = A2;

const String studID = "a0e2fa6e";

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

  rgb(0,0,255);
}

void loop() {


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
  if (uid == studID) {
    rgb(255,0,0);
    delay(1000);
    rgb(0,255,255);
  } else {
    int 
    switch(uid) {
      case "e0607fa6": printf("a ist eins\n"); break; //NFC Card
      case "41b35573": printf("a ist zwei\n"); break; //Blue Chip
      case "86136f5": printf("a ist drei\n"); break; //Smartphone
      default: printf("a ist irgendwas\n"); break;
    }
    
    isconnected = mysql_connect(host,user,pass,db);
    
     if(isconnected){
      
        Serial.print("Connected to ");
        Serial.println(host);
        //int result = mysql_query((char*)"INSERT INTO test(`id`, `texttest`) VALUES('30', 'blabla')");
        char *feld = (char*)"";
        String ausgabe = result_query((char*)"query=SELECT * FROM tinetable WHERE id = " + uid,(char*) "texttest");
        //Serial.println(ausgabe);
        if(ausgabe != ""){
          Serial.println("Query exexcuted.");
        }else{
          Serial.println("Query execution failed.");
        }
      }else{
        Serial.println("Connection failed.");
      }
      mysql_close();
    
  }
  
  //Serial.print(uid);
  Serial.println(uid);
  Serial.println();

}
