#ifndef MAIN_H
#define MAIN_H

// Include standard Arduino and AVR libraries
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Define constants
volatile uint16_t lastTimerValue = 0;          // Último valor do Timer1
volatile uint16_t timeDiff = 0;                // Diferença entre eventos
volatile bool newMeasurement = false;          // Indica se há nova medida
volatile uint8_t stableCountA = 0;             // Counts consecutive matches in range A
volatile uint8_t stableCountB = 0;             // Counts consecutive matches in range B
volatile const uint8_t minStableCount = 5;     // Minimum stable counts to confirm change

const int ledPin = 4; //PD4

/**
 * For 59 Hz 
 *   - Counts=16,000,00064 * 59=16,000,0003,776≈4,240 
 *     Counts= 64 * 5916,000,000 = 3,77616,000,000 ≈ 4,240
 * For 59.8 Hz
 *   - Counts=16,000,00064 * 59.8=16,000,0003,827.2≈4,180
 *     Counts= 64 * 59.816,000,000 = 3,827.216,000,000 ≈ 4,180
 * For 59.9 Hz
 *   - Counts=16,000,00064 * 59.9=16,000,0003,833.6≈4,175
 *     Counts= 64 * 59.916,000,000 = 3,833.616,000,000 ≈ 4,175
 * For 60.8 Hz
 *   - Counts=16,000,00064 * 60.8=16,000,0003,891.2≈4,112
 *     Counts= 64 * 60.816,000,000 = 3,891.216,000,000 ≈ 4,112
 */

// const uint16_t minCountsA = 4176; // 59.89 Hz 
const uint16_t minCountsA = 4184; // 59.77 Hz 
const uint16_t maxCountsA = 4280; 
const uint16_t minCountsB = 4112;
const uint16_t maxCountsB = 4183; // 59.78 hz
// const uint16_t maxCountsB = 4175; // 59.90 hz

#ifdef DEBUG
  #define  DEBUG_PRINT(...)        \
  {                                \
    char buffer[100];              \
    snprintf(buffer, sizeof(buffer), __VA_ARGS__); \
    Serial.println(buffer);        \
  }
#else
  #define DEBUG_PRINT(...)
#endif


// Function prototypes
void handleInterrupt();

#endif // MAIN_H
