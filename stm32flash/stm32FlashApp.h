#ifndef __STM32FLASHAPP_H__
#define __STM32FLASHAPP_H__

#include "stm32f4xx_hal.h"

#define RW_size  32 //根据需要扩大读写区范围


uint8_t fse_write(uint32_t WriteAddrb,uint32_t * data,uint16_t len);
uint8_t fse_Halfwrite(uint32_t WriteAddrb,uint16_t * data,uint16_t len);

#endif
