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
LIBS:bixi_pt-cache
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
L Screw_Terminal_1x02 J1
U 1 1 5907F10E
P 6000 2850
F 0 "J1" H 6000 3100 50  0000 C TNN
F 1 "Screw_Terminal_1x02" V 5850 2850 50  0000 C TNN
F 2 "custom:OSTYK42102030-2P-Terminal" H 6000 2625 50  0001 C CNN
F 3 "" H 5975 2850 50  0001 C CNN
	1    6000 2850
	1    0    0    -1  
$EndComp
Text Label 6200 2750 0    60   ~ 0
VCC
Text Label 6200 2950 0    60   ~ 0
GND
$Comp
L CONN_01X03 L1
U 1 1 5907F1DC
P 4500 2850
F 0 "L1" H 4500 3050 50  0000 C CNN
F 1 "CONN_01X03" V 4600 2850 50  0000 C CNN
F 2 "custom:3-wire-hole-with-relief" H 4500 2850 50  0001 C CNN
F 3 "" H 4500 2850 50  0001 C CNN
	1    4500 2850
	1    0    0    -1  
$EndComp
Text Label 4300 2950 2    60   ~ 0
GND
Text Label 4300 2850 2    60   ~ 0
DATA
$Comp
L CONN_01X03 R1
U 1 1 5907F236
P 6800 2850
F 0 "R1" H 6800 3050 50  0000 C CNN
F 1 "CONN_01X03" V 6900 2850 50  0000 C CNN
F 2 "custom:3-wire-hole-with-relief" H 6800 2850 50  0001 C CNN
F 3 "" H 6800 2850 50  0001 C CNN
	1    6800 2850
	-1   0    0    1   
$EndComp
Text Label 7000 2950 0    60   ~ 0
GND
Text Label 7000 2850 0    60   ~ 0
DATA
$Comp
L Jumper PWR_L1
U 1 1 59139D88
P 5550 3550
F 0 "PWR_L1" H 5550 3700 50  0000 C CNN
F 1 "Jumper" H 5550 3470 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 5550 3550 50  0001 C CNN
F 3 "" H 5550 3550 50  0001 C CNN
	1    5550 3550
	1    0    0    -1  
$EndComp
Text Label 4300 2750 2    60   ~ 0
VCCL
Text Label 7000 2750 0    60   ~ 0
VCCR
Text Label 5250 3550 2    60   ~ 0
VCCL
Text Label 5850 3550 0    60   ~ 0
VCC
$Comp
L Jumper PWR_R1
U 1 1 59139ED6
P 5550 3900
F 0 "PWR_R1" H 5550 4050 50  0000 C CNN
F 1 "Jumper" H 5550 3820 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 5550 3900 50  0001 C CNN
F 3 "" H 5550 3900 50  0001 C CNN
	1    5550 3900
	1    0    0    -1  
$EndComp
Text Label 5250 3900 2    60   ~ 0
VCC
Text Label 5850 3900 0    60   ~ 0
VCCR
$EndSCHEMATC
