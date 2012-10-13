int i;            // Used in various loops
int looper = 0;   // Keeps tally of total cycles

// Note: Only change pin numbers here. Skipping pins must be done manually.
int MIN = 9;      // Lowest Pin
int MAX = 11;     // Highest Pin

// 0: Automatically switch between all modes.  1: Set mode manually.
int manual_mode = 0;

int light_mode = 1;
  /*
  1 - Random
  2 - Descending
  3 - Ascending 
  4 - Ping-pong
  5 - All-At-Once
  6 - Fade In and Out
  */

  
void setup() {
  for (i = MIN; i <= MAX; i++) pinMode(i, OUTPUT);  // Set all pins to output
  Serial.begin(9600);
  randomSeed(analogRead(5));    // Generates noise.
}

void loop() {
    if(check_resistance(0)) flash_lights();    // Flashes when current drops below threshold
    print_resistance();
    
    looper++; 
    if (looper % 15 == 0 && !manual_mode) {    // Change light mode after 25 cycles
      if (light_mode == 6) light_mode = 1; else light_mode++;
    }
}


int check_resistance(int pin) {
  if (analogRead(pin) <= 350) return 1;
  else return 0;
  }
  
void flash_lights() {
  
  int random_light = random(MIN,MAX+1);
  int asc_desc = 1;    // 1: Up, 0: Down  
  int difference = MAX - MIN;   

  switch (light_mode) {
    
// Random Mode
      case 1: 
        digitalWrite(random_light, HIGH);
        delay(120);
        digitalWrite(random_light, LOW);
        break;
        
// Descending Mode      
      case 2: 
        for (i = MAX; i >= MIN; i--) {
          digitalWrite(i, HIGH);
          delay(120);
          digitalWrite(i, LOW);
        }
          break;
          
// Ascending Mode         
      case 3: 
        for (i = MIN; i <= MAX; i++) {
          digitalWrite(i, HIGH);
          delay(120);
          digitalWrite(i, LOW);
        }
          break;
          
// Ping-Pong Mode             
      case 4: 
        i = MIN;
        while (i <= MAX && asc_desc == 1) {
          digitalWrite(i, HIGH);
          delay(120);
          digitalWrite(i, LOW);
          i++;
          if (i ==  MAX) asc_desc = 0;

        }
        while (i >= MIN && asc_desc == 0) {
          digitalWrite(i, HIGH);
          delay(120);
          digitalWrite(i, LOW);
          i--;
          if (i ==  MIN) asc_desc = 1;

        }
        break;
        
// All flash     
      case 5: 
        for (i = 0; i <= difference; i++) digitalWrite(MIN+i, HIGH);
        delay(120);
        for (i = 0; i <= difference; i++) digitalWrite(MIN+i, LOW);
        delay(120);
        break;
        
// Fading       
      case 6:
      int j;
        for (i = 0; i <= 255; i++) {
          for(j = MIN; j<= MAX; j++) {
            analogWrite(j, i);
          }
          delay(2);
        }
        for (i = 255; i >= 0; i--) {
          for(j = MIN; j<= MAX; j++) {
            analogWrite(j, i);
          }
          delay(2);
        }
        break;
  }
}
void print_resistance() {
  float resistance = ((float) analogRead(0)/1024)*100;
  Serial.print("Resistance is: ");
  Serial.print(100 - resistance);
  Serial.println(" percent");
}
