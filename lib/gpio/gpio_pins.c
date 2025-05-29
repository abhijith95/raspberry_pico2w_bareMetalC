#include <stdint.h>
#include "gpio_pins.h"

/* Global variables */
gpio_pin *gpio_pin_ctrls= GPIO_PIN_CTRL;

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
    if (pin < (uint32_t) 32)
    {
        reg_value = ((uint8_t) (*(GPIO_IN) & (uint32_t)(1<<pin)));
    }
    else
    {
        reg_value = ((uint8_t) (*(GPIO_HI_IN) & (uint32_t)(1<<pin)));
    }
    return reg_value;
}

/**
 * @brief Function to write output to GPIO
 * 
 * @param pin - GPIO pin to set high or low
 * @param pin_value - Value should be 0 or 1
 */
void Write_gpio(uint8_t pin, uint8_t pin_value)
{
    if (pin < (uint32_t) 32)
    {
        *(GPIO_OUT) = ((*GPIO_OUT) | (uint32_t)(pin_value << pin));
    }
    else
    {
        *(GPIO_HI_OUT) = ((*GPIO_HI_OUT) | (uint32_t)(pin_value << pin));
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
    if((pin > 0) && (pin <= NUM_GPIO))
    {
        gpio_pin_ctrls[pin].gpio_ctrl = gpio_pin_ctrls[pin].gpio_ctrl | ((uint8_t) pin_function);
    }
    else
    {
        /* Don't take any action */
    }
}

/**
 * @brief Function to configure the GPIO pin for SIO input or output
 * 
 * @param pin - GPIO pin to configure
 * @param sio_type - Input or output
 */
void Config_gpio_sio(uint8_t pin, GPIO_SIO_TYPE_E sio_type)
{
    if (pin < (uint32_t) 32)
    {
        *(GPIO_OE) = ((*GPIO_OE) | ((uint32_t)sio_type << pin));
    }
    else
    {
        *(GPIO_HI_OE) = ((*GPIO_HI_OE) | ((uint32_t)sio_type << pin));
    }
}
