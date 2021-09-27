#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

enum houseType{
    DWELLING_HOUSE,
    GARAGE,
    BARN,
    BATH,
};

enum roomType {
    BEDROOM,
    KITCHEN,
    BATHROOM,
    LIVING_ROOM,
    CHILDREN_ROOM,
};

struct room {
    roomType type;
    int square = 0;
};

struct level {
    int height = 0;
    room rooms[4];
};

struct house {
    houseType type;
    int square = 0;
    level levels[3];
    bool oven = false;
};

struct plot {
    int id = 0;
    vector<house> houses;
};


int main() {
    plot plot;

    int plotCount;
    cin >> plotCount;
    for (int i = 0; i < plotCount; ++i) {
        plot.id++;
        int houseCount;
        cin >> houseCount;
        for (int j = 0; j < houseCount; ++j) {

        }
    }

}