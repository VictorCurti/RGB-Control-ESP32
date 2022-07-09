//================================================================
//
//  Author: Victor Curti        (May 2021)
//  Board ESP32 - Devkit V1
//  RGB Control with Alexa + OTA
//
//================================================================

#define ESPALEXA_ASYNC // Fix Webserver Espalexa v2.3.0

#include <Arduino.h>           //Vscode library for arduino
#include <AsyncElegantOTA.h>   //OTA
#include <AsyncTCP.h>          //HTML page
#include <ESPAsyncWebServer.h> //HTML
#include <map>                 //Map library (Dictionary HEX color to RGB)
#include <ESPmDNS.h>           //DNS (NAME.local)
#include <Espalexa.h>

AsyncWebServer server1(8080); // HTML web page port

// Maping pins
#define LED 2        // Onboard led
#define LED_RED 14   // Pin Red color
#define LED_GREEN 12 // Pin green color
#define LED_BLUE 13  // Pin blue color

// PWM Configuration
#define ChannelPwmRed 0   // PWM channel from red color
#define ChannelPwmGreen 1 // PWM channel from green color
#define ChannelPwmBlue 2  // PWM channel from blue color
#define FrequencyPwm 60   // Frequency of PWM[Hz]

//================================================================
//                         Global variables
//================================================================
// Delay time
int FadeDelay;
int StrobeDelay;

// ------------------------
int intensity = 128;
int Fade_Red, Fade_Green, Fade_Blue, Fade_Step, Temp;
long OldTime = -1;

// Tag comunication (LocalIp/get?PARAM_INPUT=XXXX)
const char *PARAM_INPUT_1 = "color";
const char *PARAM_INPUT_2 = "power";
const char *PARAM_INPUT_3 = "mode";
const char *PARAM_INPUT_4 = "intensity";
const char *PARAM_INPUT_5 = "speed";

// States
String Power = "OFF", Mode = "NULL", Color = "#000000";

struct RGB_Color
{
  int Red = 0; // RGB code color
  // int PwmRed = map(Red, 0, 255, 0, 1023);     //Conversion RGB (8 bits) to PWM (10 bits)
  int Green = 0; // RGB code color
  // int PwmGreen = map(Green, 0, 255, 0, 1023); //Conversion RGB (8 bits) to PWM (10 bits)
  int Blue = 0; // RGB code color
  // int PwmBlue = map(Blue, 0, 255, 0, 1023);   //Conversion RGB (8 bits) to PWM (10 bits)
} Cor_RGB;

// Alexa Esp
Espalexa espalexa;

/**************************/
std::map<char, int> HexTable;

//================================================================
//                         Functions
//================================================================

void Init_Map();
void Hex2RGB(String);
void SerialDebug();
void PWM_RGB();
void WifiConect(bool);

// Esp Alexa
void colorLightChanged(uint8_t brightness, uint32_t rgb);
//================================================================
//                         Local libraries
//================================================================

#include "HTML_Index.hpp"
#include "Credentials/credentials.hpp"

// credentials.hpp
/*
    // Your WiFi credentials.
    // Set password to "" for open networks.
    char ssid[] = "Name";
    char pass[] = "Password";
*/

//==============================================================================================
void setup()
{

  // Create a dictionary HEX color to RGB color
  Init_Map();

  // Configuration GPIO station
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED, OUTPUT);

  // Start pins
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED, LOW);

  // PWM Initialize
  ledcSetup(ChannelPwmRed, FrequencyPwm, 8);
  ledcSetup(ChannelPwmGreen, FrequencyPwm, 8);
  ledcSetup(ChannelPwmBlue, FrequencyPwm, 8);

  ledcWrite(ChannelPwmRed, 256);
  ledcWrite(ChannelPwmGreen, 256);
  ledcWrite(ChannelPwmBlue, 256);

  // Channel PWM configuration
  ledcAttachPin(LED_RED, ChannelPwmRed);
  ledcAttachPin(LED_GREEN, ChannelPwmGreen);
  ledcAttachPin(LED_BLUE, ChannelPwmBlue);

  // Conect ESP to Wifi
  Serial.begin(9600);
  WifiConect(true);

  // Change ip address to name rgbcontrol
  // ping rgbcontrol.local
  if (!MDNS.begin("rgbcontrol"))
  {
#ifdef DEBUG
    Serial.println("Error starting mDNS");
#endif
    return;
  }

  // If can`t conect to wifi, reboot device
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
#ifdef DEBUG
    Serial.println("WiFi Failed!");
#endif
    return;
  }

#ifdef DEBUG
  Serial.println("OTA HTTP server on");
#endif

#ifdef DEBUG
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("\n\n\n");
#endif

  // AsyncElegantOTA.begin(&server); // Start ElegantOTA without password
  AsyncElegantOTA.begin(&server1, "admin", "agoravai");

  // Esp Alexa
  espalexa.addDevice("Fita", colorLightChanged); // simplest definition, default state off
  espalexa.begin();

  // Create Async WebServer (File: HTML_Index.hpp)
  InitializeServer();

  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
}

void loop()
{

#ifdef DEBUG
  SerialDebug();
#endif
  if (WiFi.status() != WL_CONNECTED)
  {
    WifiConect(false);
  }
  espalexa.loop();
  PWM_RGB();
  delay(1);
}

void WifiConect(bool stage)
{
  bool aux = false;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  if (stage)
  {
    ledcWrite(ChannelPwmGreen, (128));
  }

#ifdef DEBUG
  Serial.println("Connecting to WiFi..");
#endif

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);

    if (stage)
    {
      if (aux)
      {
        ledcWrite(ChannelPwmGreen, 256);
        aux = false;
      }
      else
      {
        ledcWrite(ChannelPwmGreen, 128);
        aux = true;
      }
    }

#ifdef DEBUG
    Serial.print(".");
#endif
  }

#ifdef DEBUG
  Serial.println("Connected to the WiFi network");
#endif

  PWM_RGB();

  WiFi.setHostname("rgb-control"); // Name on router
}

// Dictionary hexdecimal to decimal
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

void Hex2RGB(String HEX_COLOR)
{
  Cor_RGB.Red = (HexTable[HEX_COLOR[1]] * 16 + HexTable[HEX_COLOR[2]]);
  Cor_RGB.Green = (HexTable[HEX_COLOR[3]] * 16 + HexTable[HEX_COLOR[4]]);
  Cor_RGB.Blue = (HexTable[HEX_COLOR[5]] * 16 + HexTable[HEX_COLOR[6]]);
}

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
    ledcWrite(ChannelPwmRed, (256 - Cor_RGB.Red));
    ledcWrite(ChannelPwmGreen, (256 - Cor_RGB.Green));
    ledcWrite(ChannelPwmBlue, (256 - Cor_RGB.Blue));

    delay(100);
  }
  else if (Power == "ON" && Mode == "Fade")
  {
    ledcWrite(ChannelPwmRed, (256 - Fade_Red));
    ledcWrite(ChannelPwmGreen, (256 - Fade_Green));
    ledcWrite(ChannelPwmBlue, (256 - Fade_Blue));

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

    ledcWrite(ChannelPwmRed, 256);
    ledcWrite(ChannelPwmGreen, 256);
    ledcWrite(ChannelPwmBlue, 256);

    switch (random(0, 7))
    {
    case 0:
      Temp = random(30, intensity);
      ledcWrite(ChannelPwmRed, (256 - Temp));
      break;
    case 1:
      Temp = random(30, intensity);
      ledcWrite(ChannelPwmGreen, (256 - Temp));
      break;
    case 2:
      Temp = random(30, intensity);
      ledcWrite(ChannelPwmBlue, (256 - Temp));
      break;
    case 3:
      Temp = random(30, intensity);
      ledcWrite(ChannelPwmRed, (256 - Temp));
      Temp = random(30, intensity);
      ledcWrite(ChannelPwmGreen, (256 - Temp));
      break;
    case 4:
      Temp = random(30, intensity);
      ledcWrite(ChannelPwmRed, (256 - Temp));
      Temp = random(30, intensity);
      ledcWrite(ChannelPwmBlue, (256 - Temp));
      break;
    case 5:
      Temp = random(30, intensity);
      ledcWrite(ChannelPwmGreen, (256 - Temp));
      Temp = random(30, intensity);
      ledcWrite(ChannelPwmBlue, (256 - Temp));
      break;
    case 6:
      Temp = random(30, intensity);
      ledcWrite(ChannelPwmRed, (256 - Temp));
      Temp = random(30, intensity);
      ledcWrite(ChannelPwmGreen, (256 - Temp));
      Temp = random(30, intensity);
      ledcWrite(ChannelPwmBlue, (256 - Temp));
      break;
    default:
      ledcWrite(ChannelPwmRed, 256);
      ledcWrite(ChannelPwmGreen, 256);
      ledcWrite(ChannelPwmBlue, 256);
    }

    delay(StrobeDelay * 10);
  }
  else if (Power == "OFF")
  {
    ledcWrite(ChannelPwmRed, 256);
    ledcWrite(ChannelPwmGreen, 256);
    ledcWrite(ChannelPwmBlue, 256);
  }
}
/*Esp with Alexa
 */
void colorLightChanged(uint8_t brightness, uint32_t rgb)
{
  // do what you need to do here, for example control RGB LED strip

  if (brightness == 0)
  {
    Power = "OFF";
  }
  else
  {
    Mode = "Color";
    Power = "ON";
  }

  // Get Color from Alexa
  Cor_RGB.Red = ((rgb >> 16) & 0xFF);
  Cor_RGB.Green = ((rgb >> 8) & 0xFF);
  Cor_RGB.Blue = (rgb & 0xFF);

  uint8_t brilho = brightness;
#ifdef DEBUG
  Serial.println("\n\n-Brilho:");
  Serial.println(brilho);
#endif
  brilho = map(brilho,
               1, 255,
               0, 100);
#ifdef DEBUG
  Serial.println(brilho);
#endif
  // Applay

  Cor_RGB.Red = (int)(Cor_RGB.Red * (brilho / 100.0));
  Cor_RGB.Green = (int)(Cor_RGB.Green * (brilho / 100.0));
  Cor_RGB.Blue = (int)(Cor_RGB.Blue * (brilho / 100.0));

#ifdef DEBUG
  Serial.print("Brightness: ");
  Serial.print(brightness);
  Serial.println("RGB[EspAlexa]: ");

  Serial.print(", Red: ");
  Serial.print((rgb >> 16) & 0xFF); // get red component
  Serial.print(", Green: ");
  Serial.print((rgb >> 8) & 0xFF); // get green
  Serial.print(", Blue: ");
  Serial.println(rgb & 0xFF); // get blue
#endif
}