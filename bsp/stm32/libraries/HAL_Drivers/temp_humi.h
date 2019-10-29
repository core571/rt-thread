#ifndef __TEMP_HUMI_H__
#define __TEMP_HUMI_H__

#define AHT10_ADDR                  0x38    /* 从机地址 */
#define AHT10_CALIBRATION_CMD       0xE1    /* 校准命令 */
#define AHT10_NORMAL_CMD            0xA8    /* 一般命令 */
#define AHT10_GET_DATA              0xAC    /* 获取数据命令 */

void aht10_hw_init(const char *name);
void aht10_read_humi(float *cur_humi);
void aht10_read_temp(float *cur_temp);

#endif