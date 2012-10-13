int red = 11;
int yellow = 10;
int green = 9;
int looper = 0;
int i = 0;
int button_pressed = 0;

void setup() {
  for (i = 9; i <= 11; i++) pinMode(i, OUTPUT);
  digitalWrite(green, HIGH);
  Serial.begin(9600);
}

void loop() {
  
  delay(1); // This way, looper tracks milliseconds.
  looper++;
  if (analogRead(0)) button_pressed = 1; 
  // If the light is green, the button press is stored but may not be immediately acted upon - 
  // This is in order to give the cars at the green light time to cross.
  
  if((button_pressed == 1  && looper >= 2000) || looper >= 8000) {
    // Current acts as crosswalk button, which only works if the light has been green for two seconds.
    // Also automatically cycles every 6 seconds.
    
    // Fade to yellow
    for (i=0; i<=255; i++) {
      analogWrite(green, 255-i);
      analogWrite(yellow, i);
      delay(1);
    }

    delay(3000);
    
    // Fade to red
    for (i=0; i<=255; i++) {
      analogWrite(yellow, 255-i);
      analogWrite(red, i);
      delay(1);
    }
    delay(5000);

    // Switch back to green
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    looper = 0;
    button_pressed = 0;
  }
}

