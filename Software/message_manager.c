#include "message_manager.h"
#include "usart_loop_queue.h"
#include "led_function.h"

SemaphoreHandle_t usart_semaphore = NULL;
__STATIC_INLINE void create_usart_semaphore(void)
{
    usart_semaphore = xSemaphoreCreateCounting( QUEUE_LENGTH, 0 );
    if( usart_semaphore == NULL )
    {
        ERROR( "create usart_semaphore fail\r\n" );
    }
}

QueueHandle_t led_system_runing_msg_queue = NULL;
__STATIC_INLINE void create_led_system_runing_msg_queue( void )
{
    led_system_runing_msg_queue = xQueueCreate( 5, sizeof ( led_parameter_t ) ); 
    if ( led_system_runing_msg_queue == NULL )
    {
        ERROR( "create led_system_runing_msg_queue fail\r\n" );
    }
}

void create_queue_semaphore(void)
{
    create_usart_semaphore();
    create_led_system_runing_msg_queue();
}
