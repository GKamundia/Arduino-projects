const int buttonPin = 18;  // button connected to digital pin 18
const int ledPins[] = {6,7,8,9,10,11,12}; // LEDs connected to digital pins 6 to 12

int buttonState = 0;  // variable to store button state
int lastButtonState = HIGH; // variable to store last button state
int pattern = 0;      // variable to store LED pattern
int frequency = 2000;  // variable to store LED blinking frequency (in milliseconds)
unsigned long buttonPressTime = 0;  // variable to store button press start time
bool change = false;  // variable to store whether to change pattern or frequency

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 7; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), pushbutton, CHANGE);  
}

void loop() {
  pushbutton();
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

void pushbutton(){
  buttonState = digitalRead(buttonPin);  // read button state

  if (buttonState == LOW && lastButtonState == HIGH) {  // button is pressed
    buttonPressTime = millis();  // store button press start time
  }

  if (buttonState == HIGH && lastButtonState == LOW && (millis() - buttonPressTime > 2000)) {  // long press
    Serial.println(pattern = (pattern + 1) % 2);  // change pattern
    change = true;  // set change flag to true
  } else if (buttonState == HIGH && lastButtonState == LOW) {  // short press
    Serial.println(frequency = frequency == 2000 ? 100 : 2000);  // change frequency
    change = true;  // set change flag to true
  }

  lastButtonState = buttonState;  // update last button state
}
