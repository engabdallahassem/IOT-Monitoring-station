// const int buzzerPin = 6;

unsigned long alarmStartTime = 0;
unsigned long alarmDuration = 0;
bool isAlarmActive = false;

void alarmSetup() {
  pinMode(buzzerPin, OUTPUT);
}
// DynamicJsonDocument control(1000);
void alarmLoop() {


  DynamicJsonDocument control(100);
  DeserializationError error = deserializeJson(control, nodemcu);
  if (error) {
    Serial.print("Error: ");
    Serial.println(error.c_str());
    return;
  }

  int buzzerState = control["buzzer"];
  alarmDuration = control["duration"];
  serializeJson(control, Serial);
  if (buzzerState == 1 && !isAlarmActive) {
    alarmStartTime = millis();
    isAlarmActive = true;
    playTune();
  }

  if (isAlarmActive && millis() - alarmStartTime >= alarmDuration) {
    stopTune();
    isAlarmActive = false;
  }
}

void playTune() {
  Serial.println("Alarm on");
  tone(buzzerPin, 440);  // Play A4 note
}

void stopTune() {
  Serial.println("Alarm off");
  noTone(buzzerPin);
}