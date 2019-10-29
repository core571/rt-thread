#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "mylog.h"
#include "led_alert.h"
#include "key.h"
#include "pm25.h"
#include "pm25_th.h"

static rt_thread_t pm25_tid = RT_NULL;

void pm25_entry(void *parameter)
{
    float dens = 0;
    
    while(1){
        if(PM25_State == KEY_TURN_ON){
            dens = gp2y_read_pm25();
            
            if(dens < 560){
                rt_event_send(&event, EVENT_LED1_BLINK);
            }
            else{
                rt_event_send(&event, EVENT_LED1_ON);
            }
            mylog("dens (ug/m3)", &dens);
        }
        else if(PM25_State == KEY_TURN_OFF){
            rt_event_send(&event, EVENT_LED1_OFF);
        }
//        dens = gp2y_read_pm25();
//        rt_kprintf("dens: %d.%d ug/m3\n", (int)dens, (int)(dens * 10) % 10);
        
        rt_thread_mdelay(1000);
    }
}

void pm25_init()
{
    gp2y_hw_init();
    pm25_tid = rt_thread_create("pm25_tid",
                                pm25_entry, RT_NULL,
                                1024,
                                RT_MAIN_THREAD_PRIORITY - 1,
                                20
                                );
    if(pm25_tid != RT_NULL)
        rt_thread_startup(pm25_tid);
}