
#include <Arduino.h>

#define BASE_PIN 17

uint32_t onTimeMins = 15;
uint32_t periodTimeHrs = 1;

uint32_t onTimeMs = onTimeMins ? onTimeMins * 60000 : 1000;           //тестування
uint32_t periodMs = periodTimeHrs ? periodTimeHrs * 3600000 : 4000;   //тестування

hw_timer_t *timer = nullptr;
bool outputOn = true;

void ARDUINO_ISR_ATTR onTimer()
{
  outputOn = !outputOn;
  digitalWrite(BASE_PIN, outputOn ? HIGH : LOW);
  uint32_t intervalMs = outputOn ? onTimeMs : periodMs - onTimeMs;
  timerAlarmWrite(timer, (uint64_t)intervalMs * 1000, true);
}

void setup()
{
  Serial.begin(115200);
  pinMode(BASE_PIN, OUTPUT);
  digitalWrite(BASE_PIN, LOW);
  timer = timerBegin(0, 80, true);
  timerStop(timer);
  timerWrite(timer, 0);
  timerAttachInterrupt(timer, &onTimer, false);
  timerAlarmWrite(timer, (uint64_t)onTimeMs * 1000, true);
  digitalWrite(BASE_PIN, HIGH);
  timerAlarmEnable(timer);
  timerStart(timer);
  Serial.println("Timer setuped");
}

void loop()
{
}
