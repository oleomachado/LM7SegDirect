/*************************************************************************
**  Device: 7-Segment                                                   **
**  File:   LM7SegDirect.cpp                                            **
**	Version: 0.1                                                        **
**                                                                      **
**  Created by Leonardo Machado 2012-11-15                              **
**                                                                      **
**  The code is provided under the MIT license please use, edit,        **
**  change, and share.                                                  **
**                                                                      **
**************************************************************************/

#include <Arduino.h>
#include <LM7SegDirect.h>

//************************************************************************
// Constructor
// Set pins for each segment 
LM7SegDirect::LM7SegDirect(byte segA, byte segB, byte segC, byte segD, byte segE, byte segF, byte segG, byte segDotn, byte isAnode) {
	_segA = segA;
	_segB = segB;
	_segC = segC;
	_segD = segD;
	_segE = segE;
	_segF = segF;
	_segG = segG;
	_segDot = segDotn;

	_isAnode = isAnode;

	pin_order[0] = _segA;
	pin_order[1] = _segB;
	pin_order[2] = _segC;
	pin_order[3] = _segD;
	pin_order[4] = _segE;
	pin_order[5] = _segF;
	pin_order[6] = _segG;
	pin_order[7] = _segDot;

	for(int i=0; i<8; i++)
	{
		pinMode(pin_order[i], OUTPUT);   
	}
}

const byte LM7SegDirect::seven_seg_digits[10][7] = { { 0,0,0,0,0,0,1 },  // = 0
													 { 1,0,0,1,1,1,1 },  // = 1
													 { 0,0,1,0,0,1,0 },  // = 2
													 { 0,0,0,0,1,1,0 },  // = 3
													 { 1,0,0,1,1,0,0 },  // = 4
													 { 0,1,0,0,1,0,0 },  // = 5
													 { 0,1,0,0,0,0,0 },  // = 6
													 { 0,0,0,1,1,1,1 },  // = 7
													 { 0,0,0,0,0,0,0 },  // = 8
													 { 0,0,0,1,1,0,0 }   // = 9
												   };

//************************************************************************
// defineDigits
// Define how many digits the 7-segment have and what are the pin numbers
void LM7SegDirect::defineDigits(byte digits, byte dig1, byte dig2, byte dig3, byte dig4){
	_digits = digits;

	digit_order[0] = dig1;
	digit_order[1] = dig2;
	digit_order[2] = dig3;
	digit_order[3] = dig4;

	for(int i=0; i<_digits; i++)
	{
		pinMode(digit_order[i], OUTPUT);   
	}
}

//---------------------------------------------------------------------
// Write one number to a specific digit in the 7-Segment led
void LM7SegDirect::digitWrite(byte digit, byte number) {
	// If the desired digit does not exist, return
	if (digit > _digits)
		return;

	// Activate the digit
	pickDigit(digit);

	// Activate each led in the digit
	int pinseq = 0;
	for (byte segCount = 0; segCount < 7; ++segCount) 
	{
		byte finalValue = seven_seg_digits[number][segCount];
		if (!_isAnode)
			finalValue = finalValue == 1 ? 0 : 1; 

		digitalWrite(pin_order[pinseq], finalValue);
		pinseq++;
	}

	// Turn off the DOT
	// TODO: Make this optional
	digitalWrite(pin_order[pinseq], _isAnode ? HIGH : LOW);

	delay(5);  // DISPLAY_BRIGHTNESS
}

//---------------------------------------------------------------------
// Write a numeric to the 7-Segment.
// Up to 4 digits
void LM7SegDirect::valueWrite(int number) {
	if (number < 10)
	{
		digitWrite(4, 0);
		digitWrite(3, 0);
		digitWrite(2, 0);
		digitWrite(1, number);
	}
	else if (number < 100)
	{
		digitWrite(4, 0);
		digitWrite(3, 0);
		digitWrite(2, number / 10);
		digitWrite(1, number % 10);
	}
	else if (number < 1000)
	{
		digitWrite(4, 0);
		digitWrite(3, number / 100);
		digitWrite(2, (number % 100) / 10);
		digitWrite(1, number % 10);
	}
	else
	{
		digitWrite(4, number / 1000);
		digitWrite(3, (number % 1000) / 100);
		digitWrite(2, (number % 100) / 10);
		digitWrite(1, number % 10);
	}
}

//---------------------------------------------------------------------
// Activate a specific digit in the 7-Segment.
void LM7SegDirect::pickDigit(int x)
{
	// If only one digit (7-Segment 1 Digit) then no need to continue here
	if (_digits == 1)
		return;

	// Turn off ALL digits
	for(int i=0; i< _digits; i++)
	{
		digitalWrite(digit_order[i], _isAnode ? LOW : HIGH);
	}

	// Turn ON only the desired digit
	digitalWrite(digit_order[x-1], _isAnode ? HIGH : LOW);
}
