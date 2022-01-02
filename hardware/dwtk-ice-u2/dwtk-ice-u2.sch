EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "dwtk-ice u2"
Date "2021-12-14"
Rev "1.0"
Comp "dwtk.rgm.io"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "Designed by: Rafael G. Martins"
$EndDescr
Text GLabel 3250 2150 0    50   BiDi ~ 0
dw
$Comp
L Device:C C3
U 1 1 613A8FA4
P 2500 2250
F 0 "C3" V 2248 2250 50  0000 C CNN
F 1 "22p" V 2339 2250 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 2538 2100 50  0001 C CNN
F 3 "~" H 2500 2250 50  0001 C CNN
F 4 "594-K220J15C0GF53L2" H 2500 2250 50  0001 C CNN "Mouser Ref."
F 5 "KERKO 22P" H 2500 2250 50  0001 C CNN "Reichelt Ref."
	1    2500 2250
	0    1    1    0   
$EndComp
$Comp
L Device:C C4
U 1 1 613A9B72
P 2500 2650
F 0 "C4" V 2660 2650 50  0000 C CNN
F 1 "22p" V 2751 2650 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 2538 2500 50  0001 C CNN
F 3 "~" H 2500 2650 50  0001 C CNN
F 4 "594-K220J15C0GF53L2" H 2500 2650 50  0001 C CNN "Mouser Ref."
F 5 "KERKO 22P" H 2500 2650 50  0001 C CNN "Reichelt Ref."
	1    2500 2650
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 613AA538
P 2250 2750
F 0 "#PWR0109" H 2250 2500 50  0001 C CNN
F 1 "GND" H 2255 2577 50  0000 C CNN
F 2 "" H 2250 2750 50  0001 C CNN
F 3 "" H 2250 2750 50  0001 C CNN
	1    2250 2750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 613E3A6A
P 3450 4750
F 0 "#PWR0110" H 3450 4500 50  0001 C CNN
F 1 "GND" H 3455 4577 50  0000 C CNN
F 2 "" H 3450 4750 50  0001 C CNN
F 3 "" H 3450 4750 50  0001 C CNN
	1    3450 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 6145FF1C
P 6350 5000
F 0 "R1" V 6143 5000 50  0000 C CNN
F 1 "22R" V 6234 5000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6280 5000 50  0001 C CNN
F 3 "~" H 6350 5000 50  0001 C CNN
F 4 "603-MFR-25FTF52-22R" H 6350 5000 50  0001 C CNN "Mouser Ref."
F 5 "METALL 22,0" H 6350 5000 50  0001 C CNN "Reichelt Ref."
	1    6350 5000
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 61460FA0
P 6350 5100
F 0 "R2" V 6465 5100 50  0000 C CNN
F 1 "22R" V 6556 5100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6280 5100 50  0001 C CNN
F 3 "~" H 6350 5100 50  0001 C CNN
F 4 "603-MFR-25FTF52-22R" H 6350 5100 50  0001 C CNN "Mouser Ref."
F 5 "METALL 22,0" H 6350 5100 50  0001 C CNN "Reichelt Ref."
	1    6350 5100
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 61353B09
P 2400 4500
F 0 "J2" H 2292 4685 50  0000 C CNN
F 1 "JST XH2P Female" H 2292 4594 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B2B-XH-A_1x02_P2.50mm_Vertical" H 2400 4500 50  0001 C CNN
F 3 "~" H 2400 4500 50  0001 C CNN
F 4 "N/A" H 2400 4500 50  0001 C CNN "Mouser Ref."
F 5 "JST XH2P ST" H 2400 4500 50  0001 C CNN "Reichelt Ref."
	1    2400 4500
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 613638B2
P 2650 4650
F 0 "#PWR0108" H 2650 4400 50  0001 C CNN
F 1 "GND" H 2655 4477 50  0000 C CNN
F 2 "" H 2650 4650 50  0001 C CNN
F 3 "" H 2650 4650 50  0001 C CNN
	1    2650 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal Y1
U 1 1 613A7694
P 2800 2450
F 0 "Y1" V 2754 2319 50  0000 R CNN
F 1 "16mhz" V 2845 2319 50  0000 R CNN
F 2 "Crystal:Crystal_HC49-U_Vertical" H 2800 2450 50  0001 C CNN
F 3 "~" H 2800 2450 50  0001 C CNN
F 4 "815-ABL-16-B4Y" H 2800 2450 50  0001 C CNN "Mouser Ref."
F 5 "16,0000-HC49U-S" H 2800 2450 50  0001 C CNN "Reichelt Ref."
	1    2800 2450
	0    1    1    0   
$EndComp
Wire Wire Line
	2800 2300 2800 2250
Wire Wire Line
	2800 2600 2800 2650
Wire Wire Line
	2650 2650 2800 2650
Wire Wire Line
	3250 2150 3300 2150
Wire Wire Line
	2250 2750 2250 2650
Wire Wire Line
	2250 2250 2350 2250
Wire Wire Line
	2350 2650 2250 2650
Connection ~ 2250 2650
Wire Wire Line
	2250 2650 2250 2250
Wire Wire Line
	6500 5000 6550 5000
Wire Wire Line
	6500 5100 6550 5100
Text GLabel 2700 4600 2    50   BiDi ~ 0
dw
Wire Wire Line
	2650 2250 2800 2250
Wire Wire Line
	3300 2350 3000 2350
Wire Wire Line
	3000 2350 3000 2250
Wire Wire Line
	3000 2250 2800 2250
Connection ~ 2800 2250
Wire Wire Line
	3300 2550 3000 2550
Wire Wire Line
	3000 2550 3000 2650
Wire Wire Line
	3000 2650 2800 2650
Connection ~ 2800 2650
$Comp
L Device:CP C5
U 1 1 61759049
P 3150 3250
F 0 "C5" H 3268 3296 50  0000 L CNN
F 1 "1u" H 3268 3205 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 3188 3100 50  0001 C CNN
F 3 "~" H 3150 3250 50  0001 C CNN
F 4 "667-ECA-2VM010B" H 3150 3250 50  0001 C CNN "Mouser Ref."
F 5 "RAD 1/63" H 3150 3250 50  0001 C CNN "Reichelt Ref."
	1    3150 3250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 6175F902
P 3150 3450
F 0 "#PWR0102" H 3150 3200 50  0001 C CNN
F 1 "GND" H 3155 3277 50  0000 C CNN
F 2 "" H 3150 3450 50  0001 C CNN
F 3 "" H 3150 3450 50  0001 C CNN
	1    3150 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 3400 3150 3450
Text GLabel 3250 2750 0    50   BiDi ~ 0
USB_D+
Text GLabel 3250 2850 0    50   BiDi ~ 0
USB_D-
Wire Wire Line
	3250 2750 3300 2750
Wire Wire Line
	3250 2850 3300 2850
$Comp
L Device:LED D1
U 1 1 61C74867
P 5650 3800
F 0 "D1" V 5689 3682 50  0000 R CNN
F 1 "Red" V 5598 3682 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 5650 3800 50  0001 C CNN
F 3 "~" H 5650 3800 50  0001 C CNN
F 4 "604-WP710A10SEC/J3" H 5650 3800 50  0001 C CNN "Mouser Ref."
F 5 "RND 135-00155" H 5650 3800 50  0001 C CNN "Reichelt Ref."
	1    5650 3800
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D2
U 1 1 61C75707
P 6100 3800
F 0 "D2" V 6139 3682 50  0000 R CNN
F 1 "Green" V 6048 3682 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 6100 3800 50  0001 C CNN
F 3 "~" H 6100 3800 50  0001 C CNN
F 4 "604-WP710A10ZGC/G" H 6100 3800 50  0001 C CNN "Mouser Ref."
F 5 "RND 135-00157" H 6100 3800 50  0001 C CNN "Reichelt Ref."
	1    6100 3800
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R6
U 1 1 61C76595
P 5650 3400
F 0 "R6" H 5720 3446 50  0000 L CNN
F 1 "1k5" H 5720 3355 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5580 3400 50  0001 C CNN
F 3 "~" H 5650 3400 50  0001 C CNN
F 4 "603-MFR-25FTF52-1K5" H 5650 3400 50  0001 C CNN "Mouser Ref."
F 5 "METALL 1,50K" H 5650 3400 50  0001 C CNN "Reichelt Ref."
	1    5650 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 61C770E0
P 6100 3400
F 0 "R7" H 6170 3446 50  0000 L CNN
F 1 "1k5" H 6170 3355 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6030 3400 50  0001 C CNN
F 3 "~" H 6100 3400 50  0001 C CNN
F 4 "603-MFR-25FTF52-1K5" H 6100 3400 50  0001 C CNN "Mouser Ref."
F 5 "METALL 1,50K" H 6100 3400 50  0001 C CNN "Reichelt Ref."
	1    6100 3400
	1    0    0    -1  
$EndComp
Text GLabel 5600 3200 0    50   Input ~ 0
LED1
Text GLabel 6050 3200 0    50   Input ~ 0
LED2
$Comp
L power:GND #PWR0105
U 1 1 61C7A67E
P 5650 4050
F 0 "#PWR0105" H 5650 3800 50  0001 C CNN
F 1 "GND" H 5655 3877 50  0000 C CNN
F 2 "" H 5650 4050 50  0001 C CNN
F 3 "" H 5650 4050 50  0001 C CNN
	1    5650 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 3200 5650 3200
Wire Wire Line
	5650 3200 5650 3250
Wire Wire Line
	6050 3200 6100 3200
Wire Wire Line
	6100 3200 6100 3250
Wire Wire Line
	5650 3650 5650 3550
Wire Wire Line
	6100 3550 6100 3650
Wire Wire Line
	5650 4050 5650 4000
Wire Wire Line
	5650 4000 6100 4000
Wire Wire Line
	6100 4000 6100 3950
Connection ~ 5650 4000
Wire Wire Line
	5650 4000 5650 3950
NoConn ~ 4700 3750
$Comp
L power:GND #PWR0106
U 1 1 6178C37E
P 5600 5450
F 0 "#PWR0106" H 5600 5200 50  0001 C CNN
F 1 "GND" H 5605 5277 50  0000 C CNN
F 2 "" H 5600 5450 50  0001 C CNN
F 3 "" H 5600 5450 50  0001 C CNN
	1    5600 5450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0101
U 1 1 61B89C58
P 4000 1750
F 0 "#PWR0101" H 4000 1600 50  0001 C CNN
F 1 "+5V" H 4015 1923 50  0000 C CNN
F 2 "" H 4000 1750 50  0001 C CNN
F 3 "" H 4000 1750 50  0001 C CNN
	1    4000 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 1850 4000 1800
Wire Wire Line
	3150 3100 3150 3050
Wire Wire Line
	3150 3050 3300 3050
Wire Wire Line
	5500 5400 5600 5400
Wire Wire Line
	5600 5450 5600 5400
Text GLabel 6550 5000 2    50   BiDi ~ 0
USB_D+
Text GLabel 6550 5100 2    50   BiDi ~ 0
USB_D-
$Comp
L Mechanical:MountingHole H1
U 1 1 626864A3
P 6250 6850
F 0 "H1" H 6350 6896 50  0000 L CNN
F 1 "MountingHole" H 6350 6805 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 6250 6850 50  0001 C CNN
F 3 "~" H 6250 6850 50  0001 C CNN
	1    6250 6850
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 62696A3B
P 6250 7100
F 0 "H2" H 6350 7146 50  0000 L CNN
F 1 "MountingHole" H 6350 7055 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 6250 7100 50  0001 C CNN
F 3 "~" H 6250 7100 50  0001 C CNN
	1    6250 7100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 62697384
P 6250 7350
F 0 "H3" H 6350 7396 50  0000 L CNN
F 1 "MountingHole" H 6350 7305 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 6250 7350 50  0001 C CNN
F 3 "~" H 6250 7350 50  0001 C CNN
	1    6250 7350
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 62697C53
P 6250 7600
F 0 "H4" H 6350 7646 50  0000 L CNN
F 1 "MountingHole" H 6350 7555 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2_Pad_Via" H 6250 7600 50  0001 C CNN
F 3 "~" H 6250 7600 50  0001 C CNN
	1    6250 7600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 4650 2650 4500
Wire Wire Line
	2650 4500 2600 4500
Wire Wire Line
	2600 4600 2700 4600
NoConn ~ 4700 3250
$Comp
L Device:C C1
U 1 1 616F1A22
P 2600 1750
F 0 "C1" H 2715 1796 50  0000 L CNN
F 1 "100n" H 2715 1705 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 2638 1600 50  0001 C CNN
F 3 "~" H 2600 1750 50  0001 C CNN
F 4 "594-K104K15X7RF53K2" H 2600 1750 50  0001 C CNN "Mouser Ref."
F 5 "KERKO 100N" H 2600 1750 50  0001 C CNN "Reichelt Ref."
	1    2600 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 2250 2250 1900
Wire Wire Line
	2250 1900 2600 1900
Connection ~ 2250 2250
Wire Wire Line
	3400 1600 3400 1800
Connection ~ 2600 1900
Wire Wire Line
	2600 1900 3050 1900
NoConn ~ 4700 2750
NoConn ~ 4700 2650
NoConn ~ 4700 3150
Text Notes 6250 4300 0    50   ~ 0
Leds
Wire Notes Line
	2100 1500 5200 1500
Wire Notes Line
	5200 5000 2100 5000
Wire Notes Line
	2100 5000 2100 1500
Wire Wire Line
	3450 4650 3450 4750
Text Notes 4600 4950 0    50   ~ 0
Microcontroller
Wire Notes Line
	5300 4450 7000 4450
Wire Notes Line
	7000 4450 7000 5700
Wire Notes Line
	7000 5700 5300 5700
Wire Notes Line
	5300 5700 5300 4450
Text Notes 6800 5650 0    50   ~ 0
USB
Text Label 6000 4750 0    50   ~ 0
USB_CONN_D+
Connection ~ 5600 5400
$Comp
L Connector:USB_B J1
U 1 1 61C21FC1
P 5600 5000
AR Path="/61C21FC1" Ref="J1"  Part="1" 
AR Path="/6175D50F/61C21FC1" Ref="J?"  Part="1" 
F 0 "J1" H 5657 5467 50  0000 C CNN
F 1 "USB B Female" H 5657 5376 50  0000 C CNN
F 2 "Connector_USB:USB_B_Lumberg_2411_02_Horizontal" H 5750 4950 50  0001 C CNN
F 3 " ~" H 5750 4950 50  0001 C CNN
F 4 "710-61400416121" H 5600 5000 50  0001 C CNN "Mouser Ref."
F 5 "USB BW" H 5600 5000 50  0001 C CNN "Reichelt Ref."
	1    5600 5000
	1    0    0    -1  
$EndComp
Text Label 6000 5450 0    50   ~ 0
USB_CONN_D-
Wire Wire Line
	6000 5450 6000 5100
Wire Wire Line
	6000 5100 5900 5100
Wire Wire Line
	6200 5100 6000 5100
Connection ~ 6000 5100
Wire Wire Line
	5900 5000 6000 5000
Wire Wire Line
	6000 4750 6000 5000
Connection ~ 6000 5000
Wire Wire Line
	6000 5000 6200 5000
NoConn ~ 4700 2150
NoConn ~ 4700 2850
NoConn ~ 4700 4350
$Comp
L power:+5V #PWR0107
U 1 1 61655010
P 5950 4700
F 0 "#PWR0107" H 5950 4550 50  0001 C CNN
F 1 "+5V" H 5965 4873 50  0000 C CNN
F 2 "" H 5950 4700 50  0001 C CNN
F 3 "" H 5950 4700 50  0001 C CNN
	1    5950 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 4800 5950 4800
Wire Wire Line
	5950 4800 5950 4700
Wire Wire Line
	2600 1600 3050 1600
$Comp
L Device:CP C2
U 1 1 61688E09
P 3050 1750
F 0 "C2" H 3168 1796 50  0000 L CNN
F 1 "10u" H 3168 1705 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 3088 1600 50  0001 C CNN
F 3 "~" H 3050 1750 50  0001 C CNN
F 4 "667-ECA-1VM100I" H 3050 1750 50  0001 C CNN "Mouser Ref."
F 5 "RAD 10/35" H 3050 1750 50  0001 C CNN "Reichelt Ref."
	1    3050 1750
	1    0    0    -1  
$EndComp
Connection ~ 3050 1600
Wire Wire Line
	3050 1600 3400 1600
NoConn ~ 4700 3350
Wire Notes Line
	6450 4350 6450 3050
$Comp
L Connector:AVR-ISP-6 J4
U 1 1 61BCF059
P 8400 2150
F 0 "J4" H 8070 2246 50  0000 R CNN
F 1 "AVR-ISP-6" H 8070 2155 50  0000 R CNN
F 2 "Connector_IDC:IDC-Header_2x03_P2.54mm_Vertical" V 8150 2200 50  0001 C CNN
F 3 " ~" H 7125 1600 50  0001 C CNN
F 4 "710-61200621621" H 8400 2150 50  0001 C CNN "Mouser Ref."
F 5 "WSL 6G" H 8400 2150 50  0001 C CNN "Reichelt Ref."
	1    8400 2150
	-1   0    0    -1  
$EndComp
Text GLabel 8450 1600 0    50   UnSpc ~ 0
ISP_VCC
$Comp
L power:GND #PWR0103
U 1 1 61BDC8A1
P 8500 2600
F 0 "#PWR0103" H 8500 2350 50  0001 C CNN
F 1 "GND" H 8505 2427 50  0000 C CNN
F 2 "" H 8500 2600 50  0001 C CNN
F 3 "" H 8500 2600 50  0001 C CNN
	1    8500 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 2600 8500 2550
Wire Wire Line
	8450 1600 8500 1600
Wire Wire Line
	8500 1600 8500 1650
Wire Wire Line
	7950 1950 8000 1950
Text GLabel 8450 3000 0    50   UnSpc ~ 0
ISP_VCC
$Comp
L power:GND #PWR0104
U 1 1 61BE9D67
P 8500 4000
F 0 "#PWR0104" H 8500 3750 50  0001 C CNN
F 1 "GND" H 8505 3827 50  0000 C CNN
F 2 "" H 8500 4000 50  0001 C CNN
F 3 "" H 8500 4000 50  0001 C CNN
	1    8500 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 4000 8500 3950
Wire Wire Line
	8450 3000 8500 3000
Wire Wire Line
	8500 3000 8500 3050
Text GLabel 7900 1700 0    50   Output ~ 0
ISP_MISO
Text GLabel 7000 2050 0    50   Input ~ 0
ISP_MOSI
Text GLabel 7000 2150 0    50   Input ~ 0
ISP_SCK
Text GLabel 7700 2250 0    50   BiDi ~ 0
dw_OUT
$Comp
L Connector:AVR-ISP-10 J5
U 1 1 61BEC967
P 8400 3550
F 0 "J5" H 8070 3646 50  0000 R CNN
F 1 "AVR-ISP-10" H 8070 3555 50  0000 R CNN
F 2 "Connector_IDC:IDC-Header_2x05_P2.54mm_Vertical" V 8150 3600 50  0001 C CNN
F 3 " ~" H 7125 3000 50  0001 C CNN
F 4 "710-61201021621" H 8400 3550 50  0001 C CNN "Mouser Ref."
F 5 "WSL 10G" H 8400 3550 50  0001 C CNN "Reichelt Ref."
	1    8400 3550
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 61BF64FD
P 7350 3800
F 0 "J3" H 7242 3985 50  0000 C CNN
F 1 "JST XH2P Female" H 7242 3894 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B2B-XH-A_1x02_P2.50mm_Vertical" H 7350 3800 50  0001 C CNN
F 3 "~" H 7350 3800 50  0001 C CNN
F 4 "N/A" H 7350 3800 50  0001 C CNN "Mouser Ref."
F 5 "JST XH2P ST" H 7350 3800 50  0001 C CNN "Reichelt Ref."
	1    7350 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 61BF6503
P 7100 4000
F 0 "#PWR0111" H 7100 3750 50  0001 C CNN
F 1 "GND" H 7105 3827 50  0000 C CNN
F 2 "" H 7100 4000 50  0001 C CNN
F 3 "" H 7100 4000 50  0001 C CNN
	1    7100 4000
	1    0    0    -1  
$EndComp
Text GLabel 7050 3900 0    50   BiDi ~ 0
dw_OUT
Wire Wire Line
	7100 4000 7100 3800
Wire Wire Line
	7100 3800 7150 3800
Wire Wire Line
	7050 3900 7150 3900
Text Notes 8950 4300 0    50   ~ 0
Output
Text GLabel 4750 3850 2    50   BiDi ~ 0
dw_OUT
Text GLabel 4750 3450 2    50   BiDi ~ 0
dw_OUT
Wire Wire Line
	4700 3450 4750 3450
Wire Wire Line
	4700 3850 4750 3850
Wire Wire Line
	4700 3950 4750 3950
Text GLabel 4750 3950 2    50   Output ~ 0
dw_TXD
Text GLabel 4750 2350 2    50   Output ~ 0
ISP_MOSI
Text GLabel 4750 2450 2    50   Input ~ 0
ISP_MISO
Text GLabel 4750 2250 2    50   Output ~ 0
ISP_SCK
Wire Wire Line
	4700 2250 4750 2250
Wire Wire Line
	4700 2350 4750 2350
Wire Wire Line
	4700 2450 4750 2450
$Comp
L Device:R R8
U 1 1 61C5B110
P 7500 2050
F 0 "R8" V 7293 2050 50  0000 C CNN
F 1 "470R" V 7384 2050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7430 2050 50  0001 C CNN
F 3 "~" H 7500 2050 50  0001 C CNN
F 4 "603-MFR-25FTF52-470R" H 7500 2050 50  0001 C CNN "Mouser Ref."
F 5 "METALL 470" H 7500 2050 50  0001 C CNN "Reichelt Ref."
	1    7500 2050
	0    1    1    0   
$EndComp
$Comp
L Device:R R9
U 1 1 61C5DC55
P 7200 2150
F 0 "R9" V 7085 2150 50  0000 C CNN
F 1 "470R" V 6994 2150 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7130 2150 50  0001 C CNN
F 3 "~" H 7200 2150 50  0001 C CNN
F 4 "603-MFR-25FTF52-470R" H 7200 2150 50  0001 C CNN "Mouser Ref."
F 5 "METALL 470" H 7200 2150 50  0001 C CNN "Reichelt Ref."
	1    7200 2150
	0    1    -1   0   
$EndComp
Wire Wire Line
	7950 1950 7950 3350
Wire Wire Line
	7950 3350 8000 3350
Wire Wire Line
	8000 3450 7900 3450
Wire Wire Line
	7900 3450 7900 2050
Wire Wire Line
	7900 2050 8000 2050
Wire Wire Line
	8000 3550 7850 3550
Wire Wire Line
	7850 3550 7850 2150
Wire Wire Line
	7850 2150 8000 2150
Wire Wire Line
	8000 3650 7800 3650
Wire Wire Line
	7800 3650 7800 2250
Wire Wire Line
	7800 2250 8000 2250
Wire Wire Line
	7650 2050 7900 2050
Connection ~ 7900 2050
Wire Wire Line
	7900 1700 7950 1700
Wire Wire Line
	7950 1700 7950 1950
Connection ~ 7950 1950
Wire Wire Line
	7700 2250 7800 2250
Connection ~ 7800 2250
Wire Wire Line
	7000 2150 7050 2150
Wire Wire Line
	7350 2150 7850 2150
Connection ~ 7850 2150
Wire Wire Line
	7000 2050 7350 2050
Wire Notes Line
	6550 1500 9250 1500
$Comp
L power:+5V #PWR0112
U 1 1 61D0E3CE
P 5550 1750
F 0 "#PWR0112" H 5550 1600 50  0001 C CNN
F 1 "+5V" H 5565 1923 50  0000 C CNN
F 2 "" H 5550 1750 50  0001 C CNN
F 3 "" H 5550 1750 50  0001 C CNN
	1    5550 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 61D11D9E
P 5550 1950
F 0 "R4" H 5481 1904 50  0000 R CNN
F 1 "22k" H 5481 1995 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5480 1950 50  0001 C CNN
F 3 "~" H 5550 1950 50  0001 C CNN
F 4 "603-MFR-25FTF52-22K" H 5550 1950 50  0001 C CNN "Mouser Ref."
F 5 "METALL 22,0K" H 5550 1950 50  0001 C CNN "Reichelt Ref."
	1    5550 1950
	1    0    0    1   
$EndComp
Wire Wire Line
	5550 2100 5550 2150
Wire Wire Line
	5550 2150 5700 2150
Wire Wire Line
	5550 1800 5550 1750
$Comp
L Device:R R5
U 1 1 61D1E9DA
P 6000 2550
F 0 "R5" H 5931 2504 50  0000 R CNN
F 1 "470R" H 5931 2595 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5930 2550 50  0001 C CNN
F 3 "~" H 6000 2550 50  0001 C CNN
F 4 "603-MFR-25FTF52-470R" H 6000 2550 50  0001 C CNN "Mouser Ref."
F 5 "METALL 470" H 6000 2550 50  0001 C CNN "Reichelt Ref."
	1    6000 2550
	1    0    0    1   
$EndComp
Text GLabel 6050 1850 2    50   BiDi ~ 0
dw_OUT
Wire Wire Line
	6000 1950 6000 1850
Wire Wire Line
	6000 1850 6050 1850
Text GLabel 5700 2750 0    50   Input ~ 0
dw_TXD
Wire Wire Line
	6000 2350 6000 2400
Wire Wire Line
	4100 1850 4100 1800
Wire Wire Line
	4100 1800 4000 1800
Connection ~ 4000 1800
Wire Wire Line
	4000 1800 3900 1800
Wire Wire Line
	3900 1850 3900 1800
Connection ~ 3900 1800
Wire Wire Line
	3900 1800 3400 1800
Wire Wire Line
	4000 1800 4000 1750
Wire Wire Line
	3450 4650 3900 4650
Wire Wire Line
	3900 4650 4000 4650
Connection ~ 3900 4650
$Comp
L MCU_Microchip_ATmega:ATmega32U2-AU U1
U 1 1 616DB556
P 4000 3250
F 0 "U1" H 4000 1761 50  0000 C CNN
F 1 "ATmega8U2-AU" H 4000 1670 50  0000 C CNN
F 2 "custom-footprints:TQFP-32_7x7mm_P0.8mm_LongPads" H 4000 3250 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/doc7799.pdf" H 4000 3250 50  0001 C CNN
F 4 "556-ATMEGA8U2-AU" H 4000 3250 50  0001 C CNN "Mouser Ref."
F 5 "ATMEGA 32-U2 TQ (equivalent!)" H 4000 3250 50  0001 C CNN "Reichelt Ref."
	1    4000 3250
	1    0    0    -1  
$EndComp
Wire Notes Line
	5300 1500 5300 2950
$Comp
L Connector_Generic:Conn_01x03 J6
U 1 1 61DB234B
P 7250 3000
F 0 "J6" H 7330 3042 50  0000 L CNN
F 1 "Jumper" H 7330 2951 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7250 3000 50  0001 C CNN
F 3 "~" H 7250 3000 50  0001 C CNN
F 4 "68797-236HLF" H 7250 3000 50  0001 C CNN "Mouser Ref."
F 5 "SL 1X40G 2,54" H 7250 3000 50  0001 C CNN "Reichelt Ref."
	1    7250 3000
	1    0    0    -1  
$EndComp
NoConn ~ 7050 2900
Text GLabel 6950 3000 0    50   UnSpc ~ 0
ISP_VCC
Wire Wire Line
	7000 3100 7050 3100
$Comp
L power:+5V #PWR0113
U 1 1 61DC3280
P 7000 2800
F 0 "#PWR0113" H 7000 2650 50  0001 C CNN
F 1 "+5V" H 7015 2973 50  0000 C CNN
F 2 "" H 7000 2800 50  0001 C CNN
F 3 "" H 7000 2800 50  0001 C CNN
	1    7000 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 2800 7000 3100
Wire Wire Line
	6950 3000 7050 3000
Wire Notes Line
	6450 3050 5300 3050
Wire Notes Line
	5300 3050 5300 4350
Wire Notes Line
	5300 4350 6450 4350
Text GLabel 4750 3050 2    50   Output ~ 0
LED1
Text GLabel 4750 3650 2    50   Output ~ 0
LED2
$Comp
L Device:R R3
U 1 1 61E1EAD2
P 5050 2750
F 0 "R3" H 4981 2704 50  0000 R CNN
F 1 "470R" H 4981 2795 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4980 2750 50  0001 C CNN
F 3 "~" H 5050 2750 50  0001 C CNN
F 4 "603-MFR-25FTF52-470R" H 5050 2750 50  0001 C CNN "Mouser Ref."
F 5 "METALL 470" H 5050 2750 50  0001 C CNN "Reichelt Ref."
	1    5050 2750
	1    0    0    1   
$EndComp
Wire Wire Line
	4700 2550 5050 2550
Wire Wire Line
	5050 2550 5050 2600
$Comp
L power:GND #PWR0114
U 1 1 61E24DA1
P 5050 2950
F 0 "#PWR0114" H 5050 2700 50  0001 C CNN
F 1 "GND" H 5055 2777 50  0000 C CNN
F 2 "" H 5050 2950 50  0001 C CNN
F 3 "" H 5050 2950 50  0001 C CNN
	1    5050 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 2950 5050 2900
NoConn ~ 4700 4250
Wire Notes Line
	5300 1500 6450 1500
Wire Notes Line
	6450 1500 6450 2950
Wire Notes Line
	6450 2950 5300 2950
Text Notes 5700 2900 0    50   ~ 0
debugWIRE output
Wire Wire Line
	5700 2750 6000 2750
Wire Wire Line
	6000 2750 6000 2700
$Comp
L Transistor_BJT:BC548 Q1
U 1 1 61D0C49C
P 5900 2150
F 0 "Q1" H 6091 2196 50  0000 L CNN
F 1 "BC548" H 6091 2105 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 6100 2075 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BC550-D.pdf" H 5900 2150 50  0001 L CNN
F 4 "821-BC548B-A1" H 5900 2150 50  0001 C CNN "Mouser Ref."
F 5 "BC 548B" H 5900 2150 50  0001 C CNN "Reichelt Ref."
	1    5900 2150
	1    0    0    -1  
$EndComp
Wire Notes Line
	6550 4350 9250 4350
Wire Notes Line
	6550 1500 6550 4350
Wire Notes Line
	9250 1500 9250 4350
Wire Wire Line
	4700 3050 4750 3050
Wire Wire Line
	4700 3650 4750 3650
Wire Notes Line
	5200 1500 5200 5000
$EndSCHEMATC
