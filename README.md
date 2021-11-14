# Arduino library for the MIC184 Temperature Sensor

Library based on the LM75 Libray by Elektronik Hannes Jochriem, Germany
See https://github.com/ehajo/LM75B

Please see examples for further usage of it.

# License

(C) 2021 venice

This library is open source and released under *[MIT license](LICENSE.txt)*. Please see this file for further information.

# MIC184

The chip communicates via I2C and converts the temperature every 10ms in 11bit resolution (0.125°).
The standard I2C address is 0x48, you can configure three bits (A0, A1, A2) on the Addon-Board to use up to 7 boards.
This gives an extended Address range of:
Binary: 0 1 0 0  1 A2 A1 A0
Hex: 0x48 to 0x4F

# Power-up condition

After power-up following register settings are default:
 - Normal operation mode
 - OS comparator mode
 - T<sub>th(ots)</sub> = 80°C
 - T<sub>hys</sub> = 75°C
 - OS output active state is *LOW*
 - Pointer value is logic 00 (Temp)

# Functions in the library

## void setAddress(uint8_t bit_A0, uint8_t bit_A1, uint8_t bit_A2)

Set the address if you use something different for A0-A2
	
## float getTemp()

Returns the temperature as float value in °C.

## float CtoF(float temperatureC)

You can use this to convert the temperature from °C to °F (I have no idea why you should to this...)

## float getTOS()

Returns the Temperature overshoot temperature stored in the Tos-register.

## void setTOS(float temperature)

Sets the Temperature overshoot temperature. This register is compared with the temp-register after each conversion to set OS-pin.

## float getHyst()

Returns the Hysteresis temperature stored in Thyst-register

## void setHyst(float temperature)

Sets the Hysteresis temperature register. This register is compared after each conversion, if temp-register < Thyst than OS-pin is set.

## void setMode(MIC184_opmode opmode)

This is used to send the device in Shutdown-mode. 
Available MIC184_opmodes are:
 - MIC184_MODE_NORMAL (default)
 - MIC184_MODE_SHUTDOWN

## void setOSMode(MIC184_OS_opmode opmode)

The OS-opmode defines how the device handles Tos and Thyst events. 
Available MIC184_OS_opmodes are:
 - MIC184_OS_COMPARATOR (default)
 - MIC184_OS_INTERRUPT
 
## void setTOSPolarity(MIC184_TOSPolarity polarity)

Defines if the polarity of OS-pin is high or low after TOS-event.
Available MIC184_TOSPolarities are:
 - MIC184_OSPOL_LOW (default)
 - MIC184_OSPOL_HIGH

## void setOSFaultQueue(MIC184_OS_Fault_queue numberfaults)

The fault queue is defined as the number of faults that must occur consecutively to activate the OS output.
Availabel MIC184_OS_Fault_queues are:
 - MIC184_FAULTS_1
 - MIC184_FAULTS_2
 - MIC184_FAULTS_4
 - MIC184_FAULTS_6