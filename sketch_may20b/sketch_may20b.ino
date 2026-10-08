#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> // Include Wire library for I2C
#include <LiquidCrystal_I2C.h> // Include LiquidCrystal_I2C library for LCD
#include <avr/wdt.h> // Include Watchdog Timer library

#define SS_PIN 5
#define RST_PIN 6
#define RELAY 4 // relay pin
#define BUZZER 2 // buzzer pin
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

// Initialize the LCD with the I2C address
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Change 0x27 to your LCD's I2C address

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();          // Initiate SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  digitalWrite(RELAY, HIGH);

  // Initialize LCD
  lcd.begin(); // Initialize LCD without specifying column and row sizes
  lcd.backlight();  // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("Put your card...");
  lcd.setCursor(0, 1);
  lcd.print("to the reader...");

  // Inisialisasi Watchdog Timer dengan timeout 2 detik
  wdt_enable(WDTO_2S);
}

void loop() 
{
  // Reset Watchdog Timer pada setiap iterasi loop
  wdt_reset();

  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent()) 
  {
    // Select one of the cards
    if (mfrc522.PICC_ReadCardSerial()) 
    {
      // Check UID
      String content = "";
      for (byte i = 0; i < mfrc522.uid.size; i++) 
      {
        if (i > 0) content += " "; // Add space between bytes
        content += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
        content += String(mfrc522.uid.uidByte[i], HEX);
      }
      content.toUpperCase();

      // Print the UID for debugging (optional)
      Serial.print("UID: ");
      Serial.println(content);

      // Clear the LCD and print the "Message" line
      lcd.clear();
      lcd.setCursor(0, 0);

      if (content == "05 83 B6 31 C6 32 00")
      {
        // Authorized
        lcd.print("Selamat Datang!");
        lcd.setCursor(0, 1);
        lcd.print("User: Andika!");
        digitalWrite(RELAY, LOW);
        delay(ACCESS_DELAY);
        digitalWrite(RELAY, HIGH);

        // Setelah selesai aksi otorisasi, kembalikan tampilan ke pesan awal
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Put your card...");
        lcd.setCursor(0, 1);
        lcd.print("to the reader...");
      }

      else if (content == "C3 E2 BE FC")
      {
        // Authorized
        lcd.print("Selamat Datang!");
        lcd.setCursor(0, 1);
        lcd.print("User: Adel!");
        digitalWrite(RELAY, LOW);
        delay(ACCESS_DELAY);
        digitalWrite(RELAY, HIGH);

        // Setelah selesai aksi otorisasi, kembalikan tampilan ke pesan awal
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Put your card...");
        lcd.setCursor(0, 1);
        lcd.print("to the reader...");
      }

      else if (content == "F5 3F 8E 75")
      {
        // Authorized
        lcd.print("Selamat Datang!");
        lcd.setCursor(0, 1);
        lcd.print("User: Rama!");
        digitalWrite(RELAY, LOW);
        delay(ACCESS_DELAY);
        digitalWrite(RELAY, HIGH);

        // Setelah selesai aksi otorisasi, kembalikan tampilan ke pesan awal
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Put your card...");
        lcd.setCursor(0, 1);
        lcd.print("to the reader...");
      }

      else if (content == "83 E1 FB F4")
      {
        // Authorized
        lcd.print("Selamat Datang!");
        lcd.setCursor(0, 1);
        lcd.print("User: Adel!");
        digitalWrite(RELAY, LOW);
        delay(ACCESS_DELAY);
        digitalWrite(RELAY, HIGH);

        // Setelah selesai aksi otorisasi, kembalikan tampilan ke pesan awal
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Put your card...");
        lcd.setCursor(0, 1);
        lcd.print("to the reader...");
      }
            
      else   
      {
        // Denied
        lcd.print("Denied!");
        lcd.setCursor(0, 1);
        lcd.print("Anda Siapa?!");
        tone(BUZZER, 300);
        delay(DENIED_DELAY);
        noTone(BUZZER);

        // Setelah selesai aksi otorisasi, kembalikan tampilan ke pesan awal
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Put your card...");
        lcd.setCursor(0, 1);
        lcd.print("to the reader...");
      }

      // Stop reading
      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1();
      // Reset MFRC522
      mfrc522.PCD_Init();
    }
  }
}
