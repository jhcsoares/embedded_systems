/*##############################################################################
Prof. Paulo Denis Garcez da Luz - 2023/2S
Desenvolvido para a placa EK-TM4C1294XL utilizando o SDK TivaWare no KEIL
Programa exemplo de uso do Shield: LCD-I2C+Teclado, Periférico Gpio, SysTick,
I2C0 e I2c7.
##############################################################################*/

Exemplo para demonstração do Shield com o projeto no KEIL.
Algumas utilizações do SDK Tivaware neste exemplo: Systick, GPIO e I2C.

Ver as figuras abaixo e configurar o projeto de forma identica:

Incluir os arquivos: main.c | startup_rvmdk.S no projeto - (Source)
Incluir o driverlib.lib (..\TivaWare_C_Series-2.2.0.295\driverlib\) - (Libraries)
Incluir o readme.txt - (Documentation)

Options:
Fig0_Device.png    -> Escolher: TM4C1294NCPDT
Fig1_Target.png    -> ARM Compiler: use default compilar version 5
Fig2_Output.png    -> Check: Create HEX file
Fig3_Listing.png   -> Verificar os checkBoxes ...
fig4_User.png      -> After Build/Rebuild - Run #1: fromelf.exe --bin Objects\OLED_EKTM4C1294XL_TW.axf --output Objects\OLED_EKTM4C1294XL_TW.bin
fig5_C_C++.png     -> Include Paths: ..\TivaWare_C_Series-2.2.0.295 | Misc Controls: --c99
fig6_Asm.png       ->
fig7_Linker.png    -> Misc Controls: --entry Reset_Handler
fig8_Debug.png     -> Select: Stellaris ICDI
fig9_Utilities.png ->

Obs: o diretório "TivaWare_C_Series-2.2.0.295" deve estar presente no mesmo
nível que o diretório "MyBlinky4" e deve estar previamente compilado.
Caso tenha problemas na compilação do TivaWare_C_Series pode descarregar
a versão do prof. pré-compilada em:
www.elf74.daeln.com.br/TivaWare_C_Series-2.2.0.295.zip

Documentos para estudar o SSD1306:
\Docs\SSD1306.pdf  -> DataSheet do Display

Links Urls:
https://oledtutorials.blogspot.com/2020/06/tutorial-1-oled-basic-programming.html
https://www.youtube.com/watch?v=nZbA2qKRk30
https://www.youtube.com/watch?v=97_Vyph9EzM

https://mischianti.org/images-to-byte-array-online-converter-cpp-arduino/
https://javl.github.io/image2cpp/
https://github.com/rickkas7/DisplayGenerator
https://rickkas7.github.io/DisplayGenerator/index.html
https://xbm.jazzychad.net/
https://github.com/afiskon/stm32-ssd1306
https://github.com/lexus2k/ssd1306
https://controllerstech.com/oled-display-using-i2c-stm32/ -> oled.zip = \Docs\LSSD1606.rar

