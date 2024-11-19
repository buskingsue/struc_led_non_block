#include "led.h"

void ledInit(LED_S* led)
{
	//포트에 해당하는 핀을 출력으로 설정
	*(led->port - 1) |= (1 << led->pinNumber); // |= 복합 연산자 += 과 같음
}
void ledON(LED_S* led)
{
	*(led->port) |= (1 << led->pinNumber);
}
void ledOFF(LED_S* led)
{
	*(led->port) &= ~(1 << led->pinNumber);
}