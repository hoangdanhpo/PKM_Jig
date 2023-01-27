#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "lcd16x2.h"
#include "delay.h"

int main(void)
{
    // Delay initialization
    DelayInit();
    // LCD initialization
    LCD_Init();
    LCD_Gotoxy(6,0);
    LCD_Puts("Danh");

				
    while(1)
		{

		}

    		

}

