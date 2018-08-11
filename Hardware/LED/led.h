#ifndef __LED_H
#define __LED_H

#include "sys.h"

// led类型 指示不同的状态
typedef enum _led_type_t
{
    SYSTEM_RUNING = 0,
    USB_ATTACHED,
    RESERVERD1,
    RESERVERD2,
}led_type_t;

#define SYSTEM_RUNING_GPIO_PORT_NUM          GPIOC
#define SYSTEM_RUNING_GPIO_BIT_NUM           GPIO_Pin_14

extern void led_init( void );
extern void set_led_value ( led_type_t led_type, BitAction value );

#endif
