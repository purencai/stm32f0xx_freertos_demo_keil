#include "sys.h"
#include "usart.h"
#include "system.h"
#include "usart_loop_queue.h"

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#pragma import ( __use_no_semihosting )             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit( int x ) 
{ 
	x = x; 
} 
//定义_sys_exit()以避免使用半主机模式    
void _ttywrch( int ch ) 
{ 
	ch = ch; 
} 
//重定义fputc函数 
int fputc( int ch, FILE *f )
{
	USART_SendData( DEBUG_USART, (uint8_t)ch );
	while ( ( USART_GetFlagStatus( DEBUG_USART, USART_FLAG_TC ) ) == RESET ) {};
	return ch;
}

void debug_usart_init( uint32_t boundrate )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	// NVIC_InitTypeDef NVIC_InitStructure;
    
	/* config USART1 clock */
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE );
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1, ENABLE );

	/* USART1 Pins configuration ************************************************/
	/* Connect pin to Periph */
	GPIO_PinAFConfig( GPIOA, GPIO_PinSource9, GPIO_AF_1 ); 
	GPIO_PinAFConfig( GPIOA, GPIO_PinSource10, GPIO_AF_1 );    

	/* Configure pins as AF pushpull */
	GPIO_InitStructure.GPIO_Pin = DUBUG_TX_GPIO_BIT_NUM | DUBUG_RX_GPIO_BIT_NUM;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init( GPIOA, &GPIO_InitStructure );  

	USART_InitStructure.USART_BaudRate = boundrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    
	USART_Init( DEBUG_USART, &USART_InitStructure ); 
	USART_Cmd( DEBUG_USART, ENABLE );

    // USART_ITConfig( DEBUG_USART, USART_IT_RXNE, ENABLE );
    // NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	// NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
	// NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// NVIC_Init( &NVIC_InitStructure );
}

__forceinline void usart_putchar( usart_t *usart_num, char ch )
{
	while ( ( USART_GetFlagStatus( usart_num, USART_FLAG_TC ) ) == RESET ) {};
    USART_SendData ( usart_num, (uint8_t)ch );
}
static char usart_tx_buff[128];
void usart_putstr( usart_t *usart_num, const char *fmt, ... )
{
	uint16_t i = 0;
    uint16_t j = 0;
	va_list ap;
	va_start( ap, fmt );
	vsprintf( usart_tx_buff, fmt, ap );
	va_end( ap );
	i = strlen( (const char *)usart_tx_buff );
	for ( j=0; j<i; j++ )
	{
        usart_putchar( usart_num, usart_tx_buff[j] );
	}
}

void usart_puts( usart_t *usart_num, const char *buff, uint16_t length )
{
	uint16_t i = 0;
	for ( i=0; i<length; i++ )
	{
        usart_putchar( usart_num, buff[i] );
	}
}

uint8_t usart_read_byte( usart_t *usart_num )
{
	return ( uint8_t )USART_ReceiveData( usart_num );
}

void USART2_IRQHandler(void)
{
   if ( USART_GetITStatus( USART2, USART_IT_RXNE ) != RESET )
   {
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        // wifi_usart_irq();
   } 
}

