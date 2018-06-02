//// Example - When joystick button is clicked, LED state changes. ////
//// When the pin attached to the interrupt pin is triggered, the ISR is executed.  -> Interrupt ////
//// Interrupt Concept = Execute ISR (Interrupt Service Routine), whenever there is data/state change, the ISR will be called asynchronously and the main program will be stopped executing.  -> [Asynchronous] ////

/// *** Seems like INT2 & INT3 work even when serial is used, even though they are RX/TX UARTserial pins.
/// *** Seems like INT6 (Digital Pin 7) works if "digitalPinToInterrupt" is passed to attachInterrupt.

int ledPin = 11;
//int intPin = 7; // INT6
//int intPin = 0; // INT2
int intPin = 1; // INT3
volatile int state = LOW;

void setup()
{
  Serial.begin(9600);
  Serial.println("!");
  
  pinMode(ledPin, OUTPUT); // Set LED pin as Output.
  
  digitalWrite(intPin, HIGH);  // Set Interrupt digital pin -> High.
  //pinMode(intPin, INPUT_PULLUP);  // Set Interrupt digital pin -> High.
  //attachInterrupt(intPin, trigger, CHANGE); // Attaching the ISR to INT3
  attachInterrupt(digitalPinToInterrupt(intPin), trigger, LOW);
  
  
  //EICRA |= (1 << ISC00);    // set INT0 to trigger on ANY logic change
  //EIMSK |= (1 << INT3);     // Turns on INT3
  //sei(); 
}

void loop()
{
  // Does Nothing
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
