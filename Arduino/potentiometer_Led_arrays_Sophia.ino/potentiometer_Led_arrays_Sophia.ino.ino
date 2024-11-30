const int ledPins[] = {3, 4, 5, 6, 7}; // Define pins connected to LEDs
int adcValue; // Define a variable to save ADC value
float delayMs;


void setup() {
  for(int i=0; i<5; i++){
     pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  adcValue = analogRead(A0); // Convert analog of pin A0 to digital
  Serial.print("convertValue:");
  Serial.println(adcValue);
  delayMs = adcValue; // the delay time depends on the adcValue
  delay(50);
  for(int i=0; i<5; i++){
    digitalWrite(ledPins[i], HIGH);
    digitalWrite(ledPins[i-1], LOW);
    if(digitalRead(ledPins[0])== HIGH){ // ensure the last ledPin turns off in sequence
  		digitalWrite(ledPins[4], LOW);
  	}    
  	delay(delayMs);
  }
  
}
