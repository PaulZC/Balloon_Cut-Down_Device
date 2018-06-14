# Balloon Cut-Down Device

A cut-down device suitable for use on High Altitude Balloons and other remote actuation projects.

![Cut-Down_Device_1.gif](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Cut-Down_Device_1.gif)

![Cut-Down_Device_1.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Cut-Down_Device_1.JPG)

![Cut-Down_Device_2.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Cut-Down_Device_2.JPG)

Designed to be interfaced to the [Iridium 9603N V5 Beacon](https://github.com/PaulZC/Iridium_9603_Beacon), but can be operated by: any push-to-close
switch; normally-open relay contact; or a 3.3V logic signal.

## Background

The cut-down device is designed to release the payload from a high altitude balloon. When connected to an
[Iridium 9603N Beacon](https://github.com/PaulZC/Iridium_9603_Beacon) it can be actuated from the ground via an Iridium Short Burst Data message.
However, the device can also operate stand-alone when connected to: an external GNSS (GPS) receiver via the Serial1 pins; or an external
altitude sensor via the I2C pins.

The device has been designed such that multiple devices can be connected together in parallel, using one pair of wires, and triggered
consecutively by increasing trigger pulse widths.

## The Design

See [Balloon_Cut-Down_Device.pdf](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/Balloon_Cut-Down_Device.pdf) for the schematic,
layout and Bill Of Materials.

The [Eagle](https://github.com/PaulZC/Balloon_Cut-Down_Device/tree/master/Eagle) directory contains the schematic and pcb design files.

See [ASSEMBLY.md](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/ASSEMBLY.md) for details on how to assemble the PCB and the device itself.

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

### Carbon-Fibre Parts

The [Drawings](https://github.com/PaulZC/Balloon_Cut-Down_Device/tree/master/Drawings) directory contains the drawings for the carbon-fibre base plate
and trigger linkage.

![Assembly_14](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_14.JPG)

### The PCB

[ASSEMBLY.md](https://github.com/PaulZC/Balloon_Cut-Down_Device/tree/master/ASSEMBLY.md) contains full instructions for the assembly of the PCB and
the Cut-Down Device itself.

![Assembly_13](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_13.JPG)

### Atmel ATSAMD21G18 Processor
![V1_SAMD.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V1_SAMD.JPG)

As used on the Adafruit Feather M0:
- https://www.adafruit.com/products/2772

### MCP111T-240 Reset Supervisor
![V1_Reset_Supervisor.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V1_Reset_Supervisor.JPG)

The Microchip MCP111-240 has an open drain output which holds the processor in reset until the supply rises above 2.4V, ensuring a clean start on power-up.

### SPX3819-3.3 Voltage Regulator
![V1_3V3_Regulator.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V1_3V3_Regulator.JPG)

The SPX3819-3.3 Voltage Regulator regulates the output from the battery, or the USB port, providing 3.3V for the processor.

MBR120 diodes protect the USB port and the battery from each other.

### MPM3610 Voltage Regulator
![V1_5V_Regulator.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V1_5V_Regulator.JPG)

The MPM3610 Voltage Regulator regulates the output from the battery, providing 5V for the servo. The servo will only operate when a battery is connected, it
won't work when the device is powered from USB alone.

### 74AHCT1G125 Level Shifter
![V1_Level_Shifter.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V1_Level_Shifter.JPG)

The 74AHCT1G125 Level Shifter is a non-inverting buffer which converts the 3.3V Pulse Width Modulation pulses from the SAMD M0 processor to 5V for the servo.

### Switches
![V1_Switches.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V1_Switches.JPG)

The cut-down device has five switches:
- CLOSE
- OPEN
- PLUS (+)
- MINUS (-)
- RESET

Press and release RESET to reset the processor. Pressing RESET twice quickly will put the processor into bootloader mode. The LED will fade up and down when in this
mode. Press RESET once to bring the processor back out of bootloader mode.

Pressing OPEN will cause the servo to move the Shark trigger to the open position.

Pressing CLOSE will cause the servo to move the Shark trigger to the closed position.

The PLUS and MINUS switches are used to put the device into [Set_Servo](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/LEARN.md#set_servo)
or [Set_Duration](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/LEARN.md#set_duration) mode.

## IO Pins
![V1_Open_Close_Pins.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V1_Open_Close_Pins.JPG)

**OPEN** and **CLOSE** can be used to open and close the Shark release via the servo. The OPEN and CLOSE push switches are connected to the same pins.
Pull OPEN low, through a push-to-close switch or a normally-open relay contact, to trigger the cut-down device.

To connect the cut-down device to an [Iridium 9603N V5 Beacon](https://github.com/PaulZC/Iridium_9603_Beacon), connect **GND** and **OPEN** to the beacon relay **COM** and **NO** pins using twin core cable.
If a Mobile Terminated message is sent to the beacon containing the text _[RELAY=1]_ , the relay NO contact will pulse closed for 1 second.
This will trigger the device if intDuration is set to '0' or '1' (see [Set_Duration](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/LEARN.md#set_duration)).

OPEN and CLOSE are connected to 3.3V inputs with pull-ups on the SAMD M0 processor. Do not connect these pins to a 5V device directly - there is no additional over-voltage protection on these pins.
Use an open-collector transistor as a buffer if you do want to connect to a 5V device.

![V1_IO_Pins_1.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V1_IO_Pins_1.JPG)

**SWCLK** and **SWDIO** are used during [programming of the SAMD bootloader](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/LEARN.md#how-do-i-install-the-atsamd21g18-bootloader).

**RST** is the processor reset signal. Pull low to reset the processor.

**3V3** is the 3.3V power rail from the SPX3819-3.3 voltage regulator.
Any peripherals connected to this will be powered continuously when power is available from the battery or USB.

**VBUS** is the power bus connecting the battery and USB power rails. VBUS will be close to 5V when connected to USB alone, or close to 9V when the
battery is connected. This pin can be used to power the board during [programming of the SAMD bootloader](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/LEARN.md#how-do-i-install-the-atsamd21g18-bootloader).

![V1_IO_Pins_2.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V1_IO_Pins_2.JPG)

**3V3SW** is the 3.3V power rail switched by Q1 and which can provide power for external serial and I2C devices.
Use these pins to power peripherals which you want to be able to disable.

**SDA** and **SCL** are the I2C bus data and clock signals.
You could use these to connect an external I2C sensor - e.g. an MPL3115A2 altitude sensor.

**TX** and **RX** are the Serial1 transmit and receive pins. You could use these to connect to an external 3.3V GNSS (GPS) receiver.

![V1_Servo_Pins.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V1_Servo_Pins.JPG)

**GND** and **5V** provide power for the servo. **PWM** is the 5V Pulse Width Modulated signal which sets the servo position.

When connecting the servo, ensure the black wire goes to GND, the red wire to 5V and the yellow wire to PWM.

## How much does the device weigh?
Including an Energiser® Ultimate Lithium L522 (PP3) battery, it weighs approx. 132g.

The weight breaks down as follows:
- Battery (Energiser L522) 			33.9g
- PCB + Battery Holder				20.6g
- Shark Release (No Trigger) 			20.2g
- HS-82MG Servo 				19.8g
- Base Plate 					17g
- M3 x 16 Screws, Nuts, Spacers (4)		5.8g
- Tower Pro Arm 				4.4g
- Trigger Block 				2.2g
- Trigger Linkage 				2g
- M3 x 4 Shoulder Screws (2) 			1.8g
- M2.5 x 14 Screws, Nuts (2) 			2.1g
- 4-40 x ¼" Screws (3)				1.5g
- 4-40 x ¾" Screw 				1.0g

## What fasteners do I need?
To secure the PCB and battery holder to the base plate:
- M3 x 16 Hex Drive Screw x 4 (McMaster 92095A184)
- 4.5mm OD, 5mm Long Spacer x 4 (McMaster 94669A099)
- M3 Nylon-Insert Locknut x 4 (McMaster 93625A100)
- M3 Washer x 4 (McMaster 90965A130)

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

## Will this really work at altitude?

Yes. I have tested the device at -47C using dry ice. The servo moved slower than usual at that temperature, but it did release as expected.

![Cold_Test_1.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Cold_Test_1.JPG)

![Cold_Test_2.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Cold_Test_2.JPG)

![Cold_Test_1.gif](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Cold_Test_1.gif)

![Cold_Test_3.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Cold_Test_3.JPG)

## Have you performed a load test?

Yes. The device has been subjected to a Lead Brick Test. A 7kg lead brick was attached and released from the device 100 times. No problems
were observed!

![Load_Test_1.gif](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Load_Test_1.gif)

## Do you recommend coating the board once it is populated?
As a minimum, I'd recommend applying a coat of acrylic protective lacquer to the processor and surrounding components (especially the crystal).
If you're using an aerosol, be careful to mask off the connectors and switches first.

## Arduino Code
The [Arduino](https://github.com/PaulZC/Balloon_Cut-Down_Device/tree/master/Arduino) directory contains the Arduino code.

The main loop is structured around a switch / case statement which provides the three modes of operation:

### Cut_Down:
The SAMD M0 processor is woken up from deep sleep by an interrupt from the OPEN or CLOSE switch. It waits to see if the switch pin stays
low for the required amount of time (intDuration) then moves the servo to the open or closed position as appropriate.
By default, intDuration will be zero - i.e. the servo will move immediately. The M0 goes back into deep sleep when the
servo move is complete.

![Cut-Down_Device_1.gif](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Cut-Down_Device_1.gif)

In reality, the required intDuration is decreased by 0.1 seconds to allow exact whole second key presses
to trigger the device. E.g. if intDuration is set to '1', a key press of 0.9s or longer will trigger the device.
This keeps things simple when triggering the device from an Iridium Beacon via Mobile Terminated messaging.

The LED will light up while the servo is moving. If the battery is low, the LED will flash quickly.

The servo will only operate when a battery is connected, it won't work when the device is powered from USB alone.

The cut-down device spends most of its time in deep sleep, which means that the Arduino IDE won't recognise it as connected. If you want to reprogram
the board, either:

- press the reset button twice quickly, to put the processor into bootloader mode

or:

- press and hold down the PLUS or MINUS switch, then press the reset switch briefly. Release the PLUS or MINUS switch after the LED goes out. This puts the
board into Set_Servo mode or Set_Duration mode where the processor is powered up continuously.

The Arduino IDE will then be able to connect to the board.

### Set_Servo:
**It is safest to disconnect the trigger linkage from the servo arm _before_ putting the device into Set_Servo mode. Remove the shoulder screw which connects the
linkage to the servo arm. Replace it after the servo limits have been set and the device has been reset into Cut_Down mode.**

The code enters Set_Servo mode if the M0 comes out of reset with the PLUS switch held down. Push and hold the PLUS switch, then press and release the RESET switch.
Keep PLUS pressed until the LED has come on and gone out. The device will then enter Set_Servo mode.

![Set_Servo_1.gif](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Set_Servo_1.gif)

The servo is moved to its mid-range position (PWM = 1500).

Depending on whether the PLUS or MINUS switches are held down, the servo is moved towards one limit (PWM = 900) or the other (PWM = 2100).

![Set_Servo_2.gif](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Set_Servo_2.gif)

If the OPEN switch is pressed, the servo position is written into flash memory as servoOpen. With the Shark release open, hold the trigger linkage over the servo
arm and move the servo until the holes line up, before pressing the OPEN switch to store the setting. The LED will give a long flash while the setting is storted.

If the CLOSED switch is pressed, the servo position is written into flash memory as servoClosed. Repeat the above with the Shark release closed and store the setting.

![Set_Servo_3.gif](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Set_Servo_3.gif)

![Set_Servo_4.gif](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Set_Servo_4.gif)

![Set_Servo_5.gif](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Set_Servo_5.gif)

The M0 will stay in this mode until reset.

![Set_Servo_6.gif](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Set_Servo_6.gif)

As the servo is powered up continuously in Set_Servo mode, the battery will discharge quickly if the device is left in this mode.
Always reset the device to put it back into Cut_Down mode when the servo positions have been stored.

After resetting the device, the shoulder screw can be replaced and the OPEN and CLOSED switches can be used to move the servo.

### Set_Duration:
Set_Duration mode is used to set how long the OPEN or CLOSED switches or pins must be pressed/closed before the servo will move. This is useful since it means
that multiple cut-down devices can be connected together in parallel, using one pair of wires, and triggered consecutively by OPEN pulses of increasing duration.
A 1 second pulse could be used to trigger the first device to release a lift balloon. A 2 second pulse could then be used to trigger a second device to
release the payload from the float balloon.

The code enters Set_Duration mode if the M0 comes out of reset with the MINUS switch held down. Push and hold the MINUS switch, then press and release the RESET switch.
Keep MINUS pressed until the LED has come on and gone out. The device will then enter Set_Duration mode.

intDuration can have a value of 0, 1, 2, 3, 4 or 5 seconds.
The LED will flash intDuration times: 0.2s on, 0.2s off, repeating intDuration times every four seconds.

If the PLUS switch is pressed, intDuration is increased by 1.

If the MINUS switch is pressed, intDuration is decreased by 1.

If either OPEN or CLOSED is pressed, intDuration is written into flash memory. The LED will give a long flash while this takes place.

The M0 will stay in this mode until reset.

### How do I install the ATSAMD21G18 bootloader?
Get yourself a Segger J-Link programmer and connect it as shown:

![Atmel_SAMD21_Programming_Cable](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Atmel_SAMD21_Programming_Cable.JPG)

Ignore the RST connection.

Connect the 5V-Supply output from the J-Link to VBUS to power the board while you configure it. Make sure the battery is not connected while you do this.

Follow Lady Ada's excellent instructions:
- https://learn.adafruit.com/proper-step-debugging-atsamd21-arduino-zero-m0/restoring-bootloader

If you are using Atmel's Studio:

![Programming_1](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Programming_1.JPG)

Select Tools \ Device Programming

![Programming_2](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Programming_2.JPG)

Select J-Link in the Tool pull-down menu
Select ATSAMD21G18A in the Device pull-down menu
Select SWD in the Interface pull-down menu
Then click Apply

![Programming_2a](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Programming_2a.JPG)

Click the J-Link icon to apply target power to the beacon

![Programming_3](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Programming_3.JPG)

Select the Target Power tab and set Current State to Power On. This will apply 5V power from the J-Link
to the beacon VBUS

![Programming_4](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Programming_4.JPG)

Close the J-Link window. In the Device Programming window click 'Read' to read the Device Signature and Target Voltage

![Programming_5](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Programming_5.JPG)

Click 'Memories', click the '...' icon to select the bootloader Flash file
Click Program to erase, program and verify the device

![Programming_6](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Programming_6.JPG)

Finally, select the J-Link icon again, select the Target Power tab and set Current State to Power Off
Close Device Programming and Atmel Studio and you are ready to configure the Beacon with the Arduino code

### How do I upload the Arduino code?
The Cut-Down Device is based on the Adafruit Feather M0 (Adalogger):
- https://www.adafruit.com/products/2796
- https://www.adafruit.com/products/2772

You can follow Lady Ada's excellent instructions:
- https://cdn-learn.adafruit.com/downloads/pdf/adafruit-feather-m0-adalogger.pdf

### What other libraries do I need?
The code uses Cristian Maglie's FlashStorage library to store and retrieve the servo settings:
- https://github.com/cmaglie/FlashStorage

## Acknowledgements

This project wouldn't have been possible without the open source designs and code kindly provided by:
- Adafruit:

   The Adafruit SAMD Board library  
   The design for the Feather M0 Adalogger  
   For more details, check out the product page at:
   - https://www.adafruit.com/product/2772  

   Adafruit invests time and resources providing this open source design, please support Adafruit and open-source hardware by purchasing products from Adafruit!  
   Designed by Adafruit Industries.  
   Creative Commons Attribution, Share-Alike license

- Arduino:

   The Arduino IDE  
   Arduino SAMD Board library  
   RTCZero library

- Cristian Maglie:

   FlashStorage library:
   - https://github.com/cmaglie/FlashStorage

- MartinL:

   M0 PWM tutorial:
   - http://forum.arduino.cc/index.php?topic=346731.msg2610904#msg2610904

## Licence

This project is distributed under a Creative Commons Share-alike 4.0 licence.
Please refer to section 5 of the licence for the "Disclaimer of Warranties and Limitation of Liability".
  

Enjoy!

**_Paul_**