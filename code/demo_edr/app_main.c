#include "system/includes.h"
#include "app_config.h"
#include "generic/log.h"
#include "os/os_api.h"
#include "event/key_event.h"
#include "event/device_event.h"
#include "btstack/avctp_user.h"

// 自身导入的
#include "system/os/FreeRTOS/task.h"
#include "lnf/key/lnf_Key.h"
#include "lnf/led/lnf_LED.h"
#include "btstack/avctp_user.h"

/*中断列表 */
const struct irq_info irq_info_table[] = {
    //中断号   //优先级0-7   //注册的cpu(0或1)
#ifdef CONFIG_IPMASK_ENABLE
    //不可屏蔽中断方法：支持写flash，但中断函数和调用函数和const要全部放在内部ram
    { IRQ_SOFT5_IDX,      6,   0    }, //此中断强制注册到cpu0
    { IRQ_SOFT4_IDX,      6,   1    }, //此中断强制注册到cpu1
#if 0 //如下，SPI1使用不可屏蔽中断设置,优先级固定7
    { IRQ_SPI1_IDX,      7,   1    },//中断强制注册到cpu0/1
#endif
#endif
#if CPU_CORE_NUM == 1
    { IRQ_SOFT5_IDX,      7,   0    }, //此中断强制注册到cpu0
    { IRQ_SOFT4_IDX,      7,   1    }, //此中断强制注册到cpu1
    { -2,     			-2,   -2   },//如果加入了该行, 那么只有该行之前的中断注册到对应核, 其他所有中断强制注册到CPU0
#endif

    { -1,     -1,   -1    },
};

/*任务列表 */
const struct task_info task_info_table[] = {
    {"app_core",            15,     1024,   256   },
    {"sys_event",           29,      512,   0     },
    {"systimer",            14,      256,   0     },
    {"sys_timer",            9,      512,   64    },
    {"audio_server",        16,      512,   64    },
    {"audio_mix",           28,      512,   0     },
    {"audio_encoder",       12,      384,   64    },
    {"vir_dev_task",        13,      256,   0     },
    {"cvsd_encoder",        13,      512,   0     },
    {"aec_encoder",         13,     1024,   0     },
    {"msbc_encoder",        13,      256,   0     },
    {"sbc_encoder",         13,      512,   0     },
#if CPU_CORE_NUM > 1
    {"#C0btencry",          16,      512,   128   },
    {"#C0btctrler",         19,      512,   384   },
    {"#C0btstack",          18,      1024,  384   },
#else
    {"btencry",             14,      512,   128   },
    {"btctrler",            19,      512,   384   },
    {"btstack",             18,      768,   384   },
#endif
    {0, 0},
};

static int main_dev_event_handler(struct device_event *event)
{
    switch (event->event) {
    case DEVICE_EVENT_IN:
        break;
    case DEVICE_EVENT_OUT:
        break;
    case DEVICE_EVENT_CHANGE:
        break;
    }
    return false;
}

/*
 * 默认的系统事件处理函数
 * 当所有活动的app的事件处理函数都返回false时此函数会被调用
 */
void app_default_event_handler(struct sys_event *event)
{
    switch (event->type) {
    case SYS_KEY_EVENT:
        extern int bt_music_key_event_handler(struct key_event * key);
        bt_music_key_event_handler((struct key_event *)event->payload);
        break;
    case SYS_DEVICE_EVENT:
        main_dev_event_handler((struct device_event *)event->payload);
        break;
    case SYS_BT_EVENT:
        extern int app_music_bt_event_handler(struct sys_event * event);
        app_music_bt_event_handler(event);
        break;
    default:
        ASSERT(0, "unknow event type: %s\n", __func__);
        break;
    }
}


// 按键的一个任务定义，函数
void keyTask(void *args);

// 获取音乐信息的回调函数
void info_cb(u8 type, u32 time, u8 *info, u16 len);

// led 扫描显示
void led_show(void *);

// 存储LED要显示的字符 '0'-'9'
uint8_t ledBuff[6] = {'2','0','0','4','0', '\0'};

void show_led_task(void *);

/*
 * 应用程序主函数
 */
void app_main()
{
    puts("------------- demo_edr app main-------------\n");

    extern void bt_ble_module_init(void);
    bt_ble_module_init();

        // 注册获取音乐信息的回调函数
    bt_music_info_handle_register(info_cb);

   /*  1. 创建LED显示任务   */
    os_task_create(show_led_task, NULL, 10, 128, 0, "show_led_task");

    // 创建一个任务进行一个按键扫描
    os_task_create(keyTask,NULL,20,1024,0,"key_task");

       // 创建一个任务进行 LED显示任务
   //  os_task_create(led_show,NULL,10,128,0,"led_show");
    // 注册定时器任务，动态扫描led 点阵
    // usr_timer_add(NULL,led_show,2,1);
    // usr_timer_add(NULL,led_show,20,1);
}


/*1. led显示任务函数*/
void show_led_task(void *args)
{

    printf("===============led task start===============\n");
    uint32_t time = 0;
    uint32_t cnt = 0;
    while(1)
    {
        // 任务调度周期10ms. 可以认为LED动态扫描时间为10ms(100Hz)
        vTaskDelayUntil(&time, 10 / 10);
        cnt++;

        // 获取连接的蓝牙设备的个数
        uint8_t btCnt =  get_total_connect_dev();
        if(btCnt)
        {
            Inf_LED_ShowNum(1, ledBuff[0] - '0');
            delay_us(200);
            Inf_LED_ShowNum(2, ledBuff[1] - '0');
            delay_us(200);
            Inf_LED_ShowNum(3, ledBuff[2] - '0');
            delay_us(200);
            Inf_LED_ShowNum(4, ledBuff[3] - '0');
            delay_us(200);
            Inf_LED_ShowNum(5, ledBuff[4] - '0');
            delay_us(200);
            Inf_LED_CloseAllNums();
            if(cnt % 100 == 0)
            {
                user_send_cmd_prepare(USER_CTRL_AVCTP_OPID_GET_PLAY_TIME, 0, NULL);
            }
        }

    }
}

// 音乐信息回调函数
void info_cb(u8 type, u32 time, u8 *info, u16 len)
{

    static uint8_t cnt = 0;
    static uint32_t totalTime = 0;
    static uint32_t currentTime = 0;

    if(type == 0) // 类型是0时表示获取的是音乐时长
    {
        cnt++;
        if(cnt == 1)
        {
            totalTime = time;
        }
        else if(cnt == 2)
        {
            currentTime = time;
            cnt = 0;

            // 计算剩余播放时长
            uint32_t remainTime = totalTime - currentTime;

            // 更新led要显示的数字
            sprintf(ledBuff, "%02d%02d%01d", remainTime / 1000 / 60, remainTime / 1000 % 60, 1);
        }
    }


}


// 识别按键对应上一首，下一首，暂停，播放功能
extern int bt_music_key_event_handler(struct key_event *key);



void keyTask(void *args)
{

    extern void bt_connection_disable(void);  // 官方：断开蓝牙
    extern void bt_connection_enable(void);   // 官方：开启蓝牙（可重连）
    extern void bt_wait_phone_connect_control(u8 enable);
    // 执行我们自己定义的按键初始化
    Inf_Key_Init();

    // 扫描周期
    uint32_t time = xTaskGetTickCount();

    struct key_event event;

    while(1)
    {


        vTaskDelayUntil(&time,20 / 10);

        // 执行我们自己定义的按按键扫描
        My_Key key = Inf_Key_Scan();

        if(key == KEY1) // 上一首
        {
            event.action = KEY_EVENT_LONG;
            event.value = KEY_VOLUME_DEC;
            bt_music_key_event_handler(&event);

            // printf("key1\n");  // 测试是否能够识别被按下
        }
        else if(key == KEY2)  // 下一首
        {
            event.action = KEY_EVENT_LONG;
            event.value = KEY_VOLUME_INC;
            bt_music_key_event_handler(&event);
            // printf("key2\n");
        }
        else if(key == KEY3)  // 减少音量
        {
            event.action = KEY_EVENT_CLICK;
            event.value = KEY_VOLUME_DEC;
            bt_music_key_event_handler(&event);
             // printf("key3\n");
        }
        else if(key == KEY4)  // 增大音量
        {
            event.action = KEY_EVENT_CLICK;
            event.value = KEY_VOLUME_INC;
            bt_music_key_event_handler(&event);
             // printf("key4\n");
        }
        else if(key == KEY5)  // 播放或暂停
        {
            event.action = KEY_EVENT_CLICK;
            event.value = KEY_OK;
            bt_music_key_event_handler(&event);
             // printf("key5\n");
        }
        else if(key == KEY6)
        {
            // printf("key6\n");
               // 1. 获取蓝牙连接状态（1=已连接，0=未连接，SDK原生函数）
                uint8_t bt_status = get_bt_connect_status();
               // extern void bt_ble_module_init(void); // 你代码里已用的蓝牙初始化函数
                extern void bt_power_ctrl(u8 enable);

                if(bt_status)
                {
                     // 已连接 → 调用官方函数断开（不毁协议栈）
                    // bt_connection_disable();
                    // 1. 【仅断开当前连接，不关闭蓝牙电源】（源码原生命令，零报错）
                    user_send_cmd_prepare(USER_CTRL_DISCONNECTION_HCI, 0, NULL);
                    // 2. 直接发送【开启可发现+可连接】命令（和static函数效果完全一致）
                   user_send_cmd_prepare(USER_CTRL_WRITE_SCAN_ENABLE, 0, NULL);  // 手机能搜到
                   user_send_cmd_prepare(USER_CTRL_WRITE_CONN_ENABLE, 0, NULL);   // 手机能连上
                    printf("KEY6：蓝牙已断开，可直接重连\n");
                }
                /*
                else
                {
                   // 未连接 → 调用官方函数开启（手机秒搜、秒连）
                    bt_connection_enable();
                    printf("KEY6：蓝牙开启配对，等待重连\n");
                } */

        }


    }
}
