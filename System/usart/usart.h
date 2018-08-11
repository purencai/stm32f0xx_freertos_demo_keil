#ifndef __USART_H_
#define	__USART_H_

#include "sys.h"

typedef USART_TypeDef usart_t;

#define USB_USART       USART2
#define USB_RX_GPIO_PORT_NUM  GPIOA
#define USB_RX_GPIO_BIT_NUM   GPIO_Pin_3
#define USB_TX_GPIO_PORT_NUM  GPIOA
#define USB_TX_GPIO_BIT_NUM   GPIO_Pin_2

#define DEBUG_USART             USART1
#define DEBUG_RX_GPIO_PORT_NUM  GPIOA
#define DUBUG_RX_GPIO_BIT_NUM   GPIO_Pin_10
#define DEBUG_TX_GPIO_PORT_NUM  GPIOA
#define DUBUG_TX_GPIO_BIT_NUM   GPIO_Pin_9

extern void debug_usart_init( uint32_t boundrate );
extern void usart_putchar( usart_t *usart_num, char ch );
extern void usart_putstr( usart_t *usart_num, const char *fmt, ... );
extern void usart_puts( usart_t *usart_num, const char *buff, uint16_t length );

extern uint8_t usart_read_byte( usart_t *usart_num );

#endif
