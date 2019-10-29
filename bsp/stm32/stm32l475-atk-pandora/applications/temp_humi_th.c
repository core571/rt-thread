#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "mylog.h"
#include "key.h"
#include "led_alert.h"
#include "temp_humi.h"
#include "temp_humi_th.h"

static rt_thread_t temp_humi_tid = RT_NULL;

static void temp_humi_entry(void *parameter)
{
    float humidity, temperature;
        
    while(1){
        if(TH_State == KEY_TURN_ON){
            aht10_read_humi(&humidity);
            aht10_read_temp(&temperature);
            
            if(humidity < 43){
                rt_event_send(&event, EVENT_LED0_BLINK);
            }
            else{
                rt_event_send(&event, EVENT_LED0_ON);
            }
            
            mylog("humidity (%)", &humidity);
            mylog("temperature (¡ãC)", &temperature);
            
//            rt_kprintf("read aht10 sensor humidity   : %d.%d %%\n", (int)humidity, (int)(humidity * 10) % 10);
//            if( temperature >= 0 )
//            {
//                rt_kprintf("read aht10 sensor temperature: %d.%d¡ãC\n", (int)temperature, (int)(temperature * 10) % 10);
//            }
//            else
//            {
//                rt_kprintf("read aht10 sensor temperature: %d.%d¡ãC\n", (int)temperature, (int)(-temperature * 10) % 10);
//            }
        }
        else if(TH_State == KEY_TURN_OFF){
            rt_event_send(&event, EVENT_LED0_OFF);
        }
        rt_thread_mdelay(1000);
    }
}

//static void hook_of_scheduler(struct rt_thread* from, struct rt_thread* to)
//{
//    rt_kprintf("from: %s -->  to: %s \n", from->name , to->name);
//}

void temp_humi_init(void)
{
//    const char *i2c_bus_name = "i2c4";
    aht10_hw_init("i2c4");
    
    // rt_scheduler_sethook(hook_of_scheduler);
    
    temp_humi_tid = rt_thread_create("temp_humi_tid",
                                     temp_humi_entry, RT_NULL,
                                     1024,
                                     RT_MAIN_THREAD_PRIORITY - 1,
                                     10
                                     );
    if(temp_humi_tid != RT_NULL)
        rt_thread_startup(temp_humi_tid);

}