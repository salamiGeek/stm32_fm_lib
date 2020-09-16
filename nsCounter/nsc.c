#include "nsc.h"

void nscInit(void)
{
    /* 使能DWT外设 */
   CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
   /* DWT CYCCNT寄存器计数清0 */
   DWT->CYCCNT = (uint32_t)0U;
   /* 使能Cortex-M DWT CYCCNT寄存器 */
   DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

/**
 * @brief  读取当前时间戳;F411主频100MHz 1/100M=10ns一个单位
 * 			溢出时间  (2^32)/100M=42.94s
 * @param  无
 * @retval 当前时间戳，即DWT_CYCCNT寄存器的值
 */
uint32_t CPU_TS_TmrRd(void)
{        
  return ((uint32_t)DWT->CYCCNT);
}
