#include <SPI.h> //library serial parallel interface
#include <Wire.h> //library untuk wire i2c
#include <RFID.h> //library RFID
#include <LiquidCrystal_I2C.h> //library LCD+I2C

#define buzzerPin 8            // Pin for buzzer

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize LCD Display at address 0x27 / 0X3F

#define sda 7 //Pin Serialdata (SDA)
#define rst 6 //pin Reset

RFID rfid(sda, rst);

void setup() {
  Serial.begin(9600); //baud komunikasi serial monitor
  lcd.begin();
  lcd.setBacklight(48); //menghidupkan lampu latar LCD
  SPI.begin(); //Prosedur antarmuka SPI
  rfid.init(); //Memulai inialisasi module RFID

  lcd.setCursor (0, 0);
  lcd.print("Siapkan Kartu");
  lcd.setCursor (0, 1);
  lcd.print("  Siapkan Altul  ");
  delay (2000);
  lcd.clear();

  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  lcd.setCursor (0, 0);
  lcd.print(" -yuk Scan RFID-");
  lcd.setCursor (0, 1);
  lcd.print("Catat IDnya!");
  
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
        digitalWrite(buzzerPin, HIGH);
        delay(300); // Delay pendek
        digitalWrite(buzzerPin, LOW);
      
      lcd.clear();
      lcd.setCursor (0, 0);
      lcd.print("UID: ");

      for (byte i = 0; i < 5; i++) {
        if (rfid.serNum[i] < 0x10) lcd.print("0");
        lcd.print(rfid.serNum[i], HEX);
        lcd.print(" ");
      }
      digitalWrite(buzzerPin, LOW);
      
      Serial.print("UID: ");
      for (byte i = 0; i < 5; i++) {
        if (rfid.serNum[i] < 0x10) Serial.print("0");
        Serial.print(rfid.serNum[i], HEX);
        Serial.print(" ");
      }
      Serial.println(); // Add a new line after printing the UID
      
      delay(5000);
      lcd.clear();
    }
  }
}
