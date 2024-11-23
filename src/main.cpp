#include "main.h"

volatile unsigned int overflowCount = 0; // Counter to track timer overflows

void setup() {

  DDRB = 0xFF; // Set PORTB (D8-D13) as output
  DDRC = 0xFF; // Set PORTC (A0-A5) as output
  DDRD = 0xFF & ~(1 << PD2); // Clear bit 2 of DDRD to make PD2 an input

  PORTB = 0x00; // Drive PORTB low
  PORTC = 0x00; // Drive PORTC low
  PORTD = 0x00; // Drive PORTD low

  #ifdef DEBUG
    Serial.begin(9600);
  #endif
  DEBUG_PRINT("Timer1 started...");

  pinMode(ledPin, OUTPUT);              // Set LED pin as output
  digitalWrite(ledPin, LOW);            // Ensure LED starts OF
  
  noInterrupts();                       // Desativa interrupções durante configuração

  // Configuração do Timer1
  TCCR1A = 0;                           // Modo normal
  TCCR1B = 0;                           // Reseta registros
  TCCR1B |= (1 << CS11) | (1 << CS10);  // Prescaler de 64
  TCNT1 = 0;                            // Reseta contador do Timer1
  
  // Configura a interrupção externa (pino 2 - INT0)
  attachInterrupt(digitalPinToInterrupt(2), handleInterrupt, RISING);
  
  interrupts();                         // Habilita interrupções

}

void loop() {
  if (newMeasurement) {
    noInterrupts();
    uint16_t currentTimeDiff = timeDiff;
    newMeasurement = false;
    interrupts();
    
    // Decide o estado do LED baseado na diferença de tempo
    if (currentTimeDiff >= minCountsA && currentTimeDiff <= maxCountsA) {
      stableCountA++;
      stableCountB = 0;               // Reset B counter if A is stable
      if (stableCountA >= minStableCount) {
        digitalWrite(ledPin, HIGH);   // Turn LED ON (Case A)
        DEBUG_PRINT("> Inversor (%d)", currentTimeDiff);
      }
    } else if (currentTimeDiff >= minCountsB && currentTimeDiff <= maxCountsB) {
      stableCountB++;
      stableCountA = 0;               // Reset A counter if B is stable
      if (stableCountB >= minStableCount) {
        digitalWrite(ledPin, LOW);    // Turn LED OFF (Case B)
        DEBUG_PRINT("> Rede Elétrica (%d)", currentTimeDiff);

      }
    } else {
      stableCountA = 0;
      stableCountB = 0;
      DEBUG_PRINT("#ERROR > NOT DETECTED (%d)", currentTimeDiff);
    }
  }
}

void handleInterrupt() {
  uint16_t currentTimerValue = TCNT1;             // Lê o valor atual do Timer1
  timeDiff = currentTimerValue - lastTimerValue;  // Calcula o intervalo
  lastTimerValue = currentTimerValue;             // Atualiza o último valor
  newMeasurement = true;                          // Marca nova medição disponível
}

