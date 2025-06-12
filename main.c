#include <stdint.h>
#include "timer.h"
#include "blinkLed.h"
#include "gpio_pins.h"

#define SYSTEM_TIMER    TIMER0_SYS_TIMER

/**
 * @brief Function to setup the clock source for the application
 * 
 * Idea is to enable XOSC clock source once the board starts running and 
 * disable ROSC clock source
 */
void clock_src_setup()
{
    clock_source_info info;
    info.startup = XOSC_STARTUP_DELAY;
    info.ctrl = 0;
    info.ctrl = (uint32_t)0xAA0;  /* Set the frequency range to 0 - 15 MHz pg 557 */
    info.ctrl |= (CLK_SRC_WRITE_ENABLE << CLK_SRC_ENABLE_BIT_POS);
    info.dormant = CLK_SRC_AWAKE;
    /* Enable XOSC source */
    Configure_clock_source(XOSC, &info);
    /* Disable ROSC source */
    Disable_ROSC();
}

/**
 * @brief Function to setup the clock generator for the board
 * 
 * Main idea is to assign the clock source for clk_ref generator. Since this generator
 * will be used to generate the ticks, needed mainly for the applications
 * 
 */
void clock_gen_setup()
{
    clock_gen_info temp;
    temp.ctrl = CLK_REF_XOSC_SRC;  /* Set XOSC as the clock source */
    Configure_clock_genrtrs(REF, &temp);
    /* Set the system clock generator to reference clock generator */
    temp.ctrl = CLK_SYS_REF_SRC;
    Configure_clock_genrtrs(SYS, &temp);
}

/**
 * @brief Function to setup the tick generators
 * 
 */
void clock_tick_setup()
{
    tick_gen_info info;
    info.ctrl = CLK_TICK_ENABLE;
    info.cycles = CLK_TICK_CYCLES_1uS;
    Configure_tick_genrtrs(TIMER0, &info);
}

/**
 * @brief Function to setup the initial settings for the board
 * 
 */
void setup()
{
    /* Main setup for the board */
    clock_src_setup();
    clock_gen_setup();
    clock_tick_setup();
    
    /* Application setup */
    blinkLed_setup();
}

/**
 * @brief Main function
 * 
 */
int main()
{
    uint64_t system_time = (uint64_t)0;

    setup();
    Reset_sys_timer(SYSTEM_TIMER);
    while(1)
    {
        Read_sys_timer(SYSTEM_TIMER, &system_time);
        if(system_time >= APPL_CYCLE_TIME_US)
        {
            /* Call the application main function */
            blinkLed_10ms();
            Reset_sys_timer(SYSTEM_TIMER);
        }
        else
        {
            /* Wait for 10ms time */
        }

    }
}
