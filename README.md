
Requirements:

Platform: FRDM-KL25Z

Libraries: frdm_bsp.h, lcd1602.h, stdio.h, i2c.h

Installation and Execution Instructions:

Set up the development environment for the FRDM-KL25Z platform, such as Keil uVision or others.

Add the required libraries to the project.

Connect the FRDM-KL25Z device to the computer using a USB cable.

Compile and flash the program onto the microcontroller.

Functions:

Initializes the LCD screen and I2C0 port.

Sets the sensitivity of the accelerometer to 2g, 4g, or 8g.

Monitors motion and counts steps and runs.

Displays the current number of steps and runs on the LCD screen.

Operation:

The program uses the accelerometer to monitor motion. Upon detecting motion, it starts counting steps and runs. The current number of steps and runs is displayed on the LCD screen.
