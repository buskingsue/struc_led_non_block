#include "Button.h"
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR       DDRB
#define LED_PORT      PORTB
#define BUTTON_DDR    DDRD
#define BUTTON_PIN    PIND

int main(void)
{
	LED_DDR = 0xff;
	Button btnOn;
	Button btnoff;
	Button btnTog;

	Button_init(&btnOn, &BUTTON_DDR, &BUTTON_PIN, BUTTON_ON); // 주소값 주고 등등등 btn은 0번
	Button_init(&btnoff, &BUTTON_DDR, &BUTTON_PIN, BUTTON_OFF);
	Button_init(&btnTog, &BUTTON_DDR, &BUTTON_PIN, BUTTON_TOGGLE);

	while (1)
	{
		if (Button_getState(&btnOn) == ACT_RELEASE)
		{
			LED_PORT = 0xff;
		}
		if (Button_getState(&btnoff) == ACT_RELEASE)
		{
			LED_PORT = 0x00;
		}
		if (Button_getState(&btnTog) == ACT_RELEASE)
		{
			LED_PORT ^= 0xff;
		}
	}
}