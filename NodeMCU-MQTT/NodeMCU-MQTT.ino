#include <LiquidCrystal_I2C.h>

#define led 16
#define upButton 0
#define downButton 2

LiquidCrystal_I2C lcd(0x27, 16, 2);

int actualTemp = 0;
int setPoint = 0;
int newSetPoint = 0;
int up ;
int down ;

void setup()
{

    pinMode(led, OUTPUT);
    pinMode(upButton, INPUT);
    pinMode(downButton, INPUT);

    lcd.begin(16, 2);
    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("Temperature:");
    lcd.setCursor(0, 1);
    lcd.print("New:");
    lcd.setCursor(7, 1);
    lcd.print(">>Act:");
}

void loop()
{
    delay(250);
    up = digitalRead(upButton);
    down =  digitalRead(downButton);

    if ((up == HIGH) && (down == LOW))
        newSetPoint += 1;
    if ((up == LOW) && (down == HIGH))
        newSetPoint -= 1;
    if ((up == HIGH) && (down == HIGH))
        setPoint = newSetPoint;

    lcd.setCursor(12, 0);
    lcd.print(actualTemp);
    lcd.setCursor(4, 1);
    lcd.print(newSetPoint);
    lcd.setCursor(12, 1);
}