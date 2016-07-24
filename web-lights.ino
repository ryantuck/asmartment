#include "FastLED/FastLED.h"
FASTLED_USING_NAMESPACE;

#define NUM_LEDS 72
#define DATA_PIN 5
#define CLOCK_PIN 0

CRGB leds[NUM_LEDS];

CRGB colors[4] = {
    CRGB::White,
    CRGB::Red,
    CRGB::Green,
    CRGB::Blue
    };

class Strip {

public:

    CRGB color;
    int idx;
    int colorIdx;
    bool allOn;

    Strip() {
        idx = 0;
        colorIdx = 0;
        color = CRGB::White;
        allOn = true;
    }

    void updateColor() {
        // update color index and set color from there
        colorIdx = (colorIdx + 1) % 4;
        color = colors[colorIdx];
    }

    void setColor(int setIdx) {
        // update color index and set color from there
        color = colors[setIdx];
    }

    void toggleAllOn() {

        allOn = !allOn;
    }

    void iterate() {

        if (allOn) {

            for (int i=0; i< NUM_LEDS; i++) {
                leds[i] = color;
            }
            FastLED.show();
            delay(100);
            for (int i=0; i< NUM_LEDS; i++) {
                leds[i] = CRGB::Black;
            }
        }
        else {
            leds[idx] = color;
            FastLED.show();
            delay(50);
            leds[idx] = CRGB::Black;
            idx = (idx + 1) % NUM_LEDS;
        }
    }
};

Strip strip = Strip();

void setup() {
    delay(2000);
    FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, BRG>(leds, NUM_LEDS);
    Particle.function("cc",toggle);
    Particle.function("on",all);
}

void loop() {

    strip.iterate();

}

int toggle(String command) {

    if (command == "white") {
        strip.setColor(0);
        return 0;
    }
    else if (command == "red") {
        strip.setColor(1);
        return 1;
    }
    else if (command == "green") {
        strip.setColor(2);
        return 2;
    }
    else if (command == "blue") {
        strip.setColor(3);
        return 3;
    }
    else {
        return -1;
    }
}

int all(String command) {

    if (command == "allOn") {
        strip.toggleAllOn();
        return 1;
    }
    else if (command == "off") {
        strip.toggleAllOn();
        return 0;
    }
    else {
        return -1;
    }

}



























