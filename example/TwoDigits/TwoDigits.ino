#include <LM7SegDirect.h>

LM7SegDirect disp(2, 3, 4, 5, 6, 7, 8, 12, true);

byte currentValue = 0;
int currentMillis = 0;
int digitQty = 2;

void setup()  { 
  disp.defineDigits(digitQty, 11, 10, 0, 0);
} 

void loop()  { 
  disp.valueWrite(currentValue);
 
  //----------------------------------------------------------------------------------------
  // For each digit 5 ms are spent to show, so if you multiply the quantity of 
  // digits for 5 you have the amount of time ellapsed in the call
  currentMillis = currentMillis + (5 * digitQty);

  if (currentMillis > 1000)
  {
    currentValue++;
    currentMillis = 0;
  }
  
  if (currentValue > 99)
    currentValue = 0;
}
