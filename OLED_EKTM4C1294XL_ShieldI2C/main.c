/*##############################################################################
Prof. Paulo Denis Garcez da Luz - 2023/2S
Desenvolvido para a placa EK-TM4C1294XL utilizando o SDK TivaWare no KEIL
Programa exemplo de uso do Shield: LCD-I2C+Teclado, Periférico Gpio, SysTick,
I2C0 e I2c7.
##############################################################################*/

//TivaWare uC: Usado internamente para identificar o uC em alguns .h
#define PART_TM4C1294NCPDT 1

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

#include "i2c.h"
#include "ssd1306.h"
#include "bitmap.h"
#include "teclado.h"

//variável que conta os ticks(1ms) - Volatile não permite o compilador otimizar o código 
static volatile unsigned int SysTicks1ms;

//Protótipos de funções criadas no programa:
void SetupSystick(void);
void SysTickIntHandler(void);
void PortM_config(void);
void PortL_config(void);
void I2C0_config(void);
void I2C0_sendSingleByte(uint8_t slave_addr, char data);
void I2C0_sendMultipleBytes(uint8_t slave_addr, uint8_t numOfBytes, char by[]);
void I2C7_config(void);
void I2C7_sendSingleByte(uint8_t slave_addr, char data);
void I2C7_sendMultipleBytes(uint8_t slave_addr, uint8_t numOfBytes, char by[]);

int main (void)
{
//controle de tempo para cada oled0, oled7:
unsigned int oled0time=0, oled7time=0, tecladotime=0;
//controle de estado do oled0, tecla:
unsigned char oled0state=0, keyc=21, Tecla;
//Configura o clock para utilizar o xtal interno de 16MHz com PLL para 80MHz
SysCtlClockFreqSet(SYSCTL_OSC_INT | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_320, 80000000);
//executa configuração e inicialização do SysTick
SetupSystick();
//executa configuração e inicialização do Port L
PortL_config();
//executa configuração e inicialização do Port M
PortM_config();	
//Tempo de 5s antes de começar o Blinky:
oled0time=SysTicks1ms+2000;
//Inicializa periférico I2C0:
I2C0_config();
//config 128x64:	
OLED0_Init();
//Limpa Buffer do Display Oled0
SSD1306_I2C0_cls();
//Desenha a Logo da Utfpr no Buffer do Oled0
SSD1306_I2C0_DrawBitmap(0,9,UtfprLogo,128,45);
//Atualiza o Buffer para a tela do Oled0
SSD1306_I2C0_UpdateScreen();
//Inicializa periférico I2C7:
I2C7_config();
//config 128x32:
OLED7_Init();
//Limpa Display Oled7
OLED7_clearDisplay();
//Escreve String no Oled7 x,y I=invertido
OLED7_sendStrXYI("@DaLuz", 0, 0);
//Escreve String no Oled7 x,y I=invertido
OLED7_sendStrXYI("ELF52 / ELF74", 1, 0);
//Escreve String no Oled7 x,y I=invertido
OLED7_sendStrXYI("UTFPR - Daeln", 2, 0);
//Escreve String no Oled7 x,y I=invertido
OLED7_sendStrXYI("Teccla: [ ]-[ ]", 3, 0);
//Escreve Caractere na posição x,y I=invertido
OLED7_sendCharXYI('?', 3, 9);
while (1)
      {
		    //Varre teclado Matricial 4x4
				Tecla=VarreTeclado();
	      //Caso nenhuma tecla
				if (Tecla==0) Tecla='?'; 
        //controle temporal do oled0
        if (SysTicks1ms>=tecladotime)
           {
             //tempo do teclado recebe o tempo atual + o tempo futuro para entrar novamente no if (100ms)
             tecladotime=SysTicks1ms+100;
						 //Escreve Caractere na posição x,y I=invertido
             OLED7_sendCharXYI(Tecla, 3, 9);
					 }
        //controle temporal do oled0
        if (SysTicks1ms>=oled0time)
           {
             //tempo do oled0 recebe o tempo atual + o tempo futuro para entrar novamente no if (2s)
             oled0time=SysTicks1ms+2000;
             //Limpa Buffer do Display Oled0
			       SSD1306_I2C0_cls();
             // flag para alteranar a Logo da Utfpr com os icones
						 if (oled0state) SSD1306_I2C0_DrawBitmap(0,9,UtfprLogo,128,45);
						 else
							  {
									//Desenha bitmap no Buffer do Oled0
									SSD1306_I2C0_DrawBitmap(0, 0, bitmap7, 24, 24);
									SSD1306_I2C0_DrawBitmap(26, 0, bitmap8, 24, 24);
									SSD1306_I2C0_DrawBitmap(54, 0, bitmap11, 24, 24);
									SSD1306_I2C0_DrawBitmap(82, 0, bitmap9, 24, 24);
									SSD1306_I2C0_DrawBitmap(106, 0, bitmap10, 24, 24);
									SSD1306_I2C0_DrawBitmap(0, 30, bitmap12, 24, 24);
									SSD1306_I2C0_DrawBitmap(26, 30, bitmap13, 24, 24);
									SSD1306_I2C0_DrawBitmap(54, 30, bitmap14, 24, 24);
									SSD1306_I2C0_DrawBitmap(82, 30, bitmap15, 24, 24);
									SSD1306_I2C0_DrawBitmap(106, 30, bitmap6, 24, 24);
								}
						 //altera estado da flag
						 oled0state=!oled0state;
						 //Atualiza o Buffer para a tela do Oled0
             SSD1306_I2C0_UpdateScreen();
           }
				//controle temporal do oled7 - Blinky de Caracteres no olde7
        if (SysTicks1ms>=oled7time)
           {
             //tempo do oled7 recebe o tempo atual + o tempo futuro para entrar novamente no if (333ms)
						 oled7time=SysTicks1ms+333;
						 //Escreve Caractere na posição x,y I=invertido
             OLED7_sendCharXYI(keyc, 3, 13);
						 //contador de caracteres para mostrar todos os caracteres no Oled7
						 keyc++;
						 //Volta para o primeiro caractere
						 if (keyc>=128) keyc=21;
					 }
			}
}

//função de tratamento da interrupção do SysTick
void SysTickIntHandler(void)
{
  SysTicks1ms++;
}

//função para configurar e inicializar o periférico Systick a 1ms
void SetupSystick(void)
{
  SysTicks1ms=0;
  //desliga o SysTick para poder configurar
  SysTickDisable();
  //clock 40MHz <=> SysTick deve contar 1ms=80k-1 do Systick_Counter - 12 trocas de contexto PP->IRQ - (1T Mov, 1T Movt, 3T LDR, 1T INC ... STR e IRQ->PP já não contabilizam atrasos para a variável)  
  SysTickPeriodSet(80000-1-12-6);
  //registra a função de atendimento da interrupção
  SysTickIntRegister(SysTickIntHandler);
  //liga o atendimento via interrupção
  SysTickIntEnable();
  //liga novamente o SysTick
  SysTickEnable();
}

//função para configurar e inicializar o periférico Port M output
void PortM_config(void)
{
//habilitar gpio port M
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
//aguardar o periférico ficar pronto para uso
while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM)) {/*Espera habilitar o port*/}
//configura o pin_4, pin_5, pin_6 e pin_7 como saída
GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6  | GPIO_PIN_7);
}

//função para configurar e inicializar o periférico Port L input
void PortL_config(void)
{
//habilitar gpio port L
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
//aguardar o periférico ficar pronto para uso
while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOL)) {/*Espera habilitar o port*/}
//configura o pin_0, pin_1, pin_2 e pin_3 como entrada
GPIOPinTypeGPIOInput(GPIO_PORTL_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
//configura os pinos para 2mA como limite de corrente e com week pull-up
GPIOPadConfigSet(GPIO_PORTL_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

void I2C0_config(void)
{
// Configure I2C0 for pins PB2 and PB3
SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
while (!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C0) || !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB));  
//Configuração da PORTB PIN2 e PIN3 - B.M.
GPIOPinConfigure(GPIO_PB2_I2C0SCL);
GPIOPinConfigure(GPIO_PB3_I2C0SDA);
GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);
I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);
}

void I2C0_sendSingleByte(uint8_t slave_addr, char data)
{
I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);
I2CMasterDataPut(I2C0_BASE, data);
I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
while(I2CMasterBusy(I2C0_BASE));
}

void I2C0_sendMultipleBytes(uint8_t slave_addr, uint8_t numOfBytes, char by[])
{
uint8_t i;
I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);
I2CMasterDataPut(I2C0_BASE, by[0]);
I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
while(I2CMasterBusy(I2C0_BASE));
for (i = 1; i < numOfBytes - 1; i++)
	  {
      I2CMasterDataPut(I2C0_BASE, by[i]);
      I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
      while(I2CMasterBusy(I2C0_BASE));
    }
I2CMasterDataPut(I2C0_BASE, by[numOfBytes - 1]);
I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
while(I2CMasterBusy(I2C0_BASE));
}

void I2C7_config(void)
{
SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C7);
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
while (!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C7) || !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD));  
//Configuração da PORTD PIN0 e PIN1 - B.M.
GPIOPinConfigure(GPIO_PD0_I2C7SCL);
GPIOPinConfigure(GPIO_PD1_I2C7SDA);
GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_0);
GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_1);
I2CMasterInitExpClk(I2C7_BASE, SysCtlClockGet(), false);
}

void I2C7_sendSingleByte(uint8_t slave_addr, char data)
{
I2CMasterSlaveAddrSet(I2C7_BASE, slave_addr, false);
I2CMasterDataPut(I2C7_BASE, data);
I2CMasterControl(I2C7_BASE, I2C_MASTER_CMD_SINGLE_SEND);
while (I2CMasterBusy(I2C7_BASE));
}

void I2C7_sendMultipleBytes(uint8_t slave_addr, uint8_t numOfBytes, char by[])
{
uint8_t i;
I2CMasterSlaveAddrSet(I2C7_BASE, slave_addr, false);
I2CMasterDataPut(I2C7_BASE, by[0]);
I2CMasterControl(I2C7_BASE, I2C_MASTER_CMD_BURST_SEND_START);
while(I2CMasterBusy(I2C7_BASE));
for (i = 1; i < numOfBytes - 1; i++)
	  {
			I2CMasterDataPut(I2C7_BASE, by[i]);
			I2CMasterControl(I2C7_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
			while (I2CMasterBusy(I2C7_BASE));
    }
I2CMasterDataPut(I2C7_BASE, by[numOfBytes - 1]);
I2CMasterControl(I2C7_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
while (I2CMasterBusy(I2C7_BASE));
}
