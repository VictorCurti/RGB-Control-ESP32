// ESP32 Projeto Telegram

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

char ssid[] = "REDE_WIFI";
char password[] = "SENHA_WIFI";

#define BOTtoken "0000000000:000000000000000000000000000000000"

#define Quarto1   0
#define Quarto2   15
#define Sala      2
#define Cozinha   4

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 1000;
long Bot_lasttime;
String id, text;
unsigned long tempo;

void setup()
{
      Serial.begin(115200);
      pinMode(Quarto1, OUTPUT);
      pinMode(Quarto2, OUTPUT);
      pinMode(Sala, OUTPUT);
      pinMode(Cozinha, OUTPUT);

      Serial.print("Connecting Wifi: ");
      Serial.println(ssid);

      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);

      while (WiFi.status() != WL_CONNECTED)
    {
            Serial.print(".");
            delay(500);
         
    }

      Serial.println("");
      Serial.println("WiFi connected");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
}

void loop()
{
      if (millis() - tempo > 2000) 
    {

        if (WiFi.status() != WL_CONNECTED)
              
            {
                      WiFi.begin("ssid", "password");
                      delay(2000);
                   
            }

            tempo = millis(); //Reseta o tempo

            int newmsg = bot.getUpdates(bot.last_message_received + 1);

        for (int i = 0; i < newmsg; i++)
             
            {
                    id = bot.messages[i].chat_id;
                    text = bot.messages[i].text;
                    text.toUpperCase();

                    // Acende a luz
    if (text.indexOf("ON1") > -1)   
                {
                          digitalWrite(Quarto1, HIGH);
                          bot.sendMessage(id, "Luz do Quarto 1 Acesa", "");
                       
                }

                    // Acende a luz
    else if (text.indexOf("ON2") > -1)   
                {
                          digitalWrite(Quarto2, HIGH);
                          bot.sendMessage(id, "Luz do Quarto 2 Acesa", "");
                       
                }

                    // Acende a luz
    else if (text.indexOf("ON3") > -1)   
                {
                          digitalWrite(Sala, HIGH);
                          bot.sendMessage(id, "Luz da Sala Acesa", "");
                       
                }

                    // Acende a luz
    else if (text.indexOf("ON4") > -1)   
                {
                          digitalWrite(Cozinha, HIGH);
                          bot.sendMessage(id, "Luz da Cozinha Acesa", "");
                       
                }

                    // Apaga a luz
    else if (text.indexOf("OFF1") > -1)   
                {
                          digitalWrite(Quarto1, LOW);
                          bot.sendMessage(id, "Luz do Quarto 1 Apagada", "");
                       
                }

                    // Apaga a luz
    else if (text.indexOf("OFF2") > -1)   
                {
                          digitalWrite(Quarto2, LOW);
                          bot.sendMessage(id, "Luz do Quarto 2 Apagada", "");
                       
                }

                    // Apaga a luz
    else if (text.indexOf("OFF3") > -1)   
                {
                          digitalWrite(Sala, LOW);
                          bot.sendMessage(id, "Luz da Sala Apagada", "");
                       
                }

                    // Apaga a luz
    else if (text.indexOf("OFF4") > -1)   
                {
                          digitalWrite(Cozinha, LOW);
                          bot.sendMessage(id, "Luz da Cozinha Apagada", "");
                       
                }

                    // Acende todas as luzes
    else if (text.indexOf("ON") > -1)   
                {
                          digitalWrite(Quarto1, HIGH);
                          digitalWrite(Quarto2, HIGH);
                          digitalWrite(Sala, HIGH);
                          digitalWrite(Cozinha, HIGH);
                          bot.sendMessage(id, "Todas Luzes Acesas", "");
                       
                }

                    // Apaga todas as luzes
    else if (text.indexOf("OFF") > -1)   
                {
                          digitalWrite(Quarto1, LOW);
                          digitalWrite(Quarto2, LOW);
                          digitalWrite(Sala, LOW);
                          digitalWrite(Cozinha, LOW);
                          bot.sendMessage(id, "Todas Luzes Apagadas", "");
                       
                }

                else if (text.indexOf("START") > -1)   
                {
                          bot.sendSimpleMessage(id, id, "");
                       
                }

                else   
                {
                          bot.sendSimpleMessage(id, "Comando Invalido", "");
                     
                }
                 
            }
         
    }
}