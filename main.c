#include <stdint.h>
#include "timer.h"

#ifdef APPL_BLINKLED
#include "blinkLed.h"
#endif

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
    info.ctrl = (uint32_t)0xAA0;  /* Set the frequency range to 0 - 15 MHz pg 557 */
    info.ctrl |= CLK_SRC_WRITE_ENABLE;
    /* Enable XOSC source */
    Configure_clock_source(XOSC, &info);
    /* Disable ROSC source */
    info.ctrl = 0;
    info.ctrl |= CLK_SRC_WRITE_DISABLE;
    Configure_clock_source(XOSC, &info);
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
    while(temp.sel != CLK_REF_XOSC_SRC)
    {
        /* Wait for the source to switch */
    }
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

    #ifdef APPL_BLINKLED
    blinkLed_setup();
    #endif
}

/**
 * @brief Main function
 * 
 */
void main()
{
    static uint16_t time_us;
    tick_gen_info *timer0 = TCK_GEN_TIMER0_INFO;

    setup();

    while(1)
    {
        if(timer0->count == (uint32_t)0)
        {
            time_us += (uint16_t)1;
        }
        else
        {
            /* Do not update the timer */
        }

        if(time_us == APPL_CYCLE_TIME_US)
        {
            /* Call the application main function */
            #ifdef APPL_BLINKLED
            blinkLed_10ms();
            #endif
        }
        else
        {
            /* Wait for 10ms time */
        }

    }
}
