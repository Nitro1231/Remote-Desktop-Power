#include <Arduino.h>
#include <arduino_homekit_server.h>
#include "Info.h"

#define PIN_SWITCH 4 // D2
#define LOG(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);

extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t remote_switch;

void setup() {
	Serial.begin(115200);
	wifi_connect();
	// homekit_storage_reset(); // to remove the previous HomeKit pairing storage when you first run this new HomeKit example
	my_homekit_setup();
}

void loop() {
	arduino_homekit_loop();
	delay(10);
}

void update(const homekit_value_t value) {
	bool data = value.bool_value;
	remote_switch.value.bool_value = data;

	if (data) {
		LOG("Switch triggered!");
		digitalWrite(PIN_SWITCH, HIGH);
		delay(300);
		digitalWrite(PIN_SWITCH, LOW);
		remote_switch.value.bool_value = false;
		homekit_characteristic_notify(&remote_switch, remote_switch.value);
	}
}

void my_homekit_setup() {
	pinMode(PIN_SWITCH, OUTPUT);
	digitalWrite(PIN_SWITCH, LOW);

	remote_switch.setter = update;
	arduino_homekit_setup(&config);
}
