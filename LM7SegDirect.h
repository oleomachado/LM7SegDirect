/*************************************************************************
**  Device: 7-Segment                                                   **
**  File:   LM7SegDirect.h                                              **
**	Version: 0.1                                                        **
**                                                                      **
**  Created by Leonardo Machado 2012-11-15                              **
**                                                                      **
**  The code is provided under the MIT license please use, edit,        **
**  change, and share.                                                  **
**                                                                      **
**************************************************************************/

#ifndef LM7SegDirect_h
#define LM7SegDirect_h

#include <Arduino.h>   //Arduino IDE >= V1.0

class LM7SegDirect
{
public:
	// Constructor
	LM7SegDirect(byte segA, byte segB, byte segC, byte segD, byte segE, byte segF, byte segG, byte segDotn, boolean isAnode);

	void valueWrite(int number);
	void defineDigits(byte digits, byte dig1, byte dig2, byte dig3, byte dig4);
	void digitWrite(byte digit, byte number);
private:
	int _isAnode;
	int _segA;
	int _segB;
	int _segC;
	int _segD;
	int _segE;
	int _segF;
	int _segG;
	int _segDot;
	int _digits;

	static const byte seven_seg_digits[10][7];
	byte pin_order[8]; // The extra item in array is defined for safety
	byte digit_order[4];
	byte _registers[16];

	void pickDigit(int x);
};

#endif 
