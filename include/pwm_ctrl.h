#ifndef __PWM_CTRL_H__
#define __PWM_CTRL_H__

#include <stdint.h>
#include "gpio_pins.h"

/* User defined macros */
#define MAX_PWM_SLICES      (uint8_t)12
#define CC_CHANNEL_A_BITS   0x0
#define CC_CHANNEL_B_BITS   0x10

/* Register macros */
#define PWM_BASE        0x400A8000

/* User defined data types */
typedef struct
{
    volatile uint32_t csr;
    volatile uint32_t div;
    volatile uint32_t ctr;
    volatile uint32_t cc;
    volatile uint32_t top;
}PWM_SLICE;

typedef enum
{
    CHANNEL_A = CC_CHANNEL_A_BITS,
    CHANNEL_B = CC_CHANNEL_B_BITS
}PWM_SLICE_CHANNEL_E;

/* Function prototypes */
void Configure_PWM_slice(uint8_t slice_num, PWM_SLICE* slice_info);
void Set_PWM_dutyCycle(uint8_t slice_num, PWM_SLICE_CHANNEL_E channel, float duty_cycle);

#endif