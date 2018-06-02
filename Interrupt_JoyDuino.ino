//// Example - When joystick button is clicked, LED state changes. ////
//// When the pin attached to the interrupt pin is triggered, the ISR is executed.  -> Interrupt ////
//// Interrupt Concept = Execute ISR (Interrupt Service Routine), whenever there is data/state change, the ISR will be called asynchronously and the main program will be stopped executing.  -> [Asynchronous] ////

/// *** INT2 & INT3 work even when serial is used, even though they are RX/TX UARTserial pins.
/// *** INT6 (Digital Pin 7) works if "digitalPinToInterrupt" is passed to attachInterrupt.

int ledPin = 11;
//int intPin = 7; // If you want to use INT6 instead of INT3 - uncomment this line and comment line 11.
//int intPin = 0; // If you want to use INT2 instead of INT3 - uncomment this line and comment line 11.
int intPin = 1; // INT3
volatile int state = LOW;

void setup()
{
  Serial.begin(9600);
  Serial.println("!");
  
  pinMode(ledPin, OUTPUT); // Set LED pin as Output.
  
  digitalWrite(intPin, HIGH);  // Set Interrupt digital pin -> High.
  attachInterrupt(digitalPinToInterrupt(intPin), trigger, LOW); // Attaching the ISR to selected interrupted pin.
}

void loop()
{
  // Not used.
}

// Interrupt Service Routine
void trigger()
{
  if (state == LOW) {
    state = HIGH;
  } 
  else {
    state = LOW; 
  }
  digitalWrite(ledPin, state);

  Serial.println("Int fired!");
  Serial.println(state);
}
