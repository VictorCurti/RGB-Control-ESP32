EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Controladora RGB Wifi"
Date "2021-05-05"
Rev "1.0"
Comp ""
Comment1 "https://github.com/VictorCurti/RGB-Control-ESP32"
Comment2 ""
Comment3 "File: \\Kicad\\RGB_Control"
Comment4 "Autor: Victor Curti"
$EndDescr
$Comp
L Device:R_Small R1
U 1 1 60628A5E
P 1750 2300
F 0 "R1" V 1554 2300 50  0000 C CNN
F 1 "1k" V 1645 2300 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 1750 2300 50  0001 C CNN
F 3 "~" H 1750 2300 50  0001 C CNN
	1    1750 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	2600 2000 2250 2000
$Comp
L power:GND #PWR02
U 1 1 6062DF52
P 2250 2750
F 0 "#PWR02" H 2250 2500 50  0001 C CNN
F 1 "GND" H 2255 2577 50  0000 C CNN
F 2 "" H 2250 2750 50  0001 C CNN
F 3 "" H 2250 2750 50  0001 C CNN
	1    2250 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R2
U 1 1 6064B3F4
P 1750 4600
F 0 "R2" V 1554 4600 50  0000 C CNN
F 1 "1k" V 1645 4600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 1750 4600 50  0001 C CNN
F 3 "~" H 1750 4600 50  0001 C CNN
	1    1750 4600
	0    1    1    0   
$EndComp
Wire Wire Line
	1850 4600 1950 4600
$Comp
L power:GND #PWR04
U 1 1 6064B412
P 2250 5050
F 0 "#PWR04" H 2250 4800 50  0001 C CNN
F 1 "GND" H 2255 4877 50  0000 C CNN
F 2 "" H 2250 5050 50  0001 C CNN
F 3 "" H 2250 5050 50  0001 C CNN
	1    2250 5050
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R3
U 1 1 6064F4E6
P 1750 6900
F 0 "R3" V 1554 6900 50  0000 C CNN
F 1 "1k" V 1645 6900 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" H 1750 6900 50  0001 C CNN
F 3 "~" H 1750 6900 50  0001 C CNN
	1    1750 6900
	0    1    1    0   
$EndComp
Wire Wire Line
	1850 6900 1950 6900
$Comp
L power:GND #PWR06
U 1 1 6064F504
P 2250 7350
F 0 "#PWR06" H 2250 7100 50  0001 C CNN
F 1 "GND" H 2255 7177 50  0000 C CNN
F 2 "" H 2250 7350 50  0001 C CNN
F 3 "" H 2250 7350 50  0001 C CNN
	1    2250 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 7350 2250 7100
Wire Notes Line
	5350 7750 5350 500 
Text Notes 700  950  0    118  ~ 24
DRIVER
$Comp
L Regulator_Linear:LM7805_TO220 U2
U 1 1 606530F0
P 9250 5050
F 0 "U2" H 9250 5292 50  0000 C CNN
F 1 "LM7806" H 9250 5201 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 9250 5275 50  0001 C CIN
F 3 "https://img.filipeflop.com/files/download/Datasheet_LM78XX.pdf" H 9250 5000 50  0001 C CNN
	1    9250 5050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 60654DBC
P 9250 6000
F 0 "#PWR015" H 9250 5750 50  0001 C CNN
F 1 "GND" H 9255 5827 50  0000 C CNN
F 2 "" H 9250 6000 50  0001 C CNN
F 3 "" H 9250 6000 50  0001 C CNN
	1    9250 6000
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR013
U 1 1 60655B34
P 8600 4800
F 0 "#PWR013" H 8600 4650 50  0001 C CNN
F 1 "+12V" H 8615 4973 50  0000 C CNN
F 2 "" H 8600 4800 50  0001 C CNN
F 3 "" H 8600 4800 50  0001 C CNN
	1    8600 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 5350 9250 6000
$Comp
L Device:C_Small C1
U 1 1 60657979
P 8600 5250
F 0 "C1" H 8692 5296 50  0000 L CNN
F 1 "C_Small" H 8692 5205 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L4.6mm_W2.0mm_P2.50mm_MKS02_FKP02" H 8600 5250 50  0001 C CNN
F 3 "~" H 8600 5250 50  0001 C CNN
	1    8600 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C2
U 1 1 6065A463
P 9800 5250
F 0 "C2" H 9892 5296 50  0000 L CNN
F 1 "C_Small" H 9892 5205 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L4.6mm_W2.0mm_P2.50mm_MKS02_FKP02" H 9800 5250 50  0001 C CNN
F 3 "~" H 9800 5250 50  0001 C CNN
	1    9800 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9550 5050 9800 5050
Wire Wire Line
	9800 5050 9800 5150
$Comp
L power:GND #PWR018
U 1 1 6065C109
P 9800 6000
F 0 "#PWR018" H 9800 5750 50  0001 C CNN
F 1 "GND" H 9805 5827 50  0000 C CNN
F 2 "" H 9800 6000 50  0001 C CNN
F 3 "" H 9800 6000 50  0001 C CNN
	1    9800 6000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 6065C6CE
P 8600 6000
F 0 "#PWR014" H 8600 5750 50  0001 C CNN
F 1 "GND" H 8605 5827 50  0000 C CNN
F 2 "" H 8600 6000 50  0001 C CNN
F 3 "" H 8600 6000 50  0001 C CNN
	1    8600 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 5150 8600 5050
Wire Wire Line
	8600 5050 8950 5050
Connection ~ 9800 5050
Wire Wire Line
	8350 5050 8600 5050
Connection ~ 8600 5050
$Comp
L Connector:Jack-DC J1
U 1 1 606C2766
P 7550 5150
F 0 "J1" H 7607 5475 50  0000 C CNN
F 1 "Jack-DC" H 7607 5384 50  0000 C CNN
F 2 "Connector_Wire:SolderWire-0.25sqmm_1x02_P4.2mm_D0.65mm_OD1.7mm" H 7600 5110 50  0001 C CNN
F 3 "~" H 7600 5110 50  0001 C CNN
	1    7550 5150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 606C404E
P 8150 6000
F 0 "#PWR012" H 8150 5750 50  0001 C CNN
F 1 "GND" H 8155 5827 50  0000 C CNN
F 2 "" H 8150 6000 50  0001 C CNN
F 3 "" H 8150 6000 50  0001 C CNN
	1    8150 6000
	1    0    0    -1  
$EndComp
Wire Notes Line
	11150 4350 5400 4350
Text Notes 5500 4650 0    118  ~ 24
POWER SUPPLY
$Comp
L power:+12V #PWR010
U 1 1 6061DE05
P 9700 2300
F 0 "#PWR010" H 9700 2150 50  0001 C CNN
F 1 "+12V" H 9715 2473 50  0000 C CNN
F 2 "" H 9700 2300 50  0001 C CNN
F 3 "" H 9700 2300 50  0001 C CNN
	1    9700 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 1600 7850 1850
Wire Wire Line
	7850 1850 7200 1850
$Comp
L power:GND #PWR017
U 1 1 60626C13
P 8650 2150
F 0 "#PWR017" H 8650 1900 50  0001 C CNN
F 1 "GND" H 8655 1977 50  0000 C CNN
F 2 "" H 8650 2150 50  0001 C CNN
F 3 "" H 8650 2150 50  0001 C CNN
	1    8650 2150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 6062AD62
P 5550 2100
F 0 "#PWR011" H 5550 1850 50  0001 C CNN
F 1 "GND" H 5555 1927 50  0000 C CNN
F 2 "" H 5550 2100 50  0001 C CNN
F 3 "" H 5550 2100 50  0001 C CNN
	1    5550 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 1950 5550 1950
Wire Wire Line
	5550 1950 5550 2100
Wire Wire Line
	7850 5050 8050 5050
Wire Wire Line
	8600 4800 8600 5050
Text Notes 5550 850  0    118  ~ 24
ESP-32
Wire Wire Line
	8600 5350 8600 6000
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 6060C5C1
P 10150 2450
F 0 "J2" H 10050 2700 50  0000 L CNN
F 1 "FITA DE LED" H 10100 2100 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 10150 2450 50  0001 C CNN
F 3 "~" H 10150 2450 50  0001 C CNN
	1    10150 2450
	1    0    0    -1  
$EndComp
Text GLabel 2600 2000 2    50   Input ~ 0
COLOR_RED
Text GLabel 2600 4300 2    50   Input ~ 0
COLOR_BLUE
Text GLabel 9850 2450 0    50   Input ~ 0
COLOR_RED
Text GLabel 9850 2650 0    50   Input ~ 0
COLOR_BLUE
Text GLabel 2600 6600 2    50   Input ~ 0
COLOR_GREEN
Text GLabel 9850 2550 0    50   Input ~ 0
COLOR_GREEN
Wire Wire Line
	9850 2650 9950 2650
Wire Wire Line
	9850 2550 9950 2550
Wire Wire Line
	9850 2450 9950 2450
$Comp
L Transistor_BJT:BC848 Q1
U 1 1 6064C08C
P 2150 2300
F 0 "Q1" H 2341 2346 50  0000 L CNN
F 1 "TIP122" H 2341 2255 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Horizontal_TabDown" H 2350 2225 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/Infineon-BC847SERIES_BC848SERIES_BC849SERIES_BC850SERIES-DS-v01_01-en.pdf?fileId=db3a304314dca389011541d4630a1657" H 2150 2300 50  0001 L CNN
	1    2150 2300
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC848 Q2
U 1 1 6064DF32
P 2150 4600
F 0 "Q2" H 2341 4646 50  0000 L CNN
F 1 "TIP122" H 2341 4555 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Horizontal_TabDown" H 2350 4525 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/Infineon-BC847SERIES_BC848SERIES_BC849SERIES_BC850SERIES-DS-v01_01-en.pdf?fileId=db3a304314dca389011541d4630a1657" H 2150 4600 50  0001 L CNN
	1    2150 4600
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC848 Q3
U 1 1 6064F144
P 2150 6900
F 0 "Q3" H 2341 6946 50  0000 L CNN
F 1 "TIP122" H 2341 6855 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Horizontal_TabDown" H 2350 6825 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/Infineon-BC847SERIES_BC848SERIES_BC849SERIES_BC850SERIES-DS-v01_01-en.pdf?fileId=db3a304314dca389011541d4630a1657" H 2150 6900 50  0001 L CNN
	1    2150 6900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 2300 1850 2300
$Comp
L Device:D D1
U 1 1 60671867
P 8200 5050
F 0 "D1" H 8200 4833 50  0000 C CNN
F 1 "1N4007" H 8200 4924 50  0000 C CNN
F 2 "Diode_THT:D_A-405_P2.54mm_Vertical_AnodeUp" H 8200 5050 50  0001 C CNN
F 3 "https://www.vishay.com/docs/88503/1n4001.pdf" H 8200 5050 50  0001 C CNN
	1    8200 5050
	-1   0    0    1   
$EndComp
$Comp
L power:+6V #PWR019
U 1 1 60935F48
P 10450 4850
F 0 "#PWR019" H 10450 4700 50  0001 C CNN
F 1 "+6V" H 10465 5023 50  0000 C CNN
F 2 "" H 10450 4850 50  0001 C CNN
F 3 "" H 10450 4850 50  0001 C CNN
	1    10450 4850
	1    0    0    -1  
$EndComp
$Comp
L power:+6V #PWR016
U 1 1 60936901
P 7850 1600
F 0 "#PWR016" H 7850 1450 50  0001 C CNN
F 1 "+6V" H 7865 1773 50  0000 C CNN
F 2 "" H 7850 1600 50  0001 C CNN
F 3 "" H 7850 1600 50  0001 C CNN
	1    7850 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R7
U 1 1 6093DCE3
P 10450 5250
F 0 "R7" H 10509 5296 50  0000 L CNN
F 1 "220" H 10509 5205 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" H 10450 5250 50  0001 C CNN
F 3 "~" H 10450 5250 50  0001 C CNN
	1    10450 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	10450 5450 10450 5350
Wire Wire Line
	10450 5150 10450 5050
Wire Wire Line
	9800 5050 10450 5050
Wire Wire Line
	10450 4850 10450 5050
Connection ~ 10450 5050
$Comp
L power:GND #PWR020
U 1 1 6094D248
P 10450 6000
F 0 "#PWR020" H 10450 5750 50  0001 C CNN
F 1 "GND" H 10455 5827 50  0000 C CNN
F 2 "" H 10450 6000 50  0001 C CNN
F 3 "" H 10450 6000 50  0001 C CNN
	1    10450 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	10450 6000 10450 5750
Wire Wire Line
	8650 1950 8650 2150
Wire Wire Line
	9700 2300 9700 2350
Wire Wire Line
	9700 2350 9950 2350
Wire Wire Line
	8150 6000 8150 5250
Wire Wire Line
	8150 5250 7850 5250
Wire Wire Line
	2250 4800 2250 5050
Wire Wire Line
	9800 5350 9800 6000
Wire Wire Line
	2250 2500 2250 2750
Wire Wire Line
	6000 7500 6550 7500
Wire Wire Line
	6550 7500 6550 7050
Wire Wire Line
	6550 7050 6000 7050
Wire Wire Line
	6550 7050 6550 6600
Wire Wire Line
	6550 6600 6000 6600
Connection ~ 6550 7050
Wire Wire Line
	6550 6600 6550 6150
Wire Wire Line
	6550 6150 6000 6150
$Comp
L power:GND #PWR021
U 1 1 6098968C
P 6750 7350
F 0 "#PWR021" H 6750 7100 50  0001 C CNN
F 1 "GND" H 6755 7177 50  0000 C CNN
F 2 "" H 6750 7350 50  0001 C CNN
F 3 "" H 6750 7350 50  0001 C CNN
	1    6750 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 7350 6750 7050
Wire Wire Line
	6750 7050 6550 7050
Text GLabel 1550 2300 0    50   Input ~ 0
LED_RED
Text GLabel 7800 2250 2    50   Input ~ 0
LED_RED
Wire Wire Line
	7200 1950 8650 1950
Wire Wire Line
	1550 2300 1650 2300
Wire Wire Line
	7200 2250 7800 2250
$Comp
L Curti:Esp32-Devkit-V1 U1
U 1 1 609D48B1
P 6350 3300
F 0 "U1" H 6775 5065 50  0000 C CNN
F 1 "Esp32-Devkit-V1" H 6775 4974 50  0000 C CNN
F 2 "CURTI:ESP32-DEVKITV1" H 6775 4883 50  0000 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf" H 6350 3450 50  0001 C CNN
	1    6350 3300
	1    0    0    -1  
$EndComp
Text GLabel 1550 4600 0    50   Input ~ 0
LED_BLUE
Wire Wire Line
	1550 6900 1650 6900
Wire Wire Line
	1550 4600 1650 4600
Text GLabel 1550 6900 0    50   Input ~ 0
LED_GREEN
Text GLabel 7800 2050 2    50   Input ~ 0
LED_BLUE
Wire Wire Line
	7800 2050 7200 2050
Text GLabel 7800 2150 2    50   Input ~ 0
LED_GREEN
Wire Wire Line
	7800 2150 7200 2150
$Comp
L Device:LED D2
U 1 1 6093F7BC
P 10450 5600
F 0 "D2" V 10489 5482 50  0000 R CNN
F 1 "LED 0805" V 10398 5482 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 10450 5600 50  0001 C CNN
F 3 "~" H 10450 5600 50  0001 C CNN
	1    10450 5600
	0    -1   -1   0   
$EndComp
Text Notes 10350 2600 0    50   ~ 0
1 - +12 V\n2 - RED\n3 - GREEN\n4 - BLUE
Connection ~ 6550 6600
Text Notes 5450 5750 0    71   ~ 14
GROUNDING MOUNTING
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 60984BDF
P 5900 7500
F 0 "H4" V 6137 7503 50  0000 C CNN
F 1 "MountingHole_Pad" V 6046 7503 50  0000 C CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 5900 7500 50  0001 C CNN
F 3 "~" H 5900 7500 50  0001 C CNN
	1    5900 7500
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 6098488A
P 5900 7050
F 0 "H3" V 6137 7053 50  0000 C CNN
F 1 "MountingHole_Pad" V 6046 7053 50  0000 C CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 5900 7050 50  0001 C CNN
F 3 "~" H 5900 7050 50  0001 C CNN
	1    5900 7050
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 60984624
P 5900 6600
F 0 "H2" V 6137 6603 50  0000 C CNN
F 1 "MountingHole_Pad" V 6046 6603 50  0000 C CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 5900 6600 50  0001 C CNN
F 3 "~" H 5900 6600 50  0001 C CNN
	1    5900 6600
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 60983D9A
P 5900 6150
F 0 "H1" V 6137 6153 50  0000 C CNN
F 1 "MountingHole_Pad" V 6046 6153 50  0000 C CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 5900 6150 50  0001 C CNN
F 3 "~" H 5900 6150 50  0001 C CNN
	1    5900 6150
	0    -1   -1   0   
$EndComp
Text Notes 5500 3700 0    50   ~ 0
Overview ESP32 Devkit V1 :\nhttps://olddocs.zerynth.com/r2.3.2/official/board.zerynth.doit_esp32/docs/index.html
Wire Wire Line
	2250 6600 2600 6600
Wire Wire Line
	2250 6600 2250 6700
Wire Wire Line
	2250 4300 2600 4300
Wire Wire Line
	2250 4300 2250 4400
Wire Wire Line
	2250 2000 2250 2100
Text Notes 3900 7500 0    50   ~ 0
Obs.: Value for R1, R2 and R3\n         Range 1k to 2k
$EndSCHEMATC
