# Servo Modification

The Balloon Cut-Down Device uses a [HiTec HS-82MG servo](https://www.servoshop.co.uk/index.php?pid=HITHS82MG&area=Servo) to operate the
[Scott Archery Shark release aid](https://scottarchery.com/collections/releases/products/shark-release). These servos are lightweight and provide high torque
for their size. But, to allow them to operate reliably at high altitude (low pressure) and low temperature, the standard grease inside the servo needs to be
replaced and lacquer needs to be applied to the internal circuit board.

![Servo_1](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Servo_1.JPG)

![Servo_2](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Servo_2.JPG)

### Set the Servo to Mid-Range

When you connect the servo to a freshly-programmed cut-down device circuit board, the circuit board will move the servo to its mid-range position.
The servo position is set by a Pulse Width Modulation (PWM) signal on the yellow wire. A pulse width of 1.5msec (1500usec) repeating every 20msec (50Hz)
will set the servo to mid-range. It is important you do this as it will help you relocate the half-moon output gear in the correct position.

You can see how the PWM pulse width causes the servo position to change in the following three images:

- Pulse Width 900usec (0.9msec)

![Servo_7](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Servo_7.JPG)

- Pulse Width 1500usec (1.5msec)

![Servo_9](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Servo_9.JPG)

- Pulse Width 2100usec (2.1msec)

![Servo_8](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Servo_8.JPG)

You can also use the [Serial_Servo](https://github.com/PaulZC/Balloon_Cut-Down_Device/tree/master/Archive/V1/Arduino/Serial_Servo) sketch to position the servo
in the correct position. This code is designed to run on the Cut-Down Device, but it will also work on an Adafruit Feather M0 or M0 Adalogger.
I haven't tested it, but it should work on the Arduino Zero too. Connect: the servo red wire to USB/VBUS (5V);
the servo black wire to GND; the servo yellow (PWM) wire to D5. The Feather must be powered via USB (5V) for reliable servo operation.

### Remove the Screws

Remove the four screws which hold the servo case parts together. You will need a good quality Philips size OO screwdriver
such as the [Wiha PicoFinish 261 P 512](http://uk.farnell.com/wiha/2610040/screwdriver-phillips-no-00x40mm/dp/282303).

![Servo_3](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Servo_3.JPG)

![Servo_4](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Servo_4.JPG)

### Remove the Standard Grease

Using several [cotton-buds, Q-tips or swabs](https://www.thorlabs.de/thorproduct.cfm?partnumber=CTA10), remove the standard grease from the top part
of the servo housing. Be careful not to leave any cotton strands behind.

![Servo_5](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Servo_5.JPG)

![Servo_6](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Servo_6.JPG)

Carefully remove the four gears, one at at time, and wipe the grease from each of them using [lint-free lens tissue](https://www.thorlabs.de/thorproduct.cfm?partnumber=MC-5).

![Servo_10](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Servo_10.JPG)

### Observe the Output Shaft Position

Once the grease is removed, you will be able to observe the flat on the output shaft. The half-moon output gear has a matching flat to locate it
precisely on the shaft.

![Servo_11](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Servo_11.JPG)

### Servo Electronics

Take a look at the servo electronics: PCB with driver IC and push-pull transistors; output shaft position-sensing potentiometer; and DC motor. I do recommend
giving both sides of the driver PCB a coat of lacquer, especially if you are intending to use it at altitude. Cover all of the PCB components with a layer of
[Acrylic Protective Lacquer (conformal coating)](https://uk.rs-online.com/web/p/conformal-coatings/3217324/) between and around the glue HiTec have applied
to the servo wiring. Let the coating dry before you reassemble the servo.

![Servo_12](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Servo_12.JPG)

![Servo_13](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Servo_13.JPG)

![Servo_13a](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Servo_13a.JPG)

The servo works by responding to the incoming PWM signal. The motor is driven in one direction or the other by the push-pull driver, until the potentiometer
senses that the output shaft is in the desired position.

### Apply Space Grease

Apply a little Castrol Braycote 601 EF grease to the teeth on all four gears plus the small gear on the motor shaft. Braycote 601 EF is a low temperature (-80C),
low outgassing, non-flammable, non-toxic grease which is approved by NASA. It is expensive, but you are only going to use a very small amount modifying each servo.

![Servo_14](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Servo_14.JPG)

### Reassemble

Reassemble the four gears onto the two shafts taking care to match the half-moon output gear with the flat on the output shaft.

Close the case and reinsert the four screws. Do not over-tighten the screws. Label the servo to indicate that the grease has been replaced.

![Servo_15](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Servo_15.JPG)


Modifying the servo will of course void your warranty.

This project is distributed under a Creative Commons Attribution + Share-alike (BY-SA) licence.
Please refer to section 5 of the licence for the “Disclaimer of Warranties and Limitation of Liability”.

Enjoy!

**_Paul_**