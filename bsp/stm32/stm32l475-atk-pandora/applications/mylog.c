#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "mylog.h"

static rt_thread_t async_tid = RT_NULL;
static struct rt_mailbox mb;
static char mb_pool[128];


void mylog(char* TAG, void* data)
{
    static mylog_TypeDef g_mylogStruct;
    g_mylogStruct.fileStr = TAG;
    g_mylogStruct.data = data;
    
    rt_mb_send(&mb, (rt_ubase_t)&g_mylogStruct);
}

static void mylog_thread_entry(void* param)
{
    mylog_TypeDef_t pstr;
    
    while(1){
        if(rt_mb_recv(&mb, (rt_ubase_t *)&pstr, RT_WAITING_FOREVER) == RT_EOK){
            rt_kprintf("[%s] data is: %d.%d\n", pstr->fileStr, (int)*(float*)pstr->data, (int)(*(float*)pstr->data * 10) % 10);
        }
    }
}

int mylog_init(void)
{
    rt_err_t result;
    
    result = rt_mb_init(&mb,
                        "mbt",                      /* 名称是 mbt */
                        &mb_pool[0],                /* 邮箱用到的内存池是 mb_pool */
                        sizeof(mb_pool) / 4,        /* 邮箱中的邮件数目，因为一封邮件占 4 字节 */
                        RT_IPC_FLAG_FIFO);          /* 采用 FIFO 方式进行线程等待 */
    
    if (result != RT_EOK){
        rt_kprintf("init mailbox failed.\n");
        return -1;
    }

    async_tid = rt_thread_create("mylog",
                                 mylog_thread_entry, RT_NULL,
                                 1024,
                                 RT_MAIN_THREAD_PRIORITY - 2,
                                 20
                                );
    
    if(async_tid != RT_NULL)
        rt_thread_startup(async_tid);
    
    return 0;
}