/*##############################################################################
Prof. Paulo Denis Garcez da Luz - 2023/2S
Desenvolvido para a placa EK-TM4C1294XL utilizando o SDK TivaWare no KEIL
Programa exemplo de blink usando 4 led, 2 botões, Periférico SysTick e UART0.
##############################################################################*/

Exemplo para aprender a configurar o projeto no KEIL.
Algumas utilizações do SDK Tivaware neste exemplo: Systick, GPIO e UART.

Obs: Para executar a comunicação serial com o Kit utilizar os programas na pasta
do projeto: RComSerial.exe ou sscom3.2.exe (Porta COM - 115200,8,1)
Comandos PC -> Placa: 1) AT00 e 2) AT01
Comandos Placa -> PC: 1) BOTAO_01_PRESS <- USR_SW1 - Led ON/OFF
USR_SW2 - Led ON/OFF

Ver as figuras abaixo e configurar o projeto de forma identica:

Incluir os arquivos: main.c | startup_rvmdk.S no projeto - (Source)
Incluir o driverlib.lib (..\TivaWare_C_Series-2.2.0.295\driverlib\) - (Libraries)
Incluir o readme.txt - (Documentation)

Options:
Fig0_Device.png    -> Escolher: TM4C1294NCPDT
Fig1_Target.png    -> ARM Compiler: use default compilar version 5
Fig2_Output.png    -> Check: Create HEX file
Fig3_Listing.png   -> Verificar os checkBoxes ...
fig4_User.png      -> After Build/Rebuild - Run #1: fromelf.exe --bin Objects\MyBlinky4.axf --output Objects\MyBlinky4.bin
fig5_C_C++.png     -> Include Paths: ..\TivaWare_C_Series-2.2.0.295 | Misc Controls: --c99
fig6_Asm.png       ->
fig7_Linker.png    -> Misc Controls: --entry Reset_Handler
fig8_Debug.png     -> Select: Stellaris ICDI
fig9_Utilities.png ->
fig10_SScom32.png  -> sscom32.exe programa de comunicação com UART0, 115200bps CMD: AT00, AT01 ...

Obs: o diretório "TivaWare_C_Series-2.2.0.295" deve estar presente no mesmo
nível que o diretório "MyBlinky4" e deve estar previamente compilado.
Caso tenha problemas na compilação do TivaWare_C_Series pode descarregar
a versão do prof. pré-compilada em:
www.elf74.daeln.com.br/TivaWare_C_Series-2.2.0.295.zip

