/*-----------------------------------------------*/
/*                                               */
/*-----------------------------------------------*/

#define BlynkSwitchList V0
#define BlynkSpeedSlider V1
#define BlynkIntensitySlider V2
#define BlynkColorPiker V3
#define BlynkPower V5

#define BlynkRedLevel V6
#define BlynkGreenLevel V7
#define BlynkBlueLevel V8

/*-----------------------------------------------*/
/*  Virtual Pins Map                             */
/*                                               */
/*  V6 - Level V - Color Red        (0 -> 256)   */
/*  V7 - Level V - Color Green      (0 -> 256)   */
/*  V8 - Level V - Color Blue       (0 -> 256)   */
/*-----------------------------------------------*/

/*  [V0] Switch - MODE
    1 - Color
    2 - Fade
    3 - Strobe
*/
BLYNK_WRITE(BlynkSwitchList)
{
    int pinValue = param.asInt();
    switch (pinValue)
    {
    case 1:
        Mode = "Color";
        Power = "ON";
        Blynk.virtualWrite(BlynkPower, 1); //set power on
        break;
    case 2:
        Mode = "Fade";
        Power = "ON";
        Blynk.virtualWrite(BlynkPower, 1); //set power on
        break;
    case 3:
        Mode = "Strobe";
        Power = "ON";
        Blynk.virtualWrite(BlynkPower, 1); //set power on
        break;

    default:
        Power = "OFF";
        Blynk.virtualWrite(BlynkPower, 0); //set power on
        break;
    }
    Fade_Red = 0;
    Fade_Green = 0;
    Fade_Blue = 0;
    Fade_Step = 0;
    randomSeed(analogRead(5));

    FadeDelay = 20;
    StrobeDelay = 200;

#ifdef DEBUG
    Serial.print("MODE [BlynkSwitchList]: ");
    Serial.println(pinValue);
#endif
}

/*  [V1] Slide Bar - Speed
    Return int (#)
    0 -> 180
*/
BLYNK_WRITE(BlynkSpeedSlider)
{
    int pinValue = param.asInt();

    FadeDelay = pinValue;
    StrobeDelay = pinValue;

#ifdef DEBUG
    Serial.print("Speed [BlynkSpeedSlider]: ");
    Serial.println(pinValue);
#endif
}

/*  [V2] Slide Bar - Intensity
    Return int (#)
    0 -> 255
*/
BLYNK_WRITE(BlynkIntensitySlider)
{
    int pinValue = param.asInt();
    intensity = pinValue;

#ifdef DEBUG
    Serial.print("Intensity [BlynkIntensitySlider]: ");
    Serial.println(pinValue);
#endif
}

/*  [V3] ZebraRGB - RGB color piker
    Return int (#)
    R: 0 -> 256
    G: 0 -> 256
    B: 0 -> 256
*/
BLYNK_WRITE(BlynkColorPiker)
{
    Cor_RGB.Red = param[0].asInt();
    Cor_RGB.Green = param[1].asInt();
    Cor_RGB.Blue = param[2].asInt();

#ifdef DEBUG
    Serial.println("Zebra [BlynkColorPiker]: ");
    Serial.print("\tRed [0->256] :\t");
    Serial.println(Cor_RGB.Red);
    Serial.print("\tGreen [0->256] :\t");
    Serial.println(Cor_RGB.Green);
    Serial.print("\tBlue [0->256] :\t");
    Serial.println(Cor_RGB.Blue);
#endif
}

/*  [V5] Button - POWER
    1 - ON
    0 - OFF
*/
BLYNK_WRITE(BlynkPower)
{
    bool pinValue = param.asInt();
    digitalWrite(LED, pinValue);
    Power = pinValue ? "ON" : "OFF";

#ifdef DEBUG
    Serial.print("POWER [BlynkPower]: ");
    Serial.println(pinValue);
#endif
}