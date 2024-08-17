/**************************************************************************************************************
 *
 * MODULE: _7_SEGMENT
 *
 * FILE NAME: _7_segment.c
 *
 * Description: Source file for the _7_segment driver
 *
 * Created on: 8/16/2024
 *
 * Author: Saeed Elsayed
 *
 **************************************************************************************************************/

#include "_7_segment.h"
#include "gpio.h"
#include <util/delay.h>


uint8 numbers[6] = {0, 0, 0, 0, 0, 0};

/*
 * Description:
 * Function to initialize 7 segments pins directions
 * */
void _7_segmentInit()
{
	for(uint8 i = 0; i < 4; i++)
	{
		GPIO_setupPinDirection(_7_SEGMENT_DECODER_PORT, _7_SEGMENT_DECODER_FIRST_PIN + i, PIN_OUTPUT);
	}

	for(uint8 i = 0; i < 6; i++)
	{
		GPIO_setupPinDirection(_7_SEGMENTS_PORT, _1st_7_SEGMENTS_PIN + i, PIN_OUTPUT);
	}

}

/*
 * Description:
 * Function to display the numbers on 7 segments
 * */
void _7_segmentDisplay()
{
	for(uint8 j = 0; j < 6; j++)
	{
		for(uint8 i = 0; i < 6; i++)
		{
			GPIO_writePin(_7_SEGMENTS_PORT, _1st_7_SEGMENTS_PIN + i, LOGIC_LOW);
		}

		GPIO_writePin(_7_SEGMENTS_PORT, _1st_7_SEGMENTS_PIN + j, LOGIC_HIGH);

		for(uint8 i = 0; i < 4; i++)
		{
			GPIO_writePin(_7_SEGMENT_DECODER_PORT, _7_SEGMENT_DECODER_FIRST_PIN + i, LOGIC_LOW);
		}

		GPIO_writePort(_7_SEGMENT_DECODER_PORT, numbers[j]);
		_delay_ms(2);
	}
}
