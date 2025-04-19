#ifndef STM32H7xx_H
#define STM32H7xx_H

#ifdef __cplusplus
extern "C" {
#endif

// Define the STM32H7 family
#if !defined(STM32H7)
#define STM32H7
#endif

// Define your specific device here if not already defined
// Recommended: pass STM32H723x via compiler flags
#if !defined(STM32H723x)
#define STM32H723x
#endif

// Include device-specific header
#if defined(STM32H723x)
#include "stm32h723xx.h"
#else
#error "Please define your STM32H7 target device (e.g. STM32H723x)"
#endif

// Common types

typedef enum { RESET = 0, SET = !RESET } FlagStatus, ITStatus;
typedef enum { DISABLE = 0, ENABLE = !DISABLE } FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))
typedef enum { SUCCESS = 0, ERROR = !SUCCESS } ErrorStatus;

// Register access macros
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)    ((REG) & (BIT))
#define CLEAR_REG(REG)        ((REG) = (0x0))
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))

#ifdef __cplusplus
}
#endif

#endif /* STM32H7xx_H */
