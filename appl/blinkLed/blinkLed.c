#include <stdint.h>
#include "gpio_pins.h"
#include "blinkLed.h"

/* Variable definitions */
#define LED_OFF_MS      (uint32_t)1000
#define LED_ON_MS       (uint32_t)1000
#define LED_GPIO        (uint8_t)0
#define PIN_HIGH        (uint8_t)1 
#define PIN_LOW         (uint8_t)0
#define TICK_UPDATE     (uint16_t)10

typedef enum
{
    LED_OFF = 0,
    LED_ON
}LED_STATES;


void blinkLed_setup()
{
    /* Configure GPIO0 to be of function SIO*/
    Config_gpio_pin(LED_GPIO, SIO_0);
    /* Configure the pin to be digital output */
    Config_gpio_sio(LED_GPIO, OUTPUT);
}


void blinkLed_10ms()
{
    static LED_STATES led_states = LED_OFF;
    static uint32_t timer = (uint32_t)0;

    switch(led_states)
    {
        case LED_OFF:
            Write_gpio(LED_GPIO, OUTPUT_LOW);
            timer += TICK_UPDATE;
            if(timer >= LED_OFF_MS)
            {
                led_states = LED_ON;
                timer = (uint32_t)0;
            }
            else
            {
                /* Stay in the current state */
            }
            break;
        case LED_ON:
            Write_gpio(LED_GPIO, OUTPUT_HIGH);
            timer += TICK_UPDATE;
            if(timer >= LED_OFF_MS)
            {
                led_states = LED_OFF;
                timer = (uint32_t)0;
            }
            else
            {
                /* Stay in the current state */
            }
            break;
        default:
            led_states = LED_OFF;
            timer = (uint32_t)0;
            break;
    }
}

