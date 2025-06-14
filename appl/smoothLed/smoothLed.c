#include "smoothLed.h"
#include "gpio_pins.h"
#include "pwm_ctrl.h"
#include "timer.h"
#include <stdint.h>

/* User defined macros */
#define LED_GPIO            (uint8_t)0
#define PWM_APPL_SLICE      (uint8_t)0
#define PWM_FREQ            (uint32_t)(60000)

/**
 * @brief Function to setup necessary things for the application
 * 
 */
void smoothled_setup()
{
    PWM_SLICE pwm_slice_0;
    clock_gen_info* clk_gen_info;
    /* Configure GPIO0 to be of function PWM */
    Config_gpio_pin(LED_GPIO, PWM_0);

    /* Configure the slice */
    pwm_slice_0.csr = 0x1;  /* Enable the pwm slice */
    pwm_slice_0.div = (1 << 8);
    pwm_slice_0.ctr = 0x0;
    pwm_slice_0.cc = 0x0;  /* Initialise the duty cycle with 0% */
    pwm_slice_0.top = 0xFFFF;
    Configure_PWM_slice(PWM_APPL_SLICE, &pwm_slice_0);

    *((uint32_t*)(PWM_BASE + 0x0F4)) |= (1 << 0); /* Clear the interrupt */

    /* Configure the system clock so the PWM freq is 200Hz */
    Read_clock_genrtrs(SYS, clk_gen_info);
    clk_gen_info->div = (PWM_FREQ << 16);
}

/**
 * @brief Main application logic
 * 
 */
void smoothled_10ms()
{
    /* Set a duty cycle of 50% */
    Set_PWM_dutyCycle(PWM_APPL_SLICE, CHANNEL_A, 10);
}
