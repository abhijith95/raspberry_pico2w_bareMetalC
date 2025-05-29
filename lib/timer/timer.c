#include <stdint.h>
#include "timer.h"

/**
 * @brief Function to configure a clock source
 * 
 * @param clk_src - Enum indicating the clock source
 * @param info - Necessary information to configure the source
 */
void Configure_clock_source(CLOCK_SOURCES clk_src, clock_source_info *info)
{
    clock_source_info *temp;
    switch(clk_src)
    {
        case XOSC:
            temp = CLK_SRC_XOSC_INFO;
            break;
        case ROSC:
            break;
        case LPOSC:
            break;
        case USB_PLL:
            break;
        case SYS_PLL:
            break;
        case GPIO0_SRC:
            break;
        case GPIO1_SRC:
            break;
        default:
            temp = CLK_SRC_XOSC_INFO;
            break;
    }
    temp->ctrl = info->ctrl;
    temp->dormant = info->dormant;
    temp->startup = info->startup;
    temp->status = info->status;

    /* Check if the clock source has been enabled or disabled */
    while((CLK_SRC_READ_STATUS(temp->status) == 0) &&
         (CLK_SRC_READ_ENABLE(temp->ctrl) == CLK_SRC_ENABLE))
    {
        /* Wait for the clock to get stable, in case enabled */
    }
}

/**
 * @brief Function to configure a clock generator
 * 
 * @param clk_gen - Enum indicating the clock generator 
 * @param info - Necessary information to configure the generator
 */
void Configure_clock_genrtrs(CLOCK_GENERATORS clk_gen, clock_gen_info *info)
{
    clock_gen_info *temp;
    switch(clk_gen)
    {
        case GPIO0_GEN:
            break;
        case GPIO1_GEN:
            break;
        case GPIO2_GEN:
            break;
        case GPIO3_GEN:
            break;
        case REF:
            temp = CLK_GEN_REF_INFO;
            break;
        case SYS:
            break;
        case PERI:
            break;
        case HSTX:
            break;
        case USB:
            break;
        case ADC:
            break;
        default:
            temp = CLK_GEN_REF_INFO;
            break;
    }
    temp->ctrl = info->ctrl;
    temp->div = info->div;
    temp->sel = info->sel;
}

/**
 * @brief Function to configure a tick generator
 * 
 * @param tick_gen - Enum indicating the tick generator
 * @param info - Necessary information to configure the tick generator
 */
void Configure_tick_genrtrs(TICK_GENERATORS tick_gen, tick_gen_info *info)
{
    tick_gen_info *temp;
    switch(tick_gen)
    {
        case PROC0:
            break;
        case PROC1:
            break;
        case TIMER0:
            temp = TCK_GEN_TIMER0_INFO;
            break;
        case TIMER1:
            temp = TCK_GEN_TIMER1_INFO;
            break;
        case WATCHDOG:
            break;
        case RISCV:
            break;
        default:
            temp = TCK_GEN_TIMER0_INFO;
            break;
    }
    temp->ctrl = info->ctrl;
    temp->count = info->count;
    temp->cycles = info->cycles;

    if((temp->ctrl & 0x00000001) == CLK_TICK_ENABLE)
    {
        while((temp->ctrl & 0x00000002) == CLK_TICK_GEN_STPD)
        {
            /* Wait until the tick generator is running */
        }
    }
    else
    {
        /* Do nothing */
    }
}
