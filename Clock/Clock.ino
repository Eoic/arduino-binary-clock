// Buttons.
const byte hoursBtnPin = 12;
const byte minutesBtnPin = 13;

// Timestamp for button down start.
long buttonTimer = 0;

// Total time in ms.
long time = 0;

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
		if (!hoursButtonDown)
		{
			hoursButtonDown = true;
			buttonTimer = millis();
		}

		if ((millis() - buttonTimer) >= longPressTime && !longPressIssued)
		{
			longPressActive = !longPressActive;
			longPressIssued = true;

			if (!longPressActive)
				hourOffset = (hourOffset - 1) % 12;
		}

		if (longPressActive && !hourUpdated && !longPressIssued)
		{
			hourOffset = (hourOffset + 1) % 12;
			hourUpdated = true;
		}

		delay(50);
	}

	if (digitalRead(hoursBtnPin) == LOW && hoursButtonDown)
	{
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

	if (digitalRead(minutesBtnPin) == LOW)
	{
		minuteUpdated = false;
		delay(50);
	}

	// Total time in ms.
	time = millis() + (hourOffset * 3600000) + (minuteOffset * 60000);

	// Calculate time from program start and add given offset.
	minutes = (time / 60000) % 60;
	hours = (time / 3600000) % 12;

	// Set output pins for hours.
	for (int i = 0; i < 4; i++)
		digitalWrite(i + 2, (bitRead(hours, i) ? HIGH : LOW));

	// Set output pins for minutes.
	for (int i = 0; i < 6; i++)
		digitalWrite(i + 6, (bitRead(minutes, i) ? HIGH : LOW));
}
