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
LIBS:bixi_node-cache
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
L RJ45 J1
U 1 1 58CDFC74
P 3950 3350
F 0 "J1" H 4150 3850 50  0000 C CNN
F 1 "RJ45" H 3800 3850 50  0000 C CNN
F 2 "Connectors:RJ45_8" H 3950 3350 50  0001 C CNN
F 3 "" H 3950 3350 50  0000 C CNN
	1    3950 3350
	1    0    0    -1  
$EndComp
$Comp
L SP3485CN U1
U 1 1 58CE0617
P 5800 3300
F 0 "U1" H 5500 3650 50  0000 L CNN
F 1 "SP3485CN" H 5900 3650 50  0000 L CNN
F 2 "Housings_DIP:DIP-8_W7.62mm" H 6850 2950 50  0001 C CIN
F 3 "" H 5800 3300 50  0000 C CNN
	1    5800 3300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR10
U 1 1 58CE067C
P 5800 3700
F 0 "#PWR10" H 5800 3450 50  0001 C CNN
F 1 "GND" H 5800 3550 50  0000 C CNN
F 2 "" H 5800 3700 50  0000 C CNN
F 3 "" H 5800 3700 50  0000 C CNN
	1    5800 3700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 58CE0696
P 4200 3800
F 0 "#PWR3" H 4200 3550 50  0001 C CNN
F 1 "GND" H 4200 3650 50  0000 C CNN
F 2 "" H 4200 3800 50  0000 C CNN
F 3 "" H 4200 3800 50  0000 C CNN
	1    4200 3800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR4
U 1 1 58CE06B0
P 4300 3800
F 0 "#PWR4" H 4300 3550 50  0001 C CNN
F 1 "GND" H 4300 3650 50  0000 C CNN
F 2 "" H 4300 3800 50  0000 C CNN
F 3 "" H 4300 3800 50  0000 C CNN
	1    4300 3800
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR9
U 1 1 58CE06CA
P 5800 2900
F 0 "#PWR9" H 5800 2750 50  0001 C CNN
F 1 "VCC" H 5800 3050 50  0000 C CNN
F 2 "" H 5800 2900 50  0000 C CNN
F 3 "" H 5800 2900 50  0000 C CNN
	1    5800 2900
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 58CE0786
P 4350 4850
F 0 "C1" H 4375 4950 50  0000 L CNN
F 1 "C" H 4375 4750 50  0000 L CNN
F 2 "Capacitors_THT:C_Axial_L3.8mm_D2.6mm_P7.50mm_Horizontal" H 4388 4700 50  0001 C CNN
F 3 "" H 4350 4850 50  0000 C CNN
	1    4350 4850
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR5
U 1 1 58CE07F1
P 4350 4700
F 0 "#PWR5" H 4350 4550 50  0001 C CNN
F 1 "VCC" H 4350 4850 50  0000 C CNN
F 2 "" H 4350 4700 50  0000 C CNN
F 3 "" H 4350 4700 50  0000 C CNN
	1    4350 4700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR6
U 1 1 58CE0C7F
P 4350 5000
F 0 "#PWR6" H 4350 4750 50  0001 C CNN
F 1 "GND" H 4350 4850 50  0000 C CNN
F 2 "" H 4350 5000 50  0000 C CNN
F 3 "" H 4350 5000 50  0000 C CNN
	1    4350 5000
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR13
U 1 1 58D6B5B6
P 8050 3200
F 0 "#PWR13" H 8050 3050 50  0001 C CNN
F 1 "VCC" H 8050 3350 50  0000 C CNN
F 2 "" H 8050 3200 50  0000 C CNN
F 3 "" H 8050 3200 50  0000 C CNN
	1    8050 3200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR14
U 1 1 58D6B5DA
P 8050 3400
F 0 "#PWR14" H 8050 3150 50  0001 C CNN
F 1 "GND" H 8050 3250 50  0000 C CNN
F 2 "" H 8050 3400 50  0000 C CNN
F 3 "" H 8050 3400 50  0000 C CNN
	1    8050 3400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR8
U 1 1 58D6B6AE
P 5550 4850
F 0 "#PWR8" H 5550 4600 50  0001 C CNN
F 1 "GND" H 5550 4700 50  0000 C CNN
F 2 "" H 5550 4850 50  0000 C CNN
F 3 "" H 5550 4850 50  0000 C CNN
	1    5550 4850
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR7
U 1 1 58D6B70F
P 5050 4850
F 0 "#PWR7" H 5050 4700 50  0001 C CNN
F 1 "VCC" H 5050 5000 50  0000 C CNN
F 2 "" H 5050 4850 50  0000 C CNN
F 3 "" H 5050 4850 50  0000 C CNN
	1    5050 4850
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 P1
U 1 1 58D6C384
P 8250 3300
F 0 "P1" H 8250 3500 50  0000 C CNN
F 1 "CONN_01X03" V 8350 3300 50  0000 C CNN
F 2 "custom:PAD_3X_OVAL_WS2812B" H 8250 3300 50  0001 C CNN
F 3 "" H 8250 3300 50  0000 C CNN
	1    8250 3300
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_1x01 J2
U 1 1 58EA38FE
P 4850 4850
F 0 "J2" H 4850 5000 50  0000 C TNN
F 1 "Screw_Terminal_1x01" V 4700 4850 50  0000 C TNN
F 2 "custom:A116169CT_SPADE_CONNECTOR" H 4850 4725 50  0001 C CNN
F 3 "" H 4850 4750 50  0001 C CNN
	1    4850 4850
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_1x01 J3
U 1 1 58EA3975
P 5350 4850
F 0 "J3" H 5350 5000 50  0000 C TNN
F 1 "Screw_Terminal_1x01" V 5200 4850 50  0000 C TNN
F 2 "custom:A116169CT_SPADE_CONNECTOR" H 5350 4725 50  0001 C CNN
F 3 "" H 5350 4750 50  0001 C CNN
	1    5350 4850
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR11
U 1 1 58EA51F3
P 6400 4550
F 0 "#PWR11" H 6400 4400 50  0001 C CNN
F 1 "VCC" H 6400 4700 50  0000 C CNN
F 2 "" H 6400 4550 50  0000 C CNN
F 3 "" H 6400 4550 50  0000 C CNN
	1    6400 4550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR12
U 1 1 58EA5217
P 6400 5050
F 0 "#PWR12" H 6400 4800 50  0001 C CNN
F 1 "GND" H 6400 4900 50  0000 C CNN
F 2 "" H 6400 5050 50  0000 C CNN
F 3 "" H 6400 5050 50  0000 C CNN
	1    6400 5050
	1    0    0    -1  
$EndComp
Connection ~ 5550 4850
Connection ~ 5050 4850
Text Label 5400 3100 2    60   ~ 0
DATA
Text Label 5400 3500 2    60   ~ 0
DATA
$Comp
L Jumper_NC_Dual JP1
U 1 1 58EA59A3
P 6400 4800
F 0 "JP1" H 6450 4700 50  0000 L CNN
F 1 "Jumper_NC_Dual" H 6400 4900 50  0000 C BNN
F 2 "custom:jumper_3_pin_fixed" H 6400 4800 50  0001 C CNN
F 3 "" H 6400 4800 50  0000 C CNN
	1    6400 4800
	0    1    1    0   
$EndComp
Text Label 8050 3300 2    60   ~ 0
DATA
$Comp
L R R1
U 1 1 5901DDA4
P 2450 3350
F 0 "R1" V 2530 3350 50  0000 C CNN
F 1 "R" V 2450 3350 50  0000 C CNN
F 2 "Resistors_THT:Resistor_Horizontal_RM7mm" V 2380 3350 50  0001 C CNN
F 3 "" H 2450 3350 50  0000 C CNN
	1    2450 3350
	0    1    1    0   
$EndComp
Text Label 3600 3800 3    60   ~ 0
DATA_DIFF_A
Text Label 3700 3800 3    60   ~ 0
DATA_DIFF_B
Text Label 3800 3800 3    60   ~ 0
DATA
Text Label 2300 3350 2    60   ~ 0
DATA_DIFF_A
Text Label 2600 3350 0    60   ~ 0
DATA_DIFF_B
Text Label 6200 3200 0    60   ~ 0
DATA_DIFF_A
Text Label 6200 3400 0    60   ~ 0
DATA_DIFF_B
Text Label 5400 3200 2    60   ~ 0
MODE
Text Label 5400 3400 2    60   ~ 0
MODE
Text Label 6300 4800 2    60   ~ 0
MODE
$Comp
L VCC #PWR2
U 1 1 5902A84B
P 4100 3800
F 0 "#PWR2" H 4100 3650 50  0001 C CNN
F 1 "VCC" H 4100 3950 50  0000 C CNN
F 2 "" H 4100 3800 50  0000 C CNN
F 3 "" H 4100 3800 50  0000 C CNN
	1    4100 3800
	-1   0    0    1   
$EndComp
$Comp
L VCC #PWR1
U 1 1 5902A94D
P 4000 3800
F 0 "#PWR1" H 4000 3650 50  0001 C CNN
F 1 "VCC" H 4000 3950 50  0000 C CNN
F 2 "" H 4000 3800 50  0000 C CNN
F 3 "" H 4000 3800 50  0000 C CNN
	1    4000 3800
	-1   0    0    1   
$EndComp
$EndSCHEMATC
