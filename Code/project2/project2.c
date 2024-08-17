#include<avr/io.h>
#include "timer1.h"
#include "_7_segment.h"


void init()
{
	DDRD &= ~(1<<PD2);   // activate internal
	PORTD |= (1<<PD2);	 // pull up resistor for INT0

	MCUCR |= (1<<ISC01) | (1<<ISC11) | (1<<ISC10);    // setting INT0 with falling edge and INT1 with rising edge
	MCUCSR &= ~(1<<ISC2);                             // setting INT2 with falling edge
	GICR |= (1<<INT0) | (1<<INT1) | (1<<INT2);        // enable INT0 and INT1 and INT2

	_7_segmentInit(); // initialize the pins of 7 segments to be output pins
	// initialize timer1 with 0 initial value, 1000 compare value, pre-scale 1024 and compare mode
	Timer1_ConfigType timer1_config = {0, 1000, F_CPU_1024, COMPARE_MODE};
	Timer1_init(&timer1_config);
}


int main(void)
{
	init(); // the function which initialize the timer and the interrupts

	while(1)
	{
		_7_segmentDisplay(); // showing the numbers of the 7 segments
	}
}
