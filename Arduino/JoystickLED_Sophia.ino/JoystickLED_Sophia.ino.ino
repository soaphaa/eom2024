/*
Project name: Joystick LED
Author: Sophia
Date: December 6, 2024

Description: A joystick controller that can adjust the colour being displayed on an RGB led.
              * The led will be red when the joystick is up, green when the joystick is right, and blue when the joystick is left or down.
              * The joystick pushbutton triggers a piezo buzzer to create a sound that will stop once the pushbutton is released. 
*/
int redPin = 11;
int greenPin = 10;
int bluePin = 9;

const int SW_pin = 8;
int xAxisPin = 0; // define X pin of Joystick
int yAxisPin = 1; // define Y pin of Joystick
int zAxisPin; // define Z pin of Joystick
int xVal = 0;
int yVal = 0;
int zVal = 0; // define 3 variables to store the values of 3 direction
int switch_status = digitalRead(SW_pin);
int buzzerPin = 6;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(zAxisPin, INPUT_PULLUP); // initialize the port to pull-up input
  Serial.begin(9600);
  pinMode(SW_pin, INPUT_PULLUP);
  digitalWrite(SW_pin, HIGH);
  pinMode(buzzerPin, OUTPUT);
}

void loop()
{
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
Serial.print(digitalRead(switch_status) + " ");
delay(200);
  if(xVal<=524){
    analogWrite(redPin, map(xVal, 0, 522, 0, 255));
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  }
  else if(xVal>511&&xVal<=1023 && yVal>500){
  analogWrite(greenPin, map(xVal, 512, 1023, 0, 255)); //green pin
  analogWrite(redPin, 0);
  analogWrite(bluePin, 0);
  }
    analogWrite(bluePin, map(yVal, 511, 1023, 0, 255)); //blue pin using y Value
  

  //  else if(xVal==522&&yVal==(504||503)){ 
  //   analogWrite(redPin,0);
  //   analogWrite(bluePin, 0);
  //   analogWrite(greenPin, 0);
  //  }  