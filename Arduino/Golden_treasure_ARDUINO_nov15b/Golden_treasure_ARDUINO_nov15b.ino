/*
  Program name: Hyperdrive
  Author: Sophia Luo
  Date: November 19th, 2024


  Description: This program has 3 buttons that each have their own LED that lights up once the button is pressed. However, there is a combination that unlocks a golden treasure. 
  This combination requires the 1st and 3rd button to be pushed at the same time. When the golden treasure is unlocked, all 3 LEDs will flash simultaneously. 
  To make the flashing stop, the RESET button must be pressed, located between the red and blue LEDs. Once this is triggered, the program will reset and the user
  can restart the game. 
*/

int buttonPin1 = 10;
int ledPin1 = 9;
int buttonPin2 = 6;
int ledPin2 = 7;
int buttonPin3 = 4;
int ledPin3 = 5;
int buttonReset = 12;

boolean blueOn = false;
boolean redOn = false;
boolean yellowOn = false;
boolean flashing = false;

void setup() {
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonReset, INPUT_PULLUP);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  Serial.begin(9600);
  Serial.println("\nUnlock the golden treasure by pressing the buttons");
}

void loop(){

  if(digitalRead(buttonPin1)==LOW && digitalRead(buttonPin3)==LOW && digitalRead(buttonPin2)==HIGH){
    Serial.println("Golden treasure unlocked");
      /*redOn = false;
      blueOn = false;
      yellowOn = false;*/
      delay(1000);
      Serial.println("Flashing lights commencing");
      flashing = true;
  }
  else{
    flashing = false;
  } 

  if(digitalRead(buttonPin1)==HIGH){
    digitalWrite(ledPin1, LOW);
    blueOn = false;
    }
    else {
      digitalWrite(ledPin1, HIGH);
      if(digitalRead(buttonPin1) == LOW){
        blueOn = true;
      }  
      //Thrust
  }


  if(digitalRead(buttonPin2)==HIGH){
    digitalWrite(ledPin2, LOW);
    redOn = false;
    }
    else{
      digitalWrite(ledPin2, HIGH);
      if(digitalRead(buttonPin2) == LOW){
        redOn = true;
      }
      //nitro
    }

  if(digitalRead(buttonPin3)==HIGH){
    digitalWrite(ledPin3, LOW);
    yellowOn = false;
    }
    else{
      digitalWrite(ledPin3, HIGH);
      if(digitalRead(buttonPin3) == LOW){
        yellowOn = true;
      } 
    
    }
  
  Serial.println(flashing);
  while(flashing == true){
      digitalWrite(ledPin1,LOW);
      digitalWrite(ledPin2,LOW);
      digitalWrite(ledPin3,LOW);
      delay(250);
      digitalWrite(ledPin1,HIGH);
      digitalWrite(ledPin2,HIGH);
      digitalWrite(ledPin3,HIGH);
      delay(250);
      if (digitalRead(buttonReset)==LOW){
        Serial.println("reset button on");
        flashing = false;
      }  
      else{
        flashing = true;

      }
  }
  delay(250);
}

