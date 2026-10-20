/**
  ******************************************************************************
  * @file    system_stm32h753xx.h
  * @author  MCD Application Team
  * @brief   CMSIS Cortex-Mx Device System Source File for STM32H7xx.
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32h753xx_system
  * @{
  */

/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef SYSTEM_STM32H753xx_H
#define SYSTEM_STM32H753xx_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup STM32H753xx_System_Includes
  * @{
  */

/**
  * @}
  */


/** @addtogroup STM32H753xx_System_Exported_types
  * @{
  */
  /* This variable is updated in three ways:
      1) by calling CMSIS function SystemCoreClockUpdate()
      2) by calling HAL API function HAL_RCC_GetSysClockFreq()
      3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
         Note: If you use this function to configure the system clock; then there
               is no need to call the 2 first functions listed above, since SystemCoreClock
               variable is updated automatically.
  */
extern uint32_t SystemCoreClock;             /*!< System Domain1 Clock Frequency  */
extern uint32_t SystemD2Clock;               /*!< System Domain2 Clock Frequency  */
extern const  uint8_t D1CorePrescTable[16] ; /*!< D1CorePrescTable prescalers table values */

/**
  * @}
  */

/** @addtogroup STM32H753xx_System_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32H753xx_System_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32H753xx_System_Exported_Functions
  * @{
  */

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);
extern void ExitRun0Mode(void);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_STM32H753xx_H */

/**
  * @}
  */

/**
  * @}
  */
