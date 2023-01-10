#include "core.h"
#include "pwm.h"
#include "button.h"
#include <FastLED.h>



//////////////////////////////////////////// CONFIG IS HERE ////////////////////////////////////////////

// Amount of leds in longest strip.
// Should be a bit bigger than actual number of leds to avoid crashes (+2 should be fine)
#define NUM_LEDS_PER_STRIP 19

// How many leds in each strip (here use real values)
int ledz[] = {1, 17};

// How many LED strips we have
#define LED_STRIPS 2

// PWM pin for external LED lights
PWM bulbs(9);

// Check button.h for button pin definition
///////////////////////////////////////////////////////////////////////////////////////////////////////



// Here we create FastLED multi-strip object
CRGB leds[LED_STRIPS][NUM_LEDS_PER_STRIP];

#include "rgb.h"


// Function for RGB button handling
void handle_btn(int id, int up, int dn) {
	if (!RGBs[id].brightness) dn = 0;
	if (up == 1) {
		RGBs[id].lightsUp();
	}
	else if (up == 2) {
		if (RGBs[id].brightness) RGBs[id].brightness = 0;
		else RGBs[id].brightness = RGBs[id].Bs - 1;
	}
	if (dn == 1) {
		RGBs[id].nextColor();
	}
	else if (dn == 2) {
		RGBs[id].nextMode();
	}
}

// Function for PWM button handling, hardcoded for now
void handle_pwm_btn() {
	if (bulber.value == 1) {
		if (bulbs.brightness == 3) bulbs.brightness = 0;
		else bulbs.set(1);
	}
	if (bulber.value == 2) {
		if (bulbs.brightness) bulbs.brightness = 0;
		else bulbs.brightness = 3;
	}
}


// Main code, runs once
void setup() {
	FastLED.addLeds<NEOPIXEL, 7>(leds[0], NUM_LEDS_PER_STRIP);
	FastLED.addLeds<NEOPIXEL, 8>(leds[1], NUM_LEDS_PER_STRIP);
	for (int i = 0; i < LED_STRIPS; i++) {
		RGBs[i].init(i, ledz[i]);
	}
}

// Main loop
void loop() {
	timer.update();
	updatebtns();
	handle_btn(1, l1_up.value, l1_dn.value);
	handle_btn(0, l2_up.value, l2_dn.value);
	handle_pwm_btn();
	for (int i = 0; i < LED_STRIPS; i++) {
		RGBs[i].update();
	}
	bulbs.update();
	FastLED.show();
}
