#include "InterruptRoutines.h"
#include "UART.h"
#include "stdio.h"
#include "project.h"

static char message[20] = {'\0'};

CY_ISR(Custom_UART_RX_ISR)  //UART message handler
{
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
    char datum = UART_ReadRxData(); 
    sprintf(message, "Received: %c\r\n", datum);  //da modificare 
    UART_PutString(message);
    }
}

CY_ISR(Custom_ISR_timer)  //timer overflow handler (useful for RX timeouts)
{
    Timer_1_ReadStatusRegister();  //clears interrupt flag 
    //istruzioni da scrivere per gestire il timeout
}

/* [] END OF FILE */
