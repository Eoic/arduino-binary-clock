// Delay after time update.
const short DELAY = 0;

// Buttons.
const byte hoursBtnPin = 11;
const byte minutesBtnPin = 12;
long buttonTimer = 0;
long longPressTime = 1000;

// Button state flags.
boolean longPressActive = false;
boolean buttonActive = false;

// Time.
byte hourOffset, minuteOffset;
byte hours, minutes, seconds;

void setup() {

  /*
     PINS     [2;11]
     Hours:   [2;6]
     Minutes: [7;11]
     Buttons: [12;13]
  */
  for(int i = 2; i <= 11; i++)
    pinMode(i, OUTPUT);

  pinMode(hoursBtnPin, INPUT);
  pinMode(minutesBtnPin, INPUT);

  hourOffset = 0;
  minuteOffset = 0;

  Serial.begin(9600);
}

void loop() {

  /*
  hoursBtnState = digitalRead(hoursBtnPin);
  minutesBtnState = digitalRead(minutesBtnPin);
  */
  
  // Calculate time from program start and add given offset.
  hours = (((millis() / 1000) / 360) + hourOffset) % 12;
  minutes = (((millis() / 1000) / 60) + minuteOffset) % 60;

  // Set output pins for minutes.
  for (int i = 0; i < 4; i++) {
    digitalWrite(i + 5, (bitRead(hours, i) ? HIGH : LOW));
    
    Serial.print("Pin number: ");
    Serial.print(i + 5);
    Serial.print(" Bit: ");
    Serial.print(bitRead(hours, i));
    Serial.println("");
  }

  Serial.println("\n");

  // Set output pins for minutes.
  for (int i = 0; i < 6; i++) {
    digitalWrite(i + 9, (bitRead(minutes, i) ? HIGH : LOW));

    Serial.print("Pin number: ");
    Serial.print(i + 9);
    Serial.print(" Bit: ");
    Serial.print(bitRead(minutes, i));
    Serial.println("");
  }

  Serial.println("------------------------");

  // Sleep for 1 minute.
  delay(DELAY);
}
