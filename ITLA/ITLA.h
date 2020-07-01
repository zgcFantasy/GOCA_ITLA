#pragma once

#ifdef DLL_EXPORT
#define DLL_EXPORT _declspec(dllexport)
#else
#define DLL_EXPORT _declspec(dllimport)
#endif // DLL_EXPORT

extern "C" {
	DLL_EXPORT short calcBIP4(short* data);

	// ------ 0x32  ResEna -----------
	DLL_EXPORT void LD_enableOut(short* data);
	DLL_EXPORT void LD_closeOut(short* data);

	// ------ 0x31  PWR -----------
	DLL_EXPORT void LD_setPower(short* data, short power);

	// ------ 0x35  FCF1 -----------
	// ------ 0x36  FCF2 -----------
	// ------ 0x67  FCF3 -----------
	DLL_EXPORT void LD_setFreqOfChannel(short fredata[3][4], double freq);
}