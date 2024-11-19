#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

// 밀리초를 저장할 변수
volatile unsigned long millis_counter = 0;

// 밀리초 반환 함수
unsigned long millis() {
	unsigned long millis_copy;
	cli(); // 인터럽트 비활성화
	millis_copy = millis_counter;
	sei(); // 인터럽트 활성화
	return millis_copy;
}

// Timer0 초기화 함수
void timer0_init() {
	// CTC 모드 설정 (Clear Timer on Compare Match)
	TCCR0 = (1 << WGM01); // WGM01 = 1 (CTC 모드)
	
	// 분주비 설정 (64 분주)
	TCCR0 |= (1 << CS01) | (1 << CS00); // CS01 = 1, CS00 = 1

	// 비교값 설정 (1ms 기준)
	OCR0 = 250 - 1; // (16MHz / 64) / 1000 - 1 = 250 - 1

	// 비교 일치 인터럽트 허용
	TIMSK |= (1 << OCIE0); // OCIE0 = 1
}

// Timer0 비교 일치 인터럽트 서비스 루틴
ISR(TIMER0_COMP_vect) {
	millis_counter++;
}

int main(void) {
	// LED 토글 간격 설정
	const unsigned long intervalB = 500; // B포트 LED (0.5초)
	const unsigned long intervalA = 1000; // A포트 LED (1초)

	unsigned long previousMillisB = 0; // B포트 이전 시간
	unsigned long previousMillisA = 0; // A포트 이전 시간

	// B 포트와 A 포트를 출력으로 설정
	DDRB = 0xFF; // B포트를 출력으로 설정
	DDRA = 0xFF; // A포트를 출력으로 설정

	// 초기 LED 상태
	PORTB = 0x00;
	PORTA = 0x00;

	// Timer0 초기화 및 인터럽트 활성화
	timer0_init();
	sei(); // 전역 인터럽트 활성화

	while (1) {
		unsigned long currentMillis = millis();

		// B 포트 LED 깜박임
		if (currentMillis - previousMillisB >= intervalB) {
			PORTB ^= 0xFF; // B포트의 모든 핀 상태 토글
			previousMillisB = currentMillis;
		}

		// A 포트 LED 깜박임
		if (currentMillis - previousMillisA >= intervalA) {
			PORTA ^= 0xFF; // A포트의 모든 핀 상태 토글
			previousMillisA = currentMillis;
		}
	}
}
