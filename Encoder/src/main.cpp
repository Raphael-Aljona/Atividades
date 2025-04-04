#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

int CLK = 19; // CANAL A
int DT = 18;  // CANAL B
int SW = 23;

// Construindo um vetor
const int8_t tabelaTransicao[4][4] =
{
    //Matriz     0  1  2  3   
/* 00 -> 0*/    { 0, -1,  1,  0}, 
/* 01 -> 1*/    { 1,  0,  0, -1}, 
/* 10 -> 2*/    {-1,  0,  0,  1}, 
/* 11 -> 3*/    { 0,  1, -1,  0}

//  +1 horario
//  0 parado
// -1 antihorario

//1023 Horario
//3201 AntiHorario
};

// Faça o encoder somar ao ir para o sentido horario e
//  subtrair quando estiver indo para o sentido anti-horário

void setup()
{
    Serial.begin(9600);
    pinMode(CLK, INPUT);
    pinMode(DT, INPUT);
}

void loop()
{
    bool leituraCanalA = digitalRead(CLK);
    bool leituraCanalB = digitalRead(DT);
    int estadoAtualEncoder = (leituraCanalA << 1 | leituraCanalB);
    static int estadoAnteriorEncoder = 3;

    static int posicao = 0;
    posicao = (posicao + tabelaTransicao[estadoAnteriorEncoder][estadoAtualEncoder]);

    Serial.println(posicao);

    estadoAnteriorEncoder = estadoAtualEncoder;
}