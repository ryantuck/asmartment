#include "FastLED/FastLED.h"
FASTLED_USING_NAMESPACE;

#define NUM_LEDS 324
#define DATA_PIN 5
#define CLOCK_PIN 0

CRGB leds[NUM_LEDS];

CRGB colors[6] = {
    CRGB(255,0,0),
    CRGB(255,255,0),
    CRGB(0,255,0),
    CRGB(0,255,255),
    CRGB(0,0,255),
    CRGB(255,0,255)
};


CRGB tungsten = CRGB(255, 214, 170);

class Led {

public:

    int idx;
    CRGB color;

    Led() {
        color = CRGB::White;
        idx = rand() % NUM_LEDS;
    }
};


class Grid {

public:

    Led pixels[6];

    int mode = 0;
    int all_count = 10;

    CRGB color = CRGB::Yellow;

    Grid() {

        for (int i=0; i<6; i++) {
            pixels[i].color = colors[i];
        }
    }

    void setMode(int x) {
        mode = x;
    }

    void refresh() {
        for (int i=0; i<NUM_LEDS; i++) {
            leds[i] = CRGB::Black;
        }
    }

    void iterate() {

        refresh();

        if (mode == 0) {

            for (int i=0; i<6; i++) {
                leds[pixels[i].idx] = pixels[i].color;
                pixels[i].idx = getNeighbor(pixels[i].idx);
            }
            FastLED.show();
            delay(50);

        }
        else if (mode == 1) {
            for (int i=0; i<all_count; i++) {
                leds[i] = color;
            }
            FastLED.show();
            delay(100);
        }
    }
};

Grid grid = Grid();

void setup() {
    delay(1000);
    FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, BRG>(leds, NUM_LEDS);
    Particle.function("set_mode", setGridMode);
    Particle.function("set_num", setGridNum);
    Particle.function("set_color", setGridColor);
}

void loop() {

    grid.iterate();

}


int setGridMode(String command) {
    if (command == "random walk") {
        grid.setMode(0);
        return 0;
    } else if (command == "all on") {
        grid.setMode(1);
        return 1;
    } else {
        return -1;
    }
}


int setGridNum(String command) {
    if (command == "100") {
        grid.all_count = 100;
        return 100;
    } else if (command == "200") {
        grid.all_count = 200;
        return 200;
    } else if (command == "324") {
        grid.all_count = 324;
        return 324;
    } else {
        return -1;
    }
}


int setGridColor(String command) {
    if (command == "red") {
        grid.color = CRGB::Red;
        return 0;
    } else if (command == "blue") {
        grid.color = CRGB::Blue;
        return 1;
    } else if (command == "green") {
        grid.color = CRGB::Green;
        return 2;
    } else if (command == "tungsten") {
        grid.color = tungsten;
        return 2;
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
        newIdx = 18*(y+1) - x - 1;
    }

    return newIdx;
}






