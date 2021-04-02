#include "RGBLedDriver.h"

static void RGBLed_WriteRed(uint8_t red);
static void RGBLed_WriteGreen(uint8_t green);
static void RGBLed_WriteBlue(uint8_t blue);

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

void RGBLed_WriteColor(Color c)
{
   RGBLed_WriteRed(c.red);
   RGBLed_WriteGreen(c.green);
   RGBLed_WriteBlue(c.blue);
   
}


/* [] END OF FILE */
