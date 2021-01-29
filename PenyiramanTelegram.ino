#include <ESP8266WiFi.h>
#include <Wire.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
//#include "DHT.h"

//#define DHTPIN D1

char ssid[] = "Anumu"; //nama wifi
char password[] = "12345678910"; //password wifi
#define BOTtoken "1393722780:AAFMtp42OQiBs4aeY5BDeWuRY_ZJgaGjlWU" //token bot telegram
#define idChat "640002329" //idbot

int sensorPin = A0;
int nilaiSensor;

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

//#define DHTTYPE DHT11
//DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //Soil.begin();
  delay(5000);
}

void loop() {
  delay(2000);
  nilaiSensor= analogRead(sensorPin);
  int Soil = map(nilaiSensor,1023,0,0,100);
  //float Soil = Soil.readTemperature();
  Serial.print("Kelembaban saat ini : ");
  Serial.print(Soil);
  Serial.println(" %");
  
  if (Soil<=20) {
    bot.sendChatAction(idChat, "Sedang mengetik...");
    Serial.print("Kelembaban saat ini : ");
    Serial.println(Soil);
    delay(3000);

    String kelembaban = "Intensitas Kelembaban : ";
    kelembaban += int(Soil);
    kelembaban += " %\n";
    kelembaban += "Kelembaban Rendah!!\n";
    bot.sendMessage(idChat, kelembaban, "");
    Serial.print("Mengirim data sensor ke telegram");
  }
    else if (Soil>=50)
  {
    bot.sendChatAction(idChat, "Sedang mengetik...");
    Serial.print("Kelembaban saat ini : ");
    Serial.println(Soil);
    delay(3000);

    String kelembaban = "Intensitas Kelembaban : ";
    kelembaban += int(Soil);
    kelembaban += " %\n";
    kelembaban += "Kelembaban Tepat\n";
    bot.sendMessage(idChat, kelembaban, "");
    Serial.print("Mengirim data sensor ke telegram");
//      digitalWrite(Relay, HIGH);
//      lcd.setCursor(9,1);
//      lcd.print("OFF   "); 
//      delay(450); 
  }

  
}
