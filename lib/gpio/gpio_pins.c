#include <stdint.h>
#include "gpio_pins.h"

/* Global variables */
GPIO_PIN_CTRLS *gpio_ctrls = GPIO_PIN_CTRL;
GPIO_PADS *gpio_pads_regs = GPIO_PADS_REG;

/**
 * @brief Function to read the GPIO value
 * 
 * Function returns the value of the GPIO found in the register. If a pin is configured as input, function returns
 * the value of the pin. For pin configured as output, it simply returns the last written pin value
 * 
 * @param pin - Pin number to get the value
 * 
 * @return uint8_t - Pin value read from the register
 */
uint8_t Read_gpio(uint8_t pin)
{
    uint8_t reg_value = (uint8_t)0;
    if (pin < LOW_REG_MAX_PINS)
    {
        reg_value = ((uint8_t) (*(GPIO_IN) & (uint32_t)(1<<pin)));
    }
    else
    {
        reg_value = ((uint8_t) (*(GPIO_HI_IN) & (uint32_t)(1<<(pin - LOW_REG_MAX_PINS))));
    }
    return reg_value;
}

/**
 * @brief Function to write output to GPIO
 * 
 * @param pin - GPIO pin to set high or low
 * @param pin_value - Value should be 0 or 1
 */
void Write_gpio(uint8_t pin, GPIO_SIO_OUTPUT_LEVEL pin_value)
{
    if (pin_value == OUTPUT_HIGH)
    {
        if (pin < LOW_REG_MAX_PINS)
        {
            *(GPIO_OUT_SET) = (1 << pin);
        }
        else
        {
            *(GPIO_HI_OUT_SET) = (1 << (pin - LOW_REG_MAX_PINS));
        }
    }
    else
    {
        if (pin < LOW_REG_MAX_PINS)
        {
            *(GPIO_OUT_CLR) = (1 << pin);
        }
        else
        {
            *(GPIO_HI_OUT_CLR) = (1 << (pin - LOW_REG_MAX_PINS));
        }
    }
}

/**
 * @brief Function to configure the selected GPIO pin
 * 
 * @param pin - GPIO pin to configure
 * @param pin_function - The function to configure the pin
 */
void Config_gpio_pin(uint8_t pin, GPIO_FUNCTIONS_E pin_function)
{
    /* Check if pin is out of range */
    if((pin >= 0) && (pin <= NUM_GPIO_PICO2W))
    {
        gpio_ctrls[pin].gpio_ctrl = (((uint32_t) pin_function) << 0);
    }
    else
    {
        /* Don't take any action */
    }
    /* Setup the GPIO Pads */
    gpio_pads_regs->gpio_pins[pin] = 0;
}

/**
 * @brief Function to configure the GPIO pin for SIO input or output
 * 
 * @param pin - GPIO pin to configure
 * @param sio_type - Input or output
 */
void Config_gpio_sio(uint8_t pin, GPIO_SIO_TYPE_E sio_type)
{
    if (pin < LOW_REG_MAX_PINS)
    {
        *(GPIO_OE_SET) = ((uint32_t)sio_type << pin);
    }
    else
    {
        *(GPIO_HI_OE_SET) = ((uint32_t)sio_type << (pin - LOW_REG_MAX_PINS));
    }
}
