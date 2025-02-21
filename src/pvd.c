/**
 * From datasheet...
 *
 * Programmable voltage detector (PVD)
 *
 * You can use the PVD to monitor the VDD power supply by comparing it to a threshold
 * selected by the PLS[2:0] bits in the Power control register 2 (PWR_CR2).
 *
 * The PVD is enabled by setting the PVDE bit.
 *
 * A PVDO flag is available, in the Power status register 2 (PWR_SR2), to indicate if VDD is
 * higher or lower than the PVD threshold. This event is internally connected to the EXTI line16
 * and can generate an interrupt if enabled through the EXTI registers. The PVD output
 * interrupt can be generated when VDD drops below the PVD threshold and/or when VDD
 * rises above the PVD threshold depending on EXTI line16 rising/falling edge configuration.
 * As an example, the service routine could perform emergency shutdown tasks.
 */

/**
 * Use this to detect falling MCU voltage. This way if caught early enough some
 * actions can be taken, before powering down.
 */

#include "stm32g4xx_hal.h"

////////////////////////////////////////////////////////////////////////////////
/**
* @brief Configure Programmable voltage detector (PVD)
*        This will trigger a PVD_PVM_IRQHandler when voltage falls below threshold
*/
////////////////////////////////////////////////////////////////////////////////
void PVD_Config(void)
{
    PWR_PVDTypeDef pvdConfig = {0};

    // Enable clock
    __HAL_RCC_PWR_CLK_ENABLE();

    // PVD configuration
    pvdConfig.Mode = PWR_PVD_MODE_IT_RISING; // Interrupt when voltage falls below threshold
                                             // it's weird that the mode is *_IT_RISING since
                                             // we are after the voltage falling, but I think
                                             // that rising simply means the PVD event is going
                                             // from no event (0) to event (1) which is 'rising'
    pvdConfig.PVDLevel = PWR_PVDLEVEL_0;     // Threshold
    HAL_PWR_ConfigPVD(&pvdConfig);

    // Enable PVD
    HAL_PWR_EnablePVD();

    // PVD_PVM_IRQn interrupt set priority and enable
    HAL_NVIC_SetPriority(PVD_PVM_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(PVD_PVM_IRQn);
}

////////////////////////////////////////////////////////////////////////////////
/**
* @brief PVD IRQ handler
*/
////////////////////////////////////////////////////////////////////////////////
void PVD_PVM_IRQHandler(void)
{
    // Call HAL PVD/PVM IRQ handler
    HAL_PWREx_PVD_PVM_IRQHandler();
}

////////////////////////////////////////////////////////////////////////////////
/**
* @brief Example Callback for PVD interrupt
*
*/
////////////////////////////////////////////////////////////////////////////////
void HAL_PWR_PVDCallback(void)
{
    // Do stuff
}