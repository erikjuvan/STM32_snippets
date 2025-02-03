void basics()
{
    __enable_irq()   // enable all interrupts
    __disable_irq()  // disable all interrupts

    // Returns the current state of the priority mask bit from the Priority Mask
    // Register. [0 if global interrupts are **enabled** and non-zero if they
    // are **disabled**]
    __get_PRIMASK()
}

void basics2()
{
    // 1. back up interrupt state; `__get_PRIMASK()` returns 0 if interrupts
    // are **enabled**, and non-zero if they are **disabled**.
    bool interrupts_enabled = (__get_PRIMASK() == 0);

    // 2. Disable interrupts
    __disable_irq();

    // do stuff

    // 3. Restore backed-up-state
    if (interrupts_enabled) {
        __enable_irq();
    }
}

void ImportantFunction1(void)
{
    uint32_t prim;

    /* Do some stuff here which can be interrupted */

    /* Read PRIMASK register, check interrupt status before you disable them */
    /* Returns 0 if they are enabled, or non-zero if disabled */
    prim = __get_PRIMASK();

    /* Disable interrupts */
    __disable_irq();

    /* Do some stuff here which can not be interrupted */

    /* Call subfunction */
    ImportantFunction2();

    /* Do some stuff here which can not be interrupted */
    /* This part is still interrupt safe if ImportantFunction2 does not enable interrupts */

    /* Enable interrupts back */
    if (!prim) {
        __enable_irq();
    }

    /* Do some stuff here which can be interrupted */
}