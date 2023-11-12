#include "AdafruitIO_WiFi.h"
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <ESP8266WiFi.h>

// CONFIGURAÇÃO DA ADAFRUITIO
#define IO_USERNAME "Felipe537asdadamdadas"
#define IO_KEY "aio_Mvlg48t0wSCvbuEQl8VYFqCAFqmL"

// CONFIGURAÇÃO DO WIFI
#define WIFI_SSID "NET_2G345036"
#define WIFI_PASS "65345036"

//AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Define o cliente MQTT
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, "io.adafruit.com", 1883, IO_USERNAME, IO_KEY);

// Define um feed MQTT
Adafruit_MQTT_Publish feed = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/meu_feed");

void setup() {
  Serial.begin(115200);
  delay(10);

  // Conecta-se à rede WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  // Conecta-se ao servidor MQTT
  MQTT_connect();
}

void loop() {
  // Publica uma mensagem no feed MQTT
  if (feed.publish("Olá, mundo MQTT!")) {
    Serial.println("Mensagem publicada com sucesso.");
  } else {
    Serial.println("Falha ao publicar a mensagem.");
  }

  delay(5000); // Aguarde 5 segundos antes de publicar novamente
}

void MQTT_connect() {
  int8_t ret;

  if (mqtt.connected()) {
    return;
  }

  Serial.print("Conectando ao Adafruit IO... ");
  while ((ret = mqtt.connect()) != 0) {
    switch (ret) {
      case 1: Serial.println("Conexão bem-sucedida!"); break;
      default:
        Serial.print("Falha na conexão. Retorno = ");
        Serial.println(ret);
        delay(5000);
    }
  }
}
