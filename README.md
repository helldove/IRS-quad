# IRS-quad

This project is inteligent system quadrotor framework for embedded base linux with  odroid-c2

source-old : based beagle bone black (some function doesnt finished)
ForOdroid : working



pwm-driver : PWm on Odroid c2 supported 2-parallel function. but we need 4 at least. so we are going to use normal GPIO to PWM with kthread and jiffy 


20-7-2017  - working for PWM device driver (ForOdroid -> DeviceDriver -> dd_gpio.c)