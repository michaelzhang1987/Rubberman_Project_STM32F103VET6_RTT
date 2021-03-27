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
//    /* ָ����ʽ�����ļ�ϵͳ������w25Q128��ʽ��ΪELM�ļ�ϵͳ */
//    dfs_mkfs("elm","W25Q128");
//    /* �����ļ�ϵͳ */
//    if(dfs_mount("W25Q128", "/","elm",0,0) == 0)  //ע����豸����һ�����Խ��ⲿflash����Ϊϵͳ�Ŀ��豸
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
    /*ֻ�д洢���ʲ������ļ�ϵͳ���Ž��и�ʽ��*/
    if(dfs_mount("W25Q128", "/","elm",0,0) == -1)
    {
      /* ָ����ʽ�����ļ�ϵͳ������w25Q128��ʽ��ΪELM�ļ�ϵͳ */
      dfs_mkfs("elm","W25Q128");
      /* �����ļ�ϵͳ */
      dfs_mount("W25Q128", "/","elm",0,0);
    }
 
    return RT_EOK;
}
/* �������Զ���ʼ�� */
INIT_COMPONENT_EXPORT(dfs_mount_init);
//
///* �����ļ�ϵͳ */
//int dfs_mount_init(void)
//{
//  /* ָ����ʽ�����ļ�ϵͳ������w25Q128��ʽ��ΪELM�ļ�ϵͳ */
//    dfs_mkfs("elm","w25Q128");
//    /* �����ļ�ϵͳ */
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
///* ϵͳ����ʱ�Զ�ִ�� */
//INIT_ENV_EXPORT(dfs_mount_init);   // ��ʼ��ִ��˳����ע��flash֮��

