#include "FastLED/FastLED.h"
FASTLED_USING_NAMESPACE;

#define NUM_LEDS 72
#define DATA_PIN 5
#define CLOCK_PIN 0

CRGB leds[NUM_LEDS];

CRGB colors[5] = {
    CRGB::White,
    CRGB::Red,
    CRGB::Green,
    CRGB::Blue,
    CRGB(255, 214, 170)
};

class Strip {

public:

    CRGB color;
    bool allOn;

    Strip() {
        color = colors[4];
        allOn = true;
    }

    void toggleAllOn() {
        allOn = !allOn;
    }

    void setColor(int setIdx) {
        color = colors[setIdx];
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
            for (int i=0; i< NUM_LEDS; i++) {
                leds[i] = CRGB::Black;
            }
            FastLED.show();
            delay(100);
        }
    }
};

Strip strip = Strip();

void setup() {
    delay(1000);
    FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, BRG>(leds, NUM_LEDS);
//    strip.setColor(4);
    Particle.function("set_color", allOneColor);
    Particle.function("on_off", toggleOnOff);
}

void loop() {
    strip.iterate();
}


int allOneColor(String command) {

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
    else if (command == "tungsten") {
        strip.setColor(4);
        return 4;
    }
    else {
        return -1;
    }
}


int toggleOnOff(String command) {

    if (command == "on") {
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
