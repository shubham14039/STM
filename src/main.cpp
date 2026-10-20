#include <stdint.h>

extern "C" int main();

/* ===================== RCC / GPIO REGISTERS ===================== */

// RCC AHB4 peripheral clock enable register
constexpr uintptr_t RCC_AHB4ENR_ADDR = 0x580244E0U;

// GPIOE base address
constexpr uintptr_t GPIOE_BASE = 0x58001000U;

// Register references
volatile uint32_t &RCC_AHB4ENR =
    *reinterpret_cast<volatile uint32_t *>(RCC_AHB4ENR_ADDR);

volatile uint32_t &GPIOE_MODER =
    *reinterpret_cast<volatile uint32_t *>(GPIOE_BASE + 0x00);

volatile uint32_t &GPIOE_BSRR =
    *reinterpret_cast<volatile uint32_t *>(GPIOE_BASE + 0x18);

/* ===================== SYSTICK REGISTERS ===================== */

constexpr uintptr_t SYST_CSR = 0xE000E010;
constexpr uintptr_t SYST_RVR = 0xE000E014;
constexpr uintptr_t SYST_CVR = 0xE000E018;

volatile uint32_t &SysTick_CTRL =
    *reinterpret_cast<volatile uint32_t *>(SYST_CSR);

volatile uint32_t &SysTick_LOAD =
    *reinterpret_cast<volatile uint32_t *>(SYST_RVR);

volatile uint32_t &SysTick_VAL =
    *reinterpret_cast<volatile uint32_t *>(SYST_CVR);

/* ===================== CLOCK ===================== */

// Default H7 clock after reset (HSI / 2)
constexpr uint32_t CPU_HZ = 16000000; // adjust if PLL changes

/* ===================== SYSTICK FUNCTIONS ===================== */

static void systick_init() {
    SysTick_LOAD = (CPU_HZ / 1000) - 1; // 1 ms tick
    SysTick_VAL  = 0;
    SysTick_CTRL = (1 << 0) | (1 << 2); // ENABLE | CLKSOURCE = CPU
}

// Delay using the counter value directly (safer than COUNTFLAG)
static void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms; ++i) {
        uint32_t start = SysTick_VAL;
        uint32_t ticks = SysTick_LOAD + 1; // ticks per ms
        while (true) {
            uint32_t now = SysTick_VAL;
            uint32_t elapsed = (start >= now) ? (start - now) : (SysTick_LOAD + 1 - (now - start));
            if (elapsed >= ticks) break;
        }
    }
}

/* ===================== MAIN ===================== */

extern "C" int main() {
    // Enable GPIOE clock
    RCC_AHB4ENR |= (1u << 4);
    volatile uint32_t tmp = RCC_AHB4ENR;
    (void)tmp;

    // Configure PE1 as output
    const uint32_t pin = 1;
    GPIOE_MODER &= ~(0x3u << (2 * pin));
    GPIOE_MODER |=  (0x1u << (2 * pin));

    systick_init();

    while (1) {
        // LD4 (green) on Nucleo H7 is active-low
        GPIOE_BSRR = (1u << (pin + 16));   // LED ON
        delay_ms(1000);

        GPIOE_BSRR = (1u << pin);          // LED OFF
        delay_ms(1000);
    }
}
