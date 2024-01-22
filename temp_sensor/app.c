 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: main.c
 *
 * Description: Mini Project 3
 *
 * Author: Mahmoud Magdy Mahmoud Ali
 *
 *******************************************************************************/

#include "std_types.h"
#include "lcd.h"
#include "adc.h"
#include "dc-motor.h"
#include "lm35_sensor.h"

int main()
{
	uint8 tempetaure = 0 , speed = 0;

	LCD_init();		/* LCD Display Initialization */
	DcMotor_Init();		/* Motor Initialization */

	ADC_ConfigType ADC_MyConfiguration = {Internal_ReferenceVolt , ADC_PRESCALER_8};

	ADC_init(&ADC_MyConfiguration);	/* ADC Initialization */

	LCD_displayStringRowColumn(0,4,"Temp  = ");
	LCD_displayStringRowColumn(1,4,"FAN is ");

	while(1){
		tempetaure = LM35_getTemperature();

				if(tempetaure < 30){
					speed = 0;
					LCD_displayStringRowColumn(1,12,"OFF");
				}
				else if (tempetaure < 60){
					speed = 25;
					LCD_displayStringRowColumn(1,12,"ON ");
				}
				else if (tempetaure < 90){
					speed = 50;
					LCD_displayStringRowColumn(1,12,"ON ");
				}
				else if (tempetaure < 120){
					speed = 75;
					LCD_displayStringRowColumn(1,12,"ON ");
				}
				else{
					speed = 100;
					LCD_displayStringRowColumn(1,12,"ON ");
				}
				DcMotor_Rotate(CW , speed);

				LCD_moveCursor(0,9);
				LCD_intgerToString(tempetaure);
				if(tempetaure < 10)
					LCD_displayString("  ");
				else if(tempetaure < 100)
					LCD_displayString(" ");

				LCD_displayCharacter('C');

	}

}
