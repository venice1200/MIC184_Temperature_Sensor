// ******************************************************************************
// 
// Arduino Library for the MIC184 Temperatur Sensor by venice (c) 2021
// 
// Library based on the LM75 Libray (C) by Elektronik Hannes Jochriem, Germany
// See https://github.com/ehajo/LM75B
// 
// Licensed under the MIT-license, see LICENSE.txt for further information.
//
// ******************************************************************************


#include "MIC184.h"


// ***************************
// 
// Constructor

MIC184::MIC184()
{	// Set standard address
	_MIC184_address = MIC184_BASE_ADDRESS;
}

// ***************************
// 
// public stuff

float MIC184::getTemp()
{	// get the temperature from the device
	uint16_t t;
	t = read16bit(MIC184_REGISTER_TEMP);
	return (float)t / 256.0f;
}

float MIC184::CtoF(float temperatureC)
{	// convert to Fahrenheit for "who the hell still use this?"
	return (temperatureC * 1.8f) + 32.0f;
}

void MIC184::setAddress(uint8_t bit_A0, uint8_t bit_A1, uint8_t bit_A2)
{	// Change address according to A0-A2 set on PCB
	_MIC184_address = MIC184_BASE_ADDRESS | ((bit_A0 & 0b00000001)<<0) | ((bit_A1 & 0b00000001)<<1) | ((bit_A2 & 0b00000001)<<2);
}

void MIC184::setMode(MIC184_opmode opmode)
{	// send the lil SO-8 to bed or wake him up
	uint8_t t = getConfRegister() & ~(MIC184_MODE_SHUTDOWN);
	setConfRegister(t | opmode);
}

void MIC184::setOSMode(MIC184_OS_opmode opmode)
{	// define the OS-pin mode as INT or COMP
	uint8_t t = getConfRegister() & ~(MIC184_OS_INTERRUPT);
	setConfRegister(t | opmode);
}

void MIC184::setTOSPolarity(MIC184_TOSPolarity polarity)
{	// Set if OSpin is high or low on TOS
	uint8_t t = getConfRegister() & ~(MIC184_OSPOL_HIGH);
	setConfRegister(t | polarity);
}

void MIC184::setOSFaultQueue(MIC184_OS_Fault_queue numberfaults)
{	// Set how many faults must occur to set OS-output
	uint8_t t = getConfRegister() & ~(MIC184_FAULTS_6);
	setConfRegister(t | numberfaults);
}
	
void MIC184::setZONE(MIC184_zone zone)
{	// Set temperatur selection Zone to internal (0) or remote (1)
	uint8_t t = getConfRegister();                   // Read Config
	setConfRegister(t | MIC184_IM_Set);                // Set IM Bit
	t = getConfRegister() & ~(MIC184_ZONE_REMOTE);     // Read Config and clear Zone Bit
	setConfRegister(t | zone);                       // Write Config with Zone Value
	t = getConfRegister() & ~(MIC184_IM_Set);          // Read Config and Clear IM Bit
	setConfRegister(t);                              // Write Config with Cleared Bits
}
	
float MIC184::getTOS()
{	// Get Overtemperature shutdown Register
	uint16_t t;
	t = read16bit(MIC184_REGISTER_TOS);
	return (float)t / 256.0f;
}

void MIC184::setTOS(float temperature)
{
	write16bit(MIC184_REGISTER_TOS, (uint16_t)(temperature*256.0));
}

float MIC184::getHyst()
{	// Get Hysteresis temperature register
	uint16_t t;
	t = read16bit(MIC184_REGISTER_THYST);
	return (float)t / 256.0f;
}

void MIC184::setHyst(float temperature)
{
	write16bit(MIC184_REGISTER_THYST, (uint16_t)(temperature*256.0));
}
	
// ***************************
// 
// private stuff

uint8_t MIC184::read8bit(uint8_t address)
{
	Wire.beginTransmission(_MIC184_address);
	Wire.write(address);
	Wire.endTransmission();
	Wire.requestFrom(_MIC184_address, (uint8_t)1);
	return Wire.read();
}

uint16_t MIC184::read16bit(uint8_t address)
{
	Wire.beginTransmission(_MIC184_address);
	Wire.write(address);
	Wire.endTransmission();
	
	Wire.requestFrom(_MIC184_address, (uint8_t)2);
	uint16_t t = Wire.read() << 8;
	t |= Wire.read();
	return t;
}

void MIC184::write16bit(uint8_t address, uint16_t value)
{
	Wire.beginTransmission(_MIC184_address);
	Wire.write(address);
	Wire.write((uint8_t)((value & 0xff00) >> 8));
	Wire.write((uint8_t)(value & 0x00ff));
	Wire.endTransmission();
}

void MIC184::write8bit(uint8_t address, uint8_t value)
{
	Wire.beginTransmission(_MIC184_address);
	Wire.write(address);
	Wire.write(value);
	Wire.endTransmission();
}

uint8_t MIC184::getConfRegister()
{
	return read8bit(MIC184_REGISTER_CONF);
}

void MIC184::setConfRegister(uint8_t conf)
{
	write8bit(MIC184_REGISTER_CONF, conf);
}