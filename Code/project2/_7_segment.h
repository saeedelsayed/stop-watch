/**************************************************************************************************************
 *
 * MODULE: _7_SEGMENT
 *
 * FILE NAME: _7_segment.h
 *
 * Description: Header file for the _7_segment driver
 *
 * Created on: 8/16/2024
 *
 * Author: Saeed Elsayed
 *
 **************************************************************************************************************/

#ifndef _7_SEGMENT_H_
#define _7_SEGMENT_H_

#include "gpio.h"

#define _7_SEGMENT_DECODER_PORT       PORTC_ID
#define _7_SEGMENT_DECODER_FIRST_PIN  PIN0_ID

#define _7_SEGMENTS_PORT              PORTA_ID
#define _1st_7_SEGMENTS_PIN           PIN0_ID

/*
 * Description:
 * Function to initialize 7 segments pins directions
 * */
void _7_segmentInit();

/*
 * Description:
 * Function to display the numbers on 7 segments
 * */
void _7_segmentDisplay();

#endif /* _7_SEGMENT_H_ */
