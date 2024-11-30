int ledPin1 = 5, // the number of the LED1 pin
ledPin2 = 6, // the number of the LED2 pin
ledPin3 = 9, // the number of the LED3 pin
ledPin4 = 10; // the number of the LED4 pin
void setup() {

pinMode(ledPin1, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(ledPin3, OUTPUT);
pinMode(ledPin4, OUTPUT);
}
void loop()
{
analogWrite(ledPin1, map(2, 0, 100, 0, 255));
analogWrite(ledPin2, map(10, 0, 100, 0, 255));
analogWrite(ledPin3, map(25, 0, 100, 0, 255));
analogWrite(ledPin4, map(100, 0, 100, 0, 255));

breath(ledPin1, 6);
breath(ledPin2, 6);
breath(ledPin3, 6);
breath(ledPin4, 6);
delay(1000);
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
