#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/* GPIO registers */
#define GPIO_IN             ((uint32_t*)  (0xD0000004))
#define GPIO_HI_IN          ((uint32_t*)  (0xD0000008))
#define GPIO_OUT            ((uint32_t*)  (0xD0000010))
#define GPIO_HI_OUT         ((uint32_t*)  (0xD0000014))
#define GPIO_OE             ((uint32_t*)  (0xD0000030))
#define GPIO_HI_OE          ((uint32_t*)  (0xD0000034))
#define GPIO_PIN_CTRL       ((gpio_pin*)  (0x40028000))
#define NUM_GPIO            ((uint8_t) 47)

/* Pin config type */
typedef enum
{
    INPUT = 0,
    OUTPUT
}GPIO_SIO_TYPE_E;

/* GPIO pin function types */
typedef enum
{
    JTAG_TCK = 0,
    SPI0_RX,
    UART0_TX,
    I2C0_SDA,
    PWM_A_0,
    SIO_0,
    PIO0_0,
    PIO1_0,
    XIP_SS_N_1,
    USB_MUXING
}GPIO_FUNCTIONS_E;

/* Definition for pin control */
typedef struct 
{
    /* data */
    uint32_t gpio_status;
    uint32_t gpio_ctrl;
}gpio_pin;

/* Function prototypes */
uint8_t Read_gpio(uint8_t pin);
void Write_gpio(uint8_t pin, uint8_t pin_value);
void Config_gpio_pin(uint8_t pin, GPIO_FUNCTIONS_E pin_function);
void Config_gpio_sio(uint8_t pin, GPIO_SIO_TYPE_E sio_type);

#endif
