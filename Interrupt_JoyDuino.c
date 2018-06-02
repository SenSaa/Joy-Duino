// {Arduino connections} <->  {Joystick & LED} :
// GND                    -   GND (of joystick button)
// 5V                     -   VCC (of joystick button)
// Pin 1 (PD3/TX)         -   Key (of joystick button)
// GND                    -   Cathode (of LED - shorter LED Pin)
// Pin 11 (PB7)           -   Anode (of LED - longer LED Pin)

// Register set definitions and interrupt header.
#include <avr/io.h>
#include <avr/interrupt.h>
 
int ledPin = 11; // Arduino Pin 11
//int intPin = 7; // If you want to use INT6 instead of INT3 - uncomment this line and comment line 15.
//int intPin = 0; // If you want to use INT2 instead of INT3 - uncomment this line and comment line 15.
int intPin = 1; // INT3
volatile int state = LOW;

void setup()
{
  Serial.begin(9600);
  Serial.println("!");
  
  DDRB = 0b10000000; // PB7 (led pin/pin 11)  = Output
  //pinMode(ledPin, OUTPUT); // Equivalent to above line, if using Arduino Library.
  
  PORTD = 0b00001000; // Set Interrupt (PD3/intPin/pin 1) as High.
  //digitalWrite(intPin, HIGH); // Equivalent to above line, if using Arduino Library.

  // Disble global interrupts
  //cli(); // Not needed - as interrupts are disabled in the ISR.

  // -----------------------------------------------------------------------------
  // External Interrupt Mask Register (EIMSK) - For Enabling External Interrupts
  // -----------------------------------------------------------------------------
 // *** Check the Microchip Atmega datasheet's External Interrupt section on how to enable specific interrupt pins.
  EIMSK |= (1 << INT3);   // Enable INT3.
  //EIMSK |= _BV(INT3);   // Another way of enabling INT3.
  //EIMSK |= 0x03;        // Another way of enabling INT3.
  //EIMSK |= 0b00001000;  // Another way of enabling INT3.
  // -----------------------------------------------------------------------------


  // -----------------------------------------------------------------------------
  // Interrupt Sense Control (ISC)
  // -----------------------------------------------------------------------------
  // *** Check the Microchip Atmega datasheet's Interrupt section for ISC truth table, to select the "trigger state" of the ISR!
  
  // Raising edge - generates interrupt request.
  EICRA |= (1 << ISC30); 
  EICRA |= (1 << ISC31);
 
  // If you want Low logic level (0) - to generate interrupt request -> Then comment lines 47 & 48, and uncomment the following 2 lines.
  //EICRA |= (0 << ISC30);
  //EICRA |= (0 << ISC31);

  // If you want any logic change (edge) - to generate interrupt request -> Then comment lines 47 & 48, and uncomment the following line.
  //EICRA |= (1 << ISC30);    
  //EICRA |= (0 << ISC31);    // Not needed, as ISC31 is 0 by default.

  // If you want a falling edge - to generate interrupt request -> Then comment lines 47 & 48, and uncomment the following line.
  //EICRA |= (1 << ISC31);    
  //EICRA |= (0 << ISC30);    // Not needed, as the default value is 0.
  
  // -----------------------------------------------------------------------------
  // -----------------------------------------------------------------------------
  
  // Enable global interrupts
  sei(); 

  // Setting EIMSK, EICRX (as well as runnig sei()) - is the equivalent to using "attachInterrupt" as examples below.
  //attachInterrupt(digitalPinToInterrupt(intPin), trigger, LOW);
  
}

void loop()
{
  // 
}

// Interrupt Service Routine - For External interrupt 3 (pin 1)
ISR (INT3_vect)
{
  if (state == LOW) {
    state = HIGH;
  } 
  else {
    state = LOW; 
  }
  
  int pin_7 = 7; 
  PORTB = (state << pin_7); // LED Pin is PB7!
  //digitalWrite(ledPin, state); // Equivalent to above line, if using Arduino Library.

  Serial.println("Int fired!");
  Serial.println(state);
}
