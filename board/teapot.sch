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
LIBS:tlv61225
LIBS:htu21d
LIBS:ms5637
LIBS:tept
LIBS:rfm69w
LIBS:sma
LIBS:testpoint
LIBS:swd
LIBS:stm32l052k8
LIBS:microusb-b
LIBS:tps79333dbvr
LIBS:tvs_small
LIBS:teapot-cache
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
L C C11
U 1 1 56707B80
P 950 5050
F 0 "C11" H 1050 5150 50  0000 L CNN
F 1 "100n" H 975 4950 50  0000 L CNN
F 2 "" H 988 4900 50  0000 C CNN
F 3 "" H 950 5050 50  0000 C CNN
	1    950  5050
	-1   0    0    1   
$EndComp
$Comp
L TLV61225 U1
U 1 1 56707CBF
P 2500 1150
F 0 "U1" V 2550 1150 60  0000 C CNN
F 1 "TLV61225" V 2450 1150 60  0000 C CNN
F 2 "footprints:SC-70" H 2450 1450 60  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1950593.pdf" H 2450 1450 60  0001 C CNN
F 4 "2492362" H 2500 1150 60  0001 C CNN "Farnell"
	1    2500 1150
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 56707DD4
P 3100 1400
F 0 "C2" H 3125 1500 50  0000 L CNN
F 1 "10u" H 3125 1300 50  0000 L CNN
F 2 "" H 3138 1250 50  0000 C CNN
F 3 "" H 3100 1400 50  0000 C CNN
F 4 "1735528" H 3100 1400 60  0001 C CNN "Farnell"
	1    3100 1400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR11
U 1 1 56707EE4
P 3100 1550
F 0 "#PWR11" H 3100 1300 50  0001 C CNN
F 1 "GND" H 3100 1400 50  0000 C CNN
F 2 "" H 3100 1550 50  0000 C CNN
F 3 "" H 3100 1550 50  0000 C CNN
	1    3100 1550
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR2
U 1 1 56707F42
P 3100 1050
F 0 "#PWR2" H 3100 900 50  0001 C CNN
F 1 "+3V3" H 3100 1190 50  0000 C CNN
F 2 "" H 3100 1050 50  0000 C CNN
F 3 "" H 3100 1050 50  0000 C CNN
	1    3100 1050
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 56708022
P 1550 1250
F 0 "C1" H 1575 1350 50  0000 L CNN
F 1 "10u" H 1575 1150 50  0000 L CNN
F 2 "" H 1588 1100 50  0000 C CNN
F 3 "" H 1550 1250 50  0000 C CNN
F 4 "1735528" H 1550 1250 60  0001 C CNN "Farnell"
	1    1550 1250
	1    0    0    -1  
$EndComp
$Comp
L L_Small L1
U 1 1 56708162
P 1800 1000
F 0 "L1" H 1830 1040 50  0000 L CNN
F 1 "4u7" H 1830 960 50  0000 L CNN
F 2 "" H 1800 1000 50  0000 C CNN
F 3 "" H 1800 1000 50  0000 C CNN
F 4 "2470318" H 1800 1000 60  0001 C CNN "Farnell"
	1    1800 1000
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X02 P1
U 1 1 567082BA
P 650 1200
F 0 "P1" H 650 1350 50  0000 C CNN
F 1 "BATT" V 750 1200 50  0000 C CNN
F 2 "footprints:AA_holder" H 650 1200 50  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1703957.pdf" H 650 1200 50  0001 C CNN
F 4 "1702629" H 650 1200 60  0001 C CNN "Farnell"
	1    650  1200
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR6
U 1 1 5670836A
P 1550 1500
F 0 "#PWR6" H 1550 1250 50  0001 C CNN
F 1 "GND" H 1550 1350 50  0000 C CNN
F 2 "" H 1550 1500 50  0000 C CNN
F 3 "" H 1550 1500 50  0000 C CNN
	1    1550 1500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR7
U 1 1 5670838C
P 1950 1500
F 0 "#PWR7" H 1950 1250 50  0001 C CNN
F 1 "GND" H 1950 1350 50  0000 C CNN
F 2 "" H 1950 1500 50  0000 C CNN
F 3 "" H 1950 1500 50  0000 C CNN
	1    1950 1500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR5
U 1 1 567083EF
P 1150 1500
F 0 "#PWR5" H 1150 1250 50  0001 C CNN
F 1 "GND" H 1150 1350 50  0000 C CNN
F 2 "" H 1150 1500 50  0000 C CNN
F 3 "" H 1150 1500 50  0000 C CNN
	1    1150 1500
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG1
U 1 1 5670841B
P 1300 1100
F 0 "#FLG1" H 1300 1195 50  0001 C CNN
F 1 "PWR_FLAG" H 1300 1280 50  0000 C CNN
F 2 "" H 1300 1100 50  0000 C CNN
F 3 "" H 1300 1100 50  0000 C CNN
	1    1300 1100
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG2
U 1 1 56708447
P 1150 1350
F 0 "#FLG2" H 1150 1445 50  0001 C CNN
F 1 "PWR_FLAG" H 1150 1530 50  0000 C CNN
F 2 "" H 1150 1350 50  0000 C CNN
F 3 "" H 1150 1350 50  0000 C CNN
	1    1150 1350
	0    1    1    0   
$EndComp
$Comp
L HTU21D U5
U 1 1 5670851D
P 1700 5100
F 0 "U5" V 1750 5050 60  0000 C CNN
F 1 "HTU21D" V 1650 5100 60  0000 C CNN
F 2 "footprints:HTU21D" H 1750 5150 60  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1792510.pdf" H 1750 5150 60  0001 C CNN
F 4 "2393536" H 1700 5100 60  0001 C CNN "Farnell"
	1    1700 5100
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR33
U 1 1 56708637
P 950 4900
F 0 "#PWR33" H 950 4750 50  0001 C CNN
F 1 "+3V3" H 950 5040 50  0000 C CNN
F 2 "" H 950 4900 50  0000 C CNN
F 3 "" H 950 4900 50  0000 C CNN
	1    950  4900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR34
U 1 1 5670867A
P 950 5200
F 0 "#PWR34" H 950 4950 50  0001 C CNN
F 1 "GND" H 950 5050 50  0000 C CNN
F 2 "" H 950 5200 50  0000 C CNN
F 3 "" H 950 5200 50  0000 C CNN
	1    950  5200
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 56708874
P 7300 3450
F 0 "R3" V 7400 3450 50  0000 C CNN
F 1 "10k" V 7300 3450 50  0000 C CNN
F 2 "" V 7230 3450 50  0000 C CNN
F 3 "" H 7300 3450 50  0000 C CNN
	1    7300 3450
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 567088B5
P 7200 3450
F 0 "R2" V 7100 3450 50  0000 C CNN
F 1 "10k" V 7200 3450 50  0000 C CNN
F 2 "" V 7130 3450 50  0000 C CNN
F 3 "" H 7200 3450 50  0000 C CNN
	1    7200 3450
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR20
U 1 1 56708996
P 7250 3250
F 0 "#PWR20" H 7250 3100 50  0001 C CNN
F 1 "+3V3" H 7250 3390 50  0000 C CNN
F 2 "" H 7250 3250 50  0000 C CNN
F 3 "" H 7250 3250 50  0000 C CNN
	1    7250 3250
	1    0    0    -1  
$EndComp
$Comp
L MS5637 U6
U 1 1 56708DE8
P 1650 6100
F 0 "U6" V 1700 6100 60  0000 C CNN
F 1 "MS5637" V 1600 6100 60  0000 C CNN
F 2 "footprints:MS563702" H 1550 6250 60  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1756129.pdf" H 1550 6250 60  0001 C CNN
F 4 "2362663" H 1650 6100 60  0001 C CNN "Farnell"
	1    1650 6100
	1    0    0    -1  
$EndComp
$Comp
L C C14
U 1 1 56708EC5
P 950 6100
F 0 "C14" H 750 6200 50  0000 L CNN
F 1 "100n" H 750 6000 50  0000 L CNN
F 2 "" H 988 5950 50  0000 C CNN
F 3 "" H 950 6100 50  0000 C CNN
	1    950  6100
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR38
U 1 1 56708F0F
P 950 5900
F 0 "#PWR38" H 950 5750 50  0001 C CNN
F 1 "+3V3" H 950 6040 50  0000 C CNN
F 2 "" H 950 5900 50  0000 C CNN
F 3 "" H 950 5900 50  0000 C CNN
	1    950  5900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR39
U 1 1 56708F9A
P 950 6350
F 0 "#PWR39" H 950 6100 50  0001 C CNN
F 1 "GND" H 950 6200 50  0000 C CNN
F 2 "" H 950 6350 50  0000 C CNN
F 3 "" H 950 6350 50  0000 C CNN
	1    950  6350
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR21
U 1 1 56709B94
P 10200 3300
F 0 "#PWR21" H 10200 3150 50  0001 C CNN
F 1 "+3V3" H 10200 3440 50  0000 C CNN
F 2 "" H 10200 3300 50  0000 C CNN
F 3 "" H 10200 3300 50  0000 C CNN
	1    10200 3300
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 56709F9B
P 10200 4150
F 0 "R6" V 10280 4150 50  0000 C CNN
F 1 "10k" V 10200 4150 50  0000 C CNN
F 2 "" V 10130 4150 50  0000 C CNN
F 3 "" H 10200 4150 50  0000 C CNN
	1    10200 4150
	1    0    0    -1  
$EndComp
$Comp
L TEPT Q1
U 1 1 5670A3C2
P 10150 3650
F 0 "Q1" H 10300 3425 60  0000 C CNN
F 1 "TEPT4400" H 9850 3900 60  0000 C CNN
F 2 "LEDs:LED-3MM" H 10025 4050 60  0001 C CNN
F 3 "http://www.vishay.com/docs/81341/tept4400.pdf" H 10025 4050 60  0001 C CNN
F 4 "SC12389" H 10150 3650 60  0001 C CNN "Farnell"
	1    10150 3650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR28
U 1 1 5670A6D2
P 10200 4300
F 0 "#PWR28" H 10200 4050 50  0001 C CNN
F 1 "GND" H 10200 4150 50  0000 C CNN
F 2 "" H 10200 4300 50  0000 C CNN
F 3 "" H 10200 4300 50  0000 C CNN
	1    10200 4300
	1    0    0    -1  
$EndComp
Text Notes 1400 6450 0    60   ~ 0
PRESSURE
Text Notes 1350 5550 0    60   ~ 0
TEMPERATURE\n& HUMIDITY
Text Notes 2150 1550 0    60   ~ 0
POWER SUPPLY
Text Notes 10450 3600 0    60   ~ 0
LIGHT\nSENSOR
$Comp
L RFM69W U3
U 1 1 5670B4E9
P 9300 1300
F 0 "U3" V 9350 1300 60  0000 C CNN
F 1 "RFM69W" V 9250 1300 60  0000 C CNN
F 2 "footprints:RFM69" H 9350 1750 60  0001 C CNN
F 3 "https://hasnet.supplies/static/RFM69W-V1.3.pdf" H 9350 1750 60  0001 C CNN
	1    9300 1300
	1    0    0    -1  
$EndComp
Text Label 2200 5000 0    60   ~ 0
I2C_SDA
Text Label 2200 5100 0    60   ~ 0
I2C_SCK
Text Label 2150 6050 0    60   ~ 0
I2C_SDA
Text Label 2150 6150 0    60   ~ 0
I2C_SCK
Text Label 10450 4000 0    60   ~ 0
LIGHT
Text Label 8750 1000 2    60   ~ 0
RFM_RESET
Text Label 9850 1100 0    60   ~ 0
RFM_NSS
Text Label 9850 1200 0    60   ~ 0
RFM_MOSI
Text Label 9850 1300 0    60   ~ 0
RFM_MISO
Text Label 9850 1400 0    60   ~ 0
RFM_SCK
$Comp
L SMA P2
U 1 1 5670BE45
P 10950 1600
F 0 "P2" H 11050 1500 60  0000 C CNN
F 1 "SMA" H 11050 1700 60  0000 C CNN
F 2 "footprints:SMA-142-0701-801" H 10950 1600 60  0001 C CNN
F 3 "" H 10950 1600 60  0000 C CNN
F 4 "1342651" H 10950 1600 60  0001 C CNN "Farnell"
	1    10950 1600
	1    0    0    -1  
$EndComp
$Comp
L TestPoint TP1
U 1 1 5670C17A
P 10100 1600
F 0 "TP1" H 10200 1650 60  0000 C CNN
F 1 "ANT" H 10200 1550 60  0000 C CNN
F 2 "" H 10100 1600 60  0000 C CNN
F 3 "" H 10100 1600 60  0000 C CNN
	1    10100 1600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR17
U 1 1 5670C5C3
P 10800 1850
F 0 "#PWR17" H 10800 1600 50  0001 C CNN
F 1 "GND" H 10800 1700 50  0000 C CNN
F 2 "" H 10800 1850 50  0000 C CNN
F 3 "" H 10800 1850 50  0000 C CNN
	1    10800 1850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR16
U 1 1 5670C6EB
P 9900 1800
F 0 "#PWR16" H 9900 1550 50  0001 C CNN
F 1 "GND" H 9900 1650 50  0000 C CNN
F 2 "" H 9900 1800 50  0000 C CNN
F 3 "" H 9900 1800 50  0000 C CNN
	1    9900 1800
	1    0    0    -1  
$EndComp
NoConn ~ 8750 1100
NoConn ~ 8750 1200
NoConn ~ 8750 1300
NoConn ~ 8750 1400
NoConn ~ 8750 1500
NoConn ~ 8750 1600
$Comp
L +3V3 #PWR14
U 1 1 5670C81E
P 8550 1650
F 0 "#PWR14" H 8550 1500 50  0001 C CNN
F 1 "+3V3" H 8550 1790 50  0000 C CNN
F 2 "" H 8550 1650 50  0000 C CNN
F 3 "" H 8550 1650 50  0000 C CNN
	1    8550 1650
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 5670C9CC
P 8700 1900
F 0 "C4" H 8725 2000 50  0000 L CNN
F 1 "100n" H 8725 1800 50  0000 L CNN
F 2 "" H 8738 1750 50  0000 C CNN
F 3 "" H 8700 1900 50  0000 C CNN
	1    8700 1900
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5670CA15
P 8500 1900
F 0 "C3" H 8525 2000 50  0000 L CNN
F 1 "10u" H 8525 1800 50  0000 L CNN
F 2 "" H 8538 1750 50  0000 C CNN
F 3 "" H 8500 1900 50  0000 C CNN
	1    8500 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 1200 3100 1200
Wire Wire Line
	3100 1200 3100 1250
Wire Wire Line
	3100 1050 3100 1100
Wire Wire Line
	3100 1100 3050 1100
Wire Wire Line
	1950 1000 1900 1000
Wire Wire Line
	1700 1100 1700 1000
Wire Wire Line
	850  1100 1950 1100
Connection ~ 1700 1100
Connection ~ 1550 1100
Wire Wire Line
	1550 1400 1550 1500
Wire Wire Line
	1950 1500 1950 1300
Wire Wire Line
	1950 1200 1900 1200
Wire Wire Line
	1900 1200 1900 1100
Connection ~ 1900 1100
Connection ~ 1300 1100
Connection ~ 1150 1350
Wire Wire Line
	950  5200 1150 5200
Wire Wire Line
	1150 5200 1150 5100
Wire Wire Line
	1150 5100 1200 5100
Connection ~ 950  4900
Wire Wire Line
	950  5900 950  5950
Wire Wire Line
	950  5950 1150 5950
Wire Wire Line
	1150 5950 1150 6050
Connection ~ 950  5950
Wire Wire Line
	950  6250 950  6350
Wire Wire Line
	1150 6150 1150 6250
Wire Wire Line
	1150 6250 950  6250
Connection ~ 950  6250
Wire Wire Line
	10200 4000 10450 4000
Connection ~ 10200 4000
Wire Wire Line
	9850 1600 10850 1600
Wire Wire Line
	10750 1500 10850 1500
Wire Wire Line
	10800 1500 10800 1450
Wire Wire Line
	10800 1450 10850 1450
Connection ~ 10800 1500
Wire Wire Line
	10800 1700 10800 1850
Wire Wire Line
	10800 1750 10850 1750
Connection ~ 10800 1700
Connection ~ 10100 1600
Wire Wire Line
	10750 1500 10750 1700
Connection ~ 10750 1700
Connection ~ 10800 1750
Wire Wire Line
	10750 1700 10850 1700
Wire Wire Line
	9850 1500 9900 1500
Wire Wire Line
	9900 1500 9900 1800
Wire Wire Line
	9900 1700 9850 1700
Connection ~ 9900 1700
Wire Wire Line
	8550 1650 8550 1700
Wire Wire Line
	8500 1700 8750 1700
Wire Wire Line
	8500 1750 8500 1700
Connection ~ 8550 1700
Wire Wire Line
	8700 1700 8700 1750
Connection ~ 8700 1700
$Comp
L GND #PWR18
U 1 1 5670CC45
P 8500 2050
F 0 "#PWR18" H 8500 1800 50  0001 C CNN
F 1 "GND" H 8500 1900 50  0000 C CNN
F 2 "" H 8500 2050 50  0000 C CNN
F 3 "" H 8500 2050 50  0000 C CNN
	1    8500 2050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR19
U 1 1 5670CC7F
P 8700 2050
F 0 "#PWR19" H 8700 1800 50  0001 C CNN
F 1 "GND" H 8700 1900 50  0000 C CNN
F 2 "" H 8700 2050 50  0000 C CNN
F 3 "" H 8700 2050 50  0000 C CNN
	1    8700 2050
	1    0    0    -1  
$EndComp
Text Notes 9150 1950 0    60   ~ 0
RADIO
Text Label 7350 4050 0    60   ~ 0
I2C_SCK
Text Label 7350 3950 0    60   ~ 0
I2C_SDA
Text Label 8550 4550 0    60   ~ 0
LIGHT
Text Label 8550 4750 0    60   ~ 0
RFM_RESET
Text Label 8550 4650 0    60   ~ 0
RFM_NSS
Text Label 8550 5050 0    60   ~ 0
RFM_SCK
Text Label 8550 4950 0    60   ~ 0
RFM_MISO
Text Label 8550 4850 0    60   ~ 0
RFM_MOSI
$Comp
L LED D1
U 1 1 5670D4A5
P 3850 1200
F 0 "D1" H 3850 1300 50  0000 C CNN
F 1 "RED" H 3850 1100 50  0000 C CNN
F 2 "" H 3850 1200 50  0000 C CNN
F 3 "" H 3850 1200 50  0000 C CNN
	1    3850 1200
	0    -1   -1   0   
$EndComp
$Comp
L +3V3 #PWR1
U 1 1 5670D516
P 3850 1000
F 0 "#PWR1" H 3850 850 50  0001 C CNN
F 1 "+3V3" H 3850 1140 50  0000 C CNN
F 2 "" H 3850 1000 50  0000 C CNN
F 3 "" H 3850 1000 50  0000 C CNN
	1    3850 1000
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5670D552
P 3850 1550
F 0 "R1" V 3930 1550 50  0000 C CNN
F 1 "1k" V 3850 1550 50  0000 C CNN
F 2 "" V 3780 1550 50  0000 C CNN
F 3 "" H 3850 1550 50  0000 C CNN
	1    3850 1550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR15
U 1 1 5670D5A3
P 3850 1700
F 0 "#PWR15" H 3850 1450 50  0001 C CNN
F 1 "GND" H 3850 1550 50  0000 C CNN
F 2 "" H 3850 1700 50  0000 C CNN
F 3 "" H 3850 1700 50  0000 C CNN
	1    3850 1700
	1    0    0    -1  
$EndComp
Text Label 8550 4350 0    60   ~ 0
LED_YELLOW
Text Label 8550 4450 0    60   ~ 0
LED_GREEN
Text Label 1400 2850 2    60   ~ 0
LED_YELLOW
Text Label 1400 2950 2    60   ~ 0
LED_GREEN
$Comp
L LED D2
U 1 1 5670D937
P 1500 3200
F 0 "D2" H 1500 3300 50  0000 C CNN
F 1 "GREEN" H 1550 3100 50  0000 C CNN
F 2 "" H 1500 3200 50  0000 C CNN
F 3 "" H 1500 3200 50  0000 C CNN
	1    1500 3200
	0    -1   -1   0   
$EndComp
$Comp
L LED D3
U 1 1 5670D9B4
P 1800 3200
F 0 "D3" H 1800 3300 50  0000 C CNN
F 1 "YELLOW" H 1850 3100 50  0000 C CNN
F 2 "" H 1800 3200 50  0000 C CNN
F 3 "" H 1800 3200 50  0000 C CNN
	1    1800 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1400 2950 1500 2950
Wire Wire Line
	1500 2950 1500 3000
Wire Wire Line
	1400 2850 1800 2850
Wire Wire Line
	1800 2850 1800 3000
$Comp
L R R4
U 1 1 5670DB19
P 1500 3550
F 0 "R4" V 1580 3550 50  0000 C CNN
F 1 "1k" V 1500 3550 50  0000 C CNN
F 2 "" V 1430 3550 50  0000 C CNN
F 3 "" H 1500 3550 50  0000 C CNN
	1    1500 3550
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 5670DB64
P 1800 3550
F 0 "R5" V 1880 3550 50  0000 C CNN
F 1 "1k" V 1800 3550 50  0000 C CNN
F 2 "" V 1730 3550 50  0000 C CNN
F 3 "" H 1800 3550 50  0000 C CNN
	1    1800 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR22
U 1 1 5670DC6D
P 1500 3700
F 0 "#PWR22" H 1500 3450 50  0001 C CNN
F 1 "GND" H 1500 3550 50  0000 C CNN
F 2 "" H 1500 3700 50  0000 C CNN
F 3 "" H 1500 3700 50  0000 C CNN
	1    1500 3700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR23
U 1 1 5670DCB3
P 1800 3700
F 0 "#PWR23" H 1800 3450 50  0001 C CNN
F 1 "GND" H 1800 3550 50  0000 C CNN
F 2 "" H 1800 3700 50  0000 C CNN
F 3 "" H 1800 3700 50  0000 C CNN
	1    1800 3700
	1    0    0    -1  
$EndComp
Text Label 7150 4650 0    60   ~ 0
SWDIO
Text Label 7150 4550 0    60   ~ 0
SWCLK
$Comp
L SWD U7
U 1 1 5670E52D
P 1650 7100
F 0 "U7" V 1650 7100 60  0000 C CNN
F 1 "SWD" V 1550 7100 60  0000 C CNN
F 2 "footprints:SWD" H 1550 7400 60  0001 C CNN
F 3 "" H 1550 7400 60  0000 C CNN
	1    1650 7100
	1    0    0    -1  
$EndComp
Text Label 2250 6900 0    60   ~ 0
SWDIO
Text Label 2250 7000 0    60   ~ 0
SWCLK
Text Label 2250 7300 0    60   ~ 0
nRST
$Comp
L +3V3 #PWR40
U 1 1 5670E977
P 1050 6900
F 0 "#PWR40" H 1050 6750 50  0001 C CNN
F 1 "+3V3" H 1050 7040 50  0000 C CNN
F 2 "" H 1050 6900 50  0000 C CNN
F 3 "" H 1050 6900 50  0000 C CNN
	1    1050 6900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR41
U 1 1 5670E9BF
P 1000 7350
F 0 "#PWR41" H 1000 7100 50  0001 C CNN
F 1 "GND" H 1000 7200 50  0000 C CNN
F 2 "" H 1000 7350 50  0000 C CNN
F 3 "" H 1000 7350 50  0000 C CNN
	1    1000 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 7000 1000 7000
Wire Wire Line
	1000 7000 1000 7350
Wire Wire Line
	1050 7300 1000 7300
Connection ~ 1000 7300
Wire Wire Line
	1050 7100 1000 7100
Connection ~ 1000 7100
NoConn ~ 2250 7100
NoConn ~ 2250 7200
Text Notes 6100 5500 0    60   ~ 0
MICROCONTROLLER
$Comp
L STM32L052K8 U4
U 1 1 5675F5E5
P 6450 4450
F 0 "U4" V 6450 4350 60  0000 C CNN
F 1 "STM32L052K8" V 6350 4350 60  0000 C CNN
F 2 "footprints:UFQFPN32" H 6550 5250 60  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1886889.pdf" H 6550 5250 60  0001 C CNN
F 4 "2488335" H 6450 4450 60  0001 C CNN "Farnell"
	1    6450 4450
	1    0    0    -1  
$EndComp
Text Label 4700 4050 2    60   ~ 0
nRST
$Comp
L C C7
U 1 1 5675FAE1
P 4750 4550
F 0 "C7" H 4775 4650 50  0000 L CNN
F 1 "100n" H 4750 4450 50  0000 L CNN
F 2 "" H 4788 4400 50  0000 C CNN
F 3 "" H 4750 4550 50  0000 C CNN
	1    4750 4550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR29
U 1 1 5675FB40
P 4750 4700
F 0 "#PWR29" H 4750 4450 50  0001 C CNN
F 1 "GND" H 4750 4550 50  0000 C CNN
F 2 "" H 4750 4700 50  0000 C CNN
F 3 "" H 4750 4700 50  0000 C CNN
	1    4750 4700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR25
U 1 1 5675FC31
P 8400 3850
F 0 "#PWR25" H 8400 3600 50  0001 C CNN
F 1 "GND" H 8400 3700 50  0000 C CNN
F 2 "" H 8400 3850 50  0000 C CNN
F 3 "" H 8400 3850 50  0000 C CNN
	1    8400 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 3850 7150 3850
Text Label 7150 4750 0    60   ~ 0
USB_DP
Text Label 7150 4850 0    60   ~ 0
USB_DM
$Comp
L C C8
U 1 1 56760BD5
P 4950 4550
F 0 "C8" H 4975 4650 50  0000 L CNN
F 1 "100n" H 4950 4450 50  0000 L CNN
F 2 "" H 4988 4400 50  0000 C CNN
F 3 "" H 4950 4550 50  0000 C CNN
	1    4950 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 4700 4750 4700
$Comp
L GND #PWR30
U 1 1 56760E0A
P 4950 4700
F 0 "#PWR30" H 4950 4450 50  0001 C CNN
F 1 "GND" H 4950 4550 50  0000 C CNN
F 2 "" H 4950 4700 50  0000 C CNN
F 3 "" H 4950 4700 50  0000 C CNN
	1    4950 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 3750 5850 3750
Wire Wire Line
	4950 3750 4950 4400
$Comp
L +3V3 #PWR24
U 1 1 56760EFE
P 4950 3750
F 0 "#PWR24" H 4950 3600 50  0001 C CNN
F 1 "+3V3" H 4950 3890 50  0000 C CNN
F 2 "" H 4950 3750 50  0000 C CNN
F 3 "" H 4950 3750 50  0000 C CNN
	1    4950 3750
	1    0    0    -1  
$EndComp
Connection ~ 4950 3750
$Comp
L +3V3 #PWR35
U 1 1 5676102C
P 7650 5250
F 0 "#PWR35" H 7650 5100 50  0001 C CNN
F 1 "+3V3" H 7650 5390 50  0000 C CNN
F 2 "" H 7650 5250 50  0000 C CNN
F 3 "" H 7650 5250 50  0000 C CNN
	1    7650 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 5250 7650 5250
$Comp
L C C12
U 1 1 567610E6
P 7300 5400
F 0 "C12" H 7325 5500 50  0000 L CNN
F 1 "100n" H 7325 5300 50  0000 L CNN
F 2 "" H 7338 5250 50  0000 C CNN
F 3 "" H 7300 5400 50  0000 C CNN
	1    7300 5400
	1    0    0    -1  
$EndComp
$Comp
L C C13
U 1 1 56761145
P 7550 5400
F 0 "C13" H 7575 5500 50  0000 L CNN
F 1 "10u" H 7575 5300 50  0000 L CNN
F 2 "" H 7588 5250 50  0000 C CNN
F 3 "" H 7550 5400 50  0000 C CNN
	1    7550 5400
	1    0    0    -1  
$EndComp
Connection ~ 7550 5250
Connection ~ 7300 5250
$Comp
L GND #PWR36
U 1 1 5676123E
P 7300 5550
F 0 "#PWR36" H 7300 5300 50  0001 C CNN
F 1 "GND" H 7300 5400 50  0000 C CNN
F 2 "" H 7300 5550 50  0000 C CNN
F 3 "" H 7300 5550 50  0000 C CNN
	1    7300 5550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR37
U 1 1 5676128E
P 7550 5550
F 0 "#PWR37" H 7550 5300 50  0001 C CNN
F 1 "GND" H 7550 5400 50  0000 C CNN
F 2 "" H 7550 5550 50  0000 C CNN
F 3 "" H 7550 5550 50  0000 C CNN
	1    7550 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 4050 5850 4050
Wire Wire Line
	4750 4050 4750 4400
Connection ~ 4750 4050
$Comp
L C C9
U 1 1 567618D3
P 5150 4550
F 0 "C9" H 5175 4650 50  0000 L CNN
F 1 "1u" H 5175 4450 50  0000 L CNN
F 2 "" H 5188 4400 50  0000 C CNN
F 3 "" H 5150 4550 50  0000 C CNN
	1    5150 4550
	1    0    0    -1  
$EndComp
$Comp
L C C10
U 1 1 56761B02
P 5350 4550
F 0 "C10" H 5375 4650 50  0000 L CNN
F 1 "100n" H 5375 4450 50  0000 L CNN
F 2 "" H 5388 4400 50  0000 C CNN
F 3 "" H 5350 4550 50  0000 C CNN
	1    5350 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 4400 5350 4150
Wire Wire Line
	5150 4150 5850 4150
Wire Wire Line
	5150 4400 5150 4150
Connection ~ 5350 4150
$Comp
L GND #PWR31
U 1 1 56761CAD
P 5150 4700
F 0 "#PWR31" H 5150 4450 50  0001 C CNN
F 1 "GND" H 5150 4550 50  0000 C CNN
F 2 "" H 5150 4700 50  0000 C CNN
F 3 "" H 5150 4700 50  0000 C CNN
	1    5150 4700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR32
U 1 1 56761D01
P 5350 4700
F 0 "#PWR32" H 5350 4450 50  0001 C CNN
F 1 "GND" H 5350 4550 50  0000 C CNN
F 2 "" H 5350 4700 50  0000 C CNN
F 3 "" H 5350 4700 50  0000 C CNN
	1    5350 4700
	1    0    0    -1  
$EndComp
$Comp
L Crystal_Small Y1
U 1 1 56762471
P 4000 3850
F 0 "Y1" H 4000 3950 50  0000 C CNN
F 1 "32.768k" H 4200 3900 50  0000 C CNN
F 2 "" H 4000 3850 50  0000 C CNN
F 3 "http://www.farnell.com/datasheets/1883680.pdf" H 4000 3850 50  0001 C CNN
F 4 "2101347" H 4000 3850 60  0001 C CNN "Farnell"
	1    4000 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 3850 5850 3850
Wire Wire Line
	3900 3850 3900 4000
$Comp
L C C5
U 1 1 56762810
P 3900 4150
F 0 "C5" H 3925 4250 50  0000 L CNN
F 1 "C" H 3925 4050 50  0000 L CNN
F 2 "" H 3938 4000 50  0000 C CNN
F 3 "" H 3900 4150 50  0000 C CNN
	1    3900 4150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR26
U 1 1 56762871
P 3900 4300
F 0 "#PWR26" H 3900 4050 50  0001 C CNN
F 1 "GND" H 3900 4150 50  0000 C CNN
F 2 "" H 3900 4300 50  0000 C CNN
F 3 "" H 3900 4300 50  0000 C CNN
	1    3900 4300
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 567628C9
P 4150 4150
F 0 "C6" H 4175 4250 50  0000 L CNN
F 1 "C" H 4175 4050 50  0000 L CNN
F 2 "" H 4188 4000 50  0000 C CNN
F 3 "" H 4150 4150 50  0000 C CNN
	1    4150 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 3950 5850 3950
Connection ~ 3900 3950
Wire Wire Line
	4150 4000 4150 3850
Connection ~ 4150 3850
$Comp
L GND #PWR27
U 1 1 56762B31
P 4150 4300
F 0 "#PWR27" H 4150 4050 50  0001 C CNN
F 1 "GND" H 4150 4150 50  0000 C CNN
F 2 "" H 4150 4300 50  0000 C CNN
F 3 "" H 4150 4300 50  0000 C CNN
	1    4150 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 3950 7350 3950
Wire Wire Line
	7150 4050 7350 4050
Wire Wire Line
	7200 4050 7200 3600
Connection ~ 7200 4050
Wire Wire Line
	7300 3950 7300 3600
Connection ~ 7300 3950
Wire Wire Line
	7250 3250 7250 3300
Wire Wire Line
	7200 3300 7300 3300
Connection ~ 7250 3300
Connection ~ 950  5200
Wire Wire Line
	950  4900 1150 4900
Wire Wire Line
	1150 4900 1150 5000
Wire Wire Line
	1150 5000 1200 5000
$Comp
L microusb-b U2
U 1 1 56764139
P 4600 1300
F 0 "U2" H 4550 950 60  0000 C CNN
F 1 "microusb-b" H 4550 850 60  0001 C CNN
F 2 "footprints:USB3065" H 4700 1300 60  0001 C CNN
F 3 "" H 4700 1300 60  0000 C CNN
	1    4600 1300
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR3
U 1 1 567642B8
P 5150 1100
F 0 "#PWR3" H 5150 950 50  0001 C CNN
F 1 "+5V" H 5150 1240 50  0000 C CNN
F 2 "" H 5150 1100 50  0000 C CNN
F 3 "" H 5150 1100 50  0000 C CNN
	1    5150 1100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR8
U 1 1 56764314
P 4900 1500
F 0 "#PWR8" H 4900 1250 50  0001 C CNN
F 1 "GND" H 4900 1350 50  0000 C CNN
F 2 "" H 4900 1500 50  0000 C CNN
F 3 "" H 4900 1500 50  0000 C CNN
	1    4900 1500
	1    0    0    -1  
$EndComp
NoConn ~ 4900 1400
Text Label 4900 1200 0    60   ~ 0
USB_DM
Text Label 4900 1300 0    60   ~ 0
USB_DP
Text Notes 4550 1850 0    60   ~ 0
MICROUSB
$Comp
L TPS79333DBVR U8
U 1 1 56785040
P 6100 1050
F 0 "U8" H 6150 900 60  0000 C CNN
F 1 "TPS79333DBVR" H 6250 1000 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-5" H 6100 1050 60  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1972784.pdf" H 6100 1050 60  0001 C CNN
F 4 "1470478" H 6100 1050 60  0001 C CNN "Farnell"
	1    6100 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 1100 5400 1100
Wire Wire Line
	5400 1100 5400 1200
Wire Wire Line
	5400 1200 5700 1200
Connection ~ 5650 1200
Wire Wire Line
	5650 1200 5650 1300
Wire Wire Line
	5650 1300 5700 1300
$Comp
L C C15
U 1 1 5678522C
P 5400 1350
F 0 "C15" H 5425 1450 50  0000 L CNN
F 1 "100n" H 5425 1250 50  0000 L CNN
F 2 "" H 5438 1200 50  0000 C CNN
F 3 "" H 5400 1350 50  0000 C CNN
	1    5400 1350
	1    0    0    -1  
$EndComp
Connection ~ 5400 1200
$Comp
L GND #PWR9
U 1 1 567852EE
P 5400 1500
F 0 "#PWR9" H 5400 1250 50  0001 C CNN
F 1 "GND" H 5400 1350 50  0000 C CNN
F 2 "" H 5400 1500 50  0000 C CNN
F 3 "" H 5400 1500 50  0000 C CNN
	1    5400 1500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR10
U 1 1 5678534E
P 5700 1500
F 0 "#PWR10" H 5700 1250 50  0001 C CNN
F 1 "GND" H 5700 1350 50  0000 C CNN
F 2 "" H 5700 1500 50  0000 C CNN
F 3 "" H 5700 1500 50  0000 C CNN
	1    5700 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 1500 5700 1400
$Comp
L C C16
U 1 1 567855AA
P 6800 1450
F 0 "C16" H 6825 1550 50  0000 L CNN
F 1 "10n" H 6825 1350 50  0000 L CNN
F 2 "" H 6838 1300 50  0000 C CNN
F 3 "" H 6800 1450 50  0000 C CNN
	1    6800 1450
	1    0    0    -1  
$EndComp
$Comp
L C C17
U 1 1 5678577A
P 7100 1450
F 0 "C17" H 7125 1550 50  0000 L CNN
F 1 "C" H 7125 1350 50  0000 L CNN
F 2 "" H 7138 1300 50  0000 C CNN
F 3 "" H 7100 1450 50  0000 C CNN
	1    7100 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 1200 7100 1200
Wire Wire Line
	7100 1200 7100 1300
$Comp
L +3V3 #PWR4
U 1 1 56785888
P 7100 1200
F 0 "#PWR4" H 7100 1050 50  0001 C CNN
F 1 "+3V3" H 7100 1340 50  0000 C CNN
F 2 "" H 7100 1200 50  0000 C CNN
F 3 "" H 7100 1200 50  0000 C CNN
	1    7100 1200
	1    0    0    -1  
$EndComp
Connection ~ 7100 1200
$Comp
L GND #PWR13
U 1 1 567858EE
P 7100 1600
F 0 "#PWR13" H 7100 1350 50  0001 C CNN
F 1 "GND" H 7100 1450 50  0000 C CNN
F 2 "" H 7100 1600 50  0000 C CNN
F 3 "" H 7100 1600 50  0000 C CNN
	1    7100 1600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR12
U 1 1 56785952
P 6800 1600
F 0 "#PWR12" H 6800 1350 50  0001 C CNN
F 1 "GND" H 6800 1450 50  0000 C CNN
F 2 "" H 6800 1600 50  0000 C CNN
F 3 "" H 6800 1600 50  0000 C CNN
	1    6800 1600
	1    0    0    -1  
$EndComp
Text Notes 6700 1700 2    60   ~ 0
10nF cap optional\nfor noise reduction
Connection ~ 5150 1100
Connection ~ 10650 1600
$Comp
L TVS_small D?
U 1 1 56786E75
P 950 1200
F 0 "D?" V 800 1200 50  0000 C CNN
F 1 "TVS_small" H 950 1125 50  0001 C CNN
F 2 "Resistors_SMD:R_0603" H 950 1200 60  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1772768.pdf" H 950 1200 60  0001 C CNN
F 4 "2368174" H 950 1200 60  0001 C CNN "Farnell"
	1    950  1200
	0    1    1    0   
$EndComp
Wire Wire Line
	850  1150 850  1100
Wire Wire Line
	850  1250 850  1300
Wire Wire Line
	850  1300 1150 1300
Connection ~ 950  1100
Connection ~ 950  1300
Wire Wire Line
	1150 1300 1150 1500
$Comp
L TVS_small D?
U 1 1 56787864
P 10650 1700
F 0 "D?" H 10650 1775 50  0000 C CNN
F 1 "TVS_small" H 10650 1625 50  0001 C CNN
F 2 "Resistors_SMD:R_0603" H 10650 1700 60  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1772768.pdf" H 10650 1700 60  0001 C CNN
F 4 "2368174" H 10650 1700 60  0001 C CNN "Farnell"
	1    10650 1700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10650 1800 10800 1800
Connection ~ 10800 1800
$EndSCHEMATC
