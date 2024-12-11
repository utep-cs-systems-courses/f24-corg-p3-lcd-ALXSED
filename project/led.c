#include <msp430.h>
#include "led.h"

static int time_count = 0;
static int time_count_2 = 0;
static int blink_limit = 0;
static int blink_count = 0;

void led_init(){
    P1DIR |= LEDS;
    P1OUT &= ~LEDS;
}

