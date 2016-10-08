// sketch for controlling an RGB LED


// pins
int r = D0;
int g = D1;
int b = D2;

// array of pins
int leds[3] = {r, g, b};

// set these based on whether RGB is common-sink or common-source
bool on = LOW;
bool off = HIGH;

// define color arrays
bool red[3] = {on, off, off};
bool yellow[3] = {on, on, off};
bool green[3] = {off, on, off};
bool cyan[3] = {off, on, on};
bool blue[3] = {off, off, on};
bool magenta[3] = {on, off, on};

bool white[3] = {on, on, on};
bool black[3] = {off, off, off};

void setup() {

    // set pins to output
    pinMode(r, OUTPUT);
    pinMode(g, OUTPUT);
    pinMode(b, OUTPUT);

    // register changeColor function with 'cc' endpoint
    Particle.function("set-color", setColor);

    // start LED off
    updateLED(black);
}

void loop() {

}

void updateLED(bool* color) {

    for (int i=0; i<3; i++) {
        digitalWrite(leds[i], color[i]);
    }
}

int setColor(String command) {

    if (command == "red") {
        updateLED(red);
        return 0;
    } else if (command == "yellow") {
        updateLED(yellow);
        return 1;
    } else if (command == "green") {
        updateLED(green);
        return 2;
    } else if (command == "cyan") {
        updateLED(cyan);
        return 3;
    } else if (command == "blue") {
        updateLED(blue);
        return 4;
    } else if (command == "magenta") {
        updateLED(magenta);
        return 5;
    }
    else {
        return -1;
    }
}

