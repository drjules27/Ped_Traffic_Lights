/*
 * Pedestrian traffic lights controlled by a button
 */
const int GREEN = 1; // declare constants to reprsent traffic light states
const int AMBER = 2;
const int RED = 3;
const int FLASHING_AMBER = 4;
volatile bool WAIT_FLAG = false; // flag to represent if WAIT button pushed
const int BUTTON = 2; // select the pin for the button - Pin 2 will cause an interrupt to be called
const int RED_TL = 3; // select the pin for the red traffic light
const int AMBER_TL = 4; // select the pin for the amber traffic light
const int GREEN_TL = 5; // select the pin for the green traffic light
const int RED_PED = 6; // select the pin for the red pedestrian light
const int GREEN_PED = 7; // select the pin for the green pedestrian light
const int WAIT_LED = 8; // select the pin for the WAIT light
unsigned long previoustime = 0; // variable to store time since WAIT button pressed
int state = GREEN;
void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(RED_TL, OUTPUT);
  pinMode(AMBER_TL, OUTPUT);
  pinMode(GREEN_TL, OUTPUT);
  pinMode(RED_PED, OUTPUT);
  pinMode(GREEN_PED, OUTPUT);
  pinMode(WAIT_LED, OUTPUT);
  pinMode(BUTTON, INPUT); 
  digitalWrite(RED_TL, LOW);
  digitalWrite(AMBER_TL, LOW);
  digitalWrite(GREEN_TL, HIGH);
  digitalWrite(RED_PED, HIGH);
  digitalWrite(GREEN_PED, LOW);
  digitalWrite(WAIT_LED, LOW);
  attachInterrupt(digitalPinToInterrupt(BUTTON), WAIT_BUTTON_PRESSED, RISING);
  WAIT_FLAG = false;
}

void loop() {
  if (state == GREEN) {
    digitalWrite(GREEN_TL, HIGH);
    digitalWrite(RED_PED, HIGH);
  }
  if (state == AMBER) {
    digitalWrite(GREEN_TL, LOW);
    digitalWrite(AMBER_TL, HIGH);
    delay(2000);
    state = RED;
  }
  if (state == RED) {
    digitalWrite(AMBER_TL, LOW);
    digitalWrite(RED_TL, HIGH);
    digitalWrite(RED_PED, LOW);
    digitalWrite(GREEN_PED, HIGH);
    digitalWrite(WAIT_LED, LOW);
    WAIT_FLAG = false;
    delay(10000);
    state = FLASHING_AMBER;
  }
  if (state == FLASHING_AMBER){
    digitalWrite(RED_TL, LOW);
    for (int count=0;count < 8;count++){
      Serial.println(count);
      digitalWrite(AMBER_TL, HIGH);
      digitalWrite(GREEN_PED, HIGH);
      delay(500);    
      digitalWrite(AMBER_TL, LOW);
      digitalWrite(GREEN_PED, LOW);
      delay(500);    
    }
    state = GREEN;
  }
  if(WAIT_FLAG == true){
   digitalWrite(WAIT_LED,HIGH);
    if(millis()-previoustime>10000){
      state = AMBER;
    }
  }
}

void WAIT_BUTTON_PRESSED(){
  WAIT_FLAG = true;
  previoustime = millis();
}


