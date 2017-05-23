EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:teensy
LIBS:custom
LIBS:bixi-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Teensy3.6 U9
U 1 1 58BEFB78
P 2600 3300
F 0 "U9" H 2600 5600 60  0000 C CNN
F 1 "Teensy3.6" H 2600 1000 60  0000 C CNN
F 2 "Teensy:Teensy35_36" H 2600 3300 60  0001 C CNN
F 3 "" H 2600 3300 60  0000 C CNN
	1    2600 3300
	1    0    0    -1  
$EndComp
Text Label 3600 5000 0    60   ~ 0
WS_7
Text Label 3600 5100 0    60   ~ 0
WS_6
Text Label 1600 1800 2    60   ~ 0
WS_8
Text Label 1600 1900 2    60   ~ 0
WS_5
Text Label 1600 2100 2    60   ~ 0
WS_4
Text Label 1600 2000 2    60   ~ 0
WS_3
Text Label 1600 5200 2    60   ~ 0
WS_2
Text Label 1600 1500 2    60   ~ 0
WS_1
Text Label 1600 1200 2    60   ~ 0
GND
Text Label 3600 4500 0    60   ~ 0
VCC
$Comp
L R R1
U 1 1 5904FF6D
P 8550 1550
F 0 "R1" V 8630 1550 50  0000 C CNN
F 1 "100" V 8550 1550 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8480 1550 50  0001 C CNN
F 3 "" H 8550 1550 50  0000 C CNN
	1    8550 1550
	0    1    1    0   
$EndComp
Text Label 8400 1550 2    60   ~ 0
1A
Text Label 8700 1550 0    60   ~ 0
1B
$Comp
L R R2
U 1 1 590502A6
P 8550 1750
F 0 "R2" V 8630 1750 50  0000 C CNN
F 1 "100" V 8550 1750 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8480 1750 50  0001 C CNN
F 3 "" H 8550 1750 50  0000 C CNN
	1    8550 1750
	0    1    1    0   
$EndComp
Text Label 8400 1750 2    60   ~ 0
2A
Text Label 8700 1750 0    60   ~ 0
2B
$Comp
L R R3
U 1 1 59050439
P 8550 1950
F 0 "R3" V 8630 1950 50  0000 C CNN
F 1 "100" V 8550 1950 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8480 1950 50  0001 C CNN
F 3 "" H 8550 1950 50  0000 C CNN
	1    8550 1950
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 590504C9
P 8550 2150
F 0 "R4" V 8630 2150 50  0000 C CNN
F 1 "100" V 8550 2150 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8480 2150 50  0001 C CNN
F 3 "" H 8550 2150 50  0000 C CNN
	1    8550 2150
	0    1    1    0   
$EndComp
$Comp
L R R5
U 1 1 5905055D
P 8550 2350
F 0 "R5" V 8630 2350 50  0000 C CNN
F 1 "100" V 8550 2350 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8480 2350 50  0001 C CNN
F 3 "" H 8550 2350 50  0000 C CNN
	1    8550 2350
	0    1    1    0   
$EndComp
$Comp
L R R6
U 1 1 590505FB
P 8550 2550
F 0 "R6" V 8630 2550 50  0000 C CNN
F 1 "100" V 8550 2550 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8480 2550 50  0001 C CNN
F 3 "" H 8550 2550 50  0000 C CNN
	1    8550 2550
	0    1    1    0   
$EndComp
$Comp
L R R7
U 1 1 59050693
P 8550 2750
F 0 "R7" V 8630 2750 50  0000 C CNN
F 1 "100" V 8550 2750 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8480 2750 50  0001 C CNN
F 3 "" H 8550 2750 50  0000 C CNN
	1    8550 2750
	0    1    1    0   
$EndComp
$Comp
L R R8
U 1 1 59050711
P 8550 2950
F 0 "R8" V 8630 2950 50  0000 C CNN
F 1 "100" V 8550 2950 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8480 2950 50  0001 C CNN
F 3 "" H 8550 2950 50  0000 C CNN
	1    8550 2950
	0    1    1    0   
$EndComp
Text Label 8400 1950 2    60   ~ 0
3A
Text Label 8400 2150 2    60   ~ 0
4A
Text Label 8400 2350 2    60   ~ 0
5A
Text Label 8400 2550 2    60   ~ 0
6A
Text Label 8400 2750 2    60   ~ 0
7A
Text Label 8400 2950 2    60   ~ 0
8A
Text Label 8700 1950 0    60   ~ 0
3B
Text Label 8700 2150 0    60   ~ 0
4B
Text Label 8700 2350 0    60   ~ 0
5B
Text Label 8700 2550 0    60   ~ 0
6B
Text Label 8700 2750 0    60   ~ 0
7B
Text Label 8700 2950 0    60   ~ 0
8B
$Comp
L ESP8266 U10
U 1 1 5904CE17
P 5350 1750
F 0 "U10" H 5350 2000 60  0000 C CNN
F 1 "ESP8266" H 5350 1750 60  0000 C CNN
F 2 "custom:ESP8266" H 5350 1750 60  0001 C CNN
F 3 "" H 5350 1750 60  0001 C CNN
	1    5350 1750
	1    0    0    -1  
$EndComp
Text Label 4650 1600 2    60   ~ 0
GND
Text Label 6050 1900 0    60   ~ 0
3V
Text Label 1600 2600 2    60   ~ 0
3V
$Comp
L R R9
U 1 1 5907EA94
P 5350 1150
F 0 "R9" V 5430 1150 50  0000 C CNN
F 1 "R" V 5350 1150 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5280 1150 50  0001 C CNN
F 3 "" H 5350 1150 50  0001 C CNN
	1    5350 1150
	0    1    1    0   
$EndComp
Text Label 4650 1900 2    60   ~ 0
CHPD
Text Label 5200 1150 2    60   ~ 0
CHPD
Text Label 5500 1150 0    60   ~ 0
3V
Text Label 4650 1700 2    60   ~ 0
TXO
Text Label 1600 3400 2    60   ~ 0
TXO
$Comp
L R R10
U 1 1 5907EE27
P 5350 900
F 0 "R10" V 5430 900 50  0000 C CNN
F 1 "R" V 5350 900 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5280 900 50  0001 C CNN
F 3 "" H 5350 900 50  0001 C CNN
	1    5350 900 
	0    1    1    0   
$EndComp
Text Label 4650 1800 2    60   ~ 0
GPIO2
Text Label 5200 900  2    60   ~ 0
GPIO2
Text Label 5500 900  0    60   ~ 0
3V
Text Label 6050 1800 0    60   ~ 0
RXI
Text Label 1600 3500 2    60   ~ 0
RXI
Text Label 6050 1600 0    60   ~ 0
GPIO0
Text Label 6050 1700 0    60   ~ 0
RST
Text Label 1600 3200 2    60   ~ 0
RST
Text Label 1600 3300 2    60   ~ 0
GPIO0
$Comp
L C C9
U 1 1 5907F490
P 5900 1000
F 0 "C9" H 5925 1100 50  0000 L CNN
F 1 "C" H 5925 900 50  0000 L CNN
F 2 "Capacitors_THT:C_Axial_L3.8mm_D2.6mm_P7.50mm_Horizontal" H 5938 850 50  0001 C CNN
F 3 "" H 5900 1000 50  0001 C CNN
	1    5900 1000
	1    0    0    -1  
$EndComp
Text Label 5900 850  1    60   ~ 0
3V
Text Label 5900 1150 3    60   ~ 0
GND
$Comp
L SP3481CN U1
U 1 1 5913BA66
P 1100 6250
F 0 "U1" H 800 6600 50  0000 L CNN
F 1 "SP3481CN" H 1200 6600 50  0000 L CNN
F 2 "Housings_DIP:DIP-8_W7.62mm" H 2150 5900 50  0001 C CIN
F 3 "" H 1100 6250 50  0001 C CNN
	1    1100 6250
	1    0    0    -1  
$EndComp
$Comp
L SP3481CN U2
U 1 1 5913BC99
P 2250 6250
F 0 "U2" H 1950 6600 50  0000 L CNN
F 1 "SP3481CN" H 2350 6600 50  0000 L CNN
F 2 "Housings_DIP:DIP-8_W7.62mm" H 3300 5900 50  0001 C CIN
F 3 "" H 2250 6250 50  0001 C CNN
	1    2250 6250
	1    0    0    -1  
$EndComp
$Comp
L SP3481CN U3
U 1 1 5913BCF8
P 3400 6250
F 0 "U3" H 3100 6600 50  0000 L CNN
F 1 "SP3481CN" H 3500 6600 50  0000 L CNN
F 2 "Housings_DIP:DIP-8_W7.62mm" H 4450 5900 50  0001 C CIN
F 3 "" H 3400 6250 50  0001 C CNN
	1    3400 6250
	1    0    0    -1  
$EndComp
$Comp
L SP3481CN U4
U 1 1 5913BD62
P 4500 6250
F 0 "U4" H 4200 6600 50  0000 L CNN
F 1 "SP3481CN" H 4600 6600 50  0000 L CNN
F 2 "Housings_DIP:DIP-8_W7.62mm" H 5550 5900 50  0001 C CIN
F 3 "" H 4500 6250 50  0001 C CNN
	1    4500 6250
	1    0    0    -1  
$EndComp
$Comp
L SP3481CN U5
U 1 1 5913BDD5
P 1100 7250
F 0 "U5" H 800 7600 50  0000 L CNN
F 1 "SP3481CN" H 1200 7600 50  0000 L CNN
F 2 "Housings_DIP:DIP-8_W7.62mm" H 2150 6900 50  0001 C CIN
F 3 "" H 1100 7250 50  0001 C CNN
	1    1100 7250
	1    0    0    -1  
$EndComp
$Comp
L SP3481CN U6
U 1 1 5913BE41
P 2250 7250
F 0 "U6" H 1950 7600 50  0000 L CNN
F 1 "SP3481CN" H 2350 7600 50  0000 L CNN
F 2 "Housings_DIP:DIP-8_W7.62mm" H 3300 6900 50  0001 C CIN
F 3 "" H 2250 7250 50  0001 C CNN
	1    2250 7250
	1    0    0    -1  
$EndComp
$Comp
L SP3481CN U7
U 1 1 5913BEB6
P 3400 7250
F 0 "U7" H 3100 7600 50  0000 L CNN
F 1 "SP3481CN" H 3500 7600 50  0000 L CNN
F 2 "Housings_DIP:DIP-8_W7.62mm" H 4450 6900 50  0001 C CIN
F 3 "" H 3400 7250 50  0001 C CNN
	1    3400 7250
	1    0    0    -1  
$EndComp
$Comp
L SP3481CN U8
U 1 1 5913BF30
P 4500 7250
F 0 "U8" H 4200 7600 50  0000 L CNN
F 1 "SP3481CN" H 4600 7600 50  0000 L CNN
F 2 "Housings_DIP:DIP-8_W7.62mm" H 5550 6900 50  0001 C CIN
F 3 "" H 4500 7250 50  0001 C CNN
	1    4500 7250
	1    0    0    -1  
$EndComp
Text Label 700  6450 2    60   ~ 0
WS_1
Text Label 1850 6450 2    60   ~ 0
WS_2
Text Label 3000 6450 2    60   ~ 0
WS_3
Text Label 4100 6450 2    60   ~ 0
WS_4
Text Label 700  7450 2    60   ~ 0
WS_5
Text Label 1850 7450 2    60   ~ 0
WS_6
Text Label 3000 7450 2    60   ~ 0
WS_7
Text Label 4100 7450 2    60   ~ 0
WS_8
Text Label 700  6350 2    60   ~ 0
VCC
Text Label 700  6150 2    60   ~ 0
VCC
Text Label 1850 6150 2    60   ~ 0
VCC
Text Label 1850 6350 2    60   ~ 0
VCC
Text Label 3000 6350 2    60   ~ 0
VCC
Text Label 3000 6150 2    60   ~ 0
VCC
Text Label 4100 6150 2    60   ~ 0
VCC
Text Label 4100 6350 2    60   ~ 0
VCC
Text Label 4100 7350 2    60   ~ 0
VCC
Text Label 4100 7150 2    60   ~ 0
VCC
Text Label 3000 7350 2    60   ~ 0
VCC
Text Label 3000 7150 2    60   ~ 0
VCC
Text Label 1850 7350 2    60   ~ 0
VCC
Text Label 1850 7150 2    60   ~ 0
VCC
Text Label 700  7150 2    60   ~ 0
VCC
Text Label 700  7350 2    60   ~ 0
VCC
NoConn ~ 4100 7050
NoConn ~ 3000 7050
NoConn ~ 1850 7050
NoConn ~ 700  7050
NoConn ~ 700  6050
NoConn ~ 1850 6050
NoConn ~ 3000 6050
NoConn ~ 4100 6050
Text Label 1500 6150 0    60   ~ 0
1A
Text Label 1500 6350 0    60   ~ 0
1B
Text Label 2650 6150 0    60   ~ 0
2A
Text Label 2650 6350 0    60   ~ 0
2B
Text Label 3800 6150 0    60   ~ 0
3A
Text Label 3800 6350 0    60   ~ 0
3B
Text Label 4900 6150 0    60   ~ 0
4A
Text Label 4900 6350 0    60   ~ 0
4B
Text Label 1500 7150 0    60   ~ 0
5A
Text Label 1500 7350 0    60   ~ 0
5B
Text Label 2650 7150 0    60   ~ 0
6A
Text Label 2650 7350 0    60   ~ 0
6B
Text Label 3800 7150 0    60   ~ 0
7A
Text Label 3800 7350 0    60   ~ 0
7B
Text Label 4900 7150 0    60   ~ 0
8A
Text Label 4900 7350 0    60   ~ 0
8B
Text Label 1100 5850 1    60   ~ 0
VCC
Text Label 2250 5850 1    60   ~ 0
VCC
Text Label 3400 5850 1    60   ~ 0
VCC
Text Label 4500 5850 1    60   ~ 0
VCC
Text Label 1100 6850 1    60   ~ 0
VCC
Text Label 2250 6850 1    60   ~ 0
VCC
Text Label 3400 6850 1    60   ~ 0
VCC
Text Label 4500 6850 1    60   ~ 0
VCC
Text Label 4500 7650 3    60   ~ 0
GND
Text Label 3400 7650 3    60   ~ 0
GND
Text Label 2250 7650 3    60   ~ 0
GND
Text Label 1100 7650 3    60   ~ 0
GND
Text Label 1100 6650 3    60   ~ 0
GND
Text Label 2250 6650 3    60   ~ 0
GND
Text Label 3400 6650 3    60   ~ 0
GND
Text Label 4500 6650 3    60   ~ 0
GND
$Comp
L C C1
U 1 1 5913E560
P 4850 4950
F 0 "C1" H 4875 5050 50  0000 L CNN
F 1 "C" H 4875 4850 50  0000 L CNN
F 2 "Capacitors_THT:C_Axial_L3.8mm_D2.6mm_P7.50mm_Horizontal" H 4888 4800 50  0001 C CNN
F 3 "" H 4850 4950 50  0001 C CNN
	1    4850 4950
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5913EA85
P 5100 4950
F 0 "C2" H 5125 5050 50  0000 L CNN
F 1 "C" H 5125 4850 50  0000 L CNN
F 2 "Capacitors_THT:C_Axial_L3.8mm_D2.6mm_P7.50mm_Horizontal" H 5138 4800 50  0001 C CNN
F 3 "" H 5100 4950 50  0001 C CNN
	1    5100 4950
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5913EAF8
P 5350 4950
F 0 "C3" H 5375 5050 50  0000 L CNN
F 1 "C" H 5375 4850 50  0000 L CNN
F 2 "Capacitors_THT:C_Axial_L3.8mm_D2.6mm_P7.50mm_Horizontal" H 5388 4800 50  0001 C CNN
F 3 "" H 5350 4950 50  0001 C CNN
	1    5350 4950
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 5913EC0A
P 5600 4950
F 0 "C4" H 5625 5050 50  0000 L CNN
F 1 "C" H 5625 4850 50  0000 L CNN
F 2 "Capacitors_THT:C_Axial_L3.8mm_D2.6mm_P7.50mm_Horizontal" H 5638 4800 50  0001 C CNN
F 3 "" H 5600 4950 50  0001 C CNN
	1    5600 4950
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 5913EC83
P 5850 4950
F 0 "C5" H 5875 5050 50  0000 L CNN
F 1 "C" H 5875 4850 50  0000 L CNN
F 2 "Capacitors_THT:C_Axial_L3.8mm_D2.6mm_P7.50mm_Horizontal" H 5888 4800 50  0001 C CNN
F 3 "" H 5850 4950 50  0001 C CNN
	1    5850 4950
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 5913ECFF
P 6100 4950
F 0 "C6" H 6125 5050 50  0000 L CNN
F 1 "C" H 6125 4850 50  0000 L CNN
F 2 "Capacitors_THT:C_Axial_L3.8mm_D2.6mm_P7.50mm_Horizontal" H 6138 4800 50  0001 C CNN
F 3 "" H 6100 4950 50  0001 C CNN
	1    6100 4950
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 5913EDA1
P 6350 4950
F 0 "C7" H 6375 5050 50  0000 L CNN
F 1 "C" H 6375 4850 50  0000 L CNN
F 2 "Capacitors_THT:C_Axial_L3.8mm_D2.6mm_P7.50mm_Horizontal" H 6388 4800 50  0001 C CNN
F 3 "" H 6350 4950 50  0001 C CNN
	1    6350 4950
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 5913EE23
P 6600 4950
F 0 "C8" H 6625 5050 50  0000 L CNN
F 1 "C" H 6625 4850 50  0000 L CNN
F 2 "Capacitors_THT:C_Axial_L3.8mm_D2.6mm_P7.50mm_Horizontal" H 6638 4800 50  0001 C CNN
F 3 "" H 6600 4950 50  0001 C CNN
	1    6600 4950
	1    0    0    -1  
$EndComp
Text Label 4850 4800 1    60   ~ 0
VCC
Text Label 5100 4800 1    60   ~ 0
VCC
Text Label 5350 4800 1    60   ~ 0
VCC
Text Label 5600 4800 1    60   ~ 0
VCC
Text Label 5850 4800 1    60   ~ 0
VCC
Text Label 6100 4800 1    60   ~ 0
VCC
Text Label 6350 4800 1    60   ~ 0
VCC
Text Label 6600 4800 1    60   ~ 0
VCC
Text Label 4850 5100 3    60   ~ 0
GND
Text Label 5100 5100 3    60   ~ 0
GND
Text Label 5350 5100 3    60   ~ 0
GND
Text Label 5600 5100 3    60   ~ 0
GND
Text Label 5850 5100 3    60   ~ 0
GND
Text Label 6100 5100 3    60   ~ 0
GND
Text Label 6350 5100 3    60   ~ 0
GND
Text Label 6600 5100 3    60   ~ 0
GND
$Comp
L RJ45_2x4 J1
U 1 1 5923D80D
P 10050 5100
F 0 "J1" H 9150 6600 50  0000 C CNN
F 1 "RJ45_2x4" H 8500 6600 50  0000 C CNN
F 2 "custom:RJ45_2x4" H 10050 5100 50  0001 C CNN
F 3 "" H 10050 5100 50  0001 C CNN
	1    10050 5100
	1    0    0    -1  
$EndComp
Text Label 7300 3750 1    60   ~ 0
1A
Text Label 7400 3750 1    60   ~ 0
1B
Text Label 7900 3750 1    60   ~ 0
GND
Text Label 8000 3750 1    60   ~ 0
GND
Text Label 8100 3750 1    60   ~ 0
2A
Text Label 8200 3750 1    60   ~ 0
2B
Text Label 8700 3750 1    60   ~ 0
GND
Text Label 8800 3750 1    60   ~ 0
GND
Text Label 8900 3750 1    60   ~ 0
3A
Text Label 9000 3750 1    60   ~ 0
3B
Text Label 9500 3750 1    60   ~ 0
GND
Text Label 9600 3750 1    60   ~ 0
GND
Text Label 9700 3750 1    60   ~ 0
4A
Text Label 9800 3750 1    60   ~ 0
4B
Text Label 10300 3750 1    60   ~ 0
GND
Text Label 10400 3750 1    60   ~ 0
GND
Text Label 7300 5550 3    60   ~ 0
5A
Text Label 7400 5550 3    60   ~ 0
5B
Text Label 7900 5550 3    60   ~ 0
GND
Text Label 8000 5550 3    60   ~ 0
GND
Text Label 8100 5550 3    60   ~ 0
6A
Text Label 8200 5550 3    60   ~ 0
6B
Text Label 8700 5550 3    60   ~ 0
GND
Text Label 8800 5550 3    60   ~ 0
GND
Text Label 8900 5550 3    60   ~ 0
7A
Text Label 9000 5550 3    60   ~ 0
7B
Text Label 9500 5550 3    60   ~ 0
GND
Text Label 9600 5550 3    60   ~ 0
GND
Text Label 9700 5550 3    60   ~ 0
8A
Text Label 9800 5550 3    60   ~ 0
8B
Text Label 10300 5550 3    60   ~ 0
GND
Text Label 10400 5550 3    60   ~ 0
GND
Text Label 10600 4300 0    60   ~ 0
GND
Text Label 10600 4400 0    60   ~ 0
GND
Text Label 10600 4500 0    60   ~ 0
GND
Text Label 10600 4600 0    60   ~ 0
GND
Text Label 10600 4800 0    60   ~ 0
GND
Text Label 10600 4700 0    60   ~ 0
GND
Text Label 10600 4900 0    60   ~ 0
GND
Text Label 10600 5000 0    60   ~ 0
GND
Text Label 10600 5100 0    60   ~ 0
GND
$EndSCHEMATC
