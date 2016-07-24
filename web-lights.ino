#include "FastLED/FastLED.h"
FASTLED_USING_NAMESPACE;

#define NUM_LEDS 16
#define DATA_PIN 3
#define CLOCK_PIN 13

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

    Strip() {
        idx = 0;
        colorIdx = 0;
        color = CRGB::White;
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

    void iterate() {

        leds[idx] = color;
        FastLED.show();
        delay(100);
        leds[idx] = CRGB::Black;
        idx = (idx + 1) % NUM_LEDS;
        }
};

Strip strip = Strip();

void setup() {
    delay(2000);
    FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, BRG>(leds, NUM_LEDS);
    Spark.function("cc",toggle);
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


























