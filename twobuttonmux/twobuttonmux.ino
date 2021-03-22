//const int ledPin = 13;
const int ledPin = 11;
const int buttonPin = 2;
const int controlPin = 12;

int control = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(controlPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  int buttonState;
  
  digitalWrite(controlPin, HIGH);
  //digitalWrite(controlPin, control&1?HIGH:LOW);
  
  buttonState = digitalRead(buttonPin);
  //if (control == 0) {
    if (buttonState == HIGH) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
  //}

  control = control + 1 % 2;
}
