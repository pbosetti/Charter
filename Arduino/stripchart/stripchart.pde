/*
  Arduino stripchart generator
  To be used with Charter app (search for it on the Mac App Store)
  (C) Paolo Bosetti 2011
*/
#define VERSION      "0.1"
#define PROMPT       Serial.println(">")
#define LOOP_DELAY   1
#define ANALOG_PINS  6
#define DIGITAL_PINS 14
#define BAUD         115200

void setup(void)
{
  // start serial port
  Serial.begin(BAUD);
  while (Serial.available() == 0) {
    delay(10);
  }
  Serial.print("Stripchart data generator ");
  Serial.println(VERSION);
  Serial.println("Available commands are 'a' (analog) and 'd' (dig.");
  for (int i = 0; i < DIGITAL_PINS; i++) {
    pinMode(i, INPUT);
  }

  PROMPT;
}


void loop(void)
{ 
  static uint8_t v = 0;
  char ch;
  if (Serial.available()) {
    ch = Serial.read();
    // Serial command parsing:
    switch(ch) {
    case '0'...'9': // Accumulates values
      v = v * 10 + ch - '0';
      break;

    case 'a':
      if (v > 0 && v <= ANALOG_PINS) {
        Serial.println(analogRead(v-1));
      }
      else {
        Serial.println("---");
        for (int i = 0; i < ANALOG_PINS; i++) {
          Serial.print("- ");
          Serial.println(analogRead(i));
        }
      }
      v = 0;
      PROMPT;
      break;

    case 'd':
      if (v > 0 && v <= DIGITAL_PINS) {
        Serial.println(analogRead(v-1));
      }
      else {
        Serial.println("---");
        for (int i = 0; i < DIGITAL_PINS; i++) {
          Serial.print("- ");
          Serial.println(digitalRead(i));
        }
      }
      v = 0;
      PROMPT;
      break;
      
    }
  }
  else {
    delay(LOOP_DELAY);
  }
}

















