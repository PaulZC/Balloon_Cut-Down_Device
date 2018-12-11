# Balloon Cut-Down Device Assembly Instructions

Here are the assembly instructions for V1 of the Balloon Cut-Down Device:

### Blank PCB

Start by having the blank PCBs manufactured. If you are based in the UK or Europe, I can recommend
[Multi-CB](https://www.multi-circuit-boards.eu/en/index.html) who can manufacture PCBs in 1-8 working days and
can process the Eagle .brd file direct - there's no need to generate Gerber files.

My recommended options are:
- Layers: 2 layers
- Format: single pieces
- Surface finish: chemical gold (ENIG)
- Material: FR4, 1.55mm
- Cu layers: 35um
- Solder stop: both sides, green
- Marking print: both sides, white

![Assembly_1](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_1.JPG)

### Add solder paste

Multi-CB can also provide you with a solder paste (SMD) stencil for the PCB. My recommended options are:
- SMD stencil for: **_bottom_** layer
- Make the Y dimension 20mm longer than the PCB itself to allow you to fix it down with tape
- Type: custom
- Pad reduction: yes, 10%
- Thickness: 100um
- Existing fiducials: lasered through
- Text type: half lasered
- Double-sided brushing: yes

Secure the blank PCB onto a flat work surface by locating it between two engineer's squares. I use a sheet of toughened glass
as the work surface as it is both very flat and easy to clean.

![Assembly_2](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_2.JPG)

Use the two round fiducials to line up the stencil with the PCB. Secure the stencil with tape.

![Assembly_3](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_3.JPG)

Apply solder paste close to the component cut-outs and then scrape the paste over the stencil using a knife blade
or a similar straight edge. Take appropriate safety precautions when working with solder paste - particularly if you are using
tin-lead solder instead of lead-free.

![Assembly_4](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_4.JPG)

![Assembly_5](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_5.JPG)

### Position the surface mount components

Position the components onto the blobs of solder paste using tweezers. A magnifier lamp or a USB microscope will
help you place the components in the correct position. U3 - the 5V regulator - is probably the trickiest
component to position. Take extra time to make sure it is centered accurately on the pads.

![Assembly_6](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_6.JPG)

![Assembly_7](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_7.JPG)

### Reflow the surface mount components

Use a reflow oven to heat the circuit board to the correct temperatures to melt the solder. A reflow oven doesn't need to be
expensive. The one shown below was assembled from:

- Quest 9L 800W mini-oven
- Inkbird PID temperature controller and 40A solid state relay
- Type K thermocouple

Several people have published good reflow oven construction guides, including [this one](http://www.die4laser.com/toaster/index.html).

![Assembly_8](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_8.JPG)

Use the correct temperature profile for your solder paste, but you won't go far wrong with 160C for four minutes, followed by
210C for one minute, followed by a cool-down with the door open. Use a flashlight to check that the solder has melted across
the whole PCB at 210C. Hold the temperature at 210C a little longer if some of the solder paste still appears 'gray' instead of 'silver'.

![Assembly_9](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_9.JPG)

All being well, your PCB should look like this:

![Assembly_10](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_10.JPG)

### Check for shorts

Carefully examine all the solder joints and correct any shorts you find.

The 'trick' to removing a short is to add more solder or solder paste and then to use
copper solder braid or wick to remove all the solder in one go.

### Install the bootloader

The SAMD21G18A processor now needs to be configured with a bootloader using a J-Link programmer or similar. See
[How do I install the ATSAMD21G18 Bootloader](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/Archive/V1/LEARN.md#how-do-i-install-the-atsamd21g18-bootloader)
for further details.

![Assembly_11](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_11.JPG)

### Add the non-surface mount components

The non-surface mount components (switches, LED, headers, battery clip) can now be positioned on the top of the PCB and soldered by hand.

![Assembly_12](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_12.JPG)

Use a cotton bud (q-tip) dipped in Iso-Propyl Alcohol (IPA / Propanol / rubbing alcohol) to remove any flux residue.

### Lacquer the PCB

I do recommend giving the PCB a coat of lacquer, especially if you are intending to use on a balloon flight.
Cover all of the surface mount components with [Acrylic Protective Lacquer (conformal coating)](https://uk.rs-online.com/web/p/conformal-coatings/3217324/)
taking care to avoid the IO pads.

![Assembly_13](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_13.JPG)

### Test the PCB

The [Arduino](https://github.com/PaulZC/Balloon_Cut-Down_Device/tree/master/Archive/V1/Arduino)
directory contains the Arduino code. Upload it using the Arduino IDE following the instructions
[here](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/Archive/V1/LEARN.md#how-do-i-upload-the-arduino-code)

The cut-down device spends most of its time in deep sleep, which means that the Arduino IDE won't recognise it as connected. If you want to reprogram
the board, either:
- press the reset button twice quickly, to put the processor into bootloader mode
or:
- press and hold down the plus or minus switch, the press the reset switch briefly, release the plus or minus switch when the LED goes out. This puts the
board into Set_Servo mode or Set_Duration mode where the processor is powered up continuously.

### Carbon Fibre Parts

The [Drawings](https://github.com/PaulZC/Balloon_Cut-Down_Device/tree/master/Archive/V1/Drawings)
directory contains the drawings for the carbon fibre base plate and trigger linkage. These parts could be made from aluminium or acrylic plastic, but for
use at high altitude I would recommend having them made from 3mm carbon fibre plate.

If you are based in the UK, I can recommend [Carbon Technology Ltd](http://www.carbontechnology.co.uk/) for the manufacture of these parts.

![Assembly_14](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_14.JPG)

### Mount The PCB

Mount the completed PCB on the base plate using:

- M3 x 16 Hex Drive Screw x 4 (McMaster 92095A184)
- 4.5mm OD, 5mm Long Spacer x 4 (McMaster 94669A099)
- M3 Nylon-Insert Locknut x 4 (McMaster 93625A100)
- M3 Washer x 4 (McMaster 90965A130)

**You will need to file the top off the M3 button head screws to allow the battery to sit correctly in the battery holder.**

![Assembly_15](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_15.JPG)

![Assembly_16](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_16.JPG)

### Mount The Servo

Mount the re-greased servo on the base plate using:

- M2.5 x 14 Hex Drive Screw x 2 (McMaster 91292A017)
- M2.5 Nylon-Insert Locknut x 2 (McMaster 93625A102)
- M2.5 Washer x 2 (McMaster 90965A115)

![Assembly_17](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_17.JPG)

![Assembly_18](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_18.JPG)

### Mount The Shark Release

Mount the Shark Release on the base plate using:

- 4-40 UNC x ¼” Socket Head Screw x 3 (McMaster 92196A106)

![Assembly_19](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_19.JPG)

![Assembly_20](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_20.JPG)

### Mount The Trigger Linkage

Fix the trigger linkage to the trigger block using:

- M3 x 4mm Dia x 4mm Long Shoulder Screw x 2 (McMaster 90323A211)

**Do not connect the trigger linkage to the servo arm with the second shoulder screw until the servo positions have been set!**

### Set The Servo Positions

Put the cut-down device into Set Servo mode and set the open and closed servo positions following the instructions
[here](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/Archive/V1/LEARN.md#set_servo)

![Assembly_21](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_21.JPG)

![Assembly_22](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_22.JPG)

![Assembly_23](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_23.JPG)

![Assembly_24](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_24.JPG)

### Attach The Trigger Linkage To The Servo

Attach the trigger linkage to the servo arm using the second shoulder screw and your cut-down device is ready to use!

![Assembly_25](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_25.JPG)

![Assembly_26](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_26.JPG)

![Assembly_27](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_27.JPG)

![Assembly_28](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Assembly_28.JPG)

### The Small Print

This project is distributed under a Creative Commons Attribution + Share-alike (BY-SA) licence.
Please refer to section 5 of the licence for the "Disclaimer of Warranties and Limitation of Liability".

Enjoy!

**_Paul_**