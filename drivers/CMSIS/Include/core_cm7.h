/**
 * @file core_cm7.h
 * @brief CMSIS Cortex-M7 Core Peripheral Access Layer Header File
 */

#ifndef __CORE_CM7_H
#define __CORE_CM7_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* Configuration of the Cortex-M7 Processor and Core Peripherals */
#define __CM7_REV                 0x0000U  /*!< Core revision r0p0                            */
#define __MPU_PRESENT             1U       /*!< MPU present                                   */
#define __NVIC_PRIO_BITS          4U       /*!< Number of Bits used for Priority Levels       */
#define __Vendor_SysTickConfig    0U       /*!< Set to 1 if different SysTick Config is used  */
#define __FPU_PRESENT             1U       /*!< FPU present                                   */
#define __ICACHE_PRESENT          1U       /*!< Instruction cache present                     */
#define __DCACHE_PRESENT          1U       /*!< Data cache present                            */

/* NVIC Interrupt Controller Type Register */
typedef struct
{
  volatile uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
  uint32_t RESERVED0[24U];
  volatile uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
  uint32_t RESERVED1[24U];
  volatile uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
  uint32_t RESERVED2[24U];
  volatile uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
  uint32_t RESERVED3[24U];
  volatile uint32_t IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
  uint32_t RESERVED4[56U];
  volatile uint8_t  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
  uint32_t RESERVED5[644U];
  volatile uint32_t STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}  NVIC_Type;

/* System Control Block */
typedef struct
{
  volatile uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  volatile uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  volatile uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  volatile uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  volatile uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  volatile uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  volatile uint8_t  SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  volatile uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  volatile uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  volatile uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  volatile uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  volatile uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  volatile uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  volatile uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  volatile uint32_t PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  volatile uint32_t DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  volatile uint32_t ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  volatile uint32_t MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  volatile uint32_t ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
  uint32_t RESERVED0[5U];
  volatile uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} SCB_Type;

/* Memory mapped structure for Nested Vectored Interrupt Controller (NVIC) */
#define NVIC_BASE           (0xE000E100UL)
#define NVIC                ((NVIC_Type      *)     NVIC_BASE     )

/* Memory mapped structure for System Control Block (SCB) */
#define SCB_BASE            (0xE000ED00UL)
#define SCB                 ((SCB_Type       *)     SCB_BASE      )

#ifdef __cplusplus
}
#endif

#endif /* __CORE_CM7_H */
