#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>


#include "temp_humi.h"

struct rt_i2c_bus_device *i2c_bus;      /* I2C总线设备句柄 */
//static rt_bool_t initialized = RT_FALSE;                /* 传感器初始化状态 */




/* 写传感器寄存器 */
static rt_err_t write_reg(struct rt_i2c_bus_device *bus, rt_uint8_t reg, rt_uint8_t *data)
{
    rt_uint8_t buf[3];
    struct rt_i2c_msg msgs;

    buf[0] = reg; //cmd
    buf[1] = data[0];
    buf[2] = data[1];

    msgs.addr = AHT10_ADDR;
    msgs.flags = RT_I2C_WR;
    msgs.buf = buf;
    msgs.len = 3;

    /* 调用I2C设备接口传输数据 */
    if (rt_i2c_transfer(bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}

/* 读传感器寄存器数据 */
static rt_err_t read_regs(struct rt_i2c_bus_device *bus, rt_uint8_t len, rt_uint8_t *buf)
{
    struct rt_i2c_msg msgs;

    msgs.addr = AHT10_ADDR;     /* 从机地址 */
    msgs.flags = RT_I2C_RD;     /* 读标志 */
    msgs.buf = buf;             /* 读写数据缓冲区指针　*/
    msgs.len = len;             /* 读写数据字节数 */

    /* 调用I2C设备接口传输数据 */
    if (rt_i2c_transfer(bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}

void aht10_read_temp(float *cur_temp)
{
    rt_uint8_t temp[6];

    write_reg(i2c_bus, AHT10_GET_DATA, 0);      /* 发送命令 */
//    rt_thread_mdelay(400);
    read_regs(i2c_bus, 6, temp);                /* 获取传感器数据 */

    /* 温度数据转换 */
    *cur_temp = ((temp[3] & 0xf) << 16 | temp[4] << 8 | temp[5]) * 200.0 / (1 << 20) - 50;
}

void aht10_read_humi(float *cur_humi)
{
    rt_uint8_t temp[6];

    write_reg(i2c_bus, AHT10_GET_DATA, 0);      /* 发送命令 */
//    rt_thread_mdelay(400);
    read_regs(i2c_bus, 6, temp);                /* 获取传感器数据 */

    /* 湿度数据转换 */
    *cur_humi = (temp[1] << 12 | temp[2] << 4 | (temp[3] & 0xf0) >> 4) * 100.0 / (1 << 20);    
}

void aht10_hw_init(const char *name)
{
    rt_uint8_t temp[2] = {0, 0};

    /* 查找I2C总线设备，获取I2C总线设备句柄 */
    i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(name);

    if (i2c_bus == RT_NULL)
    {
        rt_kprintf("can't find %s device!\n", name);
    }
    else
    {
        write_reg(i2c_bus, AHT10_NORMAL_CMD, temp);
        rt_thread_mdelay(400);

        temp[0] = 0x08;
        temp[1] = 0x00;
        write_reg(i2c_bus, AHT10_CALIBRATION_CMD, temp);
        rt_thread_mdelay(400);
//        initialized = RT_TRUE;
    }
}