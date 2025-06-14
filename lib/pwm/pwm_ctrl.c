#include "pwm_ctrl.h"

/* Global variable */
PWM_SLICE *pwm_slices = (PWM_SLICE *)PWM_BASE;


/* Function definitions */

/**
 * @brief Function to configure a given PWM slice
 * 
 * @param slice_num - Slice number to configure. Has to be less than 12
 * @param slice_info - Struct containing the config information
 */
void Configure_PWM_slice(uint8_t slice_num, PWM_SLICE* slice_info)
{
    if(slice_num < MAX_PWM_SLICES)
    {
        ((PWM_SLICE *)PWM_BASE)->cc = slice_info->cc;
        ((PWM_SLICE *)PWM_BASE)->top = slice_info->top;
        ((PWM_SLICE *)PWM_BASE)->csr = slice_info->csr;
        ((PWM_SLICE *)PWM_BASE)->div = slice_info->div;
    }
    else
    {
        /* Dont do anything, since this is incorrect */
    }
}

/**
 * @brief Function to set the PWM duty cycle
 * 
 * @param slice_num - Slice number to configure. Has to be less than 12
 * @param channel - Channel A or B to set
 * @param duty_cycle - Duty cycle in % to set
 */
void Set_PWM_dutyCycle(uint8_t slice_num, PWM_SLICE_CHANNEL_E channel, float duty_cycle)
{
    uint16_t top_value =(uint16_t)(((PWM_SLICE *)PWM_BASE)->top & 0xFFFF);
    uint16_t compare_value = (uint16_t)(duty_cycle * top_value / 100);
    ((PWM_SLICE *)PWM_BASE)->cc = (uint32_t) ((compare_value << channel) & 0xFFFFFFFF);
}
