/*
	写入操作共有4个字节，自上而下数
	字节1：读写状态，0x01代表写，00代表读
	字节2：寄存器号 0x00~0xff
	字节3：数据
	字节4：数据
*/
#define DLL_EXPORT
#include <stdio.h>
#include "ITLA.h"

// -------------- CheckSum ----------------------------------
short calcBIP4(short* data) {
	short bip8 = (data[0] & 0x0f) ^ data[1] ^ data[2] ^ data[3];
	short bip4 = ((bip8 & 0xf0) >> 4) ^ (bip8 & 0x0f);
	return bip4;
}


// ------ 0x31  PWR -----------
void LD_setPower(short* data, short power) {
	short powerCode = power * 100;
	data[0] = 0x01;
	data[1] = 0x31;
	data[2] = (powerCode & 0xff00) >> 8;
	data[3] = powerCode & 0x00ff;

	short bip4 = calcBIP4(data);
	data[0] |= (bip4 << 4);
	return;
}

// ------ 0x32  ResEna -----------
void LD_enableOut(short* data) {
	data[0] = 0x01;
	data[1] = 0x32;
	data[2] = 0x00;
	data[3] = 0x08;

	short bip4 = calcBIP4(data);
	data[0] |= (bip4 << 4);
	return;
}

void LD_closeOut(short* data) {
	data[0] = 0x01;
	data[1] = 0x32;
	data[2] = 0x00;
	data[3] = 0x00;
	short bip4 = calcBIP4(data);
	data[0] |= (bip4 << 4);
	return;
}


// ------ 0x35  FCF1 -----------
// ------ 0x36  FCF2 -----------
// ------ 0x67  FCF3 -----------
// 194.175125 THz ==> FCF1 194;FCF2 1751; FCF3 25
void LD_setFreqOfChannel(short freData[3][4], double freq) {

	short numOfFCF[3];
	short bip4_fre[3];
	for (int i = 0; i < 3; i++) {
		freData[i][0] = 0x01;
	}
	freData[0][1] = 0x35;
	freData[1][1] = 0x36;
	freData[2][1] = 0x67;

	numOfFCF[0] = (short)freq;
	numOfFCF[1] = (short)((freq - numOfFCF[0]) * 1e4);
	numOfFCF[2] = (short)((freq - numOfFCF[0] - numOfFCF[1] * 1e-4) * 1e6);

	for (int i = 0; i < 3; i++) {
		freData[i][2] = (numOfFCF[i] & 0xff00) >> 8;
		freData[i][3] = numOfFCF[i] & 0x00ff;
	}

	for (int i = 0; i < 3; i++)
	{
		bip4_fre[i] = calcBIP4(freData[i]);
		freData[i][0] |= (bip4_fre[i] << 4);
	}
	return;
}
