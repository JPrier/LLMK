#include "dependency/gpio_accessor.h"

void scan_matrix(int* result_buffer, int max) {
    int count = 0;
    for (int row = 0; row < NUM_ROWS; row++) {
        gpio->set_row_high(row);
        for (int col = 0; col < NUM_COLS; col++) {
            if (gpio->read_col(col)) {
                result_buffer[count++] = col;
            }
        }
    }
}
