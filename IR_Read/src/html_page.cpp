#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#else
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include "HTML_Index.h"
#include <map>

AsyncWebServer server(80);

// Maping pins
#define LED_RED 14
#define LED_GREEN 12
#define LED_BLUE 13

// PWM CONFIGURATION
#define ChannelPwmRed 0
#define ChannelPwmGreen 1
#define ChannelPwmBlue 2
#define FrequencyPwm 60 //Hz

int FadeDelay;
int StrobeDelay;

// Wifi
const char *ssid = "Free_Internet_Discada";
const char *password = "ManelBixo";

// Tag comunication
const char *PARAM_INPUT_1 = "color";
const char *PARAM_INPUT_2 = "power";
const char *PARAM_INPUT_3 = "mode";
const char *PARAM_INPUT_4 = "intensity";
const char *PARAM_INPUT_5 = "speed";

String Power = "OFF", Mode = "NULL", Color = "#000000";
int intensity = 128;
int Fade_Red, Fade_Green, Fade_Blue, Fade_Step;

struct RGB_Color
{
  int Red = 0; //RGB code color
  //int PwmRed = map(Red, 0, 255, 0, 1023);     //Conversion RGB (8 bits) to PWM (10 bits)
  int Green = 0; //RGB code color
  //int PwmGreen = map(Green, 0, 255, 0, 1023); //Conversion RGB (8 bits) to PWM (10 bits)
  int Blue = 0; //RGB code color
  //int PwmBlue = map(Blue, 0, 255, 0, 1023);   //Conversion RGB (8 bits) to PWM (10 bits)
} Cor_RGB;

/**************************/
std::map<char, int> HexTable;

void Init_Map();

RGB_Color Cor;

void notFound(AsyncWebServerRequest *request);
void Hex2RGB(String HEX_COLOR);
void SerialDebug();
void PWM_RGB();

void setup()
{
  Init_Map();

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("WiFi Failed!");
    return;
  }

  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html);
  });

  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam(PARAM_INPUT_1))
    {
      (request->getParam(PARAM_INPUT_1)->value()) == "" ? Color = "000000" : Color = request->getParam(PARAM_INPUT_1)->value();
      Mode = "Color";
      Power = "ON";
      Hex2RGB(Color);
    }
    else if (request->hasParam(PARAM_INPUT_2))
    {
      Power = request->getParam(PARAM_INPUT_2)->value();
    }
    else if (request->hasParam(PARAM_INPUT_3))
    {
      Mode = request->getParam(PARAM_INPUT_3)->value();
      Power = "ON";
      Fade_Red = 0;
      Fade_Green = 0;
      Fade_Blue = 0;
      Fade_Step = 0;
      randomSeed(analogRead(5));

      FadeDelay = 20;
      StrobeDelay = 200;
    }
    else if (request->hasParam(PARAM_INPUT_4))
    {
      if (request->getParam(PARAM_INPUT_4)->value() == "up")
      {
        intensity += 10;
        if (intensity > 256)
          intensity = 256;
      }
      else if (request->getParam(PARAM_INPUT_4)->value() == "down")
      {
        intensity -= 10;
        if (intensity < 0)
          intensity = 0;
      }
    }
    else if (request->hasParam(PARAM_INPUT_5))
    {
      if (request->getParam(PARAM_INPUT_5)->value() == "up")
      {
        FadeDelay++;
        StrobeDelay += 20;
      }
      else if (request->getParam(PARAM_INPUT_5)->value() == "down")
      {
        FadeDelay--;
        StrobeDelay -= 20;
      }
    }

    request->redirect("/"); // (/?color=FFFFFF)
  });

  server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", "ESP rebooting now");
    delay(500);
    request->redirect("/");
    ESP.restart();
  });

  server.onNotFound(notFound);
  server.begin();

  /***** PWM CONFIGURATION *******/
  ledcSetup(ChannelPwmRed, FrequencyPwm, 8);
  ledcSetup(ChannelPwmGreen, FrequencyPwm, 8);
  ledcSetup(ChannelPwmBlue, FrequencyPwm, 8);

  /***** PWM CHANEL *******/
  ledcAttachPin(LED_RED, ChannelPwmRed);
  ledcAttachPin(LED_GREEN, ChannelPwmGreen);
  ledcAttachPin(LED_BLUE, ChannelPwmBlue);
}

void loop()
{
  SerialDebug();

  PWM_RGB();
}

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "404 - Not found");
}

void Hex2RGB(String HEX_COLOR)
{
  Cor_RGB.Red = (HexTable[HEX_COLOR[1]] * 16 + HexTable[HEX_COLOR[2]]);
  Cor_RGB.Green = (HexTable[HEX_COLOR[3]] * 16 + HexTable[HEX_COLOR[4]]);
  Cor_RGB.Blue = (HexTable[HEX_COLOR[5]] * 16 + HexTable[HEX_COLOR[6]]);
}

void Init_Map()
{
  HexTable['0'] = 0;
  HexTable['1'] = 1;
  HexTable['2'] = 2;
  HexTable['3'] = 3;
  HexTable['4'] = 4;
  HexTable['5'] = 5;
  HexTable['6'] = 6;
  HexTable['7'] = 7;
  HexTable['8'] = 8;
  HexTable['9'] = 9;
  HexTable['a'] = 10;
  HexTable['b'] = 11;
  HexTable['c'] = 12;
  HexTable['d'] = 13;
  HexTable['e'] = 14;
  HexTable['f'] = 15;
}

long OldTime = -1;
void SerialDebug()
{
  if ((OldTime == -1) || ((millis() - OldTime) >= 1000))
  {
    OldTime = millis();
    Serial.println("Mensagens:");
    Serial.print("\tPower: ");
    Serial.println(Power);
    Serial.print("\tColor: ");
    Serial.println(Color);
    Serial.print("\t\tRED: ");
    Serial.println(Cor_RGB.Red);
    Serial.print("\t\tGREEN: ");
    Serial.println(Cor_RGB.Green);
    Serial.print("\t\tBLUE: ");
    Serial.println(Cor_RGB.Blue);

    Serial.print("\t\tFADE - RED: ");
    Serial.println(Fade_Red);
    Serial.print("\t\tFADE - GREEN: ");
    Serial.println(Fade_Green);
    Serial.print("\t\tFADE - BLUE: ");
    Serial.println(Fade_Blue);
    Serial.print("\t\tFADE - STEP: ");
    Serial.println(Fade_Step);

    Serial.print("\tMode: ");
    Serial.println(Mode);
    Serial.print("\tIntensity: ");
    Serial.println(intensity);
  }
}

void PWM_RGB()
{
  if (Power == "ON" && Mode == "Color")
  {
    ledcWrite(0, (256 - Cor_RGB.Red));
    ledcWrite(1, (256 - Cor_RGB.Green));
    ledcWrite(2, (256 - Cor_RGB.Blue));
    delay(100);
  }
  else if (Power == "ON" && Mode == "Fade")
  {
    ledcWrite(0, (256 - Fade_Red));
    ledcWrite(1, (256 - Fade_Green));
    ledcWrite(2, (256 - Fade_Blue));

    if (Fade_Step == 0 && Fade_Red < 256)
      Fade_Red++;
    else if (Fade_Step == 1 && Fade_Green < 256)
      Fade_Green++;
    else if (Fade_Step == 2 && Fade_Blue < 256)
      Fade_Blue++;
    else if (Fade_Step == 3 && Fade_Red > 0)
      Fade_Red--;
    else if (Fade_Step == 4 && Fade_Green > 0)
      Fade_Green--;
    else if (Fade_Step == 5 && Fade_Blue > 0)
      Fade_Blue--;

    if (Fade_Red == 256 && Fade_Step == 0)
      Fade_Step++;
    else if (Fade_Green == 256 && Fade_Step == 1)
      Fade_Step++;
    else if (Fade_Blue == 256 && Fade_Step == 2)
      Fade_Step++;
    else if (Fade_Red == 0 && Fade_Step == 3)
      Fade_Step++;
    else if (Fade_Green == 0 && Fade_Step == 4)
      Fade_Step++;
    else if (Fade_Blue == 0 && Fade_Step == 5)
      Fade_Step = 0;

    delay(FadeDelay);
  }
  else if (Power == "ON" && Mode == "Strobe")
  {

    ledcWrite(0, 256);
    ledcWrite(1, 256);
    ledcWrite(2, 256);

    switch (random(0, 7))
    {
    case 0:
      ledcWrite(0, (256 - random(30, intensity)));
      break;
    case 1:
      ledcWrite(1, (256 - random(30, intensity)));
      break;
    case 2:
      ledcWrite(2, (256 - random(30, intensity)));
      break;
    case 3:
      ledcWrite(0, (256 - random(30, intensity)));
      ledcWrite(1, (256 - random(30, intensity)));
      break;
    case 4:
      ledcWrite(0, (256 - random(30, intensity)));
      ledcWrite(2, (256 - random(30, intensity)));
      break;
    case 5:
      ledcWrite(1, (256 - random(30, intensity)));
      ledcWrite(2, (256 - random(30, intensity)));
      break;
    case 6:
      ledcWrite(0, (256 - random(30, intensity)));
      ledcWrite(1, (256 - random(30, intensity)));
      ledcWrite(2, (256 - random(30, intensity)));
      break;
    default:
      ledcWrite(0, 256);
      ledcWrite(1, 256);
      ledcWrite(2, 256);
    }

    delay(StrobeDelay);
  }
  else if (Power == "OFF")
  {
    ledcWrite(0, 256);
    ledcWrite(1, 256);
    ledcWrite(2, 256);
  }
}