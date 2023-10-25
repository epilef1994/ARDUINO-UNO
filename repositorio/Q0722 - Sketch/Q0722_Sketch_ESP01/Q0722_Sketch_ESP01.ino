

// INCLUSÃO DE BIBLIOTECAS
#include "config.h"

// INSTANCIANDO OBJETOS
AdafruitIO_Feed *distancia = io.feed("distancia");
AdafruitIO_Feed *intensidade = io.feed("intensidade");

// DECLARAÇÃO DE FUNÇÕES


// DECLARAÇÃO DE VARIÁVEIS
unsigned long lastUpdate = 0;

void setup() {
  Serial.begin(9600);

  io.connect();

  intensidade->onMessage(mensagemRecebida);

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 
  intensidade->get();
}

void loop() {
  io.run();

  if(Serial.available()){
    String valorRecebido = Serial.readString();
    distancia->save(valorRecebido);
  }

}

// IMPLEMENTO DE FUNÇÕES

void mensagemRecebida(AdafruitIO_Data *data) {

//  Serial.print("recebido <- ");
  Serial.println(data->value());

}
