#ifndef __USART_TASK_H__
#define __USART_TASK_H__
/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

void usart_task( void *pvParameters );

#endif


