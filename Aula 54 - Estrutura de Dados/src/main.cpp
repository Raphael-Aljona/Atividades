#include <Arduino.h>

struct Cores
{
  int r;
  int g;
  int b;
};

Cores azul;
Cores verde;
Cores vermelho;
Cores amarelo;
Cores rosa;

void setup(){
  Serial.begin(9600);

  azul.r = 0;
  azul.g = 0;
  azul.b = 255;

  verde.r = 0;
  verde.g = 255;
  verde.b = 0;

  vermelho.r = 255;
  vermelho.g = 0;
  vermelho.b = 0;

  amarelo.r = 255;
  amarelo.g = 255;
  amarelo.b = 0;

  rosa.r = 255;
  rosa.g = 0;
  rosa.b = 255;

  printf("A cor azul tem os valores RGB: %d, %d, %d \n\r", azul.r, azul.g, azul.b);
  printf("A cor verde tem os valores RGB: %d, %d, %d \n\r", verde.r, verde.g, verde.b);
  printf("A cor vermelho tem os valores RGB: %d, %d, %d \n\r", vermelho.r, vermelho.g, vermelho.b);
  printf("A cor amarelo tem os valores RGB: %d, %d, %d \n\r", amarelo.r, amarelo.g, amarelo.b);
  printf("A cor rosa tem os valores RGB: %d, %d, %d \n\r", rosa.r, rosa.g, rosa.b);
  
}

void loop(){

}

// struct Pessoa 
// {
//   char nome [20];
//   int idade;
//   float altura;
//   bool calvicie;
// };

// Pessoa aluno;
// Pessoa professor;

// void setup(){
//   Serial.begin(9600);

//   strcpy(aluno.nome, "Thiago");
//   aluno.idade = 25;
//   aluno.altura = 1.82;
//   aluno.calvicie = false;

//   strcpy(professor.nome, "Odirlei");
//   professor.idade = 47;
//   professor.altura = 1.80;
//   professor.calvicie = true;

//   // %s -> String; %d -> Decimais; %.2f Float e limita o numero a 2 casas
//   Serial.printf("meu nome é: %s\n\r", aluno.nome);
//   Serial.printf("e tenho %d anos\n\r", aluno.idade);
//   Serial.printf("tenho %.2f metros de altura\n\r", aluno.altura);
//   Serial.printf("E %s calvo", aluno.calvicie ? "sou" : "não sou");

//   Serial.printf("meu nome é: %s\n\r", professor.nome);
//   Serial.printf("e tenho %d anos\n\r", professor.idade);
//   Serial.printf("tenho %.2f metros de altura\n\r", professor.altura);
//   Serial.printf("E %s calvo", professor.calvicie ? "sou" : "não sou");
// }

// void loop(){

// }