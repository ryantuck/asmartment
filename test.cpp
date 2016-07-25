#import <iostream>
using namespace std;

#include <unistd.h>

int getNeighbor(int currentIdx);

int main() {

    int idx = 0;

    while (true) {

        int newIdx = getNeighbor(idx);

        cout << "--------------\n";
        idx = newIdx;
        sleep(1);
    }

    return 0;
}

int getNeighbor(int currentIdx) {

    // 0 bottom left
    // 323 top left

    int width = 18;
    int height = 18;

    cout << "current idx: " << currentIdx << "\n";

    // get x and y from the given idx
    int y = currentIdx / 18;
    int x;
    if (y % 2 == 0) {
        x = currentIdx % 18;
    } else {
        x = 18 - currentIdx % 18;
    }

    cout << "x/y: " << x << " / " << y << "\n";

    bool up = true;
    bool down = true;
    bool left = true;
    bool right = true;


    if (x == 0) { left = false; }
    if (x == 17) { right = false; }
    if (y == 0) { down = false; }
    if (y == 17) { up = false; }

    cout << "bools: ";
    cout << up << down << left << right;
    cout << "\n";

    bool dirs[4] = {up, down, left, right};

    // pick a random direction that's allowed
    bool dirFound = false;
    int dirIdx;
    while (!dirFound) {
        dirIdx = rand() % 4;
        bool newDir = dirs[dirIdx];
        if (newDir) { dirFound = true; }
    }

    cout << "dir idx: " << dirIdx << "\n";

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

    cout << "new idx: " << newIdx << "\n";

    return newIdx;
}

