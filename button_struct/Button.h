// Header file: Button.h
#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>

#define BUTTON_ON     0
#define BUTTON_OFF    1
#define BUTTON_TOGGLE 2

enum {PUSHED, RELEASED};
enum {NO_ACT, ACT_PUSH, ACT_RELEASE};

typedef struct _button
{
	volatile uint8_t *ddr;
	volatile uint8_t *pin;
	uint8_t           btnPin;
	uint8_t           prevState;
} Button;

void Button_init(Button *button, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNum);
uint8_t Button_getState(Button *button);

#endif