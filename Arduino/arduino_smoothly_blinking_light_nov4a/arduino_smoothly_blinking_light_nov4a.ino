int ledPin = 5; 

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  breath(ledPin,6);
  delay(250);
  breath(ledPin, 3);
  delay(250);
  breath(ledPin,1);
  delay(250);
}

void breath(int ledPin, int delayMs){
  for(int i=0; i<=175; i++){
    analogWrite(ledPin, i);
    delay(delayMs);
  }
  for(int i=175; i>=0; i--){
    analogWrite(ledPin, i);
    delay(delayMs);
  }
}
