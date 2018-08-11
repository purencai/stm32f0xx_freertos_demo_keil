#include "user_tasks.h" 
#include "usart_task.h"
#include "system.h"
#include "led_task.h"
#include "message_manager.h"

#define LED_TASK_PRIORITY         0

#define LED_TASK_STACK_DEPTH      64

void AppTaskCreate( void )
{	
    create_queue_semaphore();

    xTaskCreate ( ( TaskFunction_t ) led_task,  /* Pointer to the function that implements the task. */
                  "led_task",                /* Text name for the task.  This is to facilitate debugging only. */
                  LED_TASK_STACK_DEPTH,      /* Stack depth in words. */
                  NULL,                      /* We are not using the task parameter. */
                  LED_TASK_PRIORITY,         /* This task will run at priority. */
                  NULL );                    /* We are not using the task handle. */      
}


