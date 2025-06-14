#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/* GPIO registers */
#define SIO_BASE            0xD0000000
#define GPIO_IN                 ((volatile uint32_t*)  (SIO_BASE + 0x004))
#define GPIO_HI_IN              ((volatile uint32_t*)  (SIO_BASE + 0x008))
#define GPIO_OUT                ((volatile uint32_t*)  (SIO_BASE + 0x010))
#define GPIO_HI_OUT             ((volatile uint32_t*)  (SIO_BASE + 0x014))
#define GPIO_OUT_SET            ((volatile uint32_t*)  (SIO_BASE + 0x018))
#define GPIO_HI_OUT_SET         ((volatile uint32_t*)  (SIO_BASE + 0x01C))
#define GPIO_OUT_CLR            ((volatile uint32_t*)  (SIO_BASE + 0x020))
#define GPIO_HI_OUT_CLR         ((volatile uint32_t*)  (SIO_BASE + 0x024))
#define GPIO_OE                 ((volatile uint32_t*)  (SIO_BASE + 0x030))
#define GPIO_HI_OE              ((volatile uint32_t*)  (SIO_BASE + 0x034))
#define GPIO_OE_SET             ((volatile uint32_t*)  (SIO_BASE + 0x038))
#define GPIO_HI_OE_SET          ((volatile uint32_t*)  (SIO_BASE + 0x03C))
#define GPIO_PIN_CTRL           ((GPIO_PIN_CTRLS*)  (0x40028000))
#define GPIO_PADS_REG           ((GPIO_PADS*) (0x40038000))
#define NUM_GPIO_PICO2W             ((uint8_t) 28)
#define NUM_GPIO_RP2350             ((uint8_t) 48)
#define LOW_REG_MAX_PINS            ((uint8_t) 32)

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
    PWM_0,
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
    volatile uint32_t gpio_status;
    volatile uint32_t gpio_ctrl;
}GPIO_PIN_CTRLS;

typedef struct 
{
    volatile uint32_t voltage_select;
    volatile uint32_t gpio_pins[NUM_GPIO_RP2350];
    volatile uint32_t swclk;
    volatile uint32_t swd;
} GPIO_PADS;

typedef enum
{
    PULL_UP_ENABLE = 0,
    PULL_DOWN_ENABLE
} GPIO_PULL_UP_TYPES;

typedef enum
{
    OUTPUT_CURR_2MA = 0,
    OUTPUT_CURR_4MA,
    OUTPUT_CURR_8MA,
    OUTPUT_CURR_12MA
} GPIO_DRIVE_STGTH;

typedef enum
{
    OUTPUT_LOW = 0,
    OUTPUT_HIGH
}GPIO_SIO_OUTPUT_LEVEL;

/* Function prototypes */
uint8_t Read_gpio(uint8_t pin);
void Write_gpio(uint8_t pin, GPIO_SIO_OUTPUT_LEVEL pin_value);
void Config_gpio_pin(uint8_t pin, GPIO_FUNCTIONS_E pin_function);
void Config_gpio_sio(uint8_t pin, GPIO_SIO_TYPE_E sio_type);

#endif
