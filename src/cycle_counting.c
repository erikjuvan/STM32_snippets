////////////////////////////
// Counting cycles using DWT
////////////////////////////
/* Registers
DWT_CYCCNT   = (int *)0xE0001004; DWT->CYCCNT
DWT_CONTROL  = (int *)0xE0001000; DWT->CTRL
SCB_DEMCR    = (int *)0xE000EDFC; CoreDebug->DEMCR
*/

void EnableCC()
{
    CoreDebug->DEMCR |= 0x01000000; // Enable DWT and ITM features
    DWT->CYCCNT = 0;                // Set Cycle Count register to zero
    DWT->CTRL |= 1;                 // Enable CYCCNT
}

void DisableCC()
{
    DWT->CTRL &= ~1; // Disable CYCCNT
}

#define RESET_CC() DWT->CYCCNT = 0 // Set Cycle Count register to zero
#define GET_CC() DWT->CYCCNT

// ASM macros
/////////////
#define RESET_CC_ASM()              \
    __asm__("ldr r0, =0");          \
    __asm__("ldr r4, =0xE0001004"); \
    __asm__("str r0, [r4]")

#define GET_CC_ASM() __asm__("ldr r0, [r4]") // r0 = DWT->CYCCNT
/////////////

/* ******** */
/* EXAMPLES */
/* ******** */

// Example C with asm
/////////////////////
EnableCC();

RESET_CC_ASM();
// action_to_time();
GET_CC_ASM();
__asm__("nop"); // useful for breakpoint
/////////////////////

// Example C:
/////////////////////
EnableCC();

ResetCC();
// action();
int    cycles        = GetCC();
double seconds_taken = cycles * (1.0 / (float)SystemCoreClock);
__asm__("nop");
/////////////////////////////////

////////////////////////////////
// Counting cycles using SysTick
////////////////////////////////
/* Registers
int *STCSR = (int *)0xE000E010;	SysTick->CTRL
int *STRVR = (int *)0xE000E014;	SysTick->LOAD
int *STCVR = (int *)0xE000E018;	SysTick->VAL
*/

#define GetSTCVR() SysTick->VAL // The number of core clock cycles taken by the operation is given by: (STCVR1 - STCVR2 - 2)

// Usually not neede because HAL_Init() already initializes SysTick
void StartST()
{
    SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
    SysTick->VAL  = 0;
    SysTick->CTRL = 5;
}

void StopST()
{
    SysTick->CTRL = 0;
}

// Example (no initalization needed, because HAL_Init() already initializes SysTick
__asm__("ldr r4, =0xE000E018");
__asm__("ldr r0, [r4]"); // r0 = SysTick->VAL;
// function to time
__asm__("ldr r1, [r4]");   // r1 = SysTick->VAL;
__asm__("sub r0, r0, r1"); // r0 = r0 - r1 -> timer counts down

/////////////////////////////////
