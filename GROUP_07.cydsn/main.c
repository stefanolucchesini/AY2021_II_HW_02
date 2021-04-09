
#include "RGBLedDriver.h"
#include "InterruptRoutines.h"
#include "project.h"
#include "stdio.h"

//States definitions
#define IDLE 0
#define HDR_B_REC 1
#define R_B_REC 2
#define G_B_REC 3
#define B_B_REC 4
#define TIMER_SET 5

//Defines for timing
#define TIMEOUT_SECONDS 5 //timeout value in seconds 
#define TIME_MARGIN 5 //used when changing timeout value, adds 5 seconds to default timeout to have more time to change it manually
#define MIN 1   //minimum allowed timeout value in seconds
#define MAX 20  //maximum allowed timeout value in seconds

//Defines for tail and headers 
#define HEADER_LED 0xA0
#define HEADER_TIMEOUT 0xA1
#define TAIL 0xC0

volatile int newdatum = 0;  //flag that tells if a new byte has arrived from UART
volatile uint8_t received;  //datum received from UART
volatile int counter = 0;

int main(void)
{
       uint8_t state = IDLE;
       uint8_t timeout = 10*TIMEOUT_SECONDS; // there is an interrupt fired by the timer every 100ms, so after 10 interrupts a second has passed
       uint8_t newtimeout;   //stores new timeout value, if the tail is received it is assigned to timeout
       uint8_t datum_array[3];   //contains RGB values
       uint8_t flag = 0;   //useful to discriminate between timeout definition tail and RGB led tail
       CyGlobalIntEnable; /* Enable global interrupts. */
       UART_Start();
       isr_UART_StartEx(Custom_UART_RX_ISR);
       RGBLed_Start();

       RGBLed_WriteColor(0,0,0);  //Black color setup
       Timer_1_Start();
       isr_timer_StartEx(Custom_ISR_timer);
    
    for(;;)
    {
       switch(state){
        
    case IDLE:
       if(newdatum){
        newdatum = 0;
        if( received == HEADER_LED ) {          
            state = HDR_B_REC;
        }
        else if ( received == 'v' ){
            static char message[20] = {'\0'};
            sprintf(message, "RGB LED Program $$$"); 
            UART_PutString(message);
        }
        else if ( received == HEADER_TIMEOUT){
            state = TIMER_SET;
        }
    }
    break;
    
    case HDR_B_REC:   //received header
    counter = 0;
    while(counter < timeout){
        if(newdatum){
          newdatum = 0;
          datum_array[0] = received; //RED Byte
          state = R_B_REC;
          break;
        }
        else state = IDLE;        
    }
    break;
    
    case R_B_REC:     //received red
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
    
    case G_B_REC:   //received green
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
    
    case B_B_REC:  //received blue
    counter = 0;
    while(counter < timeout){
        if(newdatum){
           newdatum = 0;
          if(received == TAIL && flag == 1){  //it's the tail to change timeout value
            flag=0;
            timeout = newtimeout;
            state=IDLE;
            break;
        }
          if( received == TAIL) {     //tail Byte of RGB led
          state = IDLE;
          RGBLed_WriteColor(datum_array[0],datum_array[1],datum_array[2]); 
          break;
          }
          else state = IDLE;
        }
    }
    break;
    
    case TIMER_SET:
        counter = 0;
        while(counter < timeout+TIME_MARGIN*10){ 
        if(newdatum){
           newdatum = 0;
           if(received<=MIN) received = MIN;  //minimum allowed timeout
           if(received>=MAX) received = MAX;  //maximum allowed timeout
           newtimeout = received*10;
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