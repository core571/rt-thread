#ifndef __LED_ALERT_H__
#define __LED_ALERT_H__

#define LED0_PIN    GET_PIN(E, 7)
#define LED1_PIN    GET_PIN(E, 8)
#define LED2_PIN    GET_PIN(E, 9)

#define EVENT_LED0_OFF (1 << 0)
#define EVENT_LED0_ON  (1 << 1)
#define EVENT_LED0_BLINK  (1 << 2)

#define EVENT_LED1_OFF (1 << 3)
#define EVENT_LED1_ON  (1 << 4)
#define EVENT_LED1_BLINK  (1 << 5)


extern struct rt_event event;


int led_init();
void led_on(uint8_t led);
void led_off(uint8_t led);
void led_blink(uint8_t led);

#endif