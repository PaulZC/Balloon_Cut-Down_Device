# Balloon Cut-Down Device

A cut-down device suitable for use on High Altitude Balloons and other remote actuation projects.

![V3_Cut-Down_Device.gif](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Cut-Down_Device.gif)

![V3_Cut-Down_Device_1.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Cut-Down_Device_1.JPG)

![V3_Cut-Down_Device_2.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Cut-Down_Device_2.JPG)

Designed to be triggered by the [Iridium Beacon Radio Board](https://github.com/PaulZC/Iridium_Beacon_Radio_Board),
carried by the [Iridium 9603N V5 Beacon](https://github.com/PaulZC/Iridium_9603_Beacon), the cut-down will be triggered
when it receives its own (unique) serial number on the chosen radio channel. The number of cut-downs that could be
triggered by a single Iridium Beacon is essentially unlimited. The cut-down can also be configured to trigger at
a pre-defined altitude. The altitude is provided by a u-blox CAM-M8Q GNSS receiver.

## The Design

See [Balloon_Cut-Down_Device.pdf](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/Balloon_Cut-Down_Device.pdf) for the schematic,
layout and Bill Of Materials.

The [Eagle](https://github.com/PaulZC/Balloon_Cut-Down_Device/tree/master/Eagle) directory contains the schematic and pcb design files.

See [ASSEMBLY.md](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/ASSEMBLY.md) for details on how to assemble the PCB and the device itself.

See [CONFIGURE.md](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/CONFIGURE.md) for details on how to configure the servo positions and altitude limit.

The key components of Balloon Cut-Down Device are:

### Scott Archery Shark Release Aid
![Shark_2.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Shark_2.JPG)

- [Scott Archery Shark release aid](https://scottarchery.com/collections/releases/products/shark-release)

See [SHARK.md](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/SHARK.md) for details on how to incorporate the Scott Archery Shark release aid
into the Cut-Down Device.

### Hi-Tec HS-82MG Micro Servo
![HiTec_HS-82MG_Top.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/HiTec_HS-82MG_Top.JPG)

- [HiTec HS-82MG servo](https://www.servoshop.co.uk/index.php?pid=HITHS82MG&area=Servo)
- with [Tower Pro CH1.0H3G arm](https://www.servoshop.co.uk/index.php?pid=CH10H3G&area=ACCS)

See [SERVO.md](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/SERVO.md) for details on how to modify the HiTec servo for
high altitude operation.

### eRIC integrated controller
The heart of the Cut-Down Device is the eRIC4 or eRIC9 [easyRadio Integrated Controller](http://www.lprs.co.uk/products/easyradio-ism-modules/eric-soc-rf-modules.html).

![V3_eRIC.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_eRIC.JPG)

Either an eRIC4 or an eRIC9 can be installed. The eRIC4 operates at 402-470 MHz for Europe, APAC and China. The eRIC9 operates at 804-940 MHz for Europe,
North & South America, India and China. Solder the _FREQ_ split pad to select the eRIC9 915 MHz band.

Each eRIC has a unique serial number. The custom code running on the eRIC will trigger the cut-down when it receives a data packet containing that serial number.

The Shark release will open when the eRIC receives:
- Its serial number
- Or its serial number followed by a "1"

The Shark release will close when the eRIC receives:
- Its serial number followed by a "0"

If the serial number of the eRIC is _12345678_, the Shark will open when the eRIC receives either:
- _12345678_

or
- _123456781_

The Shark will close when the eRIC receives:
- _123456780_

If you are using the [Iridium Beacon](https://github.com/PaulZC/Iridium_9603_Beacon) and the
[Iridium Beacon Radio Board](https://github.com/PaulZC/Iridium_Beacon_Radio_Board) to control the cut-down, you will need to send the commands:
- _[RADIO=12345678]_ or _[RADIO=123456781]_ to open the Shark release
- _[RADIO=123456780]_ to close the Shark release

You can set the altitude limit via radio by sending: the eRIC serial number; followed by a "2"; followed by two digits which represent the altitude limit is kilometres.

If you want to set the altitude limit to 33km (33000m), send:
- _[RADIO=12345678233]_

To set the altitude limit to 1km (1000m), send:
- _[RADIO=12345678201]_

The altitude limit can be disabled by setting it to 99km. This causes the CAM-M8Q GNSS receiver to be switched completely off, significantly extending the battery life.
Send:
- _[RADIO=12345678299]_

The altitude limit can be re-enabled by setting it to anything other than 99km.

### u-blox CAM-M8Q GNSS Receiver
![V3_CAM_M8Q.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_CAM_M8Q.JPG)

Altitude data is provided by a u-blox CAM-M8Q GNSS receiver. To save power, the CAM-M8Q is configured to use only GPS satellites and ignores GLONASS, Galileo and BeiDou satellites.
Once the receiver has established a fix, the CAM-M8Q is put into low power mode to further extend the battery life. The CAM-M8Q can be disabled by setting the altitude limit to 99km.

### MCP111T-240 Reset Supervisor
![V3_Reset_Supervisor.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Reset_Supervisor.JPG)

The Microchip MCP111-240 has an open drain output which holds the eRIC in reset until the supply rises above 2.4V, ensuring a clean start on power-up.

### SPX3819-3.3 Voltage Regulator
![V3_3V3_Regulator.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_3V3_Regulator.JPG)

The SPX3819-3.3 Voltage Regulator regulates the output from the battery, or the USB port, providing 3.3V for the eRIC and the CAM-M8Q.

MBR120 diodes protect the USB port and the battery from each other.

### MPM3610 Voltage Regulator
![V3_5V_Regulator.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_5V_Regulator.JPG)

The MPM3610 Voltage Regulator regulates the output from the battery, providing 5V for the servo. The servo will only operate when a battery is connected, it
won't work when the device is powered from USB alone.

### 74AHCT1G125 Level Shifter
![V3_Level_Shifter.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Level_Shifter.JPG)

The 74AHCT1G125 Level Shifter is a non-inverting buffer which converts the 3.3V Pulse Width Modulation pulses from the eRIC to 5V for the servo.

### Switches
![V3_Switches.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Switches.JPG)

The cut-down device has five switches:
- CLOSE
- OPEN
- PLUS (+)
- MINUS (-)
- RESET

Press and release RESET to reset the eRIC.

Pressing OPEN will cause the servo to move the Shark trigger to the open position.

Pressing CLOSE will cause the servo to move the Shark trigger to the closed position.

The PLUS and MINUS switches are used to put the device into [Set_Servo](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/CONFIGURE.md#set_servo)
or [Set_Altitude](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/CONFIGURE.md#set_altitude) mode at reset.

### I/O Pins
![V3_IO_Pins.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_IO_Pins.JPG)

The eight input/output pins are used to configure the eRIC. See [Configure the eRIC](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/ASSEMBLY.md#configure-the-eric)
for more details.

### Servo Pins
![V3_Servo_Pins.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Servo_Pins.JPG)

Connect the Hi-Tec HS-82MG Micro Servo to the PCB using standard 0.1" header strip (three-way) (e.g. Farnell 1593425)

## How much does the device weigh?

Including an Energiser® Ultimate Lithium L522 (PP3) battery, it weighs 115g.

![V3_Cut-Down_Device_2](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Cut-Down_Device_2.JPG)

## What fasteners do I need?

To secure the servo to the base plate:
- M2.5 x 14 Hex Drive Screw x 2 (McMaster 91292A017)
- M2.5 Nylon-Insert Locknut x 2 (McMaster 93625A102)
- M2.5 Washer x 2 (McMaster 90965A115)

To secure the Shark release to the base plate:
- 4-40 UNC x ¼" Socket Head Screw x 3 (McMaster 92196A106)

To secure the trigger block to the Shark trigger:
- 4-40 UNC x ¾" Socket Head Screw (McMaster 92196A113)

To secure the trigger linkage to the trigger block and Tower Pro arm:
- M3 x 4mm Dia x 4mm Long Shoulder Screw x 2 (McMaster 90323A211)

## Antenna

Recommended antenna for the eRIC4 is:
- LPRS ANT-SR433 (Farnell part 2096221)

Recommended antenna for the eRIC9 is:
- LPRS ANT-SR900 (Farnell part 2096219)

http://www.lprs.co.uk/products/antennas-cables-connectors/stubby-antennas.html

The horizontal antenna orientation is important if the cut-down is positioned directly above the Iridium Beacon Radio Board on the balloon cord.

## Which 9V battery should I use?

Energiser® Ultimate Lithium L522 (PP3)

## Will this really work at altitude?

Yes. I have tested the device at -47C using dry ice. The servo moved slower than usual at that temperature, but it did release as expected.
The device was powered by an Energiser® Ultimate Lithium L522 (PP3) battery. A standard 9V battery won't work at that temperature.

![Cold_Test_1.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Cold_Test_1.JPG)

![Cold_Test_2.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Cold_Test_2.JPG)

![Cold_Test_1.gif](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Cold_Test_1.gif)

![Cold_Test_3.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Cold_Test_3.JPG)

## Do you recommend coating the board once it is populated?

As a minimum, I'd recommend applying a coat of acrylic protective lacquer to the processor and surrounding components (especially the crystal).
If you're using an aerosol, be careful to mask off the connectors and switches first.

## How do I set the servo positions and altitude limit?

See [CONFIGURE.md](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/CONFIGURE.md) for details on how to configure the servo positions and altitude limit.

## The LED flashes when I connect the battery or reset the eRIC. Why?

When the battery is connected or the reset switch is pressed, the cut-down goes into normal operation. The LED flashes to indicate the altitude limit. The default is
33km so the LED will flash three times, pause, then flash three times again.

A zero is indicated by a long flash. Two flashes followed by a long flash indicates an altitude limit of 20km.
A long flash followed by one flash indicates a limit of 1km.

To test that the CAM-M8Q is operating correctly, try setting an altitude limit of 0km (indicated by two long flashes).
The Shark will open as soon as a GPS signal is acquired (unless you are below sea level!).

## Acknowledgements

This project wouldn't have been possible without the open source designs and code kindly provided by:

### LPRS
- http://www.lprs.co.uk/products/easyradio-ism-modules/eric-soc-rf-modules.html
- http://www.lprs.co.uk/assets/files/eRIC4_9_Datasheet_1.34.pdf
- http://www.lprs.co.uk/assets/files/Custom%20programming%20eRIC.zip
- http://www.lprs.co.uk/knowledge-centre/code-examples.html

### Alan Carvalho de Assis
- https://github.com/acassis/tinygps

### Mikal Hart
- https://github.com/mikalhart/TinyGPS

## Licence

This project is distributed under a Creative Commons Share-alike 4.0 licence.
Please refer to section 5 of the licence for the "Disclaimer of Warranties and Limitation of Liability".
  

Enjoy!

**_Paul_**