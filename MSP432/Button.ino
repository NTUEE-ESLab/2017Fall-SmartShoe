int prevState = 1;
int buttonState = 1;
const int buttonPin = PUSH2;


void setupButton() {
  pinMode(buttonPin, INPUT_PULLUP);  
}

void loopButton() {
  buttonState = digitalRead(buttonPin);
  if ((buttonState == LOW)&&(buttonState != prevState)&&(initializing == 0)) {
    init_num += 1;
  }
  prevState = buttonState;  
}

