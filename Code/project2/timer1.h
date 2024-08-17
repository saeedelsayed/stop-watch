/**************************************************************************************************************
 *
 * MODULE: TIMER1
 *
 * FILE NAME: timer1.h
 *
 * Description: HEADER file for the TIMER1 driver
 *
 * Created on: November 5, 2022
 *
 * Author: Saeed Elsayed
 *
 **************************************************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_

#include "std_types.h"



typedef enum /* choose the pre-scaler for timer1 */
{
	NO_CLOCK, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024
}Timer1_Prescaler;

typedef enum /* choose the mode of the timer */
{
	NORMAL_MODE, COMPARE_MODE = 4
}Timer1_Mode;

/*
 * Description:
 * structure to send the required initial values to TIMER1
 * */
typedef struct {
 uint16 initial_value;   /* TCNT1 initial value */
 uint16 compare_value; /* OCR1 value. it will be used in compare mode only */
 Timer1_Prescaler prescaler; /* pre-scaler to choose the required frequency of the timer */
 Timer1_Mode mode;   /* choose the mode of the timer */
} Timer1_ConfigType;


/*
 * Description:
 * Function to initialize the Timer driver
 * */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*
 * Description:
 * Function to disable the Timer1
 * */
void Timer1_deInit(void);

/*
 * Description:
 * Function to set the Call Back function address
 * */
void Timer1_setCallBack(void(*a_ptr)(void));




#endif /* TIMER1_H_ */
