#include "led_function.h"

void led_off( led_type_t led_type )
{
    set_led_value( led_type, Bit_RESET );
}

void led_on( led_type_t led_type )
{
    set_led_value( led_type, Bit_SET );
}

void led_system_runing_flash( uint16_t flash_interval, uint16_t sys_interval )
{
    static uint8_t system_runing_cnt = 0;
    static uint16_t system_runing_time = 0;

    system_runing_time ++;

    if ( system_runing_cnt%2 == 0 )
    {
        set_led_value( SYSTEM_RUNING, Bit_SET );
    }
    else
    {
        set_led_value( SYSTEM_RUNING, Bit_RESET );
    }

    if ( system_runing_time == flash_interval/sys_interval )
    {
        system_runing_cnt ++;
        system_runing_time = 0;
    }
}

void led_usb_attached_flash( uint16_t flash_interval, uint16_t sys_interval )
{
    static uint8_t usb_attached_cnt = 0;
    static uint16_t usb_attached_time = 0;

    usb_attached_time ++;

    if ( usb_attached_cnt%2 == 0 )
    {
        set_led_value( USB_ATTACHED, Bit_SET );
    }
    else
    {
        set_led_value( USB_ATTACHED, Bit_RESET );
    }

    if ( usb_attached_time == flash_interval/sys_interval )
    {
        usb_attached_cnt ++;
        usb_attached_time = 0;
    }
}


void led_reserved1_flash( uint16_t flash_interval, uint16_t sys_interval )
{
    static uint8_t reserved1_cnt = 0;
    static uint16_t reserved1_time = 0;

    reserved1_time ++;

    if ( reserved1_cnt%2 == 0 )
    {
        set_led_value( RESERVERD1, Bit_SET );
    }
    else
    {
        set_led_value( RESERVERD1, Bit_RESET );
    }

    if ( reserved1_time == flash_interval/sys_interval )
    {
        reserved1_cnt ++;
        reserved1_time = 0;
    }
}


void led_reserved2_flash( uint16_t flash_interval, uint16_t sys_interval )
{
    static uint8_t reserved2_cnt = 0;
    static uint16_t reserved2_time = 0;

    reserved2_time ++;

    if ( reserved2_cnt%2 == 0 )
    {
        set_led_value( RESERVERD2, Bit_SET );
    }
    else
    {
        set_led_value( RESERVERD2, Bit_RESET );
    }

    if ( reserved2_time == flash_interval/sys_interval )
    {
        reserved2_cnt ++;
        reserved2_time = 0;
    }
}
void led_flash( led_type_t led_type, uint16_t flash_interval, uint16_t sys_interval )
{
    switch ( led_type )
    {
	case SYSTEM_RUNING:
        led_system_runing_flash ( flash_interval, sys_interval );
	break;
	case USB_ATTACHED:
        led_usb_attached_flash ( flash_interval, sys_interval );
	break;
	case RESERVERD1:
        led_reserved1_flash ( flash_interval, sys_interval );
	break;
	case RESERVERD2:
        led_reserved2_flash ( flash_interval, sys_interval );
	break;
	default:
	break;
    }
}

void led_parameter_init( led_parameter_t* led_parameter )
{
    led_parameter->status = LED_OFF;
    led_parameter->flash_interval = 0;
}

BaseType_t set_led_status( led_type_t led_type, led_status_t led_status, uint16_t flash_interval )
{
    BaseType_t QueueSendStatus = pdPASS;
    led_parameter_t led_parameter;
    
    led_parameter.status = led_status;
    led_parameter.flash_interval = flash_interval;

    switch ( led_type )
    {
	case SYSTEM_RUNING:
		QueueSendStatus = xQueueSend( led_system_runing_msg_queue, &led_parameter, 0 );
	break;
	case USB_ATTACHED:
		QueueSendStatus = xQueueSend( led_system_runing_msg_queue, &led_parameter, 0 );
	break;
	case RESERVERD1:
		QueueSendStatus = xQueueSend( led_system_runing_msg_queue, &led_parameter, 0 );
	break;
	case RESERVERD2:
		QueueSendStatus = xQueueSend( led_system_runing_msg_queue, &led_parameter, 0 );
	break;
	default:
	break;
    }

    return QueueSendStatus;
}
