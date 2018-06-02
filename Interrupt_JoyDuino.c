// {Arduino connections} <->  {Joystick & LED} :
// GND                    -   GND (of joystick button)
// 5V                     -   VCC (of joystick button)
// Pin 1 (PD3/TX)         -   Key (of joystick button)
// GND                    -   Cathode (of LED - shorter LED Pin)
// Pin 11 (PB7)           -   Anode (of LED - longer LED Pin)

// x|=y ~ x = x | y ->  bitwise or and assignment.

#include <avr/io.h>
#include <avr/interrupt.h>
 
int ledPin = 11; // Arduino Pin 11
//int intPin = 7; // INT6
//int intPin = 0; // INT2
int intPin = 1; // INT3
volatile int state = LOW;

void setup()
{
  Serial.begin(9600);
  Serial.println("!");
  
  DDRB = 0b10000000; // PB7 (led pin/pin 11)  = Output
//pinMode(ledPin, OUTPUT); // Same as line above.
  
  PORTD = 0b00001000; // Set Interrupt (PD3/intPin/pin 1) as High.
//digitalWrite(intPin, HIGH); // Equivalent to line above.

  // Disble global interrupts
  //cli();

  // -----------------------------------------------------------------------------
  // External Interrupt Mask Register (EIMSK) - For Enabling External Interrupts
  // -----------------------------------------------------------------------------
  EIMSK |= (1 << INT3);   // Enable INT3
  //EIMSK |= _BV(INT3);   
  //EIMSK |= 0x03;  
  //EIMSK |= 0b00001000; 
  // -----------------------------------------------------------------------------


  // -----------------------------------------------------------------------------
  // Interrupt Sense Control
  // -----------------------------------------------------------------------------
  
  // Low logic level (0) - generates interrupt request.
  //EICRA |= (0 << ISC30);
  //EICRA |= (0 << ISC31);

  // Any logic change (edge) - generates interrupt request.
  //EICRA |= (1 << ISC30);    // set INT0 to trigger on ANY logic change

  // Falling edge - generates interrupt request.
  //EICRA |= (1 << ISC31);    // set INT0 to trigger on falling edge

  // Raising edge - generates interrupt request.
  EICRA |= (1 << ISC30); 
  EICRA |= (1 << ISC31);
  
  // -----------------------------------------------------------------------------
  // -----------------------------------------------------------------------------
  
  // Enable global interrupts
  sei(); 

  // Setting EIMSK, EICRX (as well as runnig sei()) - is the equivalent to using "attachInterrupt" as examples below.
  //attachInterrupt(intPin, trigger, CHANGE); // Attaching the ISR to INT3
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
//digitalWrite(ledPin, state); // Equivalent to above.

  Serial.println("Int fired!");
  Serial.println(state);
}
