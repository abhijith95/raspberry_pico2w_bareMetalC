#ifndef TIMER_H
#define TIMER_H

/* Page 554 for the chosen value */
#define XOSC_STARTUP_DELAY  (uint32_t) 47
#define CLK_SRC_READ_STATUS(x)  (x & (1<<31))
#define CLK_SRC_ENABLE      0xFAB
#define CLK_SRC_DISABLE     0xD1E
#define CLK_SRC_READ_ENABLE(x)  (x & 0x00FFF000)
#define CLK_SRC_WRITE_ENABLE        0xFFFABFFF
#define CLK_SRC_WRITE_DISABLE       0xFFD1EFFF
#define CLK_REF_XOSC_SRC        0x2
#define CLK_TICK_ENABLE         0x1
#define CLK_TICK_GEN_STPD       0x0
#define CLK_TICK_GEN_RUNG       0x1
#define CLK_TICK_CYCLES_1uS     ((uint32_t) 12)
#define CONV_US_MS              ((uint16_t) 1000)
#define APPL_CYCLE_TIME_US      ((uint16_t) 10) * CONV_US_MS

/* Registers */
#define CLK_GEN_REF_INFO            ((clock_gen_info*) (0x40010030))
#define CLK_SRC_XOSC_INFO           ((clock_source_info*) (0x40048000))
#define TCK_GEN_TIMER0_INFO         ((tick_gen_info*) (0x40108018))
#define TCK_GEN_TIMER1_INFO         ((tick_gen_info*) (0x40108024))

/* Enumeration for clock sources */
typedef enum
{
    XOSC = 0,
    ROSC,
    LPOSC,
    USB_PLL,
    SYS_PLL,
    GPIO0_SRC,
    GPIO1_SRC
}CLOCK_SOURCES;

/* Enum for clock generators */
typedef enum
{
    GPIO0_GEN,
    GPIO1_GEN,
    GPIO2_GEN,
    GPIO3_GEN,
    REF,
    SYS,
    PERI,
    HSTX,
    USB,
    ADC
}CLOCK_GENERATORS;

/* Enum for tick generators */
typedef enum
{
    PROC0 = 0,
    PROC1,
    TIMER0,
    TIMER1,
    WATCHDOG,
    RISCV
}TICK_GENERATORS;

/* Information to configure clock generators */
typedef struct
{
    uint32_t ctrl;
    uint32_t div;
    uint32_t sel;
}clock_gen_info;

/* Information to configure clock sources */
typedef struct 
{
    uint32_t ctrl;
    uint32_t status;
    uint32_t dormant;
    uint32_t startup;
}clock_source_info;

/* Information to confgigure tick generators */
typedef struct
{
    uint32_t ctrl;
    uint32_t cycles;
    uint32_t count;
}tick_gen_info;


/* Function prototypes */
void Configure_clock_source(CLOCK_SOURCES clk_src, clock_source_info *info);
void Configure_clock_genrtrs(CLOCK_GENERATORS clk_gen, clock_gen_info *info);
void Configure_tick_genrtrs(TICK_GENERATORS tick_gen, tick_gen_info *info);

#endif
