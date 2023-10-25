
// INCLUSÃO DE BIBLIOTECAS
#include <NewPing.h>

// DEFINIÇÕES DE PINOS
#define pinTrig 7
#define pinEcho 8

#define pinLed 5

// DEFINIÇÕES
#define MAX_DISTANCE 100
#define DELAY_LEITURA 3000


// INSTANCIANDO OBJETOS
NewPing sonar(pinTrig, pinEcho, MAX_DISTANCE);

// DECLARAÇÃO DE FUNÇÕES


// DECLARAÇÃO DE VARIÁVEIS
unsigned long ultimaLeitura;

void setup() {
  Serial.begin(9600);

  pinMode(pinLed, OUTPUT);
}

void loop() {
  if ( millis() - ultimaLeitura > DELAY_LEITURA) {
    float distancia = sonar.ping_cm();

    if ( distancia > 0)  { // Se não houver objeto na frente não envia nada
      Serial.println(distancia);
    }
    ultimaLeitura = millis();
  }

  if (Serial.available()) {
    String mensagem = Serial.readString();
    int intensidade = mensagem.toInt();
    analogWrite(pinLed, intensidade);
  }
}

// IMPLEMENTO DE FUNÇÕES
