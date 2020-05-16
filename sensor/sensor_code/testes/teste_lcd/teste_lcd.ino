#include <LiquidCrystal.h>
 

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
 
void setup() {
  lcd.begin(16, 2);
}
 
void loop() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("FILIPEFLOP");
  lcd.setCursor(3, 1);
  lcd.print(" LCD 16x2");
  delay(5000);
   
  //Rolagem para a esquerda
  for (int posicao = 0; posicao < 3; posicao++)
  {
    lcd.scrollDisplayLeft();
    delay(300);
  }
   
  //Rolagem para a direita
  for (int posicao = 0; posicao < 6; posicao++)
  {
    lcd.scrollDisplayRight();
    delay(300);
  }
}
