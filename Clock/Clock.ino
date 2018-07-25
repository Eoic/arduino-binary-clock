// Buttons.
const byte hoursBtnPin = 12;
const byte minutesBtnPin = 13;

// Timestamp for button down start.
long buttonTimer = 0;

// Time until button long press is registered.
long longPressTime = 1000;

// Button state flags.
boolean longPressActive = false;
boolean hoursButtonDown = false;

boolean hourUpdated = false;
boolean minuteUpdated = false;

boolean longPressIssued = false;

// Time.
byte hourOffset, minuteOffset;
byte hours, minutes, seconds;

void setup()
{

	/*
     PINS     [2;11]
     Hours:   [2;5]
     Minutes: [6;11]
     Buttons: [12;13]
  */

	for (int i = 2; i <= 11; i++)
		pinMode(i, OUTPUT);

	pinMode(hoursBtnPin, INPUT);
	pinMode(minutesBtnPin, INPUT);

	hourOffset = 0;
	minuteOffset = 0;
}

void loop()
{
	// Toggle time set mode.
	if (digitalRead(hoursBtnPin) == HIGH)
	{
    // Set button as pressed down and save timestamp.
    if(!hoursButtonDown){
  	  hoursButtonDown = true;
  	  buttonTimer = millis();
    } 
    
    if((millis() - buttonTimer) >= longPressTime && !longPressIssued) {
      longPressActive = !longPressActive;
      longPressIssued = true;

      if(!longPressActive)
        hourOffset--;
    } 
    
    if(longPressActive && !hourUpdated && !longPressIssued){
        hourOffset++;
        hourUpdated = true;
    } 

    delay(50);
	}

  if(digitalRead(hoursBtnPin) == LOW && hoursButtonDown){
    hoursButtonDown = false;
    hourUpdated = false;
    longPressIssued = false;
  }

	// Set minutes.
	if (digitalRead(minutesBtnPin) == HIGH && longPressActive && !minuteUpdated)
	{
		minuteOffset++;
		minuteUpdated = true;

    delay(50);
	}

	if (digitalRead(minutesBtnPin) == LOW){
		minuteUpdated = false;

    delay(50);
	}

	// Calculate time from program start and add given offset.
	hours = ((millis() / 3600000) + hourOffset) % 12;
	minutes = ((millis() / 60000) + minuteOffset) % 60;

	// Set output pins for hours.
	for (int i = 0; i < 4; i++)
		digitalWrite(5 - i, (bitRead(hours, i) ? HIGH : LOW));

	// Set output pins for minutes.
	for (int i = 0; i < 6; i++)
		digitalWrite(11 - i, (bitRead(minutes, i) ? HIGH : LOW));
}
