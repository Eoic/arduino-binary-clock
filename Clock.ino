// Delay after time update.
const short DELAY = 0;

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
	if (digitalRead(hoursBtnPin) == LOW && hoursButtonDown)
	{
		if ((millis() - buttonTimer) >= longPressTime)
			longPressActive = !longPressTime;

		hoursButtonDown = false;
	}
	else if (digitalRead(hoursBtnPin) == HIGH && hoursButtonDown)
	{
		buttonTimer = millis();
		hoursButtonDown = true;
	}

	// Set hours.
	if (digitalRead(hoursBtnPin) == HIGH && longPressActive && !hourUpdated)
	{
		hourOffset++;
		hourUpdated = true;
	}

	if (digitalRead(hoursBtnPin) == LOW){
		hourUpdated = false;
		hoursButtonDown = false;
	}

	// Set minutes.
	if (digitalRead(minutesBtnPin) == HIGH && longPressActive && !minuteUpdated)
	{
		minuteOffset++;
		minuteUpdated = true;
	}

	if (digitalRead(minutesBtnPin) == LOW)
		minuteUpdated = false;

	// Calculate time from program start and add given offset.
	hours = ((millis() / 360000) + hourOffset) % 12;
	minutes = ((millis() / 60000) + minuteOffset) % 60;

	// Set output pins for minutes.
	for (int i = 0; i < 4; i++)
		digitalWrite(i + 2, (bitRead(hours, i) ? HIGH : LOW));

	// Set output pins for minutes.
	for (int i = 0; i < 6; i++)
		digitalWrite(i + 6, (bitRead(minutes, i) ? HIGH : LOW));

	// Sleep until next update.
	delay(DELAY);
}
