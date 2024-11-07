/*##############################################################################
Prof. Paulo Denis Garcez da Luz - 2023/2S
Desenvolvido para a placa EK-TM4C1294XL utilizando o SDK TivaWare no KEIL
Programa exemplo de blink usando 4 led, 2 botões e Periférico SysTick.
##############################################################################*/

//TivaWare uC: Usado internamente para identificar o uC em alguns .h da TivaWare
#define PART_TM4C1294NCPDT 1

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

//variável que conta os ticks(1ms) - Volatile não permite o compilador otimizar o código 
static volatile unsigned int SysTicks1ms;

//Protótipos de funções criadas no programa, código depois do main
void SysTickIntHandler(void);
void SetupSystick(void);

int main(void)
{
  //estado de cada led
  bool Led1=false,Led2=false,Led3=false,Led4=false;
  //controle via programação de anti-debouncing
  bool bt1flag=false,bt2flag=false;
  //controle de tempo para cada led
  unsigned int led1time=0,led2time=0;
  //controle de tempo para cada botão
  unsigned int bt1time=0,bt2time=0;
  //Configura o clock para utilizar o xtal externo de 25MHz
  SysCtlClockFreqSet(SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_OSC, 25000000);
  //executa configuração e inicialização do SysTick
  SetupSystick();  
  //habilitar gpio port N
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
  //aguardar o periférico ficar pronto para uso
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {/*Espera habilitar o port*/}
  //habilitar gpio port F
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  //aguardar o periférico ficar pronto para uso
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {/*Espera habilitar o port*/}
  //configura o pin_0 e pin_1 como saída
  //habilitar gpio port J
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
  //aguardar o periférico ficar pronto para uso
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)) {/*Espera habilitar o port*/}
  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1);
  //configura o pin_0 e pin_4 como saída
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
  //configura o pin_0 e pin_1 como entrada
  GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1);
  //configura os pinos para 2mA como limite de corrente e com week pull-up
  GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
  //loop infinito
  while (1)
        {
          //descomente o printf para entender os valores lidos dos botões ... modo debug com termial I/O
          //printf("Port J: Pin_0: [%d] - Pin_1: [%d]\n",GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_0),GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_1));
          //controle temporal do led1 - tempo 1s = 1000ms
          if (SysTicks1ms>=led1time)
             {
               //tempo do led recebe o tempo atual + o tempo futuro para entrar novamente no if
               led1time=SysTicks1ms+1000;
               //altera o estado do led ligado / desligado
               Led1=!Led1;
               //escreve o estado do led no pino
               GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, Led1<<1);
             }
          //controle temporal do led2 - tempo 0,5s = 500ms
          if (SysTicks1ms>=led2time)
             {
               //tempo do led recebe o tempo atual + o tempo futuro para entrar novamente no if
               led2time=SysTicks1ms+500;
               //altera o estado do led ligado / desligado
               Led2=!Led2;
               //escreve o estado do led no pino
               GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, Led2);
             }
          //ant-debouncig do botão 1
          if (bt1flag) 
	     {
	       //Botão1 liberado !!!
	       if (GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_0)&&SysTicks1ms>=bt1time)
	          {
	            //botão liberado
                    bt1flag=false;
	            //55ms para liberar estado do botão ... tempo anti-debouncing
                    bt1time=SysTicks1ms+55;				 
	          }
	     }
          else
	     {
	       //botão1 pressionado !!!
	       if ((GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_0)==0)&&(SysTicks1ms>=bt1time))
	          {
	            //botão pressionado
	            bt1flag=true;
	            //55ms para liberar estado do botão ... tempo anti-debouncing
	            bt1time=SysTicks1ms+55;				 
                    //altera o estado do led ligado / desligado
                    Led3=!Led3;
                    //escreve o estado do led no pino
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, Led3<<4);
	          }
	     }
          //ant-debouncig do botão 2
          if (bt2flag) 
	     {
	       //botão2 liberado !!!
	       if (GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_1)&&(SysTicks1ms>=bt2time))
	          {
	            //botão liberado
                    bt2flag=false;
	            //55ms para liberar estado do botão ... tempo anti-debouncing
                    bt2time=SysTicks1ms+55;				 
	          }
	     }
          else
	     {
	       //botão2 pressionado !!!
	       if ((GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_1)==0)&&(SysTicks1ms>=bt2time))
	          {
	            //botão pressionado
	            bt2flag=true;
	            //55ms para liberar estado do botão ... tempo anti-debouncing
	            bt2time=SysTicks1ms+55;				 
                    //altera o estado do led ligado / desligado
                    Led4=!Led4;
                    //escreve o estado do led no pino
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, Led4);
	          }
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
  //clock 25MHz <=> SysTick deve contar 1ms=25k-1 do Systick_Counter - 12 trocas de contexto PP->IRQ - (1T Mov, 1T Movt, 3T LDR, 1T INC ... STR e IRQ->PP já não contabilizam atrasos para a variável)  
  SysTickPeriodSet(25000-1-12-6);
  //registra a função de atendimento da interrupção
  SysTickIntRegister(SysTickIntHandler);
  //liga o atendimento via interrupção
  SysTickIntEnable();
  //liga novamente o SysTick
  SysTickEnable();
}
