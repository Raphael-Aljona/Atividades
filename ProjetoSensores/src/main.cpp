#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>

#define SS_PIN 5  // SDA
#define RST_PIN 2 // RST
#define hall 35

#define portaLed 21
#define alertaLed 0

MFRC522 mfrc522(SS_PIN, RST_PIN);

String tagAutorizada = "14 E3 39 A7"; // Substitua pelo UID da sua tag

void setup()
{
  pinMode(hall, INPUT);
  pinMode(portaLed, OUTPUT);

  Serial.begin(115200);
  SPI.begin();        // Inicia o barramento SPI
  mfrc522.PCD_Init(); // Inicia o leitor MFRC522
  Serial.println("Aproxime o cartão...");
}

void loop()
{
  static unsigned long tempoAbertura = 0;
  unsigned long duracaoAbertura = 5000;
  static bool acessoLiberado = 0;
  static int estadoPorta = 0;
  static bool estadoLed = false;
  static unsigned long intervalo = 500; 
  static unsigned long ultimoMillis = 0;
  unsigned long tempoAtual = millis();

  int estado = digitalRead(hall);

  if (acessoLiberado)
  {
    if (estado == LOW)
    {
      estadoPorta = 1;
    }
    else
    {
      estadoPorta = 2;
    }
  }

  if (estadoPorta == 1)
  {
    Serial.println("Porta destrancada");
  }

  else if (estadoPorta == 2){
     Serial.println("Porta Aberta");
  }

  if (!acessoLiberado && estado == HIGH)
  {
    Serial.println("tentativa de arrombamento");
    estadoPorta = 0;
    if (tempoAtual - ultimoMillis >= intervalo) {
    ultimoMillis = tempoAtual;
    
    estadoLed = !estadoLed;              // Inverte o estado do LED
    digitalWrite(alertaLed, estadoLed);    // Atualiza o LED
  }
  }

  if (acessoLiberado && (millis() - tempoAbertura >= duracaoAbertura) && estado == LOW)
  {
    acessoLiberado = false;
    Serial.println("Porta Trancada");
    digitalWrite(portaLed, LOW);
  }

  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  String uidLido = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    uidLido += String(mfrc522.uid.uidByte[i], HEX);
    if (i < mfrc522.uid.size - 1)
      uidLido += " ";
  }

  uidLido.toUpperCase();
  Serial.println("UID Lido: " + uidLido);

  // Verifica acesso
  if (uidLido == tagAutorizada)
  {
    Serial.println("Acesso Permitido ✅");
    digitalWrite(portaLed, HIGH);
    acessoLiberado = true;
    tempoAbertura = millis();
    Serial.println("Porta Destrancada");
  }
  else
  {
    Serial.println("Acesso Negado ❌");
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
