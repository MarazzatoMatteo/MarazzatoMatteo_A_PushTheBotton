//  Copyright ITT Eugenio Barsanti / Produced by MARAZZATO MATTEO - 4BI  //

#include <LiquidCrystal.h>



int btnSX = 8;
int btnCX = 9;
int btnDX = 10;

int lives = 1;
bool select;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);


byte heart[8] = 
{
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
};


void setup() 
{
  /*randomSeed(analogRead(0));
  lives = random(1,6);*/
  
  bool select = false;
  
  lcd.createChar(0, heart);
  lcd.begin(16,2);

  lcd.setCursor(4,0);
  lcd.print("PUSH THE");
  lcd.setCursor(5,1);
  lcd.print("BUTTON");
    delay(1200);
  moveDisplay();

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.write(byte(0));

}

void loop() 
{
  while (select == false)
  {
    selectLives();
  }

  select = false;
}

void selectLives()
{
  if (digitalRead(btnSX) == HIGH && lives > 1)
  {
    lives--;
    lcd.clear();
    for (int i = 0;i<lives;i++)
    {
      lcd.setCursor(i,0);
      lcd.write(byte(0));
    }
    delay(200);
  }

  else if (digitalRead(btnDX) == HIGH && lives < 6) 
  {
    lives++;
    lcd.clear();
    for (int i = 0;i<lives;i++)
    {
      lcd.setCursor(i,0);
      lcd.write(byte(0));
    }
    delay(200);
  }

  else if (digitalRead(btnCX) == HIGH)
  {
    select = true;
    lcd.clear();
  }
}

void moveDisplay()
{
  for(int i = 0; i<16; i++)
  {
    lcd.scrollDisplayLeft();
    delay(120);
  }
}
