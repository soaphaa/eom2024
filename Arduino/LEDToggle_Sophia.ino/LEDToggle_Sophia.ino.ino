const int ledPins[] = {3, 4, 5, 6, 7}; // Define pins connected to LEDs
const int buttonPin = 8; // Define pin connected to the push button
int x = 0; // declaring the variable for the change in ledPin num


void setup() {
  for(int i=0; i<5; i++){
     pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  while(digitalRead(buttonPin)==HIGH){ //Will only execute the code below once it exits this loop, hence whenever the pushbutton is pressed.
  }
    digitalWrite(ledPins[x], HIGH);
  	digitalWrite(ledPins[x-1], LOW);
  if(digitalRead(ledPins[0])== HIGH){ // for the last led to turn off
  	digitalWrite(ledPins[4], LOW);
  }
  	x++;
  if(x>4){
    x=0;//once it reaches the end reset back to the start
  }
  delay(200);
}
