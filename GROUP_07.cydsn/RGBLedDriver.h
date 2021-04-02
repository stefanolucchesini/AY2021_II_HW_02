/* ========================================
RGB LED INTERFACE
*/

#ifndef __RGB_LED_DRIVER_H__
    #define __RGB_LED_DRIVER_H__
    
    #include "project.h"
    
    //Define datatype to store data of colors
    typedef struct {
        uint8_t red;  //Red value (0-255)
        uint8_t green;  //Green value (0-255)
        uint8_t blue;  //Blue value (0-255)
    } Color;
    
    //Start driver
    void RGBLed_Start(void);
    
    //Stop driver
    void RGBLed_Stop(void);
    
    //Write a new color to RGB led, parameter c new color
    void RGBLed_WriteColor(Color c);
    
    static void RGBLed_WriteRed(uint8_t red)
{
 PWM_RG_WriteCompare1(red);
}

static void RGBLed_WriteGreen(uint8_t green)
{
 PWM_RG_WriteCompare2(green);
}

static void RGBLed_WriteBlue(uint8_t blue)
{
 PWM_B_WriteCompare(blue);
}
    
#endif    

/* [] END OF FILE */
