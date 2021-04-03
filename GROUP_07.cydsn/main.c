/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "RGBLedDriver.h"
#include "InterruptRoutines.h"
#include "project.h"
#include "stdio.h"

volatile int counter = 0;
#define IDLE 0
#define HDR_B_REC 1
#define R_B_REC 2
#define G_B_REC 3
#define B_B_REC 4
#define TIMER_SET 5

uint8_t state = IDLE;
uint8_t timeout = 50;
uint8_t datum_array[3];
static char message[20] = {'\0'};
volatile int newdatum = 0;  //flag
volatile uint8_t received;  //datum received from UART
int flag = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
       UART_Start();
       isr_UART_StartEx(Custom_UART_RX_ISR);
       RGBLed_Start();
       //Black color setup
       RGBLed_WriteRed(0);
       RGBLed_WriteGreen(0);
       RGBLed_WriteBlue(0);
       Timer_1_Start();
       isr_timer_StartEx(Custom_ISR_timer);
    
    for(;;)
    {
       switch(state){
       case IDLE:
       if(newdatum){
        newdatum = 0;
        if( received == 0xA0 ) { 
            sprintf(message, "Staus IDLE, Received:%c\r\n", 160);  //debug 
            UART_PutString(message);
            state = HDR_B_REC;
        }
        else if ( received == 'v' ){
            sprintf(message, "RGB LED Program $$$"); 
            UART_PutString(message);
        }
        /*else if ( received == 0xA1){
            state = TIMER_SET;
        }*/
    }
       break;
    case HDR_B_REC:
    counter = 0;
    while(counter < timeout){
        if(newdatum){
          newdatum = 0;
          datum_array[0] = received; //RED Byte
          sprintf(message, "Status: HDR_B_REC %dr\n", datum_array[0]);  //debug
          UART_PutString(message);
          state = R_B_REC;
          break;
        }
        else state = IDLE;        
    }
    break;
        case R_B_REC:
    counter = 0;
    while(counter < timeout){
       if(newdatum){
          newdatum = 0;
          datum_array[1] = received; //Green Byte
          state = G_B_REC;
          break;
        }
        else state = IDLE;
    }
   
    break;
        case G_B_REC:
    counter = 0;
    while(counter < timeout){
        if(newdatum){
           newdatum = 0;
          datum_array[2] = received; //Blue Byte
          state = B_B_REC;
          break;
        }
        else state = IDLE;
    }
    break;
        case B_B_REC:
    counter = 0;
    while( counter < timeout){
        if(newdatum){
           newdatum = 0;
          /*if(received == 0xC0 && flag == 1){
            flag=0;
            state=IDLE;
            break;
        }*/
          if( received == 0xC0) {//tail Byte
          state = IDLE;
          RGBLed_WriteRed( datum_array[0] );
          RGBLed_WriteGreen( datum_array[1] );
          RGBLed_WriteBlue( datum_array[2] ); 
          break;
          }
          else state = IDLE;
        }
    }
    break;
    case TIMER_SET:
        counter = 0;
        while(counter < (timeout+50)){ //added 50 in order to give enough time to change the timeout if it is too small from the previous setting
        if(newdatum){
           newdatum = 0;
           timeout = received*10;
           flag=1;
           state=B_B_REC;
          break;
        }
        else state = IDLE;
    
       }
    }
 }
}

/* [] END OF FILE */