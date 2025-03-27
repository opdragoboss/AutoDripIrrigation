#include <Wire.h>
#include <RTClib.h>
#include <avr/sleep.h>

RTC_DS3231 rtc;
const int relayPin = 4;

void setup() {
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW);
    Wire.begin();
    rtc.begin();
}

void loop() {
    DateTime now = rtc.now();
    
    // Turn on valve at 5:00 PM for 15 minutes
    if (now.hour() == 17 && now.minute() == 0) {
        digitalWrite(relayPin, HIGH);
        delay(15 * 60 * 1000); // 15 minutes
        digitalWrite(relayPin, LOW);
    }

    // sleep for 1 minute
    goToSleep(60); 
}

// sleep
void goToSleep(int seconds) {
    for (int i = 0; i < seconds; i++) {
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();
        sleep_cpu();
        delay(1000); // Wake after 1 second
    }
}
