# Balloon Cut-Down Device Assembly Instructions

Here are the assembly instructions for V3 of the Balloon Cut-Down Device:

### Blank PCB

The [Eagle](https://github.com/PaulZC/Balloon_Cut-Down_Device/tree/master/Eagle) directory contains the schematic and pcb design files.

Start by having the blank PCBs manufactured. If you are based in the UK or Europe, I can recommend
[Multi-CB](https://www.multi-circuit-boards.eu/en/index.html) who can manufacture PCBs in 1-8 working days and
can process the Eagle .brd file direct - there's no need to generate Gerber files.

![V3_Assembly_1](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Assembly_1.JPG)

The PCB and trigger linkage are incorporated into a single board. The design includes two score lines which Multi-CB
will machine into the board if you ask them to, allowing the trigger linkage to be easily snapped off.

![V3_Assembly_2](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Assembly_2.JPG)

My recommended options are:
- Layers: 2 layers
- Format: Panel
- Panel Type: Multiplier
- Mechanical treatment: Milled and Scored
- Panelization: Yes, by Multi-CB
- Panel size (x/y): 66.04 X 109.22 mm
- Piece size (x/y): 66.04 X 109.22 mm
- PCBs / x-, y-Axis: 1 X 1 Pieces
- Surface finish: Chemical gold (ENIG)
- Material: FR4, 1.55mm
- Cu layers: 35um
- Solder stop: both sides, green
- Marking print: both sides, white
- **Comments: VSCORE data is in layer 148**

![Multi-CB_Panelization](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/Multi-CB_Panelization.JPG)

To allow the cut-down to handle higher loads, you could select 3.2mm FR4 instead of 1.55mm.

### Add solder paste

Multi-CB can also provide you with a solder paste (SMD) stencil for the PCB. You will find the Eagle PCB file for the paste mask in the
[Eagle](https://github.com/PaulZC/Balloon_Cut-Down_Device/tree/master/Eagle) directory. My recommended options are:
- SMD stencil for: top layer
- Size (x/y): 33.02 X 92.71 mm
- Type: custom
- Pad reduction: yes, 10%
- Thickness: 100um
- Existing fiducials: lasered through
- Text type: half lasered
- Double-sided brushing: yes

Secure the blank PCB onto a flat work surface by locating it between two engineer's squares. I use a sheet of toughened glass
as the work surface as it is both very flat and easy to clean.

![V3_Assembly_3](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Assembly_3.JPG)

Use the two round fiducials to line up the stencil with the PCB. Secure the stencil with tape.

![V3_Assembly_4](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Assembly_4.JPG)

Apply solder paste close to the component cut-outs and then scrape the paste over the stencil using a knife blade
or a similar straight edge. Take appropriate safety precautions when working with solder paste - particularly if you are using
tin-lead solder instead of lead-free.

![V3_Assembly_5](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Assembly_5.JPG)

![V3_Assembly_6](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Assembly_6.JPG)

### Position the surface mount components

Position the components onto the blobs of solder paste using tweezers. A magnifier lamp or a USB microscope will
help you place the components in the correct position. IC5 - the 5V regulator - is probably the trickiest
component to position. Take extra time to make sure it is centered accurately on the pads.

![V3_Assembly_7](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Assembly_7.JPG)

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

All being well, your PCB should look like this:

![V3_Assembly_8](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Assembly_8.JPG)

### Check for shorts

Carefully examine all the solder joints and correct any shorts you find.

The 'trick' to removing a short is to add more solder or solder paste and then to use
copper solder braid or wick to remove all the solder in one go.

### Add the non-surface mount components

The non-surface mount components (switches, SMA connector, 3-pin header, battery clips) can now be positioned and soldered by hand.

![V3_Assembly_9](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Assembly_9.JPG)

![V3_Assembly_10](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Assembly_10.JPG)

Use a cotton swab dipped in Iso-Propyl Alcohol (IPA / Propanol / rubbing alcohol) to remove any flux residue.

### Mount The Shark Release

Mount the Shark Release on the base plate using:

- 4-40 UNC x ¼” Socket Head Screw x 3 (McMaster 92196A106)

![V3_Assembly_11](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Assembly_11.JPG)

![V3_Assembly_12](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Assembly_12.JPG)

### Mount The Servo

Mount the re-greased servo on the base plate using:

- M2.5 x 14 Hex Drive Screw x 2 (McMaster 91292A017)
- M2.5 Nylon-Insert Locknut x 2 (McMaster 93625A102)
- M2.5 Washer x 2 (McMaster 90965A115)

**Do not install the servo arm on the servo until the device is in Set_Servo mode and the servo has moved to its mid-range position.**

![V3_Assembly_13](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Assembly_13.JPG)

![V3_Assembly_14](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Assembly_14.JPG)

### Configure the eRIC

The eRIC will come pre-programmed with easyRadio V1.5.5. This needs to be replaced with the custom code which you will find in the
[eRIC directory](https://github.com/PaulZC/Balloon_Cut-Down_Device/tree/master/eRIC).

You can find the datasheet for the eRIC on the LPRS website:
- http://www.lprs.co.uk/products/easyradio-ism-modules/eric-soc-rf-modules.html
- http://www.lprs.co.uk/assets/files/eRIC4_9_Datasheet_1.34.pdf

Download and install the latest version of the easyRadio Companion:
- http://www.lprs.co.uk/development-tools/easyradio-evaluation-software.html
- http://www.lprs.co.uk/assets/files/easyRadiosetup%204.1.6.exe

If possible, use an FTDI TTL-232R-3V3 cable to reconfigure the board, although a TTL-232R-5V will work too.
- https://www.ftdichip.com/Products/Cables/USBTTLSerial.htm

Plug the 6-Way connector of the FTDI cable onto one end of an 8-way length of double-height 0.1" header strip. Leave the cable USB connector unconnected for now.

![V3_Assembly_15](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Assembly_15.JPG)

Insert the header strip through the holes in the PCB and then lean the header strip against the side of the holes to ensure good electrical contact. Now plug
the FTDI USB connector into your computer. The LED should be flashing once per second; if it is lit continuously ensure you do not have a jumper link connecting
the two "Boot" pads together. If required, press the Reset button to restart the eRIC.

Start the easyRadio Companion. Registering the software is recommended but is optional. Click on the "eRIC" button. Select the COM port for the FTDI
cable in the UART Settings, then click "Open Port".

Ensure the "Settings" vertical tab is selected.

Click on the "Module Info" horizontal tab. Click on "Discover Module". Wait for all of the module information to be collected. Make a note of the eight digit
eRIC serial number; you will need this to be able to trigger the cut-down. Ideally, print the serial number onto a label and stick it onto the eRIC.

![easyRadio_1.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/easyRadio_1.JPG)

Place a jumper link to link the two "Boot" header pins together; then press the Reset button to place the eRIC into bootloader mode. The LED should light up
continuously. If the LED is still flashing once per second, ensure you have the jumper link installed correctly. If required, press the Reset button to restart
the eRIC.

Click on the "Firmware Upgrades" horizontal tab. Click on "Open Firmware File" and browse to the eRIC4_Servo_CutDown_V3.hex file which you will find in the
[eRIC directory](https://github.com/PaulZC/Balloon_Cut-Down_Device/tree/master/eRIC). Select eRIC9_Servo_CutDown_V3.hex instead if you are using the 868 / 915MHz
eRIC9.

Leave "Enable Code Protect" selected and then click "Upgrade".

All being well, you should see a green progress bar followed by the message "Firmware Update Complete!".

![easyRadio_2.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/easyRadio_2.JPG)

Disconnect the FTDI USB connector from your computer, then remove the header strip.

### Making Changes to the eRIC Code

If you want to alter the programming of the eRIC, you will need to:
- Follow the instructions in http://www.lprs.co.uk/assets/files/Custom%20programming%20eRIC.zip
- Install the Texas Instruments Code Composer Studio
- Copy and unzip the eRIC_Servo_CutDown_V3.zip from the [eRIC directory](https://github.com/PaulZC/Balloon_Cut-Down_Device/tree/master/eRIC) into the Code Composer workspace directory
- Right-click in the Project Explorer window, select "Import" then "CCS Projects"
- Select the folder which you unzipped eRIC_Servo_CutDown_V3 into

You can now make alterations to the code, rebuild the project to produce a new .hex file and then use the easyRadio Companion to programme the eRIC with the new code.

### Lacquer the PCB

I do recommend giving the PCB a coat of lacquer, especially if you are intending to use on a balloon flight.
Cover all of the surface mount components with [Acrylic Protective Lacquer (conformal coating)](https://uk.rs-online.com/web/p/conformal-coatings/3217324/)
taking care to avoid the IO pads and push switches.

![V3_Assembly_nn](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Assembly_nn.JPG)

### Attach The Trigger Linkage

Fix the trigger linkage to the trigger block using:

- M3 x 4mm Dia x 4mm Long Shoulder Screw x 2 (McMaster 90323A211)

**Do not connect the trigger linkage to the servo arm with the second shoulder screw until the servo positions have been set**

### Attach the Battery

![V3_Assembly_16](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Assembly_16.JPG)

### Move the Servo to Mid-Range

Before attaching the servo arm, move the servo to its mid-range position by putting the cut-down into Set_Servo mode:
- Push and hold the PLUS switch
- Press and release the RESET switch
- Release the PLUS switch

You should hear the servo move to mid-range.

### Disconnect the Battery

### Attach the Servo Arm

Attach the servo arm, securing it with both the socket cap screw and cross-head screw.

### Reattach the Battery

### Set the Servo Positions

Put the cut-down device into Set_Servo mode and set the open and closed servo positions following the instructions
[here](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/CONFIGURE.md#set_servo)

![V3_Set_Servo_1](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Set_Servo_1.JPG)

![V3_Set_Servo_1a](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Set_Servo_1a.JPG)

![V3_Set_Servo_2](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Set_Servo_2.JPG)

![V3_Set_Servo_2a](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Set_Servo_2a.JPG)

### Attach The Trigger Linkage To The Servo

Attach the trigger linkage to the servo arm using the second shoulder screw and your cut-down device is ready to use!

![V3_Set_Servo_3](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Set_Servo_3.JPG)

### The Small Print

This project is distributed under a Creative Commons Attribution + Share-alike (BY-SA) licence.
Please refer to section 5 of the licence for the "Disclaimer of Warranties and Limitation of Liability".

Enjoy!

**_Paul_**