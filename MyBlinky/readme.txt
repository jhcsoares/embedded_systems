/*##############################################################################
Prof. Paulo Denis Garcez da Luz - 2023/2S
Desenvolvido para a placa EK-TM4C1294XL utilizando o SDK TivaWare no KEIL
Programa exemplo de blink(1s) usando apenas 1 led e Periférico SysTick.
##############################################################################*/

Exemplo para aprender a configurar o projeto no KEIL.

Ver as figuras abaixo e configurar o projeto de forma identica:

Incluir os arquivos: main.c | startup_rvmdk.S no projeto - (Source)
Incluir o driverlib.lib (..\TivaWare_C_Series-2.2.0.295\driverlib\) - (Libraries)
Incluir o readme.txt - (Documentation)

Options:
Fig0_Device.png    -> Escolher: TM4C1294NCPDT
Fig1_Target.png    -> ARM Compiler: use default compilar version 5
Fig2_Output.png    -> Check: Create HEX file
Fig3_Listing.png   -> Verificar os checkBoxes ...
fig4_User.png      -> After Build/Rebuild - Run #1: fromelf.exe --bin Objects\MyBlinky.axf --output Objects\MyBlinky.bin
fig5_C_C++.png     -> Include Paths: ..\TivaWare_C_Series-2.2.0.295 | Misc Controls: --c99
fig6_Asm.png       ->
fig7_Linker.png    -> Misc Controls: --entry Reset_Handler
fig8_Debug.png     -> Select: Stellaris ICDI
fig9_Utilities.png ->

Obs: o diretório "TivaWare_C_Series-2.2.0.295" deve estar presente no mesmo
nível que o diretório "MyBlinky" e deve estar previamente compilado.
Caso tenha problemas na compilação do TivaWare_C_Series pode descarregar
a versão do prof. pré-compilada em:
www.elf74.daeln.com.br/TivaWare_C_Series-2.2.0.295.zip

