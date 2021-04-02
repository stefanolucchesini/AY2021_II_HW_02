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

uint8_t state = IDLE;
uint8_t timeout = 50;
uint8_t datum_array[3];
static char message[20] = {'\0'};


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
       UART_Start();
       RGBLed_Start();
       RGBLed_WriteRed( 125 );
       RGBLed_WriteGreen( 125 );
       RGBLed_WriteBlue( 125 );
       Timer_1_Start();
       isr_timer_StartEx(Custom_ISR_timer);
    
    for(;;)
    {
       switch(state){
       case IDLE:
       while(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY){
          if( UART_ReadRxData() == 160 ) { 
          sprintf(message, "Staus IDLE, Received: %c\r\n", 160);  //debug 
          UART_PutString(message);
          state = HDR_B_REC;
        }
        else if ( UART_ReadRxData() == 'v' ){
        sprintf(message, "RGB LED Program $$$");  //debug 
        UART_PutString(message);
        }
    }
       break;
    case HDR_B_REC:
    counter = 0;
    while(counter < timeout){
        if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY){
          datum_array[0] = UART_ReadRxData(); //RED Byte
          sprintf(message, "Status: HDR_B_REC %d r\n", datum_array[0]);  //debug
          UART_PutString(message);
          state = R_B_REC;
          break;
        }
    }
    state = IDLE;
    break;
        case R_B_REC:
    counter = 0;
    while(counter < timeout){
       if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY){
          datum_array[1] = UART_ReadRxData(); //Green Byte
          state = G_B_REC;
          break;
        }
    }
    state = IDLE;
    break;
        case G_B_REC:
    counter = 0;
    while(counter < timeout){
        if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY){
          datum_array[2] = UART_ReadRxData(); //Blue Byte
          state = B_B_REC;
          break;
        }
    }
    state = IDLE;
    break;
        case B_B_REC:
    counter = 0;
    while( counter < timeout){
        if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY){
          if( UART_ReadRxData() == 192) {//tail Byte
          state = IDLE;
          RGBLed_WriteRed( datum_array[0] );
          RGBLed_WriteGreen( datum_array[1] );
          RGBLed_WriteBlue( datum_array[2] );       
          }  
        }
    }
    break;
    
       }
    }
}

/* [] END OF FILE */
