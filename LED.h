#ifndef LED_H_
#define LED_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

typedef struct
{
	volatile uint8_t* port;   
	// LED 연결 포트  내가 가지고 있는 데이터형 uint8
	//볼렛타일 컴파일러 최적화(skip)하지 말고 순서대로 처리
	uint8_t pinNumber;         // LED 연결 핀 번호
} LED_S; //LED_S 라는 typedef 를 사용한 자료형 재정의

// LED 초기화 함수: 지정된 핀을 출력으로 설정
void ledInit(LED_S* led) {
	//DDRB=0xff;
	*(led->port - 1) |= 0xff; //(1 << led->pinNumber); 핀 0번을 출력으로 쓴다
//PORTB - 1 ==DDRB B포트를 출력으로 쓴다
}

// LED ON 함수: 지정된 핀을 HIGH로 설정
void ledON(LED_S* led) {
	*(led->port) |= (1 << led->pinNumber);  // 해당 핀을 HIGH로 설정
}

// LED OFF 함수: 지정된 핀을 LOW로 설정
void ledOFF(LED_S* led) {
	*(led->port) &= ~(1 << led->pinNumber);  // 해당 핀을 LOW로 설정
}

#endif /* LED_H_ */
