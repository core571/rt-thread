/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "mylog.h"
#include "led_alert.h"
#include "key.h"
#include "pm25_th.h"
#include "temp_humi_th.h"
     
int main(void)
{
    mylog_init();
    key_init();
    led_init();    
    temp_humi_init();
    pm25_init();
    
    return RT_EOK;
}
