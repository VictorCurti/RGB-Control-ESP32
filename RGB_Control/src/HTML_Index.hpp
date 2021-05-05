#include <ESPAsyncWebServer.h>

void notFound(AsyncWebServerRequest *request);

// HTML web page to handle 3 input fields (input1, input2, input3)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>

<html dir="ltr" lang="pt" class="focus-outline-visible">

<head>
    <meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
    <meta name="viewport" content="width=device-width,initial-scale=1">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <title>RGB Control</title>
    <link href="https://fonts.googleapis.com/css2?family=Exo+2:wght@500&display=swap" rel="stylesheet">
    <style>
        html {
            font-family: 'Exo 2', sans-serif;
            color: #E2E2E2;
            text-align: center;
        }

        td {
            text-align: center;
            vertical-align: middle;
        }
    </style>
</head>

<body style="background-color: rgb(30, 30, 30);">
    <p>     
            <h1>RGB Control</h1>
            <h2>Color select: </h2>
            <table style="margin: 0px auto;">
                <tr>
                    <td>
                        Power :
                    </td>
                    <td>
                        <form action="/get">
                            <input type="submit" name="power" value="ON" />
                        </form>
                    </td>
                    <td>
                        <form action="/get">
                            <input type="submit" name="power" value="OFF" />
                        </form>
                    </td>
                </tr>
                <tr>
                    <form action="/get">
                        Color :
                        <input type="color" id="send" oninput="result.value = send.value">
                        <input type="text" id="result" name="color">
                        <input type="submit" value="Send color" />
                    </form>
                </tr>
                <tr>
                    <td>
                        Modo :
                    </td>
                    <td>
                        <form action="/get">
                            <input type="submit" name="mode" value="Fade" />
                        </form>
                    </td>
                    <td>
                        <form action="/get">
                            <input type="submit" name="mode" value="Strobe" />
                        </form>
                    </td>
                    <td>
                        <form action="/get">
                            <input type="submit" name="mode" value="Color" />
                        </form>
                    </td>
                </tr>
                <tr>
                    <td>
                        Intensity :
                    </td>
                    <td>
                        <form action="/get">
                            <input type="submit" name="intensity" value="up" />
                        </form>
                    </td>
                    <td>
                        <form action="/get">
                            <input type="submit" name="intensity" value="down" />
                        </form>
                    </td>
                </tr>
                <tr>
                    <td>
                        Speed :
                    </td>
                    <td>
                        <form action="/get">
                            <input type="submit" name="speed" value="up" />
                        </form>
                    </td>
                    <td>
                        <form action="/get">
                            <input type="submit" name="speed" value="down" />
                        </form>
                    </td>
                </tr>
            </table>
    </p>
</body>
<footer style="padding-top: 100px;">
    <h6>
        <p>By: Victor Curti</p>
        <p>https://github.com/VictorCurti/RGB-Control-ESP32</p>
    </h6>
</footer>
</html>
    
)rawliteral";

void InitializeServer()
{
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
            Blynk.virtualWrite(V5, 1); //set power on
            Blynk.virtualWrite(V0, 1); //Set modo as color
            Hex2RGB(Color);
        }
        else if (request->hasParam(PARAM_INPUT_2))
        {
            Power = request->getParam(PARAM_INPUT_2)->value();
            Blynk.virtualWrite(V5, (Power == "ON" ? 1 : 0)); //set state
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
            StrobeDelay = 20;

            Blynk.virtualWrite(V0, 20); //Set slider Speed as 20%

            Blynk.virtualWrite(V5, 1); //set power on
            if (Mode == "Color")
                Blynk.virtualWrite(V0, 1); //Set modo as color
            else if (Mode == "Fade")
                Blynk.virtualWrite(V0, 2); //Set modo as color
            else if (Mode == "Strobe")
                Blynk.virtualWrite(V0, 3); //Set modo as color
            else
                Blynk.virtualWrite(V0, 1); //Set modo as color
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
            Blynk.virtualWrite(V2, intensity); //Set slider Speed as %
        }
        else if (request->hasParam(PARAM_INPUT_5))
        {
            if (request->getParam(PARAM_INPUT_5)->value() == "up")
            {
                FadeDelay++;
                if (FadeDelay > 100)
                    FadeDelay = 100;
                StrobeDelay = FadeDelay;
            }
            else if (request->getParam(PARAM_INPUT_5)->value() == "down")
            {
                FadeDelay--;
                if (FadeDelay < 0)
                    FadeDelay = 0;

                StrobeDelay = FadeDelay;
            }
            Blynk.virtualWrite(V1, FadeDelay); //Set slider Speed as %
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
}

void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "404 - Not found");
}