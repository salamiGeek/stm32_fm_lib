#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "stm32f4xx_hal.h"
#include "MacroAndConst.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
//用户根据自己的需要设置
#ifdef STM32F411xE
#define STM32_FLASH_SIZE 512 	 		//所选STM32的FLASH容量大小(单位为K)
#endif
#ifdef STM32F401xC
#define STM32_FLASH_SIZE 128 	 		//所选STM32的FLASH容量大小(单位为K)
#endif
#define STM32_FLASH_WREN 1        		//使能FLASH写入(0，不使能;1，使能)

#define STM_SECTOR_SIZE	131072U		// 扇区大小:128K

#define FLASH_WAITETIME  50000          //FLASH等待超时时间

#define FIRST_128K_SECTOR_NUM		3

#ifdef STM32F411xE
// F411XE 总7个扇区   FLASH容量：512K 
//FLASH 扇区的起始地址				
#define ADDR_FLASH_SECTOR_0     ((u32)0x08000000) 	//扇区0起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_1     ((u32)0x08004000) 	//扇区1起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_2     ((u32)0x08008000) 	//扇区2起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_3     ((u32)0x0800C000) 	//扇区3起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_4     ((u32)0x08010000) 	//扇区4起始地址, 64 Kbytes  
#define ADDR_FLASH_SECTOR_5     ((u32)0x08020000) 	//扇区5起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_6     ((u32)0x08040000) 	//扇区6起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_7     ((u32)0x08060000) 	//扇区7起始地址, 128 Kbytes  

#endif	//#ifdef STM32F411xE

#ifdef STM32F401xC
// F401CCU6最多刀扇区5 FLASH容量：256K
#define ADDR_FLASH_SECTOR_0     ((u32)0x08000000) 	//扇区0起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_1     ((u32)0x08004000) 	//扇区1起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_2     ((u32)0x08008000) 	//扇区2起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_3     ((u32)0x0800C000) 	//扇区3起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_4     ((u32)0x08010000) 	//扇区4起始地址, 64 Kbytes  
#define ADDR_FLASH_SECTOR_5     ((u32)0x08020000) 	//扇区5起始地址, 128 Kbytes  
#endif	//#ifdef STM32F401xC


//////////////////////////////////////////////////////////////////////////////////////////////////////

//FLASH起始地址
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH的起始地址

u32 STMFLASH_ReadWord(u32 faddr);
u16 STMFLASH_ReadHalfWord(u32 faddr);		   //读出半字 
u32 STMFLASH_ReadLenByte(u32 ReadAddr,u16 Len);						//指定地址开始读取指定长度数据
void STMFLASH_Read(u32 ReadAddr,u32 *pBuffer,u32 NumToRead);
void STMFLASH_HalfRead(u32 ReadAddr,u16 *pBuffer,u32 NumToRead);   		//从指定地址开始读出指定长度的数据

#if STM32_FLASH_WREN	//如果使能了写   
HAL_StatusTypeDef STMFLASH_HalfWrite(u32 WriteAddr,u16 *pBuffer,u32 NumToWrite)	;	//从指定地址开始写入指定长度的数据
HAL_StatusTypeDef STMFLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite);
void Test_Write(u32 WriteAddr,u16 WriteData);      //测试写入
  
#endif	//#if STM32_FLASH_WREN	

#endif

















