const int ledPins[]={8,7,6,5};
const int buttonPins[] = {12,11,10,9};
const int startButton = 13;
int redPin = 4;
int greenPin = 3;
int bluePin = 2;

int sequence[4];
int userInput[4];

boolean startPressed = false;

void setup() {

  //led setups
  for(int i = 0; i < 4; i++){
    pinMode(ledPins[i], OUTPUT);
    Serial.begin(9600);
  }


  //button setups
  for(int i = 0; i<4; i++){
    pinMode(buttonPins[i], INPUT_PULLUP);
  }


  pinMode(startButton, INPUT);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  randomSeed(analogRead(0));


}


void loop() {
  // digitalWrite(redPin, LOW);
  // digitalWrite(greenPin, LOW);
  // digitalWrite(bluePin, LOW); // ensuring the RGB is off
  // detect the button is clicked otherwise loop until the button is clicked
  Serial.println("\nplease click start button");
  while (digitalRead(startButton) == HIGH) {
  }
  delay(1000);
  generateRandomSequence();
  playSequence();
  //buttonPressed();
  //getUserInput();
  if (userInputs()) {
    Serial.println("CONGRATULATIONS! YOU WIN!");
    digitalWrite(greenPin, LOW);
    delay(100);
    digitalWrite(greenPin, HIGH);
    delay(500);
    digitalWrite(greenPin, LOW);
    delay(500);
    digitalWrite(greenPin, HIGH);
    delay(500);
    digitalWrite(greenPin, LOW);
  }
  else{
    Serial.println("GAME OVER");
    delay(2000);
    digitalWrite(redPin, HIGH);
    delay(500);
    digitalWrite(redPin, LOW);
    delay(500);
    digitalWrite(redPin, HIGH);
    delay(500);
    digitalWrite(redPin, LOW);
  }
}
 


void generateRandomSequence() {
  for(int i = 0; i<4; i++){
      sequence[i]=random(0,3);
  }
  // for (int i = 0; i < 4; i++) {
  //   sequence[i] = random(0,3);
  // }
}

void playSequence() {
  for(int i=0; i<4; i++){
    int led = sequence[i];
    digitalWrite(ledPins[led], HIGH);
    delay(500);
    digitalWrite(ledPins[led], LOW);
    delay(250);
    Serial.println(led);
  }
}  

int buttonState(){
  int button1State = digitalRead(buttonPins[0]);
  int button2State = digitalRead(buttonPins[1]);
  int button3State = digitalRead(buttonPins[2]);
  int button4State = digitalRead(buttonPins[3]);

  if(button1State == LOW){
    return 0;
  }
  else if(button2State == LOW){
    return 1;
  }
  else if(button3State == LOW){
    return 2;
  }
  else if(button4State == LOW){
    return 3;
  }
  else{
    return 200;
  }
}

bool userInputs() {
  bool verdict = true;
  for (int i=0; i<4; i++){
    int bn = 100;
    while (bn > 10) {
      bn = buttonState();
      delay(10);
    }
    Serial.println(bn);
    if (bn != sequence[i]) {
      verdict = false;
      Serial.println("not the same");
    }
    digitalWrite(ledPins[bn], HIGH);
    delay(200);
    digitalWrite(ledPins[bn], LOW);

    // reset for the next button click
    bn = 100;
    delay(1000);
  }
  return verdict;
}

void buttonPressed(){
  for(int i = 0; i<4; i++){
    if(digitalRead(buttonPins[i]) == LOW){
      digitalWrite(ledPins[i], HIGH);
      Serial.println("buttonPressed");
    }
  }
}