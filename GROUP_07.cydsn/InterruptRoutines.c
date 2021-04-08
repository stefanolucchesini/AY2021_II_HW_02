#include "InterruptRoutines.h"
#include "UART.h"
#include "stdio.h"
#include "project.h"

extern volatile int counter;
extern volatile int newdatum;
extern volatile uint8_t received;

CY_ISR(Custom_UART_RX_ISR)  //UART message handler
{  
     newdatum = 1;
     received = UART_ReadRxData();    
}

CY_ISR(Custom_ISR_timer)  //timer overflow handler (useful for RX timeouts)
{
    Timer_1_ReadStatusRegister();  //clears interrupt flag 
    counter++;
}

/* [] END OF FILE */
