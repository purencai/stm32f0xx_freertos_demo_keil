#ifndef __MESSAGE_MANAGER_H__
#define __MESSAGE_MANAGER_H__

#include "system.h"

extern SemaphoreHandle_t usart_semaphore;
extern QueueHandle_t led_system_runing_msg_queue;

extern void create_queue_semaphore(void);

#endif//__MESSAGE_MANAGER_H__
