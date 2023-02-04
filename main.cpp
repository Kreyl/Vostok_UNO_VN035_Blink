/*
 * main.c
 *
 *  Created on: 3 февр. 2023 г.
 *      Author: layst
 */

#include <inttypes.h>
#include "K1921VK035.h"

int main() {
    RCU->HCLKCFG_bit.GPIOBEN = 1; // Enable clocking of GPIOB
    RCU->HRSTCFG_bit.GPIOBEN = 1; // Remove Reset of GPIOB

    GPIOB->DENSET = 0b1UL << 5;          // Connect pin 5 to digital subsystem
    GPIOB->INMODE |= 0b11UL << 10;       // Input functionality disabled
    GPIOB->PULLMODE &= ~(0b11UL << 10);  // No Pull Up/Down
    GPIOB->OUTMODE &= ~(0b11UL << 10);   // Output push-pull
    GPIOB->DRIVEMODE &= ~(0b11UL << 10); // High speed, high current
    GPIOB->OUTENSET = 0b1UL << 5;        // Enable pin control by DataOut reg
    GPIOB->ALTFUNCCLR = 0b1UL << 5;      // Disable alt func at the pin

    while(1) {
        GPIOB->DATAOUTTGL = 0b1UL << 5;  // Toggle pin
        for(volatile uint32_t i=0; i<1000000UL; i++); // Delay loop
    }
}

