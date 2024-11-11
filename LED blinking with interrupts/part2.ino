const int buttonPin = 2;  // button connected to digital pin 2
const int ledPins[] = {6,7,8,9,10,11,12}; // LEDs connected to digital pins 6 to 12

int buttonState = 0;  // variable to store button state
int pattern = 0;      // variable to store LED pattern
int frequency = 1000;  // variable to store LED blinking frequency (in milliseconds)
unsigned long buttonPressTime = 0;  // variable to store button press start time
bool change = false;  // variable to store whether to change pattern or frequency

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  buttonState = digitalRead(buttonPin);  // read button state

  if (buttonState == LOW) {  // button is pressed
    buttonPressTime = millis();  // store button press start time
    while (digitalRead(buttonPin) == LOW) {}  // wait for button release

    if (millis() - buttonPressTime > 1000) {  // long press
      pattern = (pattern + 1) % 2;  // change pattern
    } else {  // short press
      frequency = frequency == 1000 ? 200 : 1000;  // change frequency
    }
    change = true;  // set change flag to true
  }

  switch (pattern) {
    case 0:  // pattern 1
      if (change) {  // if change flag is set
        change = false;  // reset change flag
      } else {
        for (int i = 0; i < 7; i++) {
          digitalWrite(ledPins[i], HIGH);
          delay(frequency);
          digitalWrite(ledPins[i], LOW);
          delay(frequency);
        }
      }
      break;

    case 1:  // pattern 2
      if (change) {  // if change flag is set
        change = false;  // reset change flag
      } else {
        for (int i = 6; i >= 0; i--) {
          digitalWrite(ledPins[i], HIGH);
          delay(frequency);
          digitalWrite(ledPins[i], LOW);
          delay(frequency);
        }
      }
      break;
  }
}
