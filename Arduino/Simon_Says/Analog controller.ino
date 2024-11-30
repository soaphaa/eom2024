/*
Project name: Analog controller
Author: Sophia Luo
Date: Dec 19, 2024

Description:
*/
int adcValue; // Define a variable to save the ADC value
const int ledCount = 6; 
int ledPins[] = {3,5,6,9,10,11};
int brightness = 0;
char inChar;
int convertValue; //potentiometer

void setup() {
// Initialize the LED pins as an output
for (int thisLed = 0; thisLed < ledCount; thisLed++) {
  pinMode(ledPins[thisLed], OUTPUT);
  Serial.begin(9600);
  Serial.println(ledPins[thisLed]);
  delay(200);
}
}
void loop() {
int thisLed = 0;
adcValue = analogRead(A0); // Convert the analog of A0 port to digital
convertValue = analogRead(A1); // Convert analogy of A1 port to digital
analogWrite(ledPins, map(convertValue, 0, 1023, 0, 255));
int ledLevel = map(adcValue, 0, 1023, 0, ledCount);
for(thisLed = 0; thisLed<ledCount; thisLed++){
  if(thisLed<ledLevel){
    digitalWrite(ledPins[thisLed], HIGH);
  }
  else { // Turn off LEDs in sequence
  digitalWrite(ledPins[thisLed], LOW);
  }
  delay(250);
}
if(ledPins[thisLed], HIGH){
  delay(250);
  if (Serial.available()) {
  Serial.println("Input a brightness setting (1-100):");
    inChar = Serial.read();
    if (isdigit(inChar)) {
      int inputValue = inChar - '0'; // Convert character to integer
      brightness = map(inputValue, 0, 100, 0, 255);
      for (int thisLed = 0; thisLed < ledCount; thisLed++) {
        analogWrite(ledPins[thisLed], brightness);
      }
    }
  }
}

}
