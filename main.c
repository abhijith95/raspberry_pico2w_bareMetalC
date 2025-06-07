#include <stdint.h>
#include "timer.h"
#include "blinkLed.h"

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
    info.ctrl = (CLK_SRC_WRITE_ENABLE << CLK_SRC_ENABLE_BIT_POS);
    info.dormant = CLK_SRC_AWAKE;
    /* Enable XOSC source */
    Configure_clock_source(XOSC, &info);
    /* Disable ROSC source */
    info.ctrl = 0;
    info.ctrl =(CLK_SRC_WRITE_DISABLE << CLK_SRC_ENABLE_BIT_POS);
    info.dormant = CLK_SRC_DORMANT;
    Configure_clock_source(ROSC, &info);
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
    temp.div = 0;
    Configure_clock_genrtrs(REF, &temp);
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
    static uint32_t time_us = (uint32_t)0;
    tick_gen_info *timer0 = TCK_GEN_TIMER0_INFO;

    setup();

    while(1)
    {
        if(CLK_TICK_GET_COUNT(timer0->count) == (uint32_t)0)
        {
            time_us += (uint32_t)1;
        }
        else
        {
            /* Do not update the timer */
        }

        if(time_us >= APPL_CYCLE_TIME_US)
        {
            /* Call the application main function */
            blinkLed_10ms();
            time_us += (uint32_t)0;
        }
        else
        {
            /* Wait for 10ms time */
        }

    }
}
