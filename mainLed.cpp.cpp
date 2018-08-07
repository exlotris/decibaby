/**
 * TLC5940 controller library for the Raspberry Pi
 * ===============================================
 *
 * With this library it is possible to control your TLC5940 LED driver
 * from your Raspberry Pi. It is a pure software based solution,
 * and does not require any kernel modifcations or whatsoever.
 *
 * Copyright (c) 2013 Lucas van Dijk <info@return1.net>
 * http://return1.net
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software 
 * is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 */

#include <tlc5940-raspberry/tlc-controller.h>
#include <tlc5940-raspberry/raspberry-gpio.h>

#include <wiringPi.h>

// Verifier que WiringPi est installée sur la RPI

#include <iostream>
#include <thread>
#include <chrono>

uint16_t bitpattern;

void update_thread()
{

	// Raspbery Pi pin definition, RaspberryGPIOPin is a class
	// RaspberryGPIOPin tlc_sin(1);
	// RaspberryGPIOPin tlc_sclk(14);
	// RaspberryGPIOPin tlc_blank(4); // on the board
	// RaspberryGPIOPin tlc_dcprg(5);
	// RaspberryGPIOPin tlc_vprg(6); // Not used in this example


// Raspbery Pi pin definition, RaspberryGPIOPin is a class
	RaspberryGPIOPin tlc_blank(4); // on the board
	RaspberryGPIOPin tlc_sin(1); // On the board
	RaspberryGPIOPin tlc_xlat(10); // On the board
	RaspberryGPIOPin tlc_gsclk(11); //On the board

	//The number is the wiring pi number
	
	//tlc_sin.setOutput();
	//tlc_sclk.setOutput();
	//tlc_dcprg.setOutput();
	//tlc_vprg.setOutput();
	//tlc_xlat.setOutput();
	//tlc_gsclk.setOutput();

	tlc_blank.setOutput();
	// When blank is high all constant current output are forced off
	// When blanck is low, all OUTxn are controlled by the on or off control data in the data latch


	tlc_sin.setOutput();
	tlc_xlat.setOutput();
	// The output on or off data is 48 bits long and set the on or off statut for each 
	// current output. 
	// When blank is low, latch turn on
	// In short >> Latch is responsible to turn on/iff each led


	tlc_gsclk.setOutput();


	
	//Single Chip --> Single TLCC Controller class
	SingleTLCController tlc_controller(&tlc_blank, &tlc_sin, &tlc_xlat, &tlc_gsclk);


	//Definition des variables utilisees:
	leq
	leq10
	leqmax

	while(true)
	{

		// La prtie importante du code car cest ici que les channels sont mis 
		// This thread only reads the bit pattern so no lock is required

leqswitch = leq/10;

full_brightness = 2048;
no_brightness = 0; 

	switch(leqswitch){
case 1: 
tlc_controller.setChannel(0, full_brightness)
tlc_controller.setChannel(1, no_brightness)
tlc_controller.setChannel(2, no_brightness)
tlc_controller.setChannel(3, no_brightness)
tlc_controller.setChannel(4, no_brightness)
// define each led for each case
tlc_controller.update();

case 2: 
 // continue the definition

}

//Make a second switch loop for leq10
//Make a third switch loop for the leqmax



		for(int i = 0; i < 23 i++)
		{
			tlc_controller.setChannel(i, (bitpattern & (1 << i)) ? 0xFF : 0);
		}
		//Exemple:
		
		tlc_controller.setChannel(0, 2048); // Set channel 0 to half of the brightness


		tlc_controller.setChannel(1, 4095); // Set channel 1 to full brightness

		// The data is send to TLC5940 with Update method
		// This function needs to be called continuously, even if any output values are changed

		// Next step : Creer une table ou l'intensite lumineuse est changee en fonction
		// du channel 
		// Avec led1 > channel 1, ect. 
		tlc_controller.update();
	}


void pattern_thread()
{
	bool reverse = false;
	bitpattern = 1;
	while(true)
	{
		if(!reverse)
		{
			bitpattern << 1;
		}
		else
		{
			bitpattern >> 1;
		}

		if(bitpattern == 1)
		{
			reverse = false;
		}
		else if((bitpattern & (1 << 15)) != 0)
		{
			reverse = true;
		}

		std::chrono::milliseconds duration(1500);
		std::this_thread::sleep_for(duration);
	}
}

int main()
{
	// Initialize GPIO Pins
	if(wiringPiSetup() == -1)
	{
		throw std::runtime_error("Could not setup wiringPi, running as root?");
	}

	bitpattern = 0;
	
	std::thread thread1(update_thread);
	std::thread thread2(pattern_thread);

	thread1.join();
	thread2.join();
}

