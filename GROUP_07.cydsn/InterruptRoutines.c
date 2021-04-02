#include "InterruptRoutines.h"
#include "UART.h"
#include "stdio.h"

#include "project.h"
//char global_datum[4] = {};
//char datum_array[4] = {}; //non so come mettere tipologia stringa//

volatile int counter;
static char messaggio[20] = {'\0'};


CY_ISR(Custom_ISR_timer)  //timer overflow handler (useful for RX timeouts)
{
    Timer_1_ReadStatusRegister();  //clears interrupt flag 
    counter++;
    sprintf(messaggio, "Interrupt timer %d\n", counter);  //debug
    UART_PutString(messaggio);
    
}

/* [] END OF FILE */
