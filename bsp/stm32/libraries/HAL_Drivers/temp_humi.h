#ifndef __TEMP_HUMI_H__
#define __TEMP_HUMI_H__

#define AHT10_ADDR                  0x38    /* �ӻ���ַ */
#define AHT10_CALIBRATION_CMD       0xE1    /* У׼���� */
#define AHT10_NORMAL_CMD            0xA8    /* һ������ */
#define AHT10_GET_DATA              0xAC    /* ��ȡ�������� */

void aht10_hw_init(const char *name);
void aht10_read_humi(float *cur_humi);
void aht10_read_temp(float *cur_temp);

#endif