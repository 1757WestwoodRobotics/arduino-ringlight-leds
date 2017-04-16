/**
 * Ringlight LED Control
 * by Larry Tseng on 4/14/17.
 * 
 * Controls WS2812 leds on a ring light.
 * Uses the FastLED library: https://github.com/FastLED/FastLED.
 * Tested with Arduino Leonardo++ (16Hertz) from FRC.
 * 
 * Since there are two ringlights and one array of leds,
 * configure the loops properly. 0-23 or 24-48.
 * 
 * Last Updated 4/14/17 at 2 PM EST.
 */
 
#include <FastLED.h>

#define DATA_PIN    6
#define COLOR_ORDER GRB
#define CHIPSET     WS2812
#define NUM_LEDS    48

CRGB leds[NUM_LEDS];

// Default led HSV configurations
int led1_hue = 100;
int led1_sat = 255;
int led1_val = 255;
int led2_hue = 255;
int led2_sat = 255;
int led2_val = 255;

// Preset values
const CHSV GREEN(100, 255, 255);
const CHSV RED(0, 255, 255);
const CHSV BLUE(160, 255, 255);
const CHSV OFF(0, 0, 0);

void setup() {
  FastLED.delay(3000); // Sanity delay
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS); // Initializes leds
  setAllLEDsColor(OFF);
  updateLEDs();
}

void loop() {
  setAllLEDsColor(RED);
  updateLEDs();
  delay(1000);
  setAllLEDsColor(GREEN);
  updateLEDs();
  delay(1000);
  setAllLEDsColor(BLUE);
  updateLEDs();
  delay(1000);
  setAllLEDsRainbow(0, 5);
  updateLEDs();
  delay(1000);
  chaseTheLED(0, 200, 10, BLUE);
  delay(1000);
}

void updateLEDs() {
  FastLED.show();
  FastLED.delay(30);
}

// All LEDs functions
void setAllLEDsColor(CHSV color) {
  fill_solid(leds, NUM_LEDS, color);
//  for (int k = 0; k < 48; k++) {
//    leds[k] = color;
//  }
}

void setAllLEDsRainbow(uint8_t initialhue, uint8_t deltahue) {
  fill_rainbow(leds, NUM_LEDS, initialhue, deltahue); // May not work? Setting HSV to RGB...
}

void chaseTheLED(int startingLED, int msDelay, int howManyTimes, CHSV color) {
  for (int i = startingLED; i < (howManyTimes * NUM_LEDS); i++) {
    leds[i] = color;
    updateLEDs();
    FastLED.delay(msDelay);
    leds[i] = OFF;
  }
}

// Individual LED functions
void setIndividualLED(int led, CHSV color) {
  leds[led] = color;
}

// Individual ringlight functions
void setRingLightHue(int whichLight, int hue) {
  switch (whichLight) {
    case 1: 
      for (int i = 0; i < 24; i++) {
        leds[i] = CHSV(hue, led1_sat, led1_val);
      }
      led1_hue = hue;
      break;
    case 2:
      for (int i = 24; i < 48; i++) {
        leds[i] = CHSV(hue, led2_sat, led2_val);
      }
      led2_hue = hue;
      break;
  }
}

void setRingLightSaturation(int whichLight, int saturation) {
  switch (whichLight) {
    case 1: 
      for (int i = 0; i < 24; i++) {
        leds[i] = CHSV(led1_hue, saturation, led1_val);
      }
      led1_sat = saturation;
      break;
    case 2:
      for (int i = 24; i < 48; i++) {
        leds[i] = CHSV(led2_hue, saturation, led2_val);
      }
      led2_sat = saturation;
      break;
  }
}

void setRingLightValue(int whichLight, int value) {
  switch (whichLight) {
    case 1:
      for (int i = 0; i < 24; i++) {
        leds[i] = CHSV(led1_hue, led1_sat, value);
      }
      led1_val = value;
      break;
    case 2:
      for (int i = 24; i < 48; i++) {
        leds[i] = CHSV(led2_hue, led2_sat, value);
      }
      led2_val = value;
      break;
  }
}

