/*
  Program name: Serial monitor
  Author: Sophia Luo
  Date: November 11th, 2024

  Description: A short program to test the serial monitor
*/
int buttonPin1 = 13;
int buttonPin2 = 14;
int inInt; 
int counter; // define a variable to store characters received from serial port
void setup() {
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  Serial.begin(9600); 
  Serial.println("\nClick a button!"); // initialize serial port, set baud rate to 9600
}
void loop() {
  while(counter>=0){
    while(buttonPin1, LOW){
    counter++;
    Serial.print(counter);
    delay(1000);
    }
    while(buttonPin2, LOW){
    counter--;
    Serial.print(counter);
    delay(1000);
    }
  }
  /*if (Serial.available()) { // confirms if the data has been recieved
    inInt = Serial.parseInt(); // read an integer
    if(inInt<=100){
    Serial.println("Look at your LED!");
    Serial.println(inInt);
    // convert the received integer into PWM duty cycle of ledPin port
    analogWrite(ledPin, constrain(inInt, 0, 255));
    delay(2000);
    }
  else{
    Serial.println("Ur LED is gonna explode");
  }  
  }*/
}  