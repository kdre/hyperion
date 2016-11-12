// Author: Klaus Drechsler, drechsler ( at ) gmx.net

#include "LedDeviceAPA102ViaFT232H.h"

LedDeviceAPA102ViaFT232H::LedDeviceAPA102ViaFT232H(const enum modes mode, const int freq, const int endianess, const unsigned ledcount ) :
	LedFT232HDevice(mode, freq, endianess),
	_ledBuffer(0)
{
	_HW_ledcount = ledcount;
}

int LedDeviceAPA102ViaFT232H::write(const std::vector<ColorRgb> &ledValues)
{
	_mLedCount = ledValues.size();
	const unsigned int max_leds = std::max(_mLedCount, _HW_ledcount);
	const unsigned int startFrameSize = 4;
	const unsigned int endFrameSize = std::max<unsigned int>(((max_leds + 15) / 16), 4);
	const unsigned int APAbufferSize = (max_leds * 4) + startFrameSize + endFrameSize;

	if(_ledBuffer.size() != APAbufferSize){
		_ledBuffer.resize(APAbufferSize, 0xFF);
		_ledBuffer[0] = 0x00; 
		_ledBuffer[1] = 0x00; 
		_ledBuffer[2] = 0x00; 
		_ledBuffer[3] = 0x00; 
	}
	
	unsigned iLed=0;
	for (iLed=0; iLed < _mLedCount; ++iLed) {
		const ColorRgb& rgb = ledValues[iLed];
		_ledBuffer[4+iLed*4+0] = (0xe0+0x1f);
		_ledBuffer[4+iLed*4+1] = rgb.red;
		_ledBuffer[4+iLed*4+2] = rgb.green;
		_ledBuffer[4+iLed*4+3] = rgb.blue;
	}

	for ( ; iLed < max_leds; ++iLed) {
		_ledBuffer[4+iLed*4+0] = (0xe0+0x1f);
		_ledBuffer[4+iLed*4+1] = 0x00;
		_ledBuffer[4+iLed*4+2] = 0x00;
		_ledBuffer[4+iLed*4+3] = 0x00;
	}

	return writeBytes(_ledBuffer.size(), _ledBuffer.data());
}

int LedDeviceAPA102ViaFT232H::switchOff()
{
	return write(std::vector<ColorRgb>(_mLedCount, ColorRgb{0,0,0}));
}