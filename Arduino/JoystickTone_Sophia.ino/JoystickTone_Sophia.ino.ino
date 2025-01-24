const int ledPins[] = {13,12,11,10,9};
int numLeds = 5;
const int SW_pin = 8;
int xAxisPin = 0; // define X pin of Joystick
int yAxisPin = 1; // define Y pin of Joystick
int zAxisPin; // define Z pin of Joystick
int xVal = 0;
int yVal = 0;
int zVal = 0; // define 3 variables to store the values of 3 direction
int switch_status = digitalRead(SW_pin);
int buzzerPin = 6;
float sinVal; // Define a variable to save sine value
int toneVal;

void setup() {
  for(int i=0; i<5; i++){
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(zAxisPin, INPUT_PULLUP); // initialize the port to pull-up input
  Serial.begin(9600);
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  xVal = analogRead(xAxisPin);
  yVal = analogRead(yAxisPin);
  zVal = digitalRead(zAxisPin);
  Serial.print("X : ");
  Serial.print(xVal);
  Serial.print(" \t Y : ");
  Serial.print(yVal);
  Serial.print(" \t Z : ");
  Serial.println(zVal);
  Serial.print("Switch:  ");
  Serial.print(digitalRead(SW_pin));
  delay(200);

  int range = 1023/5;
  int ledIndex = xVal/range;

  if(ledIndex<0){
    ledIndex=0; //ensure the index isn't below 0
  }
  if(ledIndex>=numLeds){
    ledIndex = numLeds -1 ; //ensure the index doesn't go higher than 4
  }

  for(int i =0; i<5; i++){
    digitalWrite(ledPins[i], LOW); //turn off all other LEDS
  }
  digitalWrite(ledPins[ledIndex], HIGH); //turn on only the LED at the index num


  if(digitalRead(SW_pin)==0){
    sinVal = sin(yVal * (PI / 180));        
    if(yVal>511){
      toneVal = 1000 + sinVal * 100; //higher pitch
    }
    else{
      toneVal = 2000 + sinVal * 100; //lower pitch
    }

      tone(buzzerPin, toneVal);
      Serial.println("Pressed");
  }
  else{
    noTone(buzzerPin);
  }

}
