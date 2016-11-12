// Author: Klaus Drechsler, drechsler ( at ) gmx.net

#pragma once

// Hyperion includes
#include <leddevice/LedDevice.h>

// libmpsse includes
#include <mpsse.h>

///
/// The LedFT232HDevice implements an abstract base-class for LedDevices using the FT232H-device.
///
class LedFT232HDevice : public LedDevice
{

public:
	///
	/// Constructs the LedDevice attached to a FT232H-device
	///
	/// @param[in] mode The mode of the FT232H device (e.g. SPI0-SPI3, ...)
	/// @param[in] freq The clock frequency
	/// @param[in] endianess The endianess of the data: MSB or LSB
	///	
	LedFT232HDevice(enum modes mode, int freq, int endianess);

	///
	/// Destructor of the LedDevice; closes the output device if it is open
	///
	virtual ~LedFT232HDevice();

	///
	/// Opens and configures the output device
	///
	/// @return Zero on succes else negative
	///
	int open();

protected:
	///
	/// Writes the given bytes/bits to the FT232H-device
	///
	/// @param[in[ size The length of the data
	/// @param[in] data The data
	///
	/// @return Zero on succes else negative
	///
	int writeBytes(const unsigned size, const uint8_t *data);	

private:
	/// The name of the output device
	const enum modes mMode;
	/// The clock frequency
	const int mFreq_Hz;
	/// The endianess
	const int mEndianess;

	/// The File Identifier of the opened output device (or -1 if not opened)
	struct mpsse_context *mContext;	
};