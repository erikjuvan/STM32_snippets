/**
 * Perfect tool to catch a memory change via watchpoint and go to an IRQ.
 */

 #include "stm32g4xx_hal.h"

 ////////////////////////////////////////////////////////////////////////////////
 /**
 * @brief Configure 2 watchpoints that will trigger on a write access.
 *        Enable Debug Monitor exception so we can capture the moment.
 * @note  Upon hitting the watchpoint the program will enter DebugMon_Handler
 *        only if the debugger is NOT attached!
 *        If the debbugger is attached it will trigger a breakpoint.
 */
 ////////////////////////////////////////////////////////////////////////////////
void setup_watchpoints(void)
{
    // Enable TRC (Trace Control)
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    // Enable Debug Monitor exception
    CoreDebug->DEMCR |= CoreDebug_DEMCR_MON_EN_Msk;

    // --- Watchpoint 0 ---
    DWT->COMP0 = (uint32_t)&RCC->BDCR; // Address to watch
    DWT->MASK0 = 0;                    // Exact match
    DWT->FUNCTION0 = (0x6);            // Watch for writes (0x6 = write access)

    // --- Watchpoint 1 ---
#undef COMP1 // since COMP1 is defined for compressor 1 it causes a build error
    extern volatile uint32_t aStackOverFlowPtrn[4];
    DWT->COMP1 = (uint32_t)aStackOverFlowPtrn; // Second address to watch
    DWT->MASK1 = 0;                            // Exact match
    DWT->FUNCTION1 = (0x6);                    // Watch for writes (0x6 = write access)
}

 ////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Debug Monitor IRQ handler - example
 */
 ////////////////////////////////////////////////////////////////////////////////
void DebugMon_Handler(void)
{
    TRACE_FLUSH_MANUAL_IRQ_CALLS();

    TRACE_FAT("DebugMon Exception");

    print_stackdump();

    FailSafePOR();
}