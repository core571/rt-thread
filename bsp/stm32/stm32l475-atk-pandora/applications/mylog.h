#ifndef __PM25_TH_H__
#define __PM25_TH_H__

typedef struct __mylog_TypeDef
{
    char* fileStr;
    void* data;
}mylog_TypeDef;

typedef mylog_TypeDef* mylog_TypeDef_t;

void mylog(char* TAG, void* data);
int mylog_init(void);

#endif