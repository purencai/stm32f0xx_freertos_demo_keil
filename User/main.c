#include "user_tasks.h" 
#include "system.h" 

#include "delay.h"	
#include "usart.h"	
#include "led.h"	

#include "usart_loop_queue.h"

int main( void )
{  
    delay_init();
    led_init();
    // usb_queue_init();
    
    debug_usart_init( 460800 );
    LOG( "\r\nSystemCoreClock = %d\r\n", (uint32_t)SystemCoreClock );   
    LOG( "\r\nboard init finished\r\n" );
    
	AppTaskCreate();
    vTaskStartScheduler();

    while(1) 
    {
    };
}
