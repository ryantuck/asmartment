#include "FastLED/FastLED.h"
FASTLED_USING_NAMESPACE;

#define NUM_LEDS 324
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
    int redIdx;
    int blueIdx;
    int greenIdx;
    int colorIdx;
//    bool allOn;
    int mode = 1;

    Strip() {
        redIdx = rand() % NUM_LEDS;
        greenIdx = rand() % NUM_LEDS;
        blueIdx = rand() % NUM_LEDS;
        colorIdx = 0;
        color = CRGB::Blue;
//        allOn = false;
        mode = 1;
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

    void setMode(int x) {
        mode = x;
    }

    void iterate() {

        if (mode == 0) {

//            for (int i=0; i< NUM_LEDS; i++) {
//                leds[i] = color;
//            }
//            FastLED.show();
//            delay(100);
//            for (int i=0; i< NUM_LEDS; i++) {
//                leds[i] = CRGB::Black;
//            }
        } else if (mode == 1) {
            // random walk of particle
            //leds[idx] = color;

            leds[redIdx] = CRGB::Red;
            leds[greenIdx] = CRGB::Green;
            leds[blueIdx] = CRGB::Blue;

            FastLED.show();
            delay(50);

            leds[redIdx] = CRGB::Black;
            leds[greenIdx] = CRGB::Black;
            leds[blueIdx] = CRGB::Black;

            redIdx = getNeighbor(redIdx);
            greenIdx = getNeighbor(greenIdx);
            blueIdx = getNeighbor(blueIdx);

        } else {
//            leds[idx] = color;
//            FastLED.show();
//            delay(50);
//            leds[idx] = CRGB::Black;
//            idx = (idx + 1) % NUM_LEDS;
        }
    }
};

Strip strip = Strip();

void setup() {
    delay(1000);
    FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, BRG>(leds, NUM_LEDS);
    strip.setColor(1);
    Particle.function("cc", toggle);
    //Particle.function("mode", setMode);
    //Particle.function("on",all);
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

//int all(String command) {
//
//    if (command == "allOn") {
//        strip.toggleAllOn();
//        return 1;
//    }
//    else if (command == "off") {
//        strip.toggleAllOn();
//        return 0;
//    }
//    else {
//        return -1;
//    }
//
//}

int setMode(String command) {
    if (command == "random walk") {
        strip.setMode(1);
        return 1;
    } else if (command == "line") {
        strip.setMode(0);
        return 0;
    } else {
        return -1;
    }
}

int getNeighbor(int currentIdx) {

    // 0 bottom left
    // 323 top left

    int width = 18;
    int height = 18;

    // get x and y from the given idx
    int y = currentIdx / 18;
    int x;
    if (y % 2 == 0) {
        x = currentIdx % 18;
    } else {
        x = 18 - currentIdx % 18 - 1;
    }

    bool up = true;
    bool down = true;
    bool left = true;
    bool right = true;

    if (x == 0) { left = false; }
    if (x == 17) { right = false; }
    if (y == 0) { down = false; }
    if (y == 17) { up = false; }

    bool dirs[4] = {up, down, left, right};

    // pick a random direction that's allowed
    bool dirFound = false;
    int dirIdx;
    while (!dirFound) {
        dirIdx = rand() % 4;
        bool newDir = dirs[dirIdx];
        if (newDir) { dirFound = true; }
    }

    if (dirIdx == 0) { y = y + 1; }
    else if (dirIdx == 1) { y = y - 1; }
    else if (dirIdx == 2) { x = x - 1; }
    else { x = x + 1; }

    int newIdx;
    if (y % 2 == 0) {
        newIdx = 18*y + x;
    } else {
        newIdx = 18*(y+1) - x;
    }

    return newIdx;
}






