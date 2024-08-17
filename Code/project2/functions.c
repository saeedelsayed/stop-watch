#include <avr/io.h>
#include <avr/interrupt.h>
#include "std_types.h"


extern uint8 numbers[6];

unsigned char old_TCNT1; // will carry the value of TCNT1 if we paused and will return it again to
                         // the TCNT1 if we resumed

ISR(TIMER1_COMPA_vect)
{ // changing the showed numbers every time an interrupt is executed
	if(numbers[0] == 9)
	{
		numbers[0]=0;
		if(numbers[1] == 5)
		{
			numbers[1]=0;
			if(numbers[2] == 9)
			{
				numbers[2] = 0;
				if(numbers[3] == 5)
				{
					numbers[3] =0;
					if(numbers[4] == 9)
					{
						numbers[4] = 0;
						if(numbers[5] == 9)
						{
							numbers[5] = 0;
						}
						else
						{
							numbers[5]++;
						}
					}
					else
					{
						numbers[4]++;
					}
				}
				else {
					numbers[3]++;
				}
			}
			else
			{
				numbers[2]++;
			}
		}
		else{
			numbers[1]++;
		}
	}
	else
	{
		numbers[0]++;
	}
}

ISR(INT0_vect){ // making all 7 segments = 0 for resetting
	numbers[0]=0;
	numbers[1]=0;
	numbers[2]=0;
	numbers[3]=0;
	numbers[4]=0;
	numbers[5]=0;
	TCNT1=0;   // clear counter register
	TIFR |= (1<<OCF1A);  // clear the Output Compare A Match Flag to prevent
	                     // the interrupt form executing after the reset
	TIMSK |= (1<<OCIE1A);// enable the interrupt for compare register A if it was disabled after INT1

}

ISR(INT1_vect){   // pause the stop watch
	TIMSK &=  ~(1<<OCIE1A); // disable the interrupt for compare register A so the incrementation will not happen
	old_TCNT1 = TCNT1;      // keep the value of TCNT1 to reuse it in the resume
}

ISR(INT2_vect){
	if(!(TIMSK & (1<<OCIE1A))){   // checking if the pause is applied or not so that not change the value
								  // of TCNT1 in every time the push button of INT2 is pushed

    TIFR |= (1<<OCF1A);           // clear the Output Compare A Match Flag to prevent
                                  // the interrupt form executing after the resume

	TIMSK |= (1<<OCIE1A);         // enable the interrupt for compare register A
    TCNT1 =old_TCNT1;             // restoring the value of TCNT1 when the stop watch was paused
	}
}
