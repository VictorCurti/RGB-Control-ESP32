# RGB Control ESP32 by Victor Curti

# Application

## :page_with_curl: About :

This IOT project aims to control an RGB LED strip (SMD 5050) using Wifi network to communicate the APP Blynk or the HTML5 page as a microcontroller, for this project the ESP32 DevKit V1 was chosen as a controller.

## :selfie: Interfaces :
<table>
  <tr>
    <td>HTML</td>
     <td>BLynk</td>
     
  </tr>
  <tr>
    <td><img src="Image/MobileHtml.png" width="270"></td>
    <td><img src="Image/Blynk_Home.jpg" width="270"></td>
  </tr>
 </table>
 
## :question: But what is Blynk: 

Blynk is a platform designed for the Internet of Things (IOT), with an application compatible with Android and iOS. It's a digital dashboard where you can build a graphical interface for your project in a simple and fast way, dragging and dropping widgets on the dashboard.

### :iphone: App dashboard: 

| <img src="Image/Blynk_Home.jpg" alt="Home Page" width="300"> |<img src="Image/Blynk_RGB.jpg" alt="RGB Page" width="300"> |
| ----------- | ----------- |

Blynk official website [https://blynk.io/](https://blynk.io/)

## How to clone Blynk project :
1 - Download Blynk

| <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/6/67/App_Store_%28iOS%29.svg/1280px-App_Store_%28iOS%29.svg.png" alt="" width="30" height="30" align="middle">      | <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/d/d0/Google_Play_Arrow_logo.svg/768px-Google_Play_Arrow_logo.svg.png" alt="" width="30" height="30" align="middle"> |
| ----------- | ----------- |
| [Apple Store](https://apps.apple.com/us/app/blynk-iot-for-arduino-esp32/id808760481) | [Googple Play](https://play.google.com/store/apps/details?id=cc.blynk&hl=en_US) |

2 - With the application open, slide to the right and click on the QR code icon and scan the code below.

Obs.: For this project it is necessary to have a 2000 energy credit on Blynk. Initially when you create the account on the platform, your account starts with 2000 energies for free.

|  <img src="Image/BlynkClone.jpg" width="300"> | <img src="Image/Blynk_Share_Clone.jpeg" width="300">
| ----------- | ----------- |

# Circuit 

<img src="Image/PCB/RGB_Control_00.png" width="700">

## Schematic:

Full schematic: https://github.com/VictorCurti/RGB-Control-ESP32/blob/main/Kicad/RGB_Control.pdf

### Driver:

<img src="Image/Circuit/Driver.png" width="600">

### Controller :

<img src="Image/Circuit/ESP.png" width="600">

### Supply:

<img src="Image/Circuit/Supply.png" width="600">

## PCB:


|  <img src="Image/PCB/RGB_Control_00.png" width="450"> | <img src="Image/PCB/RGB_Control_01.png" width="450"> |
| ----------------------------------------------------- | ---------------------------------------------------- |
|  <img src="Image/PCB/RGB_Control_Top.png" width="450"> | <img src="Image/PCB/RGB_Control_02.png" width="450"> |
