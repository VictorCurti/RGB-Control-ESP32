#include <Arduino.h>
#include <BlynkSimpleEsp32.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <map>

#define LED 2
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

// Tag comunication
const char *PARAM_INPUT_1 = "color";
const char *PARAM_INPUT_2 = "power";
const char *PARAM_INPUT_3 = "mode";
const char *PARAM_INPUT_4 = "intensity";
const char *PARAM_INPUT_5 = "speed";

String Power = "OFF", Mode = "NULL", Color = "#000000";
int intensity = 128;
int Fade_Red, Fade_Green, Fade_Blue, Fade_Step, Temp;

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

RGB_Color Cor;

void Init_Map();
void notFound(AsyncWebServerRequest *request);
void Hex2RGB(String HEX_COLOR);
void SerialDebug();
void PWM_RGB();

#include "HTML_Index.hpp"
#include "PinsBlynk.hpp"
#include "credentials.hpp"

void setup()
{

  Init_Map();

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);

  Blynk.begin(auth, ssid, pass);

  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
#ifdef DEBUG
    Serial.println("WiFi Failed!");
#endif
    return;
  }

#ifdef DEBUG
  Serial.begin(9600);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("\n\n\n");
#endif

  InitializeServer();

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  while (!Blynk.connected())
    ;
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);

  /***** PWM CONFIGURATION *******/
  ledcSetup(ChannelPwmRed, FrequencyPwm, 8);
  ledcSetup(ChannelPwmGreen, FrequencyPwm, 8);
  ledcSetup(ChannelPwmBlue, FrequencyPwm, 8);

  /***** PWM CHANEL *******/
  ledcAttachPin(LED_RED, ChannelPwmRed);
  ledcAttachPin(LED_GREEN, ChannelPwmGreen);
  ledcAttachPin(LED_BLUE, ChannelPwmBlue);

  // Inicializa o APP Blynk com os parametros já carregados no software
  Blynk.virtualWrite(V5, 0); //Posiciona o botão POWER em OFF
}

void loop()
{
  SerialDebug();

  PWM_RGB();
  Blynk.run();
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

    Blynk.virtualWrite(V6, Cor_RGB.Red);
    Blynk.virtualWrite(V7, Cor_RGB.Green);
    Blynk.virtualWrite(V8, Cor_RGB.Blue);

    delay(100);
  }
  else if (Power == "ON" && Mode == "Fade")
  {
    ledcWrite(0, (256 - Fade_Red));
    ledcWrite(1, (256 - Fade_Green));
    ledcWrite(2, (256 - Fade_Blue));

    Blynk.virtualWrite(V6, Fade_Red);
    Blynk.virtualWrite(V7, Fade_Green);
    Blynk.virtualWrite(V8, Fade_Blue);

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
      Temp = random(30, intensity);
      ledcWrite(0, (256 - Temp));
      Blynk.virtualWrite(V6, Temp);
      break;
    case 1:
      Temp = random(30, intensity);
      ledcWrite(1, (256 - Temp));
      Blynk.virtualWrite(V7, Temp);
      break;
    case 2:
      Temp = random(30, intensity);
      ledcWrite(2, (256 - Temp));
      Blynk.virtualWrite(V8, Temp);
      break;
    case 3:
      Temp = random(30, intensity);
      ledcWrite(0, (256 - Temp));
      Blynk.virtualWrite(V6, Temp);
      Temp = random(30, intensity);
      ledcWrite(1, (256 - Temp));
      Blynk.virtualWrite(V7, Temp);
      break;
    case 4:
      Temp = random(30, intensity);
      ledcWrite(0, (256 - Temp));
      Blynk.virtualWrite(V6, Temp);
      Temp = random(30, intensity);
      ledcWrite(2, (256 - Temp));
      Blynk.virtualWrite(V8, Temp);
      break;
    case 5:
      Temp = random(30, intensity);
      ledcWrite(1, (256 - Temp));
      Blynk.virtualWrite(V7, Temp);
      Temp = random(30, intensity);
      ledcWrite(2, (256 - Temp));
      Blynk.virtualWrite(V8, Temp);
      break;
    case 6:
      Temp = random(30, intensity);
      ledcWrite(0, (256 - Temp));
      Blynk.virtualWrite(V6, Temp);
      Temp = random(30, intensity);
      ledcWrite(1, (256 - Temp));
      Blynk.virtualWrite(V7, Temp);
      Temp = random(30, intensity);
      ledcWrite(2, (256 - Temp));
      Blynk.virtualWrite(V8, Temp);
      break;
    default:
      ledcWrite(0, 256);
      ledcWrite(1, 256);
      ledcWrite(2, 256);
      Blynk.virtualWrite(V6, 0);
      Blynk.virtualWrite(V6, 0);
      Blynk.virtualWrite(V6, 0);
    }

    delay(StrobeDelay * 10);
  }
  else if (Power == "OFF")
  {
    ledcWrite(0, 256);
    ledcWrite(1, 256);
    ledcWrite(2, 256);

    Blynk.virtualWrite(V6, 0);
    Blynk.virtualWrite(V7, 0);
    Blynk.virtualWrite(V8, 0);
  }
}