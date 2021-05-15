#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

const int RELE = 8;
MFRC522 mfrc522(10, 9);   

void setup() {
  Serial.begin(9600);   
  SPI.begin();      
  mfrc522.PCD_Init();   
  
  pinMode(RELE, OUTPUT);
  digitalWrite(RELE,LOW);
  Serial.println("Ready...");
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()){
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()){
    return;
  }

  Serial.print("UID tag    :");
  String content= "";
  for (byte i = 0; i < mfrc522.uid.size; i++){
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");  
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("RELE Status : ");
  content.toUpperCase();
  if ((content.substring(1) == "D3 E0 24 1C") || (content.substring(1) == "3A 75 64 A3")){           
    digitalWrite(RELE, !digitalRead(RELE));   
  }
  
  delay(1000);
}