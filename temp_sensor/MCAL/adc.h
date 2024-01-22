 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ATmega32 ADC driver
 *
 * Author: Mahmoud Magdy Mahmoud Ali
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   5



/*******************************************************************************
 *                             Type Decelerations                               *
 *******************************************************************************/

typedef enum{
	AREF,AVCC,Internal_ReferenceVolt=3
}ADC_ReferenceVolatge;


typedef enum{
	ADC_PRESCALER_2=1,ADC_PRESCALER_4,ADC_PRESCALER_8,ADC_PRESCALER_16,ADC_PRESCALER_32,
	ADC_PRESCALER_64,ADC_PRESCALER_128
}ADC_Prescaler;


typedef struct{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern Public global variables to be used by other modules */
extern float32 ADC_ReferenceVoltValue;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 * Function take a structure containing the configuration parameters.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num);

#endif /* ADC_H_ */


