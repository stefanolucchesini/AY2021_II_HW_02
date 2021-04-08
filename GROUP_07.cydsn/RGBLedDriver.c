#include "RGBLedDriver.h"

void RGBLed_Start()
{
PWM_RG_Start();
PWM_B_Start();
}

void RGBLed_Stop()
{
PWM_RG_Stop();
PWM_B_Stop();
}

void RGBLed_WriteColor(uint8_t red, uint8_t green, uint8_t blue)
{
   RGBLed_WriteRed(red);
   RGBLed_WriteGreen(green);
   RGBLed_WriteBlue(blue);
   
}

void RGBLed_WriteRed(uint8_t red)
{
 PWM_RG_WriteCompare1(red);
}

void RGBLed_WriteGreen(uint8_t green)
{
 PWM_RG_WriteCompare2(green);
}

void RGBLed_WriteBlue(uint8_t blue)
{
 PWM_B_WriteCompare(blue);
}

/* [] END OF FILE */
