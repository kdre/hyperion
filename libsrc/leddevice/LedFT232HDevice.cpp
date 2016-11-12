// Author: Klaus Drechsler, drechsler ( at ) gmx.net


// Local Hyperion includes
#include "LedFT232HDevice.h"


LedFT232HDevice::LedFT232HDevice(enum modes mode, int freq, int endianess) : 
mMode(mode),
mFreq_Hz(freq),
mEndianess(endianess),
mContext(NULL)
{
		;
}

LedFT232HDevice::~LedFT232HDevice()
{
	Close(mContext);
}

int LedFT232HDevice::open()
{
	if((mContext = MPSSE(mMode, mFreq_Hz, mEndianess)) == NULL && !mContext->open)
	{
		std::cerr << "Failed to initialize FT232H MPSSE device. " << ErrorString(mContext) << std::endl;
		return -1;
	}

	return 0;
}

int LedFT232HDevice::writeBytes(const unsigned size, const uint8_t *data)
{
	Start(mContext); 
	
	if(Write(mContext, (char*)data, size)==MPSSE_FAIL){
		std::cerr << "Failed to write to FT232H MPSSE device." << std::endl;
		return -1;
	}
	Stop(mContext); 

	return 0;
}
