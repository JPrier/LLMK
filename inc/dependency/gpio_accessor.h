#ifndef GPIO_ACCESSOR_H
#define GPIO_ACCESSOR_H

typedef struct {
    void (*set_row_high)(int row);
    int  (*read_col)(int col);
} GPIOAccessor;

extern GPIOAccessor* gpio;

#endif
