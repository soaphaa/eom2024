// Pin configuration
const int ledPins[] = {2, 3, 4, 5};   // LED pins
const int buttonPins[] = {9,10,11,12}; // Button pins

int sequence[10];  // Stores the sequence
int userInput[10]; // Stores user input
int level = 1;     // Current game level

void setup() {
  // Set up LEDs as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Set up buttons as inputs
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  randomSeed(analogRead(0)); // Seed for random sequence generation
  generateSequence();        // Generate random sequence
}

void loop() {
  playSequence();         // Display current sequence
  if (getUserInput()) {   // Check user input
    if (level < 10) {
      level++;            // Increase level if correct
    } else {
      // Flash LEDs to indicate win
      flashLEDs();
      while (true);       // Stop the game
    }
  } else {
    // Do nothing if incorrect
  }
}

// Generate a random sequence
void generateSequence() {
  for (int i = 0; i < 10; i++) {
    sequence[i] = random(0, 3);
  }
}

// Display the sequence to the user
void playSequence() {
  for (int i = 0; i < level; i++) {
    int led = sequence[i];
    digitalWrite(ledPins[led], HIGH);
    delay(500);
    digitalWrite(ledPins[led], LOW);
    delay(250);
  }
}

// Get user input and check correctness
bool getUserInput() {
  for (int i = 0; i < level; i++) {
    while (true) {
      for (int j = 0; j < 4; j++) {
        if (digitalRead(buttonPins[j]) == LOW) {
          userInput[i] = j;
          delay(300); // Debounce delay
          if (userInput[i] != sequence[i]) {
            return false; // Incorrect input
          }
          break;
        }
      }
      if (userInput[i] == sequence[i]) {
        break;
      }
    }
  }
  flashLEDs(); // Flash LEDs for correct input
  return true;
}

// Flash all LEDs twice
void flashLEDs() {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      digitalWrite(ledPins[j], HIGH);
    }
    delay(500);
    for (int j = 0; j < 4; j++) {
      digitalWrite(ledPins[j], LOW);
    }
    delay(500);
  }
}

