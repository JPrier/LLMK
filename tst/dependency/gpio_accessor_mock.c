#include "gpio_accessor.h"
#include <stdio.h>

static void mock_set_row_high(int row) {
    printf("[MOCK] Set row %d HIGH\n", row);
}

static int mock_read_col(int col) {
    return col % 2; // fake alternating keypresses
}

GPIOAccessor mock_gpio_accessor = {
    .set_row_high = mock_set_row_high,
    .read_col = mock_read_col
};

GPIOAccessor* gpio = &mock_gpio_accessor;
