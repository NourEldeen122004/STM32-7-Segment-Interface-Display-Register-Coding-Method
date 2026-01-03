#include "stm32f4xx.h"

/* Common Cathode digit map (gfedcba) */
uint8_t digit_map[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

/* crude delay */
void delay_ms(volatile uint32_t ms)
{
    for (; ms > 0; ms--)
        for (volatile uint32_t i = 0; i < 16000; i++);
}

/* display digit 0–9 */
void display_digit(uint8_t digit)
{
    uint8_t pattern = digit_map[digit];

    /* ---- Clear all segments ---- */
    GPIOA->ODR &= ~((1<<5)|(1<<6)|(1<<7)|(1<<8)|(1<<9));
    GPIOB->ODR &= ~(1<<6);
    GPIOC->ODR &= ~(1<<7);

    /* ---- Set required segments (HIGH = ON) ---- */
    if (pattern & (1<<0)) GPIOA->ODR |= (1<<8); // a
    if (pattern & (1<<1)) GPIOA->ODR |= (1<<9); // b
    if (pattern & (1<<2)) GPIOC->ODR |= (1<<7); // c
    if (pattern & (1<<3)) GPIOB->ODR |= (1<<6); // d
    if (pattern & (1<<4)) GPIOA->ODR |= (1<<7); // e
    if (pattern & (1<<5)) GPIOA->ODR |= (1<<6); // f
    if (pattern & (1<<6)) GPIOA->ODR |= (1<<5); // g
}

int main(void)
{
    /* ---- Enable GPIO clocks ---- */
    RCC->AHB1ENR |= (1<<0); // GPIOA
    RCC->AHB1ENR |= (1<<1); // GPIOB
    RCC->AHB1ENR |= (1<<2); // GPIOC

    /* ---- Configure GPIO as OUTPUT ---- */
    // GPIOA: PA5–PA9
    GPIOA->MODER &= ~(0x3FF << (5*2));
    GPIOA->MODER |=  (0x155 << (5*2)); // output mode

    // GPIOB: PB6
    GPIOB->MODER &= ~(3 << (6*2));
    GPIOB->MODER |=  (1 << (6*2));

    // GPIOC: PC7
    GPIOC->MODER &= ~(3 << (7*2));
    GPIOC->MODER |=  (1 << (7*2));

    while (1)
    {
        /* 0 → 9 */
        for (uint8_t i = 0; i <= 9; i++)
        {
            display_digit(i);
            delay_ms(800);
        }

        /* 8 → 1 */
        for (int8_t i = 8; i >= 1; i--)
        {
            display_digit(i);
            delay_ms(800);
        }
    }
}
