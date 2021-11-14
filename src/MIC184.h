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

#ifndef MIC184_H
#define MIC184_H

#include <Arduino.h>
#include <Wire.h>

#define MIC184_BASE_ADDRESS 0x48			// Base address 0b 1 0 0 1 A2 A1 A0
#define MIC184_REGISTER_TEMP			0	// Temperatur store register (RO)
#define MIC184_REGISTER_CONF			1	// Config register
#define MIC184_REGISTER_THYST			2	// Hysteresis register
#define MIC184_REGISTER_TOS				3	// Overtemperature shutdown register

#define MIC184_CONF_OS_COMP_INT			1	// OS operation mode selection
#define MIC184_CONF_OS_POL				2	// OS polarity selection
#define MIC184_CONF_OS_F_QUE			3	// OS fault queue programming

enum MIC184_OS_opmode : uint8_t
{
	MIC184_OS_COMPARATOR = (0<<1),
	MIC184_OS_INTERRUPT = (1<<1)
};

enum MIC184_OS_Fault_queue : uint8_t
{
	MIC184_FAULTS_1 = (0<<3),
	MIC184_FAULTS_2 = (1<<3),
	MIC184_FAULTS_4 = (2<<3),
	MIC184_FAULTS_6 = (3<<3)
};

enum MIC184_TOSPolarity : uint8_t
{
	MIC184_OSPOL_LOW =  (0<<2),
	MIC184_OSPOL_HIGH = (1<<2)
};

enum MIC184_opmode : uint8_t
{
	MIC184_MODE_NORMAL = 0,
	MIC184_MODE_SHUTDOWN = 1
};

enum MIC184_zone : uint8_t
{
	MIC184_ZONE_INTERNAL = (0<<5),
	MIC184_ZONE_REMOTE   = (1<<5)
};

enum MIC184_IM : uint8_t
{
	MIC184_IM_Clear = (0<<6),
	MIC184_IM_Set   = (1<<6)
};

class MIC184
{
	// private stuff
	uint8_t _MIC184_address;
	uint8_t read8bit(const uint8_t address);
	uint16_t read16bit(const uint8_t address);
	void write16bit(const uint8_t address, const uint16_t value);
	void write8bit(const uint8_t address, const uint8_t value);
	uint8_t getConfRegister();
	void setConfRegister(uint8_t conf);

public:
	// constructor
	MIC184();
	
	// public stuff
	
	// I2C
	void setAddress(uint8_t bit_A0, uint8_t bit_A1, uint8_t bit_A2);
	
	// temperatures
	float getTemp();
	float CtoF(float temperatureC);
	float getTOS();
	void setTOS(float temperature);
	float getHyst();
	void setHyst(float temperature);
	void setOSFaultQueue(MIC184_OS_Fault_queue numberfaults);

	
	// config register stuff:
	void setMode(MIC184_opmode opmode);
	void setOSMode(MIC184_OS_opmode opmode);
	void setTOSPolarity(MIC184_TOSPolarity polarity);
	void setZONE(MIC184_zone zone);
//	uint8_t getConfRegister();
//	void setConfRegister(uint8_t conf);
	
};

#endif // MIC184
