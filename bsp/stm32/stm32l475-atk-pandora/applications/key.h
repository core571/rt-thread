#ifndef __KEY_H__
#define __KEY_H__

#define PIN_KEY2        GET_PIN(D, 8)      // PD8 :  KEY2         --> KEY
#define PIN_KEY1        GET_PIN(D, 9)      // PD9 :  KEY1         --> KEY
#define PIN_KEY0        GET_PIN(D, 10)     // PD10:  KEY0         --> KEY



typedef enum{
    KEY_TURN_OFF,
    KEY_TURN_ON
}KEY_StateTypeDef;

extern KEY_StateTypeDef TH_State;
extern KEY_StateTypeDef PM25_State;


void key_init();
#endif