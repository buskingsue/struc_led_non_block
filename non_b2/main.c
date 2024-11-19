#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile uint32_t timer0_millis = 0;

const uint8_t TIMER0_INITIAL_VALUE = 256 - (F_CPU / 64 / 1000);

void millisInit()
{
	TCCR0 &= ~((1 << WGM01) | (1 << WGM00)); // 일반 모드 설정
	TCCR0 |= (1 << CS01) | (1 << CS00); // 프리스케일러 64 설정
	TIMSK |= (1 << TOIE0); // Timer0 오버플로우 인터럽트 활성화
	TCNT0 = TIMER0_INITIAL_VALUE; // Timer0 카운터 초기화
	sei(); // 전역 인터럽트 활성화
}

ISR(TIMER0_OVF_vect)
{
	TCNT0 = TIMER0_INITIAL_VALUE; // 타이머 값을 재설정
	timer0_millis++; // 밀리초 카운터 증가
}

uint32_t millis()
{
	uint32_t millis_copy;
	cli(); // 일관된 값을 읽기 위해 인터럽트 비활성화
	millis_copy = timer0_millis;
	sei(); // 인터럽트 활성화
	return millis_copy;
}

int main(void)
{
	millisInit();
	DDRA = 0xff; // PORTA를 출력으로 설정
	DDRB = 0xff; // PORTB를 출력으로 설정
	PORTA = 0x00; // PORTA를 LOW로 초기화
	PORTB = 0x00; // PORTB를 LOW로 초기화

	uint32_t prevTime1 = 0;
	uint32_t prevTime2 = 0;

	while (1)
	{
		uint32_t currentTime = millis();

		// B 포트 1초 (1000ms)
		if (currentTime - prevTime1 >= 1000)
		{
			prevTime1 = currentTime;
			PORTB ^= 0xff; // PORTB 토글
		}
		// A 포트 0.5초 (500ms)
		if (currentTime - prevTime2 >= 500)
		{
			prevTime2 = currentTime;
			PORTA ^= 0xff; // PORTA 토글
		}
	}
}