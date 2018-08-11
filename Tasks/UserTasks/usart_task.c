#include "message_manager.h"
#include "usart_task.h"
#include "usart_loop_queue.h"

// #define USART_TASK_TEST
#ifdef USART_TASK_TEST
#define USART_TASK_INTERVAL               1000      //单位ms
#endif //USART_TASK_TEST

void usart_task( void *pvParameters )
{
    uint8_t *usart_data = NULL;

    while ( 1 )
    {
#ifdef USART_TASK_TEST
        
        LOG ( "\r\nusart_task run ...\r\n" );
        vTaskDelay ( pdMS_TO_TICKS ( USART_TASK_INTERVAL ) );
        
#else //USART_TASK_TEST
        
        while( xSemaphoreTake ( usart_semaphore, portMAX_DELAY ) != pdPASS )
        {
            ERROR ( "usart_semaphore error\r\n" );
        }

        usart_data = usb_queue_read( );
        if ( usart_data )
        {
            // file_receive ( usart_data, WRITE );
            memset ( usart_data, 0x00, BUFF_LENGTH );
        }
        else
        {
            // DEBUG ( "usart_queue empty\r\n" );
        }

        taskYIELD ();
        
#endif //USART_TASK_TEST
    }
}
