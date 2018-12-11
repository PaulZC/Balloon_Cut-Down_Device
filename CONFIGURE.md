# Balloon Cut-Down Device - Configuration

A cut-down device suitable for use on High Altitude Balloons and other remote actuation projects.

![V3_Cut-Down_Device.gif](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Cut-Down_Device.gif)

![V3_Cut-Down_Device_1.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Cut-Down_Device_1.JPG)

![V3_Cut-Down_Device_2.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Cut-Down_Device_2.JPG)

Designed to be triggered by the [Iridium Beacon Radio Board](https://github.com/PaulZC/Iridium_Beacon_Radio_Board),
carried by the [Iridium 9603N V5 Beacon](https://github.com/PaulZC/Iridium_9603_Beacon), the cut-down will be triggered
when it receives its own (unique) serial number on the chosen radio channel. The number of cut-downs that could be
triggered by a single Iridium Beacon is essentially unlimited. The cut-down can also be configured to trigger at
a pre-defined altitude. The altitude is provided by a u-blox CAM-M8Q GNSS receiver.

## Set_Altitude:

There are two methods to set the altitude limit. Using the switches or via a radio message:

### Setting the Altitude Limit using the Switches:

The code enters Set_Altitude mode if the eRIC comes out of reset with the MINUS switch held down:
- Push and hold the MINUS switch;
- then press and release the RESET switch;
- then release the MINUS switch.
- The device will then enter Set_Altitude mode.

![V3_Set_Altitude.gif](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Set_Altitude.gif)

The LED will flash three times to show that the digit three is selected.

Pressing the MINUS switch decrements the digit by one.

Pressing the PLUS switch increments the digit by one.

Pressing the CLOSE switch causes the digit to be stored as the altitude limit tens of kilometers.

Pressing the OPEN switch causes the digit to be stored as the altitude limit units of kilometers.

In the animation, the sequence of events is:
- The MINUS switch is pressed and held
- The RESET switch is pressed and released
- The MINUS switch is released
- The cut-down is now in Set_Altitude mode
- The LED flashes three times to show the digit three
- The MINUS switch is pressed and released once
- The LED flashes twice to show the digit two
- The CLOSE switch is pressed and released
- Two is stored in the altitude limit tens of kilometers and the LED gives a long flash
- The MINUS switch is pressed and released once
- The LED flashes once to show the digit one
- The MINUS switch is pressed and released once
- The LED stops flashing to show the digit zero
- The OPEN switch is pressed and released
- Zero is stored in the altitude limit units of kilometers and the LED gives a long flash
- The altitude limit is now 20km
- The RESET switch is pressed and released
- The cut-down goes into normal operation
- The LED flashes twice, followed by a long flash, to indicate the altitude limit is 20km

The eRIC will stay in Set_Altitude mode until reset. Always reset the eRIC to start normal operation.

To disable the altitude limit, set it to 99km. This causes the CAM-M8Q GNSS receiver to be switched completely off,
significantly extending the battery life.

### Setting the Altitude Limit using a Radio Message:

Each eRIC has a unique serial number. The custom code running on the eRIC will set the altitude limit when it receives a data packet containing:
the eRIC serial number; followed by a "2"; followed by two digits which represent the altitude limit is kilometres.

If the serial number of the eRIC is _12345678_, an altitude limit of 33km (33000m) will be set when the eRIC receives:
- _12345678233_

If you are using the [Iridium Beacon](https://github.com/PaulZC/Iridium_9603_Beacon) and the
[Iridium Beacon Radio Board](https://github.com/PaulZC/Iridium_Beacon_Radio_Board) to control the cut-down, you will need to set the altitude via a RADIO command.

If you want to set the altitude limit to 33km (33000m), send:
- _[RADIO=12345678233]_

To set the altitude limit to 1km (1000m), send:
- _[RADIO=12345678201]_

The altitude limit can be disabled by setting it to 99km. This causes the CAM-M8Q GNSS receiver to be switched completely off, significantly extending the battery life.
Send:
- _[RADIO=12345678299]_

The altitude limit can be re-enabled by setting it to anything other than 99km.

## Set_Servo:

**It is safest to disconnect the trigger linkage from the servo arm _before_ putting the device into Set_Servo mode. Remove the shoulder screw which connects the
linkage to the servo arm. Replace it after the servo limits have been set and the device has been reset.**

**If you are setting the servo positions for the first time, do not install the servo arm on the servo until the device is in Set_Servo mode and the servo has moved to
its mid-range position.**

The code enters Set_Servo mode if the eRIC comes out of reset with the PLUS switch held down:
- Push and hold the PLUS switch;
- then press and release the RESET switch;
- then release the PLUS switch.
- The device will then enter Set_Servo mode.

![V3_Set_Servo.gif](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Set_Servo.gif)

The servo is moved to its mid-range position (PWM = 1500). 

Depending on whether the PLUS or MINUS switches are held down, the servo is moved towards one limit (PWM = 900) or the other (PWM = 2100).

With the Shark release closed, hold the trigger linkage over the servo arm and move the servo until the holes are slightly offset as shown.

![V3_Set_Servo_1](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Set_Servo_1.JPG)

![V3_Set_Servo_1a](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Set_Servo_1a.JPG)

When the CLOSED switch is pressed, the servo position is written into non-volatile memory. The LED will give a long flash while the setting is storted.

Next, open the Shark release and move the servo until the holes are slightly offset as shown.

![V3_Set_Servo_2](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Set_Servo_2.JPG)

![V3_Set_Servo_2a](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Set_Servo_2a.JPG)

When the OPEN switch is pressed, the servo position is written into non-volatile memory. The LED will give a long flash while the setting is storted.

It is important that the holes are slightly offset as shown, to prevent the servo from attempting to force the released aid open or closed.
This will damage the servo.

The eRIC will stay in this mode until reset.

As the servo is powered continuously in Set_Servo mode, the battery will discharge quickly if the device is left in this mode.
Always reset the device to put it back into Cut_Down mode when the servo positions have been stored.

After resetting the device, the shoulder screw can be replaced and the OPEN and CLOSED switches can be used to move the servo.

## Licence

This project is distributed under a Creative Commons Share-alike 4.0 licence.
Please refer to section 5 of the licence for the "Disclaimer of Warranties and Limitation of Liability".
  
Enjoy!

**_Paul_**