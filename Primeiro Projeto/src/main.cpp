#include <Arduino.h>
#define pinLed 2

void setup()
{
    pinMode(pinLed, OUTPUT);
}

void loop()
{

    bool botaoAtual = digitalRead(0);
    static bool botaoAnterior = true;
    static bool estadoLed = true;

    if (botaoAtual && !botaoAnterior)
    {
        estadoLed = !estadoLed;

        if (estadoLed)
        {
            
        }
        else
            digitalWrite(pinLed, LOW);
    }

    botaoAnterior = botaoAtual;
}