#include "InterruptRoutines.h"
#include "UART.h"
#include "stdio.h"
#include "project.h"

extern volatile int counter;
extern volatile int newdatum;
extern volatile uint8_t received;

CY_ISR(Custom_UART_RX_ISR)  //UART message handler
{  
     if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
     newdatum = 1;  //tells that a new byte has arrived
     received = UART_ReadRxData();  //saves received byte
    }
    
}

CY_ISR(Custom_ISR_timer)  //timer overflow handler (useful for RX timeouts)
{
    Timer_1_ReadStatusRegister();  //clears interrupt flag 
    counter++;  //increased 10 times per second
}

/* [] END OF FILE */
