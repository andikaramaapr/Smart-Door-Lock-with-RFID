#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> //library untuk wire i2c
#include <RFID.h> //library RFID

#define RST_PIN         6          // Configurable, typical RST_PIN for RC522 is D9
#define SS_PIN          7         // Configurable, typical SDA_PIN for RC522 is D10

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change 0x27 to your I2C address if different

void setup() {
  Serial.begin(9600);             // Initialize serial communications
  lcd.begin(16, 2);               // Initialize LCD
  lcd.backlight();                // Turn on backlight
  SPI.begin();                     // Init SPI bus
  mfrc522.PCD_Init();              // Init MFRC522

  lcd.setCursor(0, 0);
  lcd.print("RFID Ready");
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print("Place card near");

  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Show some details of the PICC (card)
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("UID:");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    lcd.print(" ");
    lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    lcd.print(mfrc522.uid.uidByte[i], HEX);
  }

  // Halt PICC
  mfrc522.PICC_HaltA();

  // Stop encryption on PCD
  mfrc522.PCD_StopCrypto1();

  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RFID Ready");
}
