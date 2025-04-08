#include <Arduino.h>
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {  
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();

}

void loop() {

}
