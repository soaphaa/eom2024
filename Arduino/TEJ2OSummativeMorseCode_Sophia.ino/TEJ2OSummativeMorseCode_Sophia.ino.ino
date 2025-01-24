#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
int buttonPin = 13;
int buzzerPin = 12;
int ledPin = 11;
const int SW_pin = 10;
bool SwOn = false; //button press detection
int currentMode = 0; //set to default

int counter;
String morse = "";
unsigned long pressStartTime = 0;  // Variable to track when the button was first pressed
unsigned long pressDuration = 0;
int xPin = A2;
int yPin = A3;  
int xVal, yVal;
int pos;
int previousPos = -1;

char inChar = ' ';
String inputStr = "";
String engTrans = " ";
bool strComplete = false;
bool inputComplete = false;
const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // alphabet
const String morseDict[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."}; // Morse dictionary

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD to ensure it functions
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(SW_pin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  
  lcd.print("test20");
  Serial.print("test");

  // Removed the incorrect loop that tries to overwrite morseDict[] array
}

void loop() {
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
  // Serial.print("X : ");
  // Serial.print(xVal);
  // Serial.print(" \t Y : ");
  // Serial.println(yVal);

  writeMorse();

  pos = 0;
  bool SWState = digitalRead(SW_pin);

  lcd.setCursor(0, 1);

  if(digitalRead(SWState) == LOW){
    SwOn = true;
  }
  else{
    SwOn = false;
  }

  if (SwOn == true) {
    delay(50);  // Added a small delay for debouncing the button
    int newMode = checkJoystickPos();
    if (newMode != currentMode && newMode != 0) {
      currentMode = newMode;
      playGame(currentMode);
    }
  }
}

int checkJoystickPos() {
  if (yVal == 0) {  // Joystick moved up
    pos = 1;
  }
  else if (xVal == 0) {  // Joystick moved left
    pos = 2;
  }
  else if (yVal == 1023) {  // Joystick moved down
    pos = 3;
  }
  else if (xVal == 1023) {  // Joystick moved right
    pos = 4;
  }
  else {  // Joystick in neutral position, no mode selected
    pos = 0;
  }
  return pos;
  Serial.print(pos);
  delay(100);
}

void playGame(int n) {
  switch (pos) {
    case 1:
      readMorse();
      lcd.clear();
      lcd.print("Mode: Read morse");
      break;

    case 2:
      writeMorse();
      lcd.clear();
      lcd.print("Mode: Write morse");
      break;

    case 3:
      minigame();
      lcd.clear();
      lcd.print("Mode: minigame");
      break;

    // case 4:
    //   messages();
    //   lcd.clear();
    //   lcd.print("Mode: messages..");
    //   break;

    default:
      break;
  }
}

void readMorse() {
    lcd.clear();
    
    if (Serial.available()) {
        inChar = Serial.read(); // Read one character
        inputStr += inChar;     // Append character to input string
        Serial.print("Current Input: ");
        Serial.println(inputStr);
        
        if (inChar == '\n') {   // End of input
            strComplete = true;
        }
    }
    lcd.setCursor(0, 0);
    lcd.print(inputStr);

    // Ensure input is complete
    if (strComplete) {
        String morseTrans = "";
        lcd.clear();
        lcd.setCursor(0, 1);

        // Convert inputStr to char array
        int len = inputStr.length();
        char arrayChar[len + 1];
        inputStr.toCharArray(arrayChar, len + 1);

        // Convert input to Morse code
        for (int i = 0; i < len; i++) {
            char currentChar = toupper(arrayChar[i]); // Normalize case
            for (int j = 0; j < sizeof(alphabet) - 1; j++) {
                if (currentChar == alphabet[j]) {
                    morseTrans += morseDict[j] + " "; // Add Morse code
                    break;
                }
            }
        }

        // Debugging Morse Translation
        Serial.println("Morse Translation:");
        Serial.println(morseTrans);
        
        // Display the Morse code
        lcd.print(morseTrans);

        // Reset input
        inputStr = "";
        strComplete = false;
    }
}


void writeMorse() {
  lcd.clear();
  lcd.setCursor(0, 0);

  if (digitalRead(buttonPin) == LOW) {
    if (pressStartTime == 0) {
      pressStartTime = millis();  // Record the time when the button is first pressed
      digitalWrite(ledPin, HIGH);
    }
    delay(10);
  }
  else {  // Button is released
    if (pressStartTime != 0) {  // Check if the button was previously pressed
      pressDuration = millis() - pressStartTime;  // Calculate the duration of the press
      digitalWrite(ledPin, LOW);

      // Determine what to print based on press duration
      if (pressDuration < 500) {  // Less than 1 second
        morse += ".";
      }
      else if (pressDuration >= 500) {  // Greater than or equal to 2.5 seconds
        morse += "_";
      }

      String currentMorse = morse;

      if (millis() - pressStartTime > 10000 && morse!="") {  // 10 second timeout
        bool validMorse = false;

        for (int i = 0; i < sizeof(alphabet) - 1; i++) {
            if (morseDict[i] == currentMorse) {
                engTrans+= alphabet[i];
                validMorse = true;
                break;
            }
        } 

      

    if(!validMorse){
      engTrans+="?";
    }

      // Reset the pressStartTime
      pressStartTime = 0;
    }
  }

  if(engTrans != " " && morse != " "){
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(engTrans);  // Print the English translation
    Serial.print(engTrans);
  
    }
  }

  lcd.setCursor(0, 0);
  lcd.print(morse);

}

void minigame() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Playing MiniGame...");
  delay(1000);  // Placeholder for mini game code
}
