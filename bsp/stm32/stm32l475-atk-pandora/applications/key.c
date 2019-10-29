#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "led_alert.h"
#include "key.h"


KEY_StateTypeDef TH_State = KEY_TURN_OFF;
KEY_StateTypeDef PM25_State = KEY_TURN_OFF;

static void key_cb0(void *args)
{
    static uint8_t i = 0;
    i++;
    if(!rt_pin_read(PIN_KEY0)){
        if (i & 0x01){
            TH_State = KEY_TURN_ON;
        }
        else{
            TH_State = KEY_TURN_OFF;
        }
    }
}

static void key_cb1(void *args)
{
    static uint8_t i = 0;
    i++;
    if(!rt_pin_read(PIN_KEY1)){
        if (i & 0x01){
            PM25_State = KEY_TURN_ON;
        }
        else{
            PM25_State = KEY_TURN_OFF;
        }
    }
}

static void key_cb2(void *args)
{
    static uint8_t i = 0;
    i++;
    if(!rt_pin_read(PIN_KEY2)){
        if (i & 0x01){
            led_on(2);
        }
        else{
            led_off(2);
        }
    }    
}


void key_init()
{
    rt_pin_mode(PIN_KEY0, PIN_MODE_INPUT);
    rt_pin_mode(PIN_KEY1, PIN_MODE_INPUT);
    rt_pin_mode(PIN_KEY2, PIN_MODE_INPUT);
    
    rt_pin_attach_irq(PIN_KEY0, PIN_IRQ_MODE_FALLING, key_cb0, RT_NULL);
    rt_pin_attach_irq(PIN_KEY1, PIN_IRQ_MODE_FALLING, key_cb1, RT_NULL);
    rt_pin_attach_irq(PIN_KEY2, PIN_IRQ_MODE_FALLING, key_cb2, RT_NULL);

    rt_pin_irq_enable(PIN_KEY0, PIN_IRQ_ENABLE);
    rt_pin_irq_enable(PIN_KEY1, PIN_IRQ_ENABLE);
    rt_pin_irq_enable(PIN_KEY2, PIN_IRQ_ENABLE);
}

