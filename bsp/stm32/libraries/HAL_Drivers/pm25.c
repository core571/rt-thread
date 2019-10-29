#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "pm25.h"

#define ADC_DEV_NAME        "adc1"  /* ADC 设备名称 */
#define ADC_DEV_CHANNEL     3       /* ADC 通道 */
#define REFER_VOLTAGE       330         /* 参考电压 3.3V,数据精度乘以100保留2位小数*/
#define CONVERT_BITS        (1 << 12)   /* 转换位数为12位 */
#define   RATIO       0.2            
#define   NO_DUST_VOLTAGE      400   


#define ILED_PIN    GET_PIN(B, 8)

rt_adc_device_t adc_dev;            /* ADC 设备句柄 */  

void gp2y_hw_init()
{
    rt_pin_mode(ILED_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(ILED_PIN, PIN_LOW);
    
    
    /* 查找设备 */
    adc_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_NAME);

    if (adc_dev == RT_NULL)
    {
        rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_DEV_NAME);
    }
    /* 使能设备 */
    rt_adc_enable(adc_dev, ADC_DEV_CHANNEL);
}

float gp2y_read_pm25()
{
    rt_uint32_t value;
    float    voltage,dens;
    
    rt_pin_write(ILED_PIN, PIN_HIGH);
    rt_hw_us_delay(280);
    
    /* 读取采样值 */
    value = rt_adc_read(adc_dev, ADC_DEV_CHANNEL);
    
    rt_pin_write(ILED_PIN, PIN_LOW);
    
    
    
    /* 转换为对应电压值 */
    voltage = value * (3300 / 4096.0) * 11;
//    vol = value * REFER_VOLTAGE / CONVERT_BITS * 11;
//    rt_kprintf("the voltage is :%d.%02d \n", vol / 100, vol % 100);
    
    if(voltage >= NO_DUST_VOLTAGE){
        dens = (voltage - NO_DUST_VOLTAGE) * RATIO;
        return  dens;
    }
    else{
        return 0;
    }
}
