//TivaWare uC: Usado internamente para identificar o uC em alguns .h da TivaWare
#define PART_TM4C1294NCPDT 1

#define HISTOGRAM_SIZE 256

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "images.h"

//variável para receber o retorno do cfg do clk
uint32_t SysClock;

typedef uint16_t (*ram_function_t)(uint16_t, uint16_t, uint8_t*, uint16_t*);
volatile unsigned long ram_buffer[72/4];
ram_function_t EightBitHistogram_ASM_ram = (ram_function_t)ram_buffer;

// Prototipos
void SetupUart(void);
void UART_Interruption_Handler(void);
uint16_t EightBitHistogram_C(uint16_t width, uint16_t height, uint8_t *p_image, uint16_t *p_histogram);
void send_csv_file(uint16_t *p_histogram);
void UART_send_uint16_t(uint16_t number);
void copy_from_flash_to_ram(void *source, void *destiny, int size);


extern uint16_t EightBitHistogram_ASM(uint16_t width, uint16_t height, uint8_t *p_image, uint16_t *p_histogram);


int main(void)
{
  SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240), 120000000);
	SetupUart();
	
	EightBitHistogram_ASM_ram = (ram_function_t)((unsigned long)EightBitHistogram_ASM_ram + (unsigned long)0x00000001);
	copy_from_flash_to_ram((void*)EightBitHistogram_ASM, (void*)ram_buffer, 72);
	
	uint16_t histogram[256];

//	uint16_t image0_size = EightBitHistogram_C(HEIGHT0, WIDTH0, (uint8_t*)image0, histogram);
//	send_csv_file(histogram);
//	
//	uint16_t image1_size = EightBitHistogram_C(HEIGHT1, WIDTH1, (uint8_t*)image1, histogram);
//	send_csv_file(histogram);
//	
//	uint16_t image0_size_asm = EightBitHistogram_ASM(HEIGHT0, WIDTH0, (uint8_t*)image0, histogram);
//	send_csv_file(histogram);
//	
//	uint16_t image1_size_asm = EightBitHistogram_ASM(HEIGHT1, WIDTH1, (uint8_t*)image1, histogram);
//	send_csv_file(histogram);
	
	uint16_t image0_size_ASM_ram = EightBitHistogram_ASM_ram(HEIGHT0, WIDTH0, (uint8_t*)image0, histogram);
	send_csv_file(histogram);

	uint16_t image1_size_ASM_ram = EightBitHistogram_ASM_ram(HEIGHT1, WIDTH1, (uint8_t*)image1, histogram);
	send_csv_file(histogram);
	
	return 0;
}


void SetupUart(void)
{
  //Habilitar porta serial a 115200 com interrupção seguindo sequencia de inicializações abaixo:
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0));
  UARTConfigSetExpClk(UART0_BASE, SysClock, 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
  UARTFIFODisable(UART0_BASE);
  UARTIntEnable(UART0_BASE,UART_INT_RX);
  UARTIntRegister(UART0_BASE,UART_Interruption_Handler);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
  GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE,(GPIO_PIN_0|GPIO_PIN_1));
}

void UART_Interruption_Handler(void) 
{
  //limpar IRQ exec
  UARTIntClear(UART0_BASE, UARTIntStatus(UART0_BASE, true));
}

uint16_t EightBitHistogram_C(uint16_t width, uint16_t height, uint8_t *p_image, uint16_t *p_histogram)
{
	uint16_t image_size = width * height;
	
	if(image_size >= 65535)
		return 0;
	
	//clear histogram
	uint16_t i = 0;
	for(i = 0; i < 256; i++)
		p_histogram[i] = 0;
	
	uint16_t j = 0;
	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			uint8_t value = p_image[i * width + j];
			p_histogram[value]++;
		}
	}
	
	//return image size
	return image_size;
}

void send_csv_file(uint16_t *p_histogram)
{
	//Start flag
	UARTCharPut(UART0_BASE, 'S');
	UARTCharPut(UART0_BASE, '\r');
	UARTCharPut(UART0_BASE, '\n');
	
	UARTCharPut(UART0_BASE, 'X');
	UARTCharPut(UART0_BASE, ',');
	UARTCharPut(UART0_BASE, 'Y');
	UARTCharPut(UART0_BASE, '\r');
	UARTCharPut(UART0_BASE, '\n');
	
	uint16_t i = 0;
	
	for(i = 0; i < HISTOGRAM_SIZE; i++)
	{
		UART_send_uint16_t(i);		
		UARTCharPut(UART0_BASE, ',');
		UART_send_uint16_t(p_histogram[i]);		
		UARTCharPut(UART0_BASE, '\r');
		UARTCharPut(UART0_BASE, '\n');
	}
	
	//End flag
	UARTCharPut(UART0_BASE, 'E');
	UARTCharPut(UART0_BASE, '\r');
	UARTCharPut(UART0_BASE, '\n');
}

void UART_send_uint16_t(uint16_t number)
{
	if(number < 10)
	{
		UARTCharPut(UART0_BASE, number + '0');
		return;
	}
	
	UART_send_uint16_t(number / 10);
	UARTCharPut(UART0_BASE, (number % 10) + '0');
}

void copy_from_flash_to_ram(void *source, void *destiny, int size)
{
	uint8_t *source_uint8_t = source;
	uint8_t *destiny_uint8_t = destiny;
	
	source_uint8_t--;
	
	while(size)
	{
		*destiny_uint8_t = *source_uint8_t;
		destiny_uint8_t++;
		source_uint8_t++;
		size--;
	}
}

