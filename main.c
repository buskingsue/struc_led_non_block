#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LED.h"

int main()
{
	//DDRB = 0xff;

	// 구조체 변수 선언 및 초기화
	LED_S m_led;
	m_led.port = &PORTB;   // 포트 B 사용
	m_led.pinNumber = 0;   // 초기 핀 번호는 0번

	// LED 초기화
	ledInit(&m_led);
	while (1)
	{
		ledON(&m_led);     // 현재 핀의 LED 켜기
		_delay_ms(300);    // 300ms 대기
		ledOFF(&m_led);    // 현재 핀의 LED 끄기
		_delay_ms(300);    // 300ms 대기

		// 다음 핀으로 이동
		m_led.pinNumber++;
		if (m_led.pinNumber == 8) // 핀 번호가 8 이상이 되면 0으로 초기화
		m_led.pinNumber = 0;
		
	}
}
