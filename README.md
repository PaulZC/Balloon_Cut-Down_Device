# Balloon_Cut-Down_Device


A cut-down device suitable for use on High Altitude Balloons and other remote actuation projects.

![V3_Cut-Down_Device.gif](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Cut-Down_Device.gif)

![V3_Cut-Down_Device_1.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Cut-Down_Device_1.JPG)

![V3_Cut-Down_Device_2.JPG](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/img/V3_Cut-Down_Device_2.JPG)

Designed to be triggered by the [Iridium Beacon Radio Board](https://github.com/PaulZC/Iridium_Beacon_Radio_Board),
carried by the [Iridium 9603N V5 Beacon](https://github.com/PaulZC/Iridium_9603_Beacon), the cut-down will be triggered
when it receives its own (unique) serial number on the chosen radio channel. The number of cut-downs that could be
triggered by a single Iridium Beacon is essentially unlimited. The cut-down can also be configured to trigger at
a pre-defined altitude.

The device comprises:
- [Scott Archery Shark release aid](https://scottarchery.com/collections/releases/products/shark-release), actuated by a
- [HiTec HS-82MG servo](https://www.servoshop.co.uk/index.php?pid=HITHS82MG&area=Servo), controlled by the
- [LPRS eRIC4 or eRIC9 integrated radio module](http://www.lprs.co.uk/products/easyradio-ism-modules/eric-soc-rf-modules.html).
- The altitude is provided by a [u-blox CAM-M8Q GNSS receiver](https://www.u-blox.com/en/product/cam-m8-series)

See [LEARN.md](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/LEARN.md) for further details.

See [SERVO.md](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/SERVO.md) for details on how to modify the HiTec servo for
high altitude operation.

See [SHARK.md](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/SHARK.md) for details on how to incorporate the Scott Archery Shark release aid
into the Cut-Down Device.

See [ASSEMBLY.md](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/ASSEMBLY.md) for details on how to assemble the PCB and the device itself.

See [CONFIGURE.md](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/CONFIGURE.md) for details on how to configure the servo positions and altitude limit.

See [Balloon_Cut-Down_Device.pdf](https://github.com/PaulZC/Balloon_Cut-Down_Device/blob/master/Balloon_Cut-Down_Device.pdf) for the schematic,
layout and Bill Of Materials.

The [Eagle](https://github.com/PaulZC/Balloon_Cut-Down_Device/tree/master/Eagle) directory contains the schematic and pcb design files.

The [eRIC](https://github.com/PaulZC/Balloon_Cut-Down_Device/tree/master/eRIC) directory contains the code for the eRIC integrated radio module.

The [Drawings](https://github.com/PaulZC/Balloon_Cut-Down_Device/tree/master/Drawings) directory contains the drawings for the trigger linkage.

This project is distributed under a Creative Commons Attribution + Share-alike (BY-SA) licence.
Please refer to section 5 of the licence for the "Disclaimer of Warranties and Limitation of Liability".

Enjoy!

**_Paul_**