////////////////////////////////////////////////////////////////////////////////
/**
 * Memory Protection Unit (MPU).
 *
 * This will issue a Hardfault interrupt if trying to write to memory under
 * MPU protection.
 *
 * The minimum size of protected memory is 32 bytes, so it is not ideal for
 * catching memory writes on small memory ares like a single int or byte.
 *
 * Explanatino of how memory regions work (e.g. what memory will be protected)
 * if e.g. specifiying addr 0x14
 *
 * ME: can you explain why MPU when the address to protect is e.g.
 * 0x20000150 and the size to protect is set to 32 bytes it will actually protect 0x20000140 to 0x20000160..
 *
 * CHATGPT:
 * The behavior you're seeing with the MPU (Memory Protection Unit) on the Cortex-M4 —
 * where setting protection for 0x20000150 with a 32-byte region results in protection
 * from 0x20000140 to 0x20000160 — is due to how the MPU aligns memory regions.
 *
 * MPU Alignment Rules:
 * 1. Power-of-Two Region Sizes:
 *   - The MPU only supports region sizes that are powers of two (e.g., 32B, 64B, 128B, etc.).
 *   - In your case, 32 bytes is valid (since 2**5=32)
 * 2. Alignment to Region Size:
 *   - The base address must be aligned to the size of the region.
 *   - For a 32-byte region, the base address must be aligned to 32 bytes, meaning it should be a multiple of 0x20 (32 in hex).
 *
 * Why 0x20000140 to 0x20000160?
 * - Your target address: 0x20000150
 * - Region size: 32 bytes
 * The MPU rounds down the base address to the nearest 32-byte aligned boundary:
 * 1. Alignment calculation:
 *   0x20000150 rounded down to the nearest multiple of 0x20 → 0x20000140.
 * 2. Protected range:
 *   Starting at 0x20000140 and covering 32 bytes → up to 0x20000160 (exclusive).
 * So, the MPU ends up protecting 0x20000140 to 0x2000015F, since 0x20000160 is the first unprotected address.
 */
////////////////////////////////////////////////////////////////////////////////

#include "stm32g4xx_hal.h"

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Configure MPU to protect memory area
 *
 * The MPU requires memory regions to be sized as powers of two and aligned
 * to their size. For example, protecting an address like 0x20000150 with a
 * 32-byte (0x20) region will result in the MPU protecting the aligned range
 * 0x20000140 to 0x2000015F. This alignment ensures proper MPU configuration
 * but may lead to overprotection of adjacent memory.
 */
////////////////////////////////////////////////////////////////////////////////
void mpu_protect(const void *addr)
{
    // Enable the MPU clock if required (usually not needed on Cortex-M4)

    // Disable MPU before configuration
    MPU->CTRL = 0;

    // Configure MPU Region 0 for addr
    MPU->RNR = 0;                // Select Region 0
    MPU->RBAR = (uint32_t) addr; // Base address

    // Set region size to 32 bytes (smallest allowed) and mark as read-only
    // AP = 0b110: privileged read-only, unprivileged no access
    MPU->RASR = (0b110 << 24) |  // Access permission
                (0b000 << 19) |  // TEX (normal memory)
                (0 << 18) |      // S (non-shareable)
                (0 << 17) |      // C (non-cacheable)
                (0 << 16) |      // B (non-bufferable)
                (4 << 1)  |      // Region size = 2^(4+1) = 32 bytes
                (1 << 0);        // Enable this region

    // Enable MPU with default memory map for privileged access
    MPU->CTRL = (1 << 2) |  // Enable MPU during hard fault, NMI, etc.
                (1 << 0);   // Enable MPU globally

    // Ensure MPU settings take effect
    __DSB();
    __ISB();
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief HardFault IRQ handler - example
 */
////////////////////////////////////////////////////////////////////////////////
void HardFault_Handler(void)
{
    printf("HardFault");

    print_stackdump();
}
