#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"
#include "sys.h"

class led
{
private:
    /* data */

    // led number
    static const u8 kled0 = 0;
    static const u8 kled1 = 1;

public:
    led(/* args */);
    ~led();
    void init(void);
    void on(u8 led_no);
    void off(u8 led_no);
    void blink(u8 led_no);
};

#endif