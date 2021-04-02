#include "InterruptRoutines.h"
#include "UART.h"
#include "stdio.h"
#include "project.h"
//char global_datum[4] = {};
//char datum_array[4] = {}; //non so come mettere tipologia stringa//
static char message[20] = {'\0'};
//int count = 0;

CY_ISR(Custom_UART_RX_ISR)  //UART message handler
{
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
    char datum = UART_ReadRxData(); 
    //datum_array[count] = datum;
    //count++;
    sprintf(message, "Received: %c\r\n", datum);  //da modificare 
    UART_PutString(message);
    /*if (count == 3){
        count = 0;
        global_datum[0]=datum_array[0];
        global_datum[1]=datum_array[1];
        global_datum[2]=datum_array[2];
        global_datum[3]=datum_array[3];
    }*/
    }
}

CY_ISR(Custom_ISR_timer)  //timer overflow handler (useful for RX timeouts)
{
    Timer_1_ReadStatusRegister();  //clears interrupt flag 
    //istruzioni da scrivere per gestire il timeout
}

/* [] END OF FILE */
