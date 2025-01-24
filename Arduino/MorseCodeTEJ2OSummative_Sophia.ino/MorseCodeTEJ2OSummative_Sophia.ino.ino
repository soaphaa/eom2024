#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
int buttonPin = 13;
int ledPin = 11;
int buzzerPin = 12;

int togglePin = 8;

int currentMode = 0;//set to default

int RED = A1;
int GREEN = A2;
int BLUE = A0;

int pos = -1;

//toggle states
int toggleState;
int lastToggleState = HIGH;

int debounceDelay = 30;

int ditLength = 240; //the length of a dit (dot) in morse code

//other values computed from dit length
int ditSpace = ditLength; //distance between dits within a letter
int dahLength = (ditLength * 3); //3 times the dit for a dash
int letterSpace = (ditLength*3); //distance between letters
int wordSpace = (ditLength*6); //distance between words
int gap; //the gap between letters or words

//variables to track the time the button was pressed and its duration
int pressStartTime = 0; 
int pressDuration = 0;  

int lastButtonReleaseTime; //to calculate the gap between buttonPresses


unsigned long lastDebounceTime = 0; // Time of the last debounce event

String inputStr = "";
String morseSeq = "";
String keyStr = ""; //stores the translation from morse to english
char ch;

bool togglePressed, buttonPressed, newLetter, newWord, letterFound, morseFound, morseDetected, wordsDetected;


const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // alphabet
char* morseDict[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", 
                    ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
                     "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."}; 

char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  newLetter = false;
  newWord = false;
  letterFound = false;
  morseFound = false;
  togglePressed = false; //toggle button
  buttonPressed = false;
  morseDetected = false;
  wordsDetected = false;

   // Print a message to the LCD to ensure it functions
  pinMode(buttonPin, INPUT);
  pinMode(togglePin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);

  Serial.begin(9600);

  lcd.print("Press the button");
  Serial.println("____________________________________");
  Serial.println("Morse code Arduino Project");
  Serial.println("Options: \nMorse Code decoder \nMorse Code encoder \nMinigame");
  
  delay(2000);

  Serial.println("____________________________________");
  Serial.println("Click the button to toggle your mode!");

}

void loop() {
  lcd.setCursor(0, 1);
  int reading = digitalRead(togglePin);

  // Checking the toggle button state
  if (reading != lastToggleState) {
    lastDebounceTime = millis(); // Reset the debounce timer
  }

  // If the debounce time has passed, update the toggle button state
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != toggleState) {
      lastDebounceTime = millis(); // Update the debounce timer
      toggleState = reading;

      if (toggleState == LOW && !togglePressed) {
        togglePressed = true; // Mark the toggle button as pressed
        
        // Update the position state (`pos`)
        if (pos == -1) {
          pos = 0; // Start at 0 when first pressed
        } else {
          pos++;
          if (pos > 2) {
            pos = 0;  // Reset to 0 if it exceeds 2
          }
        }

        // Clear the LCD when switching modes
        lcd.clear();

        Serial.print("Mode switched to: ");
        Serial.println(pos);
      }
    }
  }

  // Reset togglePressed state when toggle button is released
  if (toggleState == HIGH) {
    togglePressed = false;
  }

  // Perform mode change based on pos
  switch (pos) {
    case 0:  // Mode 0: Read Morse
      analogWrite(RED, 255);
      analogWrite(GREEN, 0);
      analogWrite(BLUE, 0);
      readMorse(); // Call readMorse method
      break;

    case 1:  // Mode 1: Write Morse
      analogWrite(RED, 0);
      analogWrite(GREEN, 255);
      analogWrite(BLUE, 0);
      writeMorse(); // Call writeMorse method
      break;

    case 2:  // Mode 2: Minigame
      analogWrite(RED, 0);
      analogWrite(GREEN, 0);
      analogWrite(BLUE, 255);
      minigame(); // Call minigame method
      break;

    default:  // Handle invalid `pos` values
      // Ensure `pos` is reset to a valid state
      pos = -1;
      break;
  }

  lastToggleState = reading; // Save the reading for next loop
  delay(100);
}



  // if(buttonState && !buttonPressed){
  //   checkJoystickPos();
  //   buttonPressed = true;
  //   Serial.println("Position: " + pos);
  // }
  // if(lastSWState == LOW){
  //   int newMode = checkJoystickPos();
  //   if(newMode != currentMode && newMode!=0){
  //     currentMode = newMode;
  //     playGame(currentMode);
  //   }



// int checkJoystickPos(){ //returns the joystick position

//   if (yVal == 0) {  // Joystick moved up
//         pos = 1;
//       }
//      else if (xVal == 0) {  // Joystick moved left
//         pos = 2;
//       }
//     else if (yVal == 1023) {  // Joystick moved down
//         pos = 3;
//       }
//     else if (xVal == 1023) {  // Joystick moved right
//         pos = 4;
//       }
//      else {  // Joystick in neutral position, no mode selected
//       pos = 0;
//     }
//     return pos;
// }


// void playGame(int n){
//     switch(pos){
//       case 0:
//       digitalWrite(rPin, HIGH);
//       digitalWrite(gPin, LOW);
//       digitalWrite(bPin, LOW);
     
//       readMorse();
//       lcd.clear();
//       lcd.print("Mode: Read morse");
     
//       break;


//       case 1:

//       digitalWrite(rPin, LOW);
//       digitalWrite(gPin, HIGH);
//       digitalWrite(bPin, LOW);

//       writeMorse();
//       lcd.clear();
//       lcd.print("Mode: Write morse");


//       break;


//       case 2:

//       digitalWrite(rPin, LOW);
//       digitalWrite(gPin, LOW);
//       digitalWrite(bPin, HIGH);
//       minigame();
//       lcd.clear();
//       lcd.print("Mode: minigame");


//       break;


//       case 4:
//       messages();
//       lcd.clear();
//       lcd.print("Mode: messages..");


//       break;


//       default:
//       break;


//     }
// }


void readMorse() {
  Serial.println("reading morse");
  //reset the other method values
  morseSeq = ""; 
  keyStr = "";
  // serialEvent();
  // inputStr = "sOs";
  // Serial.println(inputStr);
  // // Ensure input is complete
  // if (letterComplete) {
  //   String morseTrans = "";


  //   // Clear the display
  //   lcd.clear();
  //   lcd.setCursor(0, 0);
  //   lcd.print("Enter on the monitor:");


  //   // Convert inputStr to char array
  //   int len = inputStr.length();
  //   char arrayChar[len + 1];
  //   inputStr.toCharArray(arrayChar, len + 1);


  //   // Convert input to Morse code
  //   for (int i = 0; i < len; i++) {
  //     char currentChar = toupper(arrayChar[i]); // ignore lower or uppercase
  //     for (int j = 0; j < sizeof(alphabet) - 1; j++) {
  //       if (currentChar == alphabet[j]) {
  //         morseTrans += morseDict[j] + " "; // Add Morse code with space separator
  //         break;
  //       }
  //     }
  //   }


  //   // Display the Morse code
  //   Serial.println("Morse Translation:");
  //   Serial.println(morseTrans);


  //   // Reset input
  //   inputStr = "";
  //   strComplete = false;
  // }
  // delay(500); 
}


void serialEvent() {
  // while (Serial.available()) {
  //   char inChar = (char)Serial.read();
  //   if (inChar == '\n') {
  //     strComplete = true;
  //   } else {
  //     inputStr += inChar;
  //   }
  // }
}

void writeMorse() {
  int morseButtonReading = digitalRead(buttonPin); // Read the Morse input button state

  // Handle debounce logic for the Morse input button
  if (morseButtonReading != buttonPressed) {
    lastDebounceTime = millis(); // Reset debounce timer
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (morseButtonReading == LOW && !buttonPressed) {
      buttonPressed = true;
      pressStartTime = millis(); // Record the press start time
      digitalWrite(ledPin, HIGH);
      digitalWrite(buzzerPin, HIGH);
    }

    if (morseButtonReading == HIGH && buttonPressed) {
      buttonPressed = false; // Reset button press state
      pressDuration = millis() - pressStartTime; // Calculate press duration
      digitalWrite(ledPin, LOW);
      digitalWrite(buzzerPin, LOW);

      // Determine if DOT or DASH
      if (pressDuration < ditLength * 1.5) {
        morseSeq += ".";  
      } else {
        morseSeq += "-"; 
      }

      lcd.setCursor(0,1);
      lcd.print(morseSeq);

      // Update last button release time
      lastButtonReleaseTime = millis();

      // Set newLetter to true, indicating the start of a new sequence
      newLetter = true;
    }

    // Calculate the gap between button presses
    gap = millis() - lastButtonReleaseTime;

    // Check if the gap exceeds the letter space
    if (newLetter && gap >= letterSpace) {
      Serial.println("Processing Morse sequence...");
      letterFound = false;

      // Compare the Morse sequence to the dictionary
      for (int i = 0; i < 26; i++) {
        if (morseSeq == morseDict[i]) {
          keyStr += alpha[i]; // Add the letter to the translated string
          letterFound = true;
          break; // Stop searching once a match is found
        }
      }

      // Handle unknown Morse sequences
      if (!letterFound) {
        digitalWrite(buzzerPin, HIGH); // Indicate error with a beep
        delay(100);
        digitalWrite(buzzerPin, LOW);
      }

      // Reset the Morse sequence
      morseSeq = ""; // Clear the current Morse sequence
      newLetter = false;

      // Update the LCD with the current translation
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(keyStr); // Print the translated text
    }
  }

  // Debugging: Print the current Morse sequence
  Serial.print("Morse Sequence: ");
  Serial.println(morseSeq);
}





    // else {  // Button is released
    //   if (pressStartTime != 0) {  // Check if the button was previously pressed
    //     pressDuration = millis() - pressStartTime;  // Calculate the duration of the press
    //     digitalWrite(ledPin, LOW);


    //     // Determine what to print based on press duration
    //     if (pressDuration < 500) {  // Less than 1 second
    //       morse+=".";
    //     }
    //     else if (pressDuration >= 500) {  // Greater than or equal to 2.5 seconds
    //       morse+="_";
    //     }


    //     // Reset the pressStartTime
    //     pressStartTime = 0;
    //   }
    // }

    // char morseCode[] = morse; //how do you determine the size of this array? Idk Arraylist?
    // morseTranslation(morseCode);


void minigame() {
  lcd.clear();
  lcd.setCursor(0, 0);
  //reset the other method values
  morseSeq = ""; 
  keyStr = "";
  lcd.print("Playing MiniGame...");
  Serial.print("minigame mode");
}


void messages() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Messages...");
  // Add your message logic here
}


//void morseTranslation(char morseCode[]){




  //////figure out how this works?? ///////
  // char* morseCodeDict[]
  //       = { ".-",   "-...", "-.-.", "-..",  ".",    "..-.",
  //           "--.",  "....", "..",   ".---", "-.-",  ".-..",
  //           "--",   "-.",   "---",  ".--.", "--.-", ".-.",
  //           "...",  "-",    "..-",  "...-", ".--",  "-..-",
  //           "-.--", "--.." };
 
  // char* token = strtok(morseCode, " ");
  //   while (token != null) {
  //       for (int i = 0; i < 26; i++) {
  //           if (strcmp(token, morseCodeDict[i]) == 0) {
  //               lcd.print("%c", 'A' + i);
  //               break;
  //           }
  //       }







