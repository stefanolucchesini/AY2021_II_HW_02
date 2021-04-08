/* ========================================
RGB LED INTERFACE
*/

#ifndef __RGB_LED_DRIVER_H__
    #define __RGB_LED_DRIVER_H__
    
    #include "project.h"
      
    //Start driver
    void RGBLed_Start(void);
    
    //Stop driver
    void RGBLed_Stop(void);
    
    //Write a new color to RGB led
    void RGBLed_WriteColor(uint8_t red, uint8_t green, uint8_t blue);
    //Write color intensity to Red led
    void RGBLed_WriteRed(uint8_t red);
    //Write color intensity to Green led
    void RGBLed_WriteGreen(uint8_t green);
    //Write color intensity to Blue led
    void RGBLed_WriteBlue(uint8_t blue);
    
#endif    

/* [] END OF FILE */
