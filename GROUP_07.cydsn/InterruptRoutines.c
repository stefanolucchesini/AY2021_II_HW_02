#include "InterruptRoutines.h"
#include "UART.h"
#include "stdio.h"

#include "project.h"
//char global_datum[4] = {};
//char datum_array[4] = {}; //non so come mettere tipologia stringa//

volatile int counter;
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
    //sprintf(messaggio, "Interrupt timer %d\n", counter);  //debug
    //UART_PutString(messaggio);
    
}

/* [] END OF FILE */
