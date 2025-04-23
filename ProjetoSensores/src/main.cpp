
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5  // SDA 
#define RST_PIN 2 // RST
#define hall 35

#define portaLed 21
#define alertaLed 25

MFRC522 mfrc522(SS_PIN, RST_PIN);

String tagAutorizada = "14 E3 39 A7"; // Tag do UID

void setup()
{
  pinMode(hall, INPUT);
  pinMode(portaLed, OUTPUT);
  pinMode(alertaLed, OUTPUT);

  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Aproxime o cartão...");
}

void loop()
{
  static unsigned long tempoAbertura = 0;
  unsigned long duracaoAbertura = 5000;
  static bool acessoLiberado = 0;
  static int estadoPorta = 0;
  static int estadoAnteriorPorta = -1;
  static bool estadoLed = false;
  static unsigned long intervalo = 500;
  static unsigned long ultimoMillis = 0;
  unsigned long tempoAtual = millis();

  int estadoHall = digitalRead(hall);

  if (acessoLiberado)
  {
    if (estadoHall == LOW)
    {
      estadoPorta = 1;
    }
    else
    {
      estadoPorta = 2;
    }
  }

  if (estadoPorta != estadoAnteriorPorta)
  {
    if (estadoPorta == 1)
    {
      Serial.println("Porta Fechada");
    }
    else if (estadoPorta == 2)
    {
      Serial.println("Porta Aberta");
    }
    estadoAnteriorPorta = estadoPorta;
  }

  static bool arrombamentoAnterior = false;
  bool tentativaArrombamento = (!acessoLiberado && estadoHall == HIGH);

  if (tentativaArrombamento)
  {
    if (!arrombamentoAnterior)
    {
      Serial.println("Tentativa de arrombamento");
      arrombamentoAnterior = true;
    }

    if (tempoAtual - ultimoMillis >= intervalo)
    {
      ultimoMillis = tempoAtual;
      estadoLed = !estadoLed;
      digitalWrite(alertaLed, estadoLed);
    }
  }
  else
  {
    arrombamentoAnterior = false;
    digitalWrite(alertaLed, LOW);
  }

  if (acessoLiberado && (millis() - tempoAbertura >= duracaoAbertura) && estadoHall == LOW)
  {
    acessoLiberado = false;
    Serial.println("Porta Trancada");
    digitalWrite(portaLed, LOW);
    estadoPorta = 0;
    estadoAnteriorPorta = -1;
  }

  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  // Le e armazena a informação do ID
  String uidLido = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    uidLido += String(mfrc522.uid.uidByte[i], HEX);
    if (i < mfrc522.uid.size - 1)
      uidLido += " ";
  }

  uidLido.toUpperCase();
  // Exibe o ID na serial
  // Serial.println("UID Lido: " + uidLido); 

  if (uidLido == tagAutorizada)
  {
    Serial.println("Acesso Permitido");
    digitalWrite(portaLed, HIGH);
    acessoLiberado = true;
    tempoAbertura = millis();
    Serial.println("Porta Destrancada");
  }
  else
  {
    Serial.println("Acesso Negado");
  }

  mfrc522.PICC_HaltA(); // Para de ler a tag atual e libera para ler uma outra tag
  mfrc522.PCD_StopCrypto1(); // Encerra a criptografia da comunicação entre o leitor e a tag RFID.
}