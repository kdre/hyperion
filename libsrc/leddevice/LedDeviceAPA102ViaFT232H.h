// Author: Klaus Drechsler, drechsler ( at ) gmx.net

#pragma once

// hyperion incluse
#include "LedFT232HDevice.h"

// libmpsse includes
#include <mpsse.h>

///
/// Implementation of the LedDevice interface for writing to APA102 led device.
///
/// APA102ViaFT232H
///
class LedDeviceAPA102ViaFT232H : public LedFT232HDevice
{
public:
	///
	/// Constructs the LedDevice for a string containing leds of the type APA102
	///
	/// @param[in] mode The mode of the FT232H device (e.g. SPI0-SPI3, ...)
	/// @param[in] freq The clock frequency
	/// @param[in] endianess The endianess of the data: MSB or LSB
	///
	LedDeviceAPA102ViaFT232H(const enum modes mode, const int freq, const int endianess, const unsigned ledcount );

	///
	/// Writes the led color values to the led-device
	///
	/// @param ledValues The color-value per led
	/// @return Zero on succes else negative
	///
	virtual int write(const std::vector<ColorRgb> &ledValues);

	/// Switch the leds off
	virtual int switchOff();

private:

	/// The buffer containing the packed RGB values
	std::vector<uint8_t> _ledBuffer;
	unsigned int _HW_ledcount;
	unsigned int _mLedCount;

};
