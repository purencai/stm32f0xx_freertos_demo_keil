#ifndef __USART_LOOP_QUEUE_H__
#define __USART_LOOP_QUEUE_H__

#include "usart.h"

#define QUEUE_LENGTH 3
#define BUFF_LENGTH 1024
#define QUEUE_TIME_OUT 20

typedef struct loop_queue
{
    uint8_t front;
    uint8_t rear;
    uint16_t cnt;
    
    uint16_t timer_cnt;
    uint16_t buff_cnt; 
    uint8_t *usart_buff; 
}LOOP_QUEUE;

extern LOOP_QUEUE usb_lq;

extern uint8_t *usb_queue_insert ( void );
extern uint8_t *usb_queue_read ( void );
extern void usb_queue_init ( void );
extern void usb_usart_irq ( void );
extern void usb_timer_irq ( void );

#endif //__USART_LOOP_QUEUE_H__

