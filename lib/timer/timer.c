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
    uint8_t sel_bits;
    uint8_t ctrl_bits;
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
            sel_bits = 7u;
            ctrl_bits = 3u;
            break;
        case SYS:
            temp = CLK_GEN_SYS_INFO;
            sel_bits = 1u;
            ctrl_bits = 1u;
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
    // while((temp->sel & sel_bits) != (temp->ctrl & ctrl_bits))
    // {
    //     /* Wait for the source to switch */
    // }
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
    /* Disable the tick generator while configuring the cycles*/
    temp->ctrl = CLK_TICK_DISABLE;
    temp->cycles = info->cycles;
    /* Write the original ctrl value */
    temp->ctrl = info->ctrl;

    if(((temp->ctrl & 0x1) >> 1) == CLK_TICK_ENABLE)
    {
        while(((temp->ctrl & 0x2) >> 2) != CLK_TICK_GEN_RUNG)
        {
            /* Wait until the tick generator is running */
        }
    }
    else
    {
        /* Do nothing */
    }
}

/**
 * @brief Function to reset the system timer registers to zero
 * 
 * @param timer_info - Struct pointing to the system timer registers
 */
void Reset_sys_timer(sys_timer_info* timer_info)
{
    /* Write to the low reigster first */
    timer_info->timelw = RESET_TIMER;
    timer_info->timehw = RESET_TIMER;
}

/**
 * @brief Function to read the system timer
 * 
 * @param timer - Struct pointing to the system timer registers
 * @param sys_time - Variable containing the final value of the system time
 */
void Read_sys_timer(sys_timer_info* timer, uint64_t* sys_time)
{
    *sys_time = (((uint64_t) timer->timehr) << 32u) | timer->timelr;
}


void Disable_ROSC()
{
    *((volatile uint32_t*)(CLK_SRC_ROSC_INFO)) = (CLK_SRC_WRITE_DISABLE << CLK_SRC_ENABLE_BIT_POS);
    volatile uint32_t* temp = ((volatile uint32_t*)(CLK_SRC_ROSC_INFO + 0x1C));
    while ((*temp & (1 << 31)) != 0);
}


void Enable_ROSC()
{
    *((volatile uint32_t*)(CLK_SRC_ROSC_INFO)) = (CLK_SRC_WRITE_ENABLE << CLK_SRC_ENABLE_BIT_POS);
    volatile uint32_t* temp = ((volatile uint32_t*)(CLK_SRC_ROSC_INFO + 0x1C));
    while ((*temp & (1 << 31)) != 1);
}