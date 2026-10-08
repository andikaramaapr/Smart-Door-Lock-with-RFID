#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16,2);
int timer = 1000;

void setup()
{
  lcd.begin ();
}

void loop()
{ 
  //Prosedur Tes Hapus Karakter Pada LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LAWLAW ELC"); //(Ganti Nama Anda, Karakter Sebanyak 16 termasuk spasi)
  lcd.setCursor(0,1);
  lcd.print("Tes No Display");
  delay(timer*2);
  lcd.clear();
  delay(timer*2);
  lcd.setCursor(0,0);
  lcd.print("LAWLAW ELC"); //(Ganti Nama Anda, Karakter Sebanyak 16 termasuk spasi)
  lcd.setCursor(0,1);
  lcd.print("Tes No Display");
  delay(timer*2);
  lcd.clear();
  delay(timer*2);
  lcd.setCursor(0,0);
  lcd.print("LAWLAW ELC"); //(Ganti Nama Anda, Karakter Sebanyak 16 termasuk spasi)
  lcd.setCursor(0,1);
  lcd.print("Tes No Display");
  delay(timer);
}
