EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title "Electris Arcade Controller"
Date ""
Rev "A"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:R_US R?
U 1 1 6088391D
P 4000 2350
F 0 "R?" V 3950 2200 50  0000 C CNN
F 1 "68" V 3950 2500 50  0000 C CNN
F 2 "" V 4040 2340 50  0001 C CNN
F 3 "~" H 4000 2350 50  0001 C CNN
	1    4000 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	3850 2350 3800 2350
$Comp
L Device:R_US R?
U 1 1 60886309
P 4000 4250
F 0 "R?" V 3950 4100 50  0000 C CNN
F 1 "68" V 3950 4400 50  0000 C CNN
F 2 "" V 4040 4240 50  0001 C CNN
F 3 "~" H 4000 4250 50  0001 C CNN
	1    4000 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	3850 4250 3800 4250
Text HLabel 4200 3950 2    50   Input ~ 0
UART_RX
Text HLabel 4200 4050 2    50   Output ~ 0
UART_TX
Wire Wire Line
	4200 3950 3800 3950
Wire Wire Line
	3800 4050 4200 4050
$Comp
L Device:Crystal Y?
U 1 1 6088B93C
P 4100 3000
F 0 "Y?" V 4000 3050 50  0000 L CNN
F 1 "16MHz" V 4200 3050 50  0000 L CNN
F 2 "" H 4100 3000 50  0001 C CNN
F 3 "~" H 4100 3000 50  0001 C CNN
	1    4100 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	4100 3150 3900 3150
Wire Wire Line
	3900 2950 3800 2950
Wire Wire Line
	4100 3150 4300 3150
Connection ~ 4100 3150
$Comp
L Device:C C?
U 1 1 6088E6F7
P 4450 3150
F 0 "C?" V 4300 3150 50  0000 C CNN
F 1 "C" V 4400 3250 50  0000 C CNN
F 2 "" H 4488 3000 50  0001 C CNN
F 3 "~" H 4450 3150 50  0001 C CNN
	1    4450 3150
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 6088F621
P 4450 2850
F 0 "C?" V 4300 2850 50  0000 C CNN
F 1 "C" V 4400 2950 50  0000 C CNN
F 2 "" H 4488 2700 50  0001 C CNN
F 3 "~" H 4450 2850 50  0001 C CNN
	1    4450 2850
	0    1    1    0   
$EndComp
Wire Wire Line
	4300 2850 4100 2850
Connection ~ 4100 2850
$Comp
L power:GND #PWR0111
U 1 1 6089033B
P 4650 3200
F 0 "#PWR0111" H 4650 2950 50  0001 C CNN
F 1 "GND" H 4655 3027 50  0000 C CNN
F 2 "" H 4650 3200 50  0001 C CNN
F 3 "" H 4650 3200 50  0001 C CNN
	1    4650 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 3200 4650 3150
Wire Wire Line
	4650 2850 4600 2850
Wire Wire Line
	4600 3150 4650 3150
Connection ~ 4650 3150
Wire Wire Line
	4650 3150 4650 2850
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J?
U 1 1 608934EF
P 8100 2500
F 0 "J?" H 8150 2817 50  0000 C CNN
F 1 "GFX_ICSP" H 8150 2726 50  0000 C CNN
F 2 "" H 8100 2500 50  0001 C CNN
F 3 "~" H 8100 2500 50  0001 C CNN
	1    8100 2500
	1    0    0    -1  
$EndComp
Text Label 7500 2400 0    50   ~ 0
ICSP_MISO
Wire Wire Line
	7500 2400 7900 2400
Text Label 7500 2500 0    50   ~ 0
ICSP_SCK
Wire Wire Line
	7500 2500 7900 2500
Text Label 8850 2500 2    50   ~ 0
ICSP_MOSI
Wire Wire Line
	8850 2500 8400 2500
$Comp
L power:+5V #PWR0112
U 1 1 60895B36
P 8450 2350
F 0 "#PWR0112" H 8450 2200 50  0001 C CNN
F 1 "+5V" H 8465 2523 50  0000 C CNN
F 2 "" H 8450 2350 50  0001 C CNN
F 3 "" H 8450 2350 50  0001 C CNN
	1    8450 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 2350 8450 2400
Wire Wire Line
	8450 2400 8400 2400
$Comp
L power:GND #PWR0113
U 1 1 6089760C
P 8450 2650
F 0 "#PWR0113" H 8450 2400 50  0001 C CNN
F 1 "GND" H 8455 2477 50  0000 C CNN
F 2 "" H 8450 2650 50  0001 C CNN
F 3 "" H 8450 2650 50  0001 C CNN
	1    8450 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 2650 8450 2600
Wire Wire Line
	8450 2600 8400 2600
Text Label 7500 2600 0    50   ~ 0
nRST
$Comp
L Device:R_US R?
U 1 1 608997A5
P 7200 2400
F 0 "R?" H 7268 2446 50  0000 L CNN
F 1 "10K" H 7268 2355 50  0000 L CNN
F 2 "" V 7240 2390 50  0001 C CNN
F 3 "~" H 7200 2400 50  0001 C CNN
	1    7200 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 2550 7200 2600
Wire Wire Line
	7200 2600 7900 2600
Wire Wire Line
	7200 2250 7200 2200
$Comp
L power:+5V #PWR0114
U 1 1 6089AFFC
P 7200 2200
F 0 "#PWR0114" H 7200 2050 50  0001 C CNN
F 1 "+5V" H 7215 2373 50  0000 C CNN
F 2 "" H 7200 2200 50  0001 C CNN
F 3 "" H 7200 2200 50  0001 C CNN
	1    7200 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 6089BA8B
P 6850 2650
F 0 "#PWR0115" H 6850 2400 50  0001 C CNN
F 1 "GND" H 6855 2477 50  0000 C CNN
F 2 "" H 6850 2650 50  0001 C CNN
F 3 "" H 6850 2650 50  0001 C CNN
	1    6850 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:Jumper_NC_Small JP?
U 1 1 6089C94A
P 7000 2600
F 0 "JP?" H 7000 2812 50  0000 C CNN
F 1 "GFX_RST" H 7000 2721 50  0000 C CNN
F 2 "" H 7000 2600 50  0001 C CNN
F 3 "~" H 7000 2600 50  0001 C CNN
	1    7000 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 2600 7200 2600
Connection ~ 7200 2600
Wire Wire Line
	6850 2650 6850 2600
Wire Wire Line
	6850 2600 6900 2600
Text Label 4200 2550 2    50   ~ 0
ICSP_MOSI
Wire Wire Line
	4200 2550 3800 2550
Text Label 4200 2650 2    50   ~ 0
ICSP_MISO
Wire Wire Line
	3800 2650 4200 2650
Wire Wire Line
	3800 2850 4100 2850
Wire Wire Line
	3900 2950 3900 3150
Text Label 4200 2750 2    50   ~ 0
ICSP_SCK
Wire Wire Line
	4200 2750 3800 2750
Text Label 4200 3750 2    50   ~ 0
nRST
Wire Wire Line
	4200 3750 3800 3750
$Comp
L Device:C C?
U 1 1 608A5854
P 2200 2450
F 0 "C?" H 2315 2496 50  0000 L CNN
F 1 "0.1uF" H 2315 2405 50  0000 L CNN
F 2 "" H 2238 2300 50  0001 C CNN
F 3 "~" H 2200 2450 50  0001 C CNN
	1    2200 2450
	1    0    0    -1  
$EndComp
$Comp
L MCU_Microchip_ATmega:ATmega328P-MU U?
U 1 1 608A7EE6
P 3200 3450
F 0 "U?" H 3200 1861 50  0000 C CNN
F 1 "ATmega328P-MU" H 3200 1770 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-32-1EP_5x5mm_P0.5mm_EP3.1x3.1mm" H 3200 3450 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 3200 3450 50  0001 C CNN
	1    3200 3450
	1    0    0    -1  
$EndComp
NoConn ~ 2600 2450
NoConn ~ 2600 2550
Wire Wire Line
	2200 2300 2200 2250
Wire Wire Line
	2200 2250 2600 2250
Wire Wire Line
	2200 2600 2200 2650
$Comp
L power:GND #PWR0116
U 1 1 608AD8CE
P 2200 2650
F 0 "#PWR0116" H 2200 2400 50  0001 C CNN
F 1 "GND" H 2205 2477 50  0000 C CNN
F 2 "" H 2200 2650 50  0001 C CNN
F 3 "" H 2200 2650 50  0001 C CNN
	1    2200 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 608B20EE
P 1650 2450
F 0 "C?" H 1765 2496 50  0000 L CNN
F 1 "0.1uF" H 1765 2405 50  0000 L CNN
F 2 "" H 1688 2300 50  0001 C CNN
F 3 "~" H 1650 2450 50  0001 C CNN
	1    1650 2450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0117
U 1 1 608B26D5
P 3200 1850
F 0 "#PWR0117" H 3200 1700 50  0001 C CNN
F 1 "+5V" H 3215 2023 50  0000 C CNN
F 2 "" H 3200 1850 50  0001 C CNN
F 3 "" H 3200 1850 50  0001 C CNN
	1    3200 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 1850 3200 1900
Wire Wire Line
	3200 1900 3300 1900
Wire Wire Line
	3300 1900 3300 1950
Connection ~ 3200 1900
Wire Wire Line
	3200 1900 3200 1950
$Comp
L power:+5V #PWR0118
U 1 1 608B4744
P 1650 2250
F 0 "#PWR0118" H 1650 2100 50  0001 C CNN
F 1 "+5V" H 1665 2423 50  0000 C CNN
F 2 "" H 1650 2250 50  0001 C CNN
F 3 "" H 1650 2250 50  0001 C CNN
	1    1650 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 608B5003
P 1650 2650
F 0 "#PWR0119" H 1650 2400 50  0001 C CNN
F 1 "GND" H 1655 2477 50  0000 C CNN
F 2 "" H 1650 2650 50  0001 C CNN
F 3 "" H 1650 2650 50  0001 C CNN
	1    1650 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 2600 1650 2650
Wire Wire Line
	1650 2250 1650 2300
$Comp
L Device:R_US R?
U 1 1 608F8676
P 4000 4550
F 0 "R?" V 3950 4400 50  0000 C CNN
F 1 "470" V 3950 4700 50  0000 C CNN
F 2 "" V 4040 4540 50  0001 C CNN
F 3 "~" H 4000 4550 50  0001 C CNN
	1    4000 4550
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 608F9040
P 4000 4650
F 0 "R?" V 3950 4500 50  0000 C CNN
F 1 "470" V 3950 4800 50  0000 C CNN
F 2 "" V 4040 4640 50  0001 C CNN
F 3 "~" H 4000 4650 50  0001 C CNN
	1    4000 4650
	0    1    1    0   
$EndComp
Wire Wire Line
	3850 4550 3800 4550
Wire Wire Line
	3800 4650 3850 4650
Wire Wire Line
	4150 4650 4300 4650
$Comp
L Device:Jumper_NC_Small JP?
U 1 1 6090742F
P 4550 4550
F 0 "JP?" H 4700 4600 50  0000 C CNN
F 1 "6R" H 4450 4600 50  0000 C CNN
F 2 "" H 4550 4550 50  0001 C CNN
F 3 "~" H 4550 4550 50  0001 C CNN
	1    4550 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:Jumper_NC_Small JP?
U 1 1 60908714
P 4550 4700
F 0 "JP?" H 4700 4750 50  0000 C CNN
F 1 "6G" H 4450 4750 50  0000 C CNN
F 2 "" H 4550 4700 50  0001 C CNN
F 3 "~" H 4550 4700 50  0001 C CNN
	1    4550 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:Jumper_NC_Small JP?
U 1 1 609089FA
P 4550 5300
F 0 "JP?" H 4700 5350 50  0000 C CNN
F 1 "7B" H 4450 5350 50  0000 C CNN
F 2 "" H 4550 5300 50  0001 C CNN
F 3 "~" H 4550 5300 50  0001 C CNN
	1    4550 5300
	1    0    0    -1  
$EndComp
$Comp
L Device:Jumper_NO_Small JP?
U 1 1 6090B66D
P 4550 5150
F 0 "JP?" H 4700 5200 50  0000 C CNN
F 1 "7G" H 4450 5200 50  0000 C CNN
F 2 "" H 4550 5150 50  0001 C CNN
F 3 "~" H 4550 5150 50  0001 C CNN
	1    4550 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:Jumper_NO_Small JP?
U 1 1 6090C05A
P 4550 5000
F 0 "JP?" H 4700 5050 50  0000 C CNN
F 1 "7R" H 4450 5050 50  0000 C CNN
F 2 "" H 4550 5000 50  0001 C CNN
F 3 "~" H 4550 5000 50  0001 C CNN
	1    4550 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:Jumper_NO_Small JP?
U 1 1 6090C320
P 4550 4850
F 0 "JP?" H 4700 4900 50  0000 C CNN
F 1 "6B" H 4450 4900 50  0000 C CNN
F 2 "" H 4550 4850 50  0001 C CNN
F 3 "~" H 4550 4850 50  0001 C CNN
	1    4550 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 4850 4650 4850
Wire Wire Line
	5050 4700 4650 4700
Wire Wire Line
	5050 4550 4650 4550
Wire Wire Line
	4150 4550 4350 4550
Wire Wire Line
	4450 4700 4350 4700
Wire Wire Line
	4350 4700 4350 4550
Connection ~ 4350 4550
Wire Wire Line
	4350 4550 4450 4550
Wire Wire Line
	4450 4850 4350 4850
Wire Wire Line
	4350 4850 4350 4700
Connection ~ 4350 4700
Wire Wire Line
	4300 4650 4300 5000
Wire Wire Line
	4300 5000 4450 5000
Wire Wire Line
	4450 5150 4300 5150
Wire Wire Line
	4300 5150 4300 5000
Connection ~ 4300 5000
Wire Wire Line
	4450 5300 4300 5300
Wire Wire Line
	4300 5300 4300 5150
Connection ~ 4300 5150
$Comp
L Connector:DB15_Female J?
U 1 1 60937AE0
P 8100 4250
AR Path="/60937AE0" Ref="J?"  Part="1" 
AR Path="/6087F3EE/60937AE0" Ref="J?"  Part="1" 
F 0 "J?" H 8254 4296 50  0000 L CNN
F 1 "VGA" H 8254 4205 50  0000 L CNN
F 2 "" H 8100 4250 50  0001 C CNN
F 3 " ~" H 8100 4250 50  0001 C CNN
	1    8100 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 3550 7800 3550
Wire Wire Line
	7400 3750 7800 3750
Wire Wire Line
	7400 3950 7800 3950
NoConn ~ 7800 4150
$Comp
L power:GND #PWR?
U 1 1 60937AEA
P 7350 5050
AR Path="/60937AEA" Ref="#PWR?"  Part="1" 
AR Path="/6087F3EE/60937AEA" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7350 4800 50  0001 C CNN
F 1 "GND" H 7355 4877 50  0000 C CNN
F 2 "" H 7350 5050 50  0001 C CNN
F 3 "" H 7350 5050 50  0001 C CNN
	1    7350 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 4350 7800 4350
Wire Wire Line
	7800 4550 7350 4550
Connection ~ 7350 4550
Wire Wire Line
	7350 4550 7350 4350
Wire Wire Line
	7800 4750 7350 4750
Wire Wire Line
	7350 4550 7350 4750
Connection ~ 7350 4750
Wire Wire Line
	7800 4950 7350 4950
Wire Wire Line
	7350 4750 7350 4950
Connection ~ 7350 4950
Wire Wire Line
	7350 4950 7350 5050
NoConn ~ 7800 3650
Wire Wire Line
	7800 3850 7350 3850
Wire Wire Line
	7350 3850 7350 4350
Connection ~ 7350 4350
NoConn ~ 7800 4050
NoConn ~ 7800 4250
Text Label 7400 4450 0    50   ~ 0
VGA_HSYNC
Wire Wire Line
	7400 4450 7800 4450
Text Label 7400 4650 0    50   ~ 0
VGA_VSYNC
Wire Wire Line
	7400 4650 7800 4650
NoConn ~ 7800 4850
Text Label 7400 3550 0    50   ~ 0
VGA_R
Text Label 7400 3750 0    50   ~ 0
VGA_G
Text Label 7400 3950 0    50   ~ 0
VGA_B
Text Label 5050 4550 2    50   ~ 0
VGA_R
Text Label 5050 4700 2    50   ~ 0
VGA_G
Text Label 5050 4850 2    50   ~ 0
VGA_B
Wire Wire Line
	5050 5300 4650 5300
Wire Wire Line
	5050 5150 4650 5150
Wire Wire Line
	5050 5000 4650 5000
Text Label 5050 5000 2    50   ~ 0
VGA_R
Text Label 5050 5150 2    50   ~ 0
VGA_G
Text Label 5050 5300 2    50   ~ 0
VGA_B
Text Label 4650 2350 2    50   ~ 0
VGA_VSYNC
Wire Wire Line
	4150 2350 4650 2350
Text Label 4650 4250 2    50   ~ 0
VGA_HSYNC
Wire Wire Line
	4150 4250 4650 4250
$Comp
L Device:Speaker LS?
U 1 1 608FCAF1
P 3850 6350
F 0 "LS?" H 4020 6346 50  0000 L CNN
F 1 "Speaker" H 4020 6255 50  0000 L CNN
F 2 "" H 3850 6150 50  0001 C CNN
F 3 "~" H 3840 6300 50  0001 C CNN
	1    3850 6350
	1    0    0    -1  
$EndComp
$EndSCHEMATC
