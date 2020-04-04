#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define OUT_heat 8
#define IN_upButton 2
#define IN_downButton 3
#define ONE_WIRE_TEMP 4

int temperature = 0;
int setPoint = 0;
int newSetPoint = 0;
int margin = 1;
int up;
int down;
int cycles = 8;

LiquidCrystal_I2C lcd(0x27, 16, 2);

OneWire oneWire(ONE_WIRE_TEMP);
DallasTemperature sensors(&oneWire);

void setup()
{
    pinMode(OUT_heat, OUTPUT);
    pinMode(IN_upButton, INPUT_PULLUP);
    pinMode(IN_downButton, INPUT_PULLUP);

    sensors.begin();

    lcd.begin(16, 2);
    lcd.init();
    lcd.backlight();

    lcd.setCursor(1, 0);
    lcd.print("Temperature:");
    lcd.setCursor(0, 1);
    lcd.print("New:");
    lcd.setCursor(7, 1);
    lcd.print(">> SP:");
}

void loop()
{
    if (cycles == 8)
    {
        sensors.requestTemperatures();
        temperature = sensors.getTempCByIndex(0);
        cycles = 0;
    };
    up = digitalRead(IN_upButton);
    down = digitalRead(IN_downButton);

    if ((up == HIGH) && (down == LOW) && (newSetPoint < 99))
        newSetPoint = newSetPoint + 1;
    if ((up == LOW) && (down == HIGH) && (newSetPoint > 0))
        newSetPoint = newSetPoint - 1;
    if ((up == LOW) && (down == LOW))
        setPoint = newSetPoint;

    if (temperature < 10)
    {
        lcd.setCursor(13, 0);
        lcd.print(' ');
        lcd.setCursor(14, 0);
    }
    else
    {
        lcd.setCursor(13, 0);
    };
    lcd.print(temperature);

    if (newSetPoint < 10)
    {
        lcd.setCursor(4, 1);
        lcd.print(' ');
        lcd.setCursor(5, 1);
    }
    else
    {
        lcd.setCursor(4, 1);
    };
    lcd.print(newSetPoint);
    if (setPoint < 10)
    {
        lcd.setCursor(13, 1);
        lcd.print(' ');
        lcd.setCursor(14, 1);
    }
    else
    {
        lcd.setCursor(13, 1);
    };

    lcd.print(setPoint);

    if (setPoint - margin > temperature)
    {
        digitalWrite(OUT_heat, HIGH);
    }
    else
    {
        digitalWrite(OUT_heat, LOW);
    };

    cycles++;
    delay(125);
}
