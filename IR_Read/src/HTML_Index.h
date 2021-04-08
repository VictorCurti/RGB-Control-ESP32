#include <ESPAsyncWebServer.h>

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
        <p>www.github.com/################################</p>
        <p>Linkedin : linkedin.com </p>
    </h6>
</footer>
</html>
    
)rawliteral";