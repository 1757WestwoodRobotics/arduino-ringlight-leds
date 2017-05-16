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
    
  sequentialRainbow(10, 10, 100);    delay(1000);
  sequentialRainbow(25, 25, 100);    delay(1000);
  sequentialRainbow(50, 5, 100);    delay(1000);
  sequentialRainbow(10, 10, 100);    delay(3000);
  setAllLEDsColor(RED);    delay(1000);
  setAllLEDsColor(GREEN);    delay(1000);
  setAllLEDsColor(BLUE);    delay(1000);
  setAllLEDsColor(OFF);    delay(250);
  chaseTheLED(0, 200, 10, BLUE);    delay(1000);
  setAllLEDsRainbow(0, 5);    delay(1000);

}

void updateLEDs() {
  FastLED.show();
  FastLED.delay(30);
}

// All LEDs functions
void setAllLEDsColor(CHSV color) {
  fill_solid(leds, NUM_LEDS, color);
  updateLEDs();
}

void setAllLEDsRainbow(uint8_t initialhue, uint8_t deltahue) {
  fill_rainbow(leds, NUM_LEDS, initialhue, deltahue);
  updateLEDs();
}

void sequentialRainbow(uint8_t initialhue, uint8_t deltahue, int msDelay) {
  uint8_t hue = initialhue + deltahue;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue, 255, 255);
    updateLEDs();
    delay(msDelay);
    hue += deltahue;
  }
}

void chaseTheLED(int startingLED, int msDelay, int howManyTimes, CHSV color) {    // howManyTimes isn't implemented yet.
  for (int i = startingLED; i < NUM_LEDS; i++) {
    setIndividualLED(i, color);
    FastLED.delay(msDelay);
    leds[i] = OFF;
  }
}

// Individual LED functions
void setIndividualLED(int led, CHSV color) {
  leds[led] = color;
  updateLEDs();
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
  updateLEDs();
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
  updateLEDs();
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
  updateLEDs();
}

