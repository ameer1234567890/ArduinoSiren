int input = 0;
int BUZZER_PIN = 13; // buzzer pin
int BUTTON_PIN = 2; // button pin
int j = 3; // start pin
int k = 12; // end pin
boolean lastButton = LOW;
boolean currentButton = LOW;


void setup() {
  for (int i = 3; i <= 12; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}


boolean debounce(boolean last) { // function to solve the problem of button bouncing
  boolean current = digitalRead(BUTTON_PIN);
  if (last != current) {
    delay(5);
    current = digitalRead(BUTTON_PIN);
  }
  return current;
}


void loop() {
  for (int i = 3; i <= 12; i++) {
    digitalWrite(i, LOW);
    currentButton = debounce(lastButton);
  }
  if (lastButton == LOW && currentButton == HIGH) {
    input++;
  }
  lastButton = currentButton;
  settone(input);
}

void settone(int input) {
  if (input == 1) {
    one();
  } else if (input == 2) {
    oneA();
  } else if (input == 3) {
    two();
  } else if (input == 4) {
    twoA();
  } else if (input == 5) {
    three();
  } else if (input == 6) {
    threeA();
  } else if (input == 7) {
    four();
  }
}
void one() { // this function produces the 1st siren sound with ON/OFF led transition.
  // whoop up
  for (int hz = 440; hz < 1000; hz += 25) {
    tone(BUZZER_PIN, hz, 50);
    delay(5);
    for (int i = 3; i <= 7; i++) {
      digitalWrite(i, HIGH);
    }
  }
  // whoop down
  for (int hz = 1000; hz > 440; hz -= 25) {
    tone(BUZZER_PIN, hz, 50);
    delay(5);
    for (int i = 3; i <= 7; i++) {
      digitalWrite(i, LOW);
      digitalWrite(i + 5, HIGH);
    }
  }
}


void oneA() { // this function produces a differnt transition of 1st siren.
  // whoop up
  for (int hz = 440; hz < 1000; hz += 25) {
    tone(BUZZER_PIN, hz, 50);
    delay(5);
  }
  if (j >= 3) {
    digitalWrite(j, HIGH);
    j = j + 1;
    digitalWrite(k, HIGH);
    k = k - 1;
    if (j == 8) {
      j = 3;
    }
    if (k == 7) {
      k = 12;
    }
  }
  // whoop down
  for (int hz = 1000; hz > 440; hz -= 25) {
    tone(BUZZER_PIN, hz, 50);
    delay(5);
  }
}


void two() { // this function produces the 2nd siren sound with progressive led transition.
  // whoop up
  for (int hz = 440; hz < 1000; hz += 25) {
    tone(BUZZER_PIN, hz, 50);
    delay(5);
  }
  loopF(3, 12, 20);
  loopR(12, 3, 20);
  // whoop down
  for (int hz = 1000; hz > 440; hz -= 25) {
    tone(BUZZER_PIN, hz, 50);
    delay(5);
  }
}


void twoA() { // this function produces a differnt transition of 2nd siren.
  // whoop up
  for (int hz = 440; hz < 1000; hz += 25) {
    tone(BUZZER_PIN, hz, 50);
    delay(5);
  }
  loopF(3, k, 20);
  loopR(12, j, 20);
  k--;
  if (k == 3) {
    k = 12;
  }
  j++;
  if (j == 12) {
    j = 3;
  }
  // whoop down
  for (int hz = 1000; hz > 440; hz -= 25) {
    tone(BUZZER_PIN, hz, 50);
    delay(5);
  }
}


void three() { // this function produces the 3rd siren (ambulance) sound with led transition.
  tone(BUZZER_PIN, 440, 200);
  delay(300);
  for (int i = 3; i <= 6; i++) {
    digitalWrite(i, HIGH);
  }
  noTone(BUZZER_PIN);
  tone(BUZZER_PIN, 494, 500);
  delay(300);
  for (int i = 3; i <= 6; i++) {
    digitalWrite(i, LOW);
    digitalWrite(i + 6, HIGH);
  }
  noTone(BUZZER_PIN);
  tone(BUZZER_PIN, 523, 300);
  delay(200);
  digitalWrite(7, HIGH);
  delay(50);
  digitalWrite(8, HIGH);
  delay(50);
  noTone(BUZZER_PIN);
}


void threeA() { // this function produces a differnt transition of 3rd siren.
  tone(BUZZER_PIN, 440, 200);
  delay(100);
  loopF(5, 10, 20);
  loopR(10, 5, 20);
  noTone(BUZZER_PIN);
  for (int i = 3; i <= 4; i++) {
    digitalWrite(i, HIGH);
    digitalWrite(i + 8, HIGH);
  }
  tone(BUZZER_PIN, 494, 500);
  delay(300);
  noTone(BUZZER_PIN);
  for (int i = 3; i <= 4; i++) {
    digitalWrite(i, LOW);
    digitalWrite(i + 8, LOW);
  }
  tone(BUZZER_PIN, 523, 300);
  delay(300);
  noTone(BUZZER_PIN);
}


void four() { // this function produces the 4th siren (police) sound with led transition.
  for (int i = 3; i <= 11; i += 2) {
    digitalWrite(i, HIGH);
  }
  for (int hz = 440; hz < 1000; hz++) {
    tone(BUZZER_PIN, hz, 50);
    delay(5);
  }
  for (int i = 3; i <= 11; i += 2) {
    digitalWrite(i, LOW);
  }
  for (int i = 4; i <= 12; i += 2) {
    digitalWrite(i, HIGH);
  }
  for (int hz = 1000; hz > 440; hz--) {
    tone(BUZZER_PIN, hz, 50);
    delay(5);
  }
}


// some extra functions other than the siren tones

void loopF(int spin, int epin, int dela) { //loopF can blink the led in forward direction, so spin must be lower than epin.
  for (int i = spin; i <= epin; i++) {
    digitalWrite(i, HIGH);
    delay(dela);
    low();
    if (spin == epin) {
      spin = 3;
      epin = 12;
    }
  }
}


void loopR(int epin, int spin, int dela) { // loopR can blink the led in reverse/backward direction, so epin must be lower than spin.
  for (int i = epin; i >= spin; i--) {
    digitalWrite(i, HIGH);
    delay(dela);
    low();
    if (spin == epin) {
      spin = 3;
      epin = 12;
    }
  }
}


void low() { // used by loopF and loopR
  for (int i = 3; i <= 12; i++)
    digitalWrite(i, LOW);
}
