 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega32 ADC driver
 *
 * Author: Mahmoud Magdy Mahmoud Ali
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
#include "adc.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "std_types.h"

float32 ADC_ReferenceVoltValue;	/* Variable that sensors will use in its calculations

/*
*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************
*/
void ADC_init(const ADC_ConfigType * Config_Ptr)
{

	switch(Config_Ptr->ref_volt){
		case AVCC:
			ADC_ReferenceVoltValue = 5;
			break;

		case Internal_ReferenceVolt:
			ADC_ReferenceVoltValue = 2.56;
			break;
		}

		/* ADMUX Register Bits Description:
		 -> REFS1:0 = 01 to choose the reference voltage
		 -> ADLAR   = 0 (right adjusted)
		 -> MUX4:0  = 00000 to choose channel 0 as initialization
		 */
		ADMUX = (ADMUX & 0x3F) | ((Config_Ptr->ref_volt)<<6);

		/* ADCSRA Register Bits Description:
		 -> ADEN    = 1 Enable ADC
		 -> ADIE    = 0 Disable ADC Interrupt
		 -> ADATE   = 0 Disable Auto Trigger
		 -> ADPS2:0  = selecting the prescaler.
		 */
		ADCSRA = (1<<ADEN) ;

		ADCSRA = (ADCSRA & 0xF8) | (Config_Ptr->prescaler);
}

uint16 ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x1F; /* Input channel number must be from 0 --> 7 */

	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */

	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */

	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */

	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */

	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */

	return ADC; /* Read the digital value from the data register */
}
