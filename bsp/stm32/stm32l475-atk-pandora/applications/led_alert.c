#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "led_alert.h"

/* 事件控制块 */
struct rt_event event;
static rt_thread_t led_tid = RT_NULL;

void led_entry(void *parameter)
{
    rt_uint32_t e;
    rt_err_t result;
    while(1){
        result = rt_event_recv(&event,
                               (EVENT_LED0_OFF | EVENT_LED0_ON | EVENT_LED0_BLINK |
                                EVENT_LED1_OFF | EVENT_LED1_ON | EVENT_LED1_BLINK),
                               RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                               RT_WAITING_FOREVER, 
                               &e
                              );
        if (result == RT_EOK){
            if(e & EVENT_LED0_OFF){
                led_off(0);
            }
            else if(e & EVENT_LED0_ON){
                led_on(0);
            }
            else if(e & EVENT_LED0_BLINK){
                led_blink(0);
            }

            if(e & EVENT_LED1_OFF){
                led_off(1);
            }
            else if(e & EVENT_LED1_ON){
                led_on(1);
            }
            else if(e & EVENT_LED1_BLINK){
                led_blink(1);
            }
        }
    }
}

int led_init()
{
    rt_err_t result;

    /* 初始化事件对象 */
    result = rt_event_init(&event, "event", RT_IPC_FLAG_FIFO);
    if (result != RT_EOK){
        rt_kprintf("init event failed.\n");
        return -1;
    }
    
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
    
    led_off(3);
    
    led_tid = rt_thread_create("led",
                               led_entry, RT_NULL,
                               1024,
                               RT_MAIN_THREAD_PRIORITY - 2,
                               20
                              );
    if(led_tid != RT_NULL)
        rt_thread_startup(led_tid);
    
    return 0;
}

void led_on(uint8_t led)
{
    switch(led){
    case 0:
        rt_pin_write(LED0_PIN, PIN_LOW);
        break;
    case 1:
        rt_pin_write(LED1_PIN, PIN_LOW);
        break;
    case 2:
        rt_pin_write(LED2_PIN, PIN_LOW);
        break;
    default:
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_pin_write(LED2_PIN, PIN_LOW);
    }
}

void led_off(uint8_t led)
{
    switch(led){
    case 0:
        rt_pin_write(LED0_PIN, PIN_HIGH);
        break;
    case 1:
        rt_pin_write(LED1_PIN, PIN_HIGH);
        break;
    case 2:
        rt_pin_write(LED2_PIN, PIN_HIGH);    
        break;
    default:
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_pin_write(LED2_PIN, PIN_HIGH);
    }
}

void led_blink(uint8_t led)
{
    led_on(led);
    rt_thread_mdelay(20);
    led_off(led);
//    rt_thread_mdelay(200);
}