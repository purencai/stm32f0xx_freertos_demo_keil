#include "usart_loop_queue.h"
#include "system.h"

uint8_t usb_usart_queue[QUEUE_LENGTH][BUFF_LENGTH] = { 0x00 };
LOOP_QUEUE usb_lq;

__STATIC_INLINE uint8_t *loop_queue_insert( LOOP_QUEUE *q, uint8_t queue[][BUFF_LENGTH] )
{
    uint8_t *head = NULL;

    if ( ( q->rear + 1 ) % QUEUE_LENGTH == q->front )
    {
        return NULL;
    }
    q->rear = (q->rear + 1) % QUEUE_LENGTH;
    head = &queue[q->rear][0];
    q->cnt++;
    return head;
}
__STATIC_INLINE uint8_t *loop_queue_read( LOOP_QUEUE *q, uint8_t queue[][BUFF_LENGTH] )
{
    uint8_t *head = NULL;

    if ( q->front == q->rear )
    {
        return NULL;
    }
    head = &queue[q->front][0];
    q->front = ( q->front + 1 ) % QUEUE_LENGTH;
    q->cnt--;
    return head;
}
__STATIC_INLINE uint8_t *loop_queue_get_rear( LOOP_QUEUE *q, uint8_t queue[][BUFF_LENGTH] )
{
    uint8_t *head = NULL;
    head = &queue[q->rear][0];
    return head;
}
__STATIC_INLINE uint8_t *is_loop_queue_empty ( LOOP_QUEUE *q, uint8_t queue[][BUFF_LENGTH] )
{
    if ( q->front == q->rear )
    {
        return NULL;
    }
    return &queue[q->front][0];
}

__STATIC_INLINE void loop_queue_init( LOOP_QUEUE *q, uint8_t queue[][BUFF_LENGTH] )
{
    q->front = 0;
    q->rear = 0;
    q->cnt = 0;
    q->timer_cnt = 0;
    q->buff_cnt = 0;
    q->usart_buff = loop_queue_get_rear( q, queue );
}

__STATIC_INLINE void usart_irq( LOOP_QUEUE *q, usart_t *usart_num )
{
    if ( q->usart_buff == NULL )
    {
        q->timer_cnt = QUEUE_TIME_OUT + 1;
        return;
    }
    q->usart_buff[q->buff_cnt] = usart_read_byte ( usart_num );
    q->buff_cnt++;
    if (q->buff_cnt == BUFF_LENGTH)
    {
        q->buff_cnt = BUFF_LENGTH - 1;
    }
    q->timer_cnt = 1;
}

__STATIC_INLINE void timer_irq( LOOP_QUEUE *q, uint8_t queue[][BUFF_LENGTH] )
{
    BaseType_t xHigherPriorityTaskWoken;
    if ( q->timer_cnt > 0 )
    {
        q->timer_cnt++;
    }
    if ( q->timer_cnt > QUEUE_TIME_OUT )
    {
        q->usart_buff = loop_queue_insert( q, queue );
        //printf("lq:%d\r\n", q->front);
        if ( q->usart_buff == NULL )
        {
            printf("full\r\n");
        }
        q->buff_cnt = 0;
        q->timer_cnt = 0;
        //give a counting semaphore
        if ( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED )return;
        xSemaphoreGiveFromISR( usart_semaphore, &xHigherPriorityTaskWoken );
        portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    }
}

uint8_t *usb_queue_insert( void )
{
    return loop_queue_insert( &usb_lq, usb_usart_queue );
}

uint8_t *usb_queue_read( void )
{
    return loop_queue_read( &usb_lq, usb_usart_queue );
}

void usb_queue_init( void )
{
    loop_queue_init( &usb_lq, usb_usart_queue );
}

void usb_usart_irq( void )
{
    usart_irq( &usb_lq, USB_USART );
}

void usb_timer_irq( void )
{
    timer_irq( &usb_lq, usb_usart_queue );
}
