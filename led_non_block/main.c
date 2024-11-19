//blocking delay
//non blocking millis 함수
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
 
int main(void)
{
	DDRA = 0xff;
	DDRB =0xff; // 0b11111111 -> 출력 설정

	PORTB = 0x00;
	PORTA = 0x00;

	while (1)
	{
		PORTB ^= 0xff;
		_delay_ms(1000);
		PORTA ^= 0xff;
		_delay_ms (500);
	}
}