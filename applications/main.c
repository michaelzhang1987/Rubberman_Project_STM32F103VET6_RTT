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
#include "fal.h"
#include "easyflash.h"

/* defined the LED0 pin: PC13 */
#define LED0_PIN    GET_PIN(C, 13)

int Reboot_Time = 0;

int main(void)
{
    int count = 1;
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    
    fal_init();
    if(easyflash_init() == EF_NO_ERR)
    {
      ef_get_env_blob("reboot_times",&Reboot_Time,4,NULL);
    }
    Reboot_Time++;
    ef_set_env_blob("reboot_times",&Reboot_Time,4);
    rt_kprintf("reboot_time is = %d\n",Reboot_Time);
    
    while (count++)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}