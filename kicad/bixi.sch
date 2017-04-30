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
L RJ45 J8
U 1 1 58BEF56F
P 10300 5150
F 0 "J8" H 10500 5650 50  0000 C CNN
F 1 "RJ45" H 10150 5650 50  0000 C CNN
F 2 "Connectors:RJ45_8" H 10300 5150 50  0001 C CNN
F 3 "" H 10300 5150 50  0000 C CNN
	1    10300 5150
	1    0    0    -1  
$EndComp
$Comp
L Teensy3.6 U1
U 1 1 58BEFB78
P 2600 3300
F 0 "U1" H 2600 5600 60  0000 C CNN
F 1 "Teensy3.6" H 2600 1000 60  0000 C CNN
F 2 "Teensy:Teensy35_36" H 2600 3300 60  0001 C CNN
F 3 "" H 2600 3300 60  0000 C CNN
	1    2600 3300
	1    0    0    -1  
$EndComp
$Comp
L RJ45 J7
U 1 1 58BF0128
P 10300 3900
F 0 "J7" H 10500 4400 50  0000 C CNN
F 1 "RJ45" H 10150 4400 50  0000 C CNN
F 2 "Connectors:RJ45_8" H 10300 3900 50  0001 C CNN
F 3 "" H 10300 3900 50  0000 C CNN
	1    10300 3900
	1    0    0    -1  
$EndComp
$Comp
L RJ45 J6
U 1 1 58BF0276
P 10300 2650
F 0 "J6" H 10500 3150 50  0000 C CNN
F 1 "RJ45" H 10150 3150 50  0000 C CNN
F 2 "Connectors:RJ45_8" H 10300 2650 50  0001 C CNN
F 3 "" H 10300 2650 50  0000 C CNN
	1    10300 2650
	1    0    0    -1  
$EndComp
$Comp
L RJ45 J5
U 1 1 58BF02BE
P 10300 1400
F 0 "J5" H 10500 1900 50  0000 C CNN
F 1 "RJ45" H 10150 1900 50  0000 C CNN
F 2 "Connectors:RJ45_8" H 10300 1400 50  0001 C CNN
F 3 "" H 10300 1400 50  0000 C CNN
	1    10300 1400
	1    0    0    -1  
$EndComp
$Comp
L RJ45 J4
U 1 1 58BF0569
P 9100 5150
F 0 "J4" H 9300 5650 50  0000 C CNN
F 1 "RJ45" H 8950 5650 50  0000 C CNN
F 2 "Connectors:RJ45_8" H 9100 5150 50  0001 C CNN
F 3 "" H 9100 5150 50  0000 C CNN
	1    9100 5150
	1    0    0    -1  
$EndComp
$Comp
L RJ45 J3
U 1 1 58BF05B1
P 9100 3900
F 0 "J3" H 9300 4400 50  0000 C CNN
F 1 "RJ45" H 8950 4400 50  0000 C CNN
F 2 "Connectors:RJ45_8" H 9100 3900 50  0001 C CNN
F 3 "" H 9100 3900 50  0000 C CNN
	1    9100 3900
	1    0    0    -1  
$EndComp
$Comp
L RJ45 J2
U 1 1 58BF05F9
P 9100 2650
F 0 "J2" H 9300 3150 50  0000 C CNN
F 1 "RJ45" H 8950 3150 50  0000 C CNN
F 2 "Connectors:RJ45_8" H 9100 2650 50  0001 C CNN
F 3 "" H 9100 2650 50  0000 C CNN
	1    9100 2650
	1    0    0    -1  
$EndComp
$Comp
L RJ45 J1
U 1 1 58BF0641
P 9100 1400
F 0 "J1" H 9300 1900 50  0000 C CNN
F 1 "RJ45" H 8950 1900 50  0000 C CNN
F 2 "Connectors:RJ45_8" H 9100 1400 50  0001 C CNN
F 3 "" H 9100 1400 50  0000 C CNN
	1    9100 1400
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 58BF16CF
P 6800 4850
F 0 "C1" H 6825 4950 50  0000 L CNN
F 1 "C" H 6825 4750 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D4.7mm_W2.5mm_P5.00mm" H 6838 4700 50  0001 C CNN
F 3 "" H 6800 4850 50  0000 C CNN
	1    6800 4850
	1    0    0    -1  
$EndComp
$Comp
L sn75lbc978 U2
U 1 1 5904BED1
P 5350 4050
F 0 "U2" H 5350 5500 60  0000 C CNN
F 1 "sn75lbc978" H 5350 4050 60  0000 C CNN
F 2 "Housings_SSOP:SSOP-56_7.5x18.5mm_Pitch0.635mm" H 5350 4050 60  0001 C CNN
F 3 "" H 5350 4050 60  0001 C CNN
	1    5350 4050
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
Text Label 4600 3000 2    60   ~ 0
WS_1
Text Label 4600 3200 2    60   ~ 0
WS_2
Text Label 4600 3400 2    60   ~ 0
WS_3
Text Label 4600 3600 2    60   ~ 0
WS_4
Text Label 4600 4500 2    60   ~ 0
WS_5
Text Label 4600 4700 2    60   ~ 0
WS_6
Text Label 4600 4900 2    60   ~ 0
WS_7
Text Label 4600 5100 2    60   ~ 0
WS_8
Text Label 1600 1200 2    60   ~ 0
GND
Text Label 3600 4500 0    60   ~ 0
VCC
Text Label 6100 4400 0    60   ~ 0
VCC
Text Label 6100 3800 0    60   ~ 0
VCC
Text Label 4600 3800 2    60   ~ 0
VCC
Text Label 4600 4400 2    60   ~ 0
VCC
Text Label 4600 3900 2    60   ~ 0
GND
Text Label 4600 4000 2    60   ~ 0
GND
Text Label 4600 4100 2    60   ~ 0
GND
Text Label 4600 4200 2    60   ~ 0
GND
Text Label 4600 4300 2    60   ~ 0
GND
Text Label 6100 3900 0    60   ~ 0
GND
Text Label 6100 4000 0    60   ~ 0
GND
Text Label 6100 4100 0    60   ~ 0
GND
Text Label 6100 4200 0    60   ~ 0
GND
Text Label 6100 4300 0    60   ~ 0
GND
Text Label 6100 2900 0    60   ~ 0
VCC
Text Label 4600 2800 2    60   ~ 0
GND
Text Label 4600 2900 2    60   ~ 0
GND
Text Label 4600 3100 2    60   ~ 0
VCC
Text Label 4600 3300 2    60   ~ 0
VCC
Text Label 4600 3500 2    60   ~ 0
VCC
Text Label 4600 3700 2    60   ~ 0
VCC
Text Label 4600 4600 2    60   ~ 0
VCC
Text Label 4600 4800 2    60   ~ 0
VCC
Text Label 4600 5000 2    60   ~ 0
VCC
Text Label 4600 5200 2    60   ~ 0
VCC
NoConn ~ 4600 5300
NoConn ~ 4600 5400
NoConn ~ 6100 2700
NoConn ~ 6100 2800
NoConn ~ 6100 3000
NoConn ~ 6100 3100
Text Label 6100 5400 0    60   ~ 0
1B
Text Label 6100 5300 0    60   ~ 0
1A
Text Label 6100 5200 0    60   ~ 0
2B
Text Label 6100 5100 0    60   ~ 0
2A
Text Label 6100 5000 0    60   ~ 0
3B
Text Label 6100 4900 0    60   ~ 0
3A
Text Label 6100 4800 0    60   ~ 0
4B
Text Label 6100 4700 0    60   ~ 0
4A
Text Label 6100 4600 0    60   ~ 0
5B
Text Label 6100 4500 0    60   ~ 0
5A
Text Label 6100 3700 0    60   ~ 0
6B
Text Label 6100 3600 0    60   ~ 0
6A
Text Label 6100 3500 0    60   ~ 0
7B
Text Label 6100 3400 0    60   ~ 0
7A
Text Label 6100 3300 0    60   ~ 0
8B
Text Label 6100 3200 0    60   ~ 0
8A
Text Label 8750 1850 3    60   ~ 0
1A
Text Label 8850 1850 3    60   ~ 0
1B
Text Label 8750 3100 3    60   ~ 0
2A
Text Label 8850 3100 3    60   ~ 0
2B
Text Label 8750 4350 3    60   ~ 0
3A
Text Label 8850 4350 3    60   ~ 0
3B
Text Label 8750 5600 3    60   ~ 0
4A
Text Label 8850 5600 3    60   ~ 0
4B
Text Label 9950 1850 3    60   ~ 0
5A
Text Label 10050 1850 3    60   ~ 0
5B
Text Label 9950 3100 3    60   ~ 0
6A
Text Label 10050 3100 3    60   ~ 0
6B
Text Label 9950 4350 3    60   ~ 0
7A
Text Label 10050 4350 3    60   ~ 0
7B
Text Label 9950 5600 3    60   ~ 0
8A
Text Label 10050 5600 3    60   ~ 0
8B
Text Label 9350 1850 3    60   ~ 0
GND
Text Label 9450 1850 3    60   ~ 0
GND
Text Label 9350 3100 3    60   ~ 0
GND
Text Label 9450 3100 3    60   ~ 0
GND
Text Label 10550 1850 3    60   ~ 0
GND
Text Label 10650 1850 3    60   ~ 0
GND
Text Label 10550 3100 3    60   ~ 0
GND
Text Label 10650 3100 3    60   ~ 0
GND
Text Label 9350 4350 3    60   ~ 0
GND
Text Label 9450 4350 3    60   ~ 0
GND
Text Label 10550 4350 3    60   ~ 0
GND
Text Label 10650 4350 3    60   ~ 0
GND
Text Label 10650 5600 3    60   ~ 0
GND
Text Label 10550 5600 3    60   ~ 0
GND
Text Label 9350 5600 3    60   ~ 0
GND
Text Label 9450 5600 3    60   ~ 0
GND
$Comp
L R R1
U 1 1 5904FF6D
P 7550 2450
F 0 "R1" V 7630 2450 50  0000 C CNN
F 1 "100" V 7550 2450 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7480 2450 50  0001 C CNN
F 3 "" H 7550 2450 50  0000 C CNN
	1    7550 2450
	0    1    1    0   
$EndComp
Text Label 7400 2450 2    60   ~ 0
1A
Text Label 7700 2450 0    60   ~ 0
1B
$Comp
L R R2
U 1 1 590502A6
P 7550 2650
F 0 "R2" V 7630 2650 50  0000 C CNN
F 1 "100" V 7550 2650 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7480 2650 50  0001 C CNN
F 3 "" H 7550 2650 50  0000 C CNN
	1    7550 2650
	0    1    1    0   
$EndComp
Text Label 7400 2650 2    60   ~ 0
2A
Text Label 7700 2650 0    60   ~ 0
2B
$Comp
L R R3
U 1 1 59050439
P 7550 2850
F 0 "R3" V 7630 2850 50  0000 C CNN
F 1 "100" V 7550 2850 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7480 2850 50  0001 C CNN
F 3 "" H 7550 2850 50  0000 C CNN
	1    7550 2850
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 590504C9
P 7550 3050
F 0 "R4" V 7630 3050 50  0000 C CNN
F 1 "100" V 7550 3050 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7480 3050 50  0001 C CNN
F 3 "" H 7550 3050 50  0000 C CNN
	1    7550 3050
	0    1    1    0   
$EndComp
$Comp
L R R5
U 1 1 5905055D
P 7550 3250
F 0 "R5" V 7630 3250 50  0000 C CNN
F 1 "100" V 7550 3250 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7480 3250 50  0001 C CNN
F 3 "" H 7550 3250 50  0000 C CNN
	1    7550 3250
	0    1    1    0   
$EndComp
$Comp
L R R6
U 1 1 590505FB
P 7550 3450
F 0 "R6" V 7630 3450 50  0000 C CNN
F 1 "100" V 7550 3450 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7480 3450 50  0001 C CNN
F 3 "" H 7550 3450 50  0000 C CNN
	1    7550 3450
	0    1    1    0   
$EndComp
$Comp
L R R7
U 1 1 59050693
P 7550 3650
F 0 "R7" V 7630 3650 50  0000 C CNN
F 1 "100" V 7550 3650 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7480 3650 50  0001 C CNN
F 3 "" H 7550 3650 50  0000 C CNN
	1    7550 3650
	0    1    1    0   
$EndComp
$Comp
L R R8
U 1 1 59050711
P 7550 3850
F 0 "R8" V 7630 3850 50  0000 C CNN
F 1 "100" V 7550 3850 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7480 3850 50  0001 C CNN
F 3 "" H 7550 3850 50  0000 C CNN
	1    7550 3850
	0    1    1    0   
$EndComp
Text Label 7400 2850 2    60   ~ 0
3A
Text Label 7400 3050 2    60   ~ 0
4A
Text Label 7400 3250 2    60   ~ 0
5A
Text Label 7400 3450 2    60   ~ 0
6A
Text Label 7400 3650 2    60   ~ 0
7A
Text Label 7400 3850 2    60   ~ 0
8A
Text Label 7700 2850 0    60   ~ 0
3B
Text Label 7700 3050 0    60   ~ 0
4B
Text Label 7700 3250 0    60   ~ 0
5B
Text Label 7700 3450 0    60   ~ 0
6B
Text Label 7700 3650 0    60   ~ 0
7B
Text Label 7700 3850 0    60   ~ 0
8B
Text Label 6800 4700 1    60   ~ 0
VCC
Text Label 6800 5000 3    60   ~ 0
GND
$Comp
L ESP8266 U3
U 1 1 5904CE17
P 5350 1750
F 0 "U3" H 5350 2000 60  0000 C CNN
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
Text Label 3600 2300 0    60   ~ 0
3V
$EndSCHEMATC
