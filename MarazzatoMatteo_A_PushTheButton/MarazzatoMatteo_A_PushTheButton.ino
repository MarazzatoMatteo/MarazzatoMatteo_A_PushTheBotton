//  Copyright ITT Eugenio Barsanti / Produced by MARAZZATO MATTEO - 4BI  //


#include <LiquidCrystal.h>


int btnSX = 8;
int btnCX = 9;
int btnDX = 10;

int lives = 1;
bool select;

int typeOfCharact;
int location;

float startTime;
float finalTime;

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
  B00000,
};

byte good[8] = 
{
  B00000,
  B01010,
  B10101,
  B01010,
  B00000,
  B10001,
  B01110,
  B00000
};

byte bad[8] = 
{
  B00000,
  B11011,
  B11011,
  B11011,
  B00000,
  B01010,
  B10101,
  B00000
};


void setup() 
{
  Serial.begin(9600);
  
  randomSeed(analogRead(5));
  
  bool select = false;
  bool choose = false;
  
  lcd.createChar(0, heart);
  lcd.createChar(1, good);
  lcd.createChar(2, bad);
  
  lcd.begin(16,2);
  
  moveDisplay();

  lcd.clear();
}

void loop() 
{
  lcd.setCursor(0,0);
  lcd.write(byte(0));
  
  while (select == false)
  {
    printStringLives();
    selectLives();
  }

    delay(1000);
    
  if (lives > 0)
  {
    for (int i = 1;i<=lives*i;i++)
    {
      printCharacter();
      delay(750);
    }
  }
    delay(500);
    
  printEndGame();
  
    delay(1000);
  timer();
    delay(4000);

  lcd.clear();
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
    startTime = millis();
    lcd.clear();
  }
}

void moveDisplay()
{
  lcd.setCursor(4,0);
  lcd.print("PUSH THE");
  lcd.setCursor(5,1);
  lcd.print("BUTTON");
    delay(1200);
    
  for(int i = 0; i<16; i++)
  {
    lcd.scrollDisplayLeft();
    delay(120);
  }
}

void printStringLives()
{
  lcd.setCursor(10,0);
  lcd.print("SELECT");
  lcd.setCursor(6,1);
  lcd.print("YOUR LIVES");
}

void timer()
{
    lcd.clear();
    finalTime = millis();
    lcd.setCursor(2,0);
    lcd.print("PLAYING TIME");

    if ((finalTime - startTime)/1000 < 10)
    {
      lcd.setCursor(4,1);
      lcd.print("00");
      lcd.setCursor(6,1);
      lcd.print((finalTime - startTime)/1000);
      lcd.setCursor(7,1);
      lcd.print(" sec");
    }

    else if ((finalTime - startTime)/1000 >= 10 && ((finalTime - startTime)/1000) < 100)
    {
      lcd.setCursor(4,1);
      lcd.print("0");
      lcd.setCursor(5,1);
      lcd.print((finalTime - startTime)/1000);
      lcd.setCursor(7,1);
      lcd.print(" sec");
    }

    else if ((finalTime - startTime)/1000 >= 100)
    {
      lcd.setCursor(4,1);
      lcd.print((finalTime - startTime)/1000);
      lcd.setCursor(7,1);
      lcd.print(" sec");
    }

    lives = 1;
    select = false;
}

void printCharacter()
{
  typeOfCharact = random(0,10);
  location = random(1,4);

    int btnRight;
    int btnWrong1;
    int btnWrong2;
    
    if (location == 1){btnRight = btnSX;btnWrong1 = btnCX;btnWrong2 = btnDX;}
    else if (location == 2){btnRight = btnCX;btnWrong1 = btnDX;btnWrong2 = btnSX;}
    else{btnRight = btnDX;btnWrong1 = btnCX;btnWrong2 = btnSX;}

    if (location == 1){location = 3;}
    else if (location == 2){location = 8;}
    else if (location == 3){location = 12;}

  if (typeOfCharact < 7)
  {
    lcd.clear();
    lcd.setCursor(location,1);
    lcd.write(byte(1));
    redrawLives();

      delay(200);
    
    int wait = 0;
    int pressure = 0;
      int i = 0;
    while (wait < 150)
    {
      if (digitalRead(btnRight) == HIGH){pressure = 1;}
      else if (digitalRead(btnSX) == LOW && digitalRead(btnCX) == LOW && digitalRead(btnDX) == LOW){pressure = 0;}
      
      if (pressure == 1)
      {
      wait = 150;
      }
      else if (pressure == 0){wait++;}

        Serial.println(i++);
    }

      delay(150);

    if (pressure == 1)
    {
      lives--;
      redrawLives();
    }

    else{redrawLives();}
  }

  else if (typeOfCharact > 6)
  {
    lcd.clear();
    lcd.setCursor(location,1);
    lcd.write(byte(2));
    redrawLives();

      delay(200);

    int wait = 0;
    int pressure = 0;
      int i = 0;
    while (wait < 150)
    {
      if (digitalRead(btnRight) == HIGH && digitalRead(btnWrong1) == LOW && digitalRead(btnWrong2) == LOW){pressure = 1;}
      else if (digitalRead(btnSX) == LOW && digitalRead(btnCX) == LOW && digitalRead(btnDX) == LOW || (digitalRead(btnRight) == HIGH || digitalRead(btnWrong1) == HIGH || digitalRead(btnWrong2) == HIGH)){pressure = 0;}
      
      if (pressure == 1)
      {
      wait = 150;
      }
      else if (pressure == 0){wait++;}

        Serial.println(i++);
    }

      delay(150);

    if (pressure == 1){redrawLives();}

    else 
    {
      lives--;
      redrawLives();
    }
  }
}

void redrawLives()
{

  if (lives == 0){delay(250);lcd.clear();}

  else
  {
    for (int i = 0;i<lives;i++)
    {
      lcd.setCursor(i,0);
      lcd.write(byte(0));
    }
  }
}

void printEndGame()
{
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("!GAME!");
  lcd.setCursor(5,1);
  lcd.print("!OVER!");
}


//  Copyright ITT Eugenio Barsanti / Produced by MARAZZATO MATTEO - 4BI  //
