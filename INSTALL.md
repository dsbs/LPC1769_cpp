
There is nothing to install. But there are some requiremets for this software to
compile and run:

   - CodeSourcery (Sourcery G++ Lite 2011.03-42) 4.5.2 with compiler GNU toolchain for ARM
   - GNU Make 3.81 for makefile
   - Doxygen 1.72 for documentation generation
   - Open On-Chip Debugger 0.5.0-dev-00897-gae02a0e (2011-06-02-20:33) for flashing
   - libftdi-0.19 Open Source FTDI driver
   - libusb 0.1.8 Library for talking to USB devices from user-space. 
     Needed by libftdi, libusb-devel must be installed as well

If you are using Linux ( as we use Ubutu 11.04 ) additional action is required to get the access to USB (no needed for root)

   1. create file "45-ft2232-libftdi.rules"
   2. print in to the file following content:
      BUS=="usb", ACTION=="add", SUBSYSTEM!="usb_device", SYSFS{idProduct}=="baf8", SYSFS{idVendor}=="0403", MODE:="0666", GROUP:="users"
   3. move the file 45-ft2232-libftdi.rules under /etc/udev/rules.d 
   4. re-log

