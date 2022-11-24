#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char s1 =0;    // the number which will be displayed on the first 7 segment
unsigned char s2 =0;    // the number which will be displayed on the second 7 segment
unsigned char m1 =0;    // the number which will be displayed on the third 7 segment
unsigned char m2 =0;    // the number which will be displayed on the 4th 7 segment
unsigned char h1 =0;    // the number which will be displayed on the 5th 7 segment
unsigned char h2 =0;    // the number which will be displayed on the 6th 7 segment

unsigned char old_TCNT1; // will carry the value if TCNT1 if we paused and will return it again to
                         // the TCNT1 if we resumed




void init(){

	DDRC |= 0x0f;      // set the first four pins in port c as output pins
	DDRA |= 0x3f;      // set the first sex pins in port a as output pins
	DDRD &= ~(1<<PD2);   // activate internal
	PORTD |= (1<<PD2);	 // pull up resistor for INT0
	TCCR1A |= (1<<FOC1A) | (1<<FOC1B);
	TCCR1B |= (1<<CS10) | (1<<CS12) | (1<<WGM12);     //choosing the prescaler to be 1024    setting the compare mode
	TCNT1 =0;
	OCR1A = 1000;                  // compare will happen every 1s (1000 ms)
	TIMSK |=  (1<<OCIE1A);         // enable the interrupt for compare register A
	SREG |= (1<<7);                // enable the interrupt
	MCUCR |= (1<<ISC01) | (1<<ISC11) | (1<<ISC10);    // setting INT0 with falling edge and INT1 with rising edge
	MCUCSR &= ~(1<<ISC2);                             // setting INT2 with falling edge
	GICR |= (1<<INT0) | (1<<INT1) | (1<<INT2);        // enable INT0 and INT1 and INT2

}

ISR(TIMER1_COMPA_vect){ // changing the showed numbers every time an interrupt is executed
	if(s1 == 9){
		s1=0;
		if(s2 == 5){
			s2=0;
			if(m1 == 9){
				m1 = 0;
				if(m2 == 5){
					m2 =0;
					if(h1 == 9){
						h1 = 0;
						if(h2 == 9){
							h2 = 0;
						}
						else
						{
							h2++;
						}
					}
					else
					{
						h1++;
					}
				}
				else {
					m2++;
				}
			}
			else
			{
				m1++;
			}
		}
		else{
			s2++;
		}
	}
	else
	{
		s1++;
	}
}

ISR(INT0_vect){ // making all 7 segments = 0 for resetting
	s1=0;
	s2=0;
	m1=0;
	m2=0;
	h1=0;
	h2=0;
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

void display(){
	// clear the first 6 pins in port a then choose which 7-SEG we want it to be showed and enable it
    // clear the first 4 pins in port c then choose the number we want to show it and enable its pins

	PORTA &= 0xc0;
	PORTA |= 0x20;
	PORTC &= 0xf0;
	PORTC |= s1;
	_delay_ms(2);

	PORTA &=0xc0;
	PORTA |= 0x10;
	PORTC &= 0xf0;
	PORTC |= s2;
	_delay_ms(2);

	PORTA &=0xc0;
	PORTA |= 0x08;
	PORTC &= 0xf0;
	PORTC |= m1;
	_delay_ms(2);

	PORTA &=0xc0;
	PORTA |= 0x04;
	PORTC &= 0xf0;
	PORTC |= m2;
	_delay_ms(2);

	PORTA &=0xc0;
	PORTA |= 0x02;
	PORTC &= 0xf0;
	PORTC |= h1;
	_delay_ms(2);

	PORTA &=0xc0;
	PORTA |= 0x01;
	PORTC &= 0xf0;
	PORTC |= h2;
	_delay_ms(2);

}



int main(void){


	init(); // the function which initialize the timer and the interrupts


	while(1){

		display(); // showing the numbers of the 7 segments

	}
}
