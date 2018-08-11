#include "led.h" 

void led_init( void )
{
    GPIO_InitTypeDef GPIO_InitStructure;    
    
    /* GPIOC Periph clock enable */
    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOC, ENABLE );

    /* Configure PC10 and PC11 in output pushpull mode */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init( GPIOC, &GPIO_InitStructure );
}

void set_led_value( led_type_t led_type, BitAction value )
{
	switch ( led_type )
	{
	case SYSTEM_RUNING:
		GPIO_WriteBit( SYSTEM_RUNING_GPIO_PORT_NUM, SYSTEM_RUNING_GPIO_BIT_NUM, value );
	break;
	case USB_ATTACHED:
		GPIO_WriteBit( SYSTEM_RUNING_GPIO_PORT_NUM, SYSTEM_RUNING_GPIO_BIT_NUM, value );
	break;
	case RESERVERD1:
		GPIO_WriteBit( SYSTEM_RUNING_GPIO_PORT_NUM, SYSTEM_RUNING_GPIO_BIT_NUM, value );
	break;
	case RESERVERD2:
		GPIO_WriteBit( SYSTEM_RUNING_GPIO_PORT_NUM, SYSTEM_RUNING_GPIO_BIT_NUM, value );
	break;
	default:
	break;
	}
}
