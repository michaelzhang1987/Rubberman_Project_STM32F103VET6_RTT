/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-27     SummerGift   add spi flash port file
 */

#include <rtthread.h>
#include "spi_flash.h"
#include "spi_flash_sfud.h"
#include "drv_spi.h"

#include "dfs_fs.h"

#if defined(BSP_USING_SPI_FLASH)
static int rt_hw_spi_flash_init(void)
{
    __HAL_RCC_GPIOF_CLK_ENABLE();
    rt_hw_spi_device_attach("spi1", "spi10", GPIOA, GPIO_PIN_4);

    if (RT_NULL == rt_sfud_flash_probe("W25Q128", "spi10"))
    {
        return -RT_ERROR;
    };

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_init);
#endif

//int dfs_mount_init(void)
//{
//    /* 指定格式化的文件系统，即将w25Q128格式化为ELM文件系统 */
//    dfs_mkfs("elm","W25Q128");
//    /* 挂载文件系统 */
//    if(dfs_mount("W25Q128", "/","elm",0,0) == 0)  //注册块设备，这一步可以将外部flash抽象为系统的块设备
//    {
// 
//        return -RT_ERROR;
// 
//    }
// 
//    return RT_EOK;
//}

int dfs_mount_init(void)
{
    /*只有存储介质不存在文件系统，才进行格式化*/
    if(dfs_mount("W25Q128", "/","elm",0,0) == -1)
    {
      /* 指定格式化的文件系统，即将w25Q128格式化为ELM文件系统 */
      dfs_mkfs("elm","W25Q128");
      /* 挂载文件系统 */
      dfs_mount("W25Q128", "/","elm",0,0);
    }
 
    return RT_EOK;
}
/* 导出到自动初始化 */
INIT_COMPONENT_EXPORT(dfs_mount_init);
//
///* 挂载文件系统 */
//int dfs_mount_init(void)
//{
//  /* 指定格式化的文件系统，即将w25Q128格式化为ELM文件系统 */
//    dfs_mkfs("elm","w25Q128");
//    /* 挂载文件系统 */
//    if(dfs_mount("w25Q128","/","elm",0,0) == 0)
//    {
//        rt_kprintf("dfs_mount success\r\n");
//                return RT_EOK;
//    }
//    else {
//        rt_kprintf("dfs_mount fail\r\n");
//        return -RT_ERROR;
//    }
//}
///* 系统启动时自动执行 */
//INIT_ENV_EXPORT(dfs_mount_init);   // 初始化执行顺序在注册flash之后

