//// Example - When joystick position changes or button is clicked, LED is triggered ON. ////
//// There is a loop executed periodically (Synchronously) reading position and button state. -> Polling ////
//// Polling Concept = Periodically reading device state/data -> [Synchronous] ////

int verPin = A0;
int horPin = A1;
int selPin = 1;
int led = 11;
const int threshold = 400;

void setup() {
    pinMode(selPin, INPUT);
  digitalWrite(selPin, HIGH);

  Serial.begin(9600);

  Serial.println("!");

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);  
}

void loop() {
  int verPos = analogRead(verPin);
  int horPos = analogRead(horPin);
  boolean selBtn = digitalRead(selPin);

  Serial.println(verPos);
  Serial.println(horPos);
  Serial.println(selBtn);

  if (selBtn == 0) {
    digitalWrite(led, HIGH);
    delay(25);
    digitalWrite(led, LOW);
    delay(200);
  }
  else if (verPos > 400 || horPos > threshold) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW); 
  }

  delay(100);
}
