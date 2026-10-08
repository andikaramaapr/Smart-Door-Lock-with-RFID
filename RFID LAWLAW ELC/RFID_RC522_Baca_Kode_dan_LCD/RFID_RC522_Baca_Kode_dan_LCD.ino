#include <SPI.h> //library serial parallel interface
#include <Wire.h> //library untuk wire i2c
#include <RFID.h> //library RFID
#include <LiquidCrystal_I2C.h> //library LCD+I2C

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
  delay (5000);
  lcd.clear();
}

void loop() {
  lcd.setCursor (0, 0);
  lcd.print(" -yuk Scan RFID-");
  lcd.setCursor (0, 1);
  lcd.print("Catat IDnya!");
  
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      lcd.clear();
      lcd.setCursor (0, 0);
      lcd.print("ID terbaca :    ");

      lcd.setCursor (0, 1);
      Serial.print(rfid.serNum[0], HEX); //serial no.1
      Serial.print(" ");
      lcd.print(rfid.serNum[0], HEX);

      Serial.print(rfid.serNum[1], HEX); //serial no.2
      Serial.print(" ");
      lcd.print(rfid.serNum[1], HEX);

      Serial.print(rfid.serNum[2], HEX); //serial no.3
      Serial.print(" ");
      lcd.print(rfid.serNum[2], HEX);

      Serial.print(rfid.serNum[3], HEX); //serial no.4
      Serial.print(" ");
      lcd.print(rfid.serNum[3], HEX);

      Serial.print(rfid.serNum[4], HEX); //serial no.5
      Serial.println("");
      lcd.print(rfid.serNum[4], HEX);

      delay(10000);
      lcd.clear();
    }
  }
}
