#include "dependency/gpio_accessor.h"
#include "system/stm32h7xx.h"

static void set_row_high_impl(int row) {
    // Use BSRR register
}

static int read_col_impl(int col) {
    return (GPIOC->IDR >> col) & 1;
}

GPIOAccessor stm32_gpio_accessor = {
    .set_row_high = set_row_high_impl,
    .read_col = read_col_impl
};

GPIOAccessor* gpio = &stm32_gpio_accessor;
