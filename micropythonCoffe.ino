#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <DHT.h>
#include <UniversalTelegramBot.h>

WiFiClientSecure client;

#define BOTtoken "640620942:AAGfmC9MRD5ca13LTBsIQGARW8nLiBn9-_Q"  //Token do bot criado para dar o aviso
UniversalTelegramBot bot(BOTtoken, client);

#define LED 3

#define BUZZER 1   //Pino de entrada do buzzer
#define BUTTON 2       //Pino de entrada do botão
#define DHTTYPE DHT11   //Definindo o sensor
#define DHTPIN 0        //Pino do DHT 

DHT dht(DHTPIN, DHTTYPE, 15); //Iniciando o sensor

//Configurando wifi
const char* ssid = "ConnectionPoint";
const char* password = "beatriz99";


void setup() {

  Serial.begin(9600);
  // Iniciando o DHT 
  dht.begin();

  //Configurando buzzer e botão
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);

  // Conectando na rede wifi
  WiFi.begin(ssid, password);
  
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); //MUDAR
  }
  if (WiFi.status() == WL_CONNECTED){
      Serial.print("conectado");
    
  }

}

void loop() {

  //Lendo a temperatura em graus Celsius
  int t = dht.readTemperature();
  //Leitura do botão
  byte valor = digitalRead(BUTTON);

 // String id;

  //int newmsg = bot.getUpdates(bot.last_message_received + 1);
  //for (int i=0; i< newmsg; i++){
   // id = bot.messages[i].chat_id;
  //}

  if (t > 20){
    if (WiFi.status() == WL_CONNECTED){
      //bot.sendSimpleMessage(id, "Estou pronto! Venha me beber.", "");
      digitalWrite(LED, HIGH);
    
    }
    else{
      digitalWrite(BUZZER, HIGH);
      if (valor == HIGH ){  
        digitalWrite(BUZZER, LOW);
      }
    }
  }
  else{
    delay(5000);
  }

}
