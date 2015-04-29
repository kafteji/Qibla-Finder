# Project : Qibla Finder
# Author : Fahmi Ghediri
#Date : 04-29-2015


this Solution offers the possibility of detecting the Qibla direction based on the user's geographical location retrieved by the sim68v GPS module.

this project has 2 main parts :

1- the first part is executed on the STM32F3-Discovery Board.
It detects the north direction, retrieves the user's longitude and latitude and then sends the collected data via a serial communication over a bluetooth link to the laptop to be processed.

2- the second part is a little Qt application. It receives data from the STM32 board and calculates the Qibla's direction, then it sends the specified direction to the STM32 to be displayed with a blinking LED.

3- Hardware Components :

	- STM32 F303 Discovery.

	- SIM68v GPS Module.
	
	- HC-05 Bluetooth Module.


Regards !!