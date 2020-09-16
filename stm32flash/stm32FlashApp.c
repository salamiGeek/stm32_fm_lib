#include "stm32FlashApp.h"
#include "stmflash.h"
#include <string.h>

/**
 * 写入格式要求：
 * HalfWord：0:1 标识头,用于识别该地址是否被当前程序使用
 *  标识头可以采用:0xAA55 等
 * 2:RW_size-1 数据字段
*/

//-------------------------------------------------------------------
/**
 * 功能：检查扇区内容是否已经写入过
 * 检查标志：起始地址=0xAA55
 * 如果初始化了，则返回   1
 * 如果没有初始化，则返回 0
 * 
*/
uint8_t checkAddrInit(uint32_t WriteAddr, uint32_t * data)
{
    uint8_t res;

    if(STMFLASH_ReadWord(WriteAddr) == data[0])
        res = 1;
    else res = 0;

    return res;
}

uint8_t checkAddrInit_Half(uint32_t WriteAddr, uint16_t * data)
{
    uint8_t res;

    if(STMFLASH_ReadHalfWord(WriteAddr) == data[0])
        res = 1;
    else res = 0;

    return res;
}

//-------------------------------------------------------------------
/**
 * 功能：更新某个位置的值
 * 检查好了扇区是否初始化之后就要开始写数据
 * 写数据需要将数据从扇区读出，然后再覆盖
 * data:空值部分需要用0xFFFF填充;开头需要有一个标志，如0xAA55
 * 不允许操过最大写范围（宏定义）
 * 返回值：正确:0 ;错误:1;
 * WriteAddrb:起始地址
 * data：数据指针
 * len：写入长度(32位个数)
*/
uint8_t fse_write(uint32_t WriteAddrb,uint32_t * data,uint16_t len)
{
    uint16_t i;
    uint8_t res;
    uint32_t fse_writeBuff[RW_size];
    memset(fse_writeBuff,0xFFFFFFFF,RW_size*4);   //初始化数组空间    
    if(len < RW_size)
    {
        if(checkAddrInit(WriteAddrb,data))
        {
            // 发现非空白区域
            // 先读取出来之后再写
            STMFLASH_Read(WriteAddrb,fse_writeBuff,len);
            for(i=0;i<len;i++)
            {
                if(data[i] != 0xFFFFFFFF)
                {
                    fse_writeBuff[i] = data[i];
                }
            }
            if(STMFLASH_Write(WriteAddrb,fse_writeBuff,len) == HAL_OK){
                res = 0;
            }
            else{
                res = 1;
            }
        }
        else
        {
            //发现空白区域
            //直接写
            if(STMFLASH_Write(WriteAddrb,data,len) == HAL_OK)
                res = 0;
            else{
                res = 1;
            }
        }
    }
    else
    {
        //超过限定读写范围,请修改宏定义；注意：RW_size值太大可能导致堆栈不够
        res = 1;
    }
    
    return res;
}

//-------------------------------------------------------------------
/**
 * 功能：更新某个位置的值
 * 检查好了扇区是否初始化之后就要开始写数据
 * 写数据需要将数据从扇区读出，然后再覆盖
 * data:空值部分需要用0xFFFF填充;开头需要有一个标志，如0xAA55
 * 不允许操过最大写范围（宏定义）
 * 返回值：正确:0 ;错误:1;
 * WriteAddrb:起始地址
 * data：数据指针
 * len：写入长度(16位个数)
*/
uint8_t fse_Halfwrite(uint32_t WriteAddrb,uint16_t * data,uint16_t len)
{
    uint16_t i;
    uint8_t res;
    uint16_t fse_writeBuff[RW_size];
    memset(fse_writeBuff,0xFFFF,RW_size*2);   //初始化数组空间    
    if(len < RW_size)
    {
        if(checkAddrInit_Half(WriteAddrb,data))
        {
            // 发现非空白区域
            // 先读取出来之后再写
            STMFLASH_HalfRead(WriteAddrb,fse_writeBuff,len);
            for(i=0;i<len;i++)
            {
                if(data[i] != 0xFFFF)
                {
                    fse_writeBuff[i] = data[i];
                }
            }
            if(STMFLASH_HalfWrite(WriteAddrb,fse_writeBuff,len) == HAL_OK){
                res = 0;
            }
            else{
                res = 1;
            }
        }
        else
        {
            //发现空白区域
            //直接写
            if(STMFLASH_HalfWrite(WriteAddrb,data,len) == HAL_OK)
                res = 0;
            else{
                res = 1;
            }
        }
    }
    else
    {
        //超过限定读写范围,请修改宏定义；注意：RW_size值太大可能导致堆栈不够
        res = 1;
    }
    
    return res;
}
