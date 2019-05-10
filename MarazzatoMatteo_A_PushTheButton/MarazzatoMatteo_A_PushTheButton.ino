//  Copyright ITT Eugenio Barsanti / Produced by MARAZZATO MATTEO - 4BI  //

//#include <LiquidCrystal.h>

//LiquidCrystal lcd(2, 3, 4, 5, 6, 7);


int button = 2;




void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  if (digitalRead(button)== HIGH)
  {
    delay(1000);
    Serial.println("OK");
  }

  else
  {
    delay(1000);
    Serial.println("NO");
  }
}
