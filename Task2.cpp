#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


enum houseType{
    HOUSE,
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

struct Room {
    int square = 0;
    roomType type;
};

struct Floor {
    int height = 0;
    vector<Room> rooms;
};

struct House {
    int square = 0;
    vector<Floor> floors;
    bool oven = false;
};

struct Garage {
    int square = 0;
};

struct Barn {
    int square = 0;
};

struct Bath {
    int square = 0;
    bool oven = false;
};

struct Plot {
    int id = 0;
    House house;
    Garage garage;
    Barn barn;
    Bath bath;
};

int main() {
    int plotCount;
    int buildingsCount = 0;
    int floorsCount = 0;
    cin >> plotCount;
    vector<Plot> plots;
    for (int i = 0; i < plotCount; ++i) {
        Plot plot;
        plot.id++;
        cin >> buildingsCount;
        for (int j = 0; j < buildingsCount; ++j) {
            char answer;
            cin >> answer;
            switch (answer) {
                case HOUSE:
                    cin >> plot.house.square;
                    cin >> answer;
                    if (answer == 'y' || answer == 'Y') {
                        plot.house.oven = true;
                    } else if (answer == 'n' || answer == 'N') {
                        plot.house.oven = false;
                    }
                    cin >> floorsCount;
                    for (int k = 0; k < floorsCount; ++k) {
                        Floor floor;
                        cin >> floor.height;
                        int roomCount;
                        cin >> roomCount;
                        for (int l = 0; l < roomCount; ++l) {

                        }
                        plot.house.floors.push_back(floor);
                    }
                    break;
                case GARAGE:
                    break;
                case BARN:
                    break;
                case BATH:
                    break;
                default:
                    break;
            }
        }
        plots.push_back(plot);
    }
}