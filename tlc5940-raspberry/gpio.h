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

#ifndef GPIO_H_
#define GPIO_H_

#include <cstdint>

enum class PinDirection : std::uint8_t
{
	IN = 0,
	OUT
};

enum class PinValue : std::uint8_t
{
	LOW = 0,
	HIGH
};

/**
 * This is an abstract base class for GPIO pins.
 * 
 * Subclasses should allow control of a specific GPIO pin, suitable
 * for the used processor.
 */
class BaseGPIOPin
{
	public:
		virtual void open() = 0;
		virtual void close() = 0;
		virtual bool is_open() = 0;
		
		virtual void setDirection(PinDirection direction) = 0;
		virtual PinDirection getDirection() = 0;

		// Some shortcuts
		virtual void setOutput();
		virtual void setInput();

		virtual void setValue(PinValue value) = 0;
		virtual PinValue getValue() = 0;

		// For the value also some shortcuts
		virtual void setHigh();
		virtual void setLow();
		
		virtual inline void pulse() 
		{
			this->setHigh();
			this->setLow();
		}
};

#endif
