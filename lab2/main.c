/*##############################################################################
Desenvolvido para a placa EK-TM4C1294XL utilizando o SDK TivaWare no KEIL
Laboratório 2 - Sistemas Embarcados
##############################################################################*/

//TivaWare uC: Usado internamente para identificar o uC em alguns .h da TivaWare
#define PART_TM4C1294NCPDT 1

#include "images.h"

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"


//variável que conta os ticks(1ms) - Volatile não permite o compilador otimizar o código 
static volatile unsigned int SysTicks;

//variável para receber o retorno do cfg do clk
uint32_t SysClock;

//Protótipos de funções criadas no programa, código depois do main
void SetupSystick(void);
void SysTickIntHandler(void);
void SetupUart(void);
void UART_Interruption_Handler(void);

//ASM
uint16_t EightBitHistogram_ASM(uint16_t width, uint16_t height, uint8_t *p_image, uint16_t *p_histogram);
extern uint16_t IMAGE_SIZE;

uint16_t EightBitHistogram_C(uint16_t width, uint16_t height, uint8_t *p_image, uint16_t *p_histogram);
void send_csv_file(uint16_t *p_histogram);
void UART_send_uint16_t(uint16_t number);

//RAM definitions
unsigned long ram_buffer[72/4];
void copy_from_flash_to_ram(void *source, void *destiny, int size);
typedef uint16_t (*ram_function_t)(uint16_t, uint16_t, uint8_t*, uint16_t*);

int main(void)
{
  SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240), 120000000);
	
  //executa configuração e inicialização do SysTick
  SetupSystick();
	
	//executa configuração e inicialização da UART
	SetupUart();
	
	//copying EightBitHistogram_ASM to RAM
	//-1 because of THUMB instructions
	copy_from_flash_to_ram((void*)((int)EightBitHistogram_ASM-1), (void*)ram_buffer, 72);
	
//	//EightBitHistogram_ASM_ram points to ram_buffer
	ram_function_t EightBitHistogram_ASM_ram;
	EightBitHistogram_ASM_ram = (ram_function_t)((int)ram_buffer+1);
	
	uint16_t histogram[256];

////	uint16_t image0_size = EightBitHistogram_C(HEIGHT0, WIDTH0, image0, histogram);
////	send_csv_file(histogram);
//	
//	uint16_t image1_size = EightBitHistogram_C(HEIGHT1, WIDTH1, image1, histogram);
//	send_csv_file(histogram);
//	
	uint16_t image0_size_asm = EightBitHistogram_ASM(HEIGHT0, WIDTH0, (uint8_t*)image0, histogram);
	send_csv_file(histogram);
	
	uint16_t image1_size_asm = EightBitHistogram_ASM(HEIGHT1, WIDTH1, (uint8_t*)image1, histogram);
	send_csv_file(histogram);
//	
//	uint16_t image0_size_ASM_ram = EightBitHistogram_ASM_ram(HEIGHT0, WIDTH0, (uint8_t*)image0, histogram);
//	send_csv_file(histogram);
	
//	uint16_t image1_size_ASM_ram = EightBitHistogram_ASM_ram(HEIGHT1, WIDTH1, (uint8_t*)image1, histogram);
//	send_csv_file(histogram);
}

//função de tratamento da interrupção do SysTick
void SysTickIntHandler(void)
{
  SysTicks++;
}

//função para configurar e inicializar o periférico Systick a 1ms
void SetupSystick(void)
{
  SysTicks=0;
	
  //desliga o SysTick para poder configurar
  SysTickDisable();
	
  //clock 40MHz <=> SysTick deve contar 1ms=40k-1 do Systick_Counter - 12 trocas de contexto PP->IRQ - (1T Mov, 1T Movt, 3T LDR, 1T INC ... STR e IRQ->PP já não contabilizam atrasos para a variável)  
  SysTickPeriodSet(40000-1-12-6);
	
  //registra a função de atendimento da interrupção
  SysTickIntRegister(SysTickIntHandler);
	
  //liga o atendimento via interrupção
  SysTickIntEnable();
	
  //liga novamente o SysTick
  SysTickEnable();
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
	
	while(size)
	{
		*destiny_uint8_t = *source_uint8_t;
		destiny_uint8_t++;
		source_uint8_t++;
		size--;
	}
}
