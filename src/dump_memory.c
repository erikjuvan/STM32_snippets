
void update_watchdog(void)
{
    IWDG->KR = IWDG_KEY_RELOAD;
    WWDG->CR = 127;
}

// returns 0 if interrupts are enabled, and non-zero if they are disabled.
bool irqs_are_enabled(void)
{
    return __get_PRIMASK() == 0;
}

void print_nvic_iser(void)
{
    // NVIC ISER registers count depends on the MCU (usually 8 for Cortex-M)
    int num_isers = (SCnSCB->ICTR & 0xF) + 1; // Get the number of ISER registers

    for (int i = 0; i < num_isers; i++)
    {
        printf("NVIC->ISER[%d]: 0x%08X\n", i, NVIC->ISER[i]);
    }
}

void app_dump_memory(const char *str, uint32_t start_addr, uint32_t size)
{
    volatile uint32_t *addr = (uint32_t *)start_addr;
    uint32_t end_addr = start_addr + size;

    printf("BEGIN %s (start_addr:0x%08X  end_addr:%08X  size:%u)\n", str, start_addr, end_addr, size);

    for (; (uint32_t)addr < end_addr; addr++)
    {
        // Attempt to read the memory address safely
        uint32_t value = *addr;

        // Print the address and its value
        printf("0x%08X: 0x%08X\n", (uint32_t)addr, value);

        // Update watchdogs to prevent reset
        app_update_watchdog();

        // Delay to allow time for TRACE to finish
        HAL_Delay(5);
    }

    printf("END %s\n", str);
}

void dump_registers(const char* str)
{
    #define REG_ENTRY(NAME)        { #NAME, NAME, sizeof(*NAME) }
    #define REG_ENTRY_MEMBER(NAME) { #NAME, NAME, sizeof(NAME) }
    struct {
        const char *name;
        void *base;
        uint32_t size;
    } regs[] = {
        REG_ENTRY(DMA1_Channel1),
        REG_ENTRY(ADC2),
        REG_ENTRY(TIM8),
        REG_ENTRY(RCC),
        REG_ENTRY_MEMBER(NVIC->ISER),
    };

    printf("=== BEGIN '%s' ===\n", str);

    for (int i = 0; i < sizeof(regs) / sizeof(regs[0]); ++i)
    {
        app_dump_memory(regs[i].name, (uint32_t)regs[i].base, regs[i].size);
    }

    // TRACE additional values not directly memory locations
    printf("IRQs %s\n", irqs_are_enabled() ? "ENABLED" : "DISABLED");
    print_nvic_iser();

    printf("=== END '%s' ===\n", str);
}
