#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

enum houseType {
    HOUSE = 1,
    GARAGE,
    BARN,
    BATH,
};

enum roomType {
    BEDROOM = 1,
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
    bool isOvenAvaliable = false;
};

struct Garage {
    int square = 0;
};

struct Barn {
    int square = 0;
};

struct Bath {
    int square = 0;
    bool isOvenAvaliable = false;
};

struct Plot {
    int id = 0;
    vector<House> houses;
    vector<Garage> garages;
    vector<Barn> barns;
    vector<Bath> baths;
};

string getVillageInfo(vector<Plot> plots) {
    string result = "";

    result += "In the village " + to_string(plots.size()) + " plots\n";

    for (int i = 0; i < plots.size(); i++) {

        result += to_string((i + 1))  + " plot has\n" 
        + to_string(plots[i].houses.size()) + " dwelling houses\n"
        + to_string(plots[i].garages.size()) + " garages\n" 
        + to_string(plots[i].barns.size()) + " barns\n" 
        + to_string(plots[i].baths.size()) + " baths\n"; 

        for (int j = 0; j < plots[i].houses.size(); j++) {

            result += "House " 
            + to_string((j + 1)) + " square is " 
            + to_string(plots[i].houses[j].square) + " m2\n";

            if (plots[i].houses[j].isOvenAvaliable) {
                result += "Oven is avaliable\n";
            } else {
                result += "Oven is not avaliable\n";
            }
           
            result += "House " 
            + to_string((j + 1)) + " have " 
            + to_string(plots[i].houses[j].floors.size()) + " floors\n";

            for (int k = 0; k < plots[i].houses[j].floors.size(); k++) {

                result += "Floor " 
                + to_string((k + 1)) + " height is " 
                + to_string(plots[i].houses[j].floors[k].height) + " m\n";

                result += "Floor " 
                + to_string((k + 1)) + " have " 
                + to_string(plots[i].houses[j].floors[k].rooms.size()) + " rooms\n";

                for (int l = 0; l < plots[i].houses[j].floors[k].rooms.size(); l++) {

                    result += "Room " 
                    + to_string((l + 1)) + " square is " 
                    + to_string(plots[i].houses[j].floors[k].rooms[l].square) + " m\n";

                    string roomType;

                    switch (plots[i].houses[j].floors[k].rooms[l].type) 
                    {
                    case roomType::BEDROOM:
                        roomType = " bedroom ";
                        break;
                    case roomType::KITCHEN:
                        roomType = " kitchen ";
                        break;
                    case roomType::CHILDREN_ROOM:
                        roomType = " children room ";
                        break;
                    case roomType::LIVING_ROOM:
                        roomType = " living room ";
                        break;
                    case roomType::BATHROOM:
                        roomType = " bathroom ";
                        break;
                    default:
                        break;
                    }
                    result += "Type - " + roomType + "\n";    
                }
            }
        }

        for (int j = 0; j < plots[i].garages.size(); j++) {

            result += "Garage " + to_string((j + 1)) + " square is "
            + to_string(plots[i].garages[j].square) + " m2\n";
        }

        for (int j = 0; j < plots[i].barns.size(); j++) {

            result += "Barn " + to_string((j + 1)) + " square is " 
            + to_string(plots[i].barns[j].square) + " m2\n";
        }
        
        for (int j = 0; j < plots[i].baths.size(); j++) {

            result += "Bath " + to_string((j + 1)) + " square is " 
            + to_string(plots[i].baths[j].square) + " m2\n";

             if (plots[i].baths[j].isOvenAvaliable) {
                result += "Oven is avaliable\n";
            } else {
                result += "Oven is not avaliable\n";
            }
        }
    }
    return result;
}

int getTotalSquare(Plot plot) {
    int totalSquare = 0;

    for (int i = 0; i < plot.houses.size(); i++) {
        totalSquare += plot.houses[i].square;
    }
    for (int i = 0; i < plot.garages.size(); i++) {
        totalSquare += plot.garages[i].square;
    }
    for (int i = 0; i < plot.barns.size(); i++) {
        totalSquare += plot.barns[i].square;
    }
    for (int i = 0; i < plot.baths.size(); i++) {
        totalSquare += plot.baths[i].square;
    }

    return totalSquare;
}

int main() {
    int plotCount;
    int buildingsCount = 0;
    int floorsCount = 0;
    vector<Plot> plots;
    cout << "Input the number of plots in village\n";
    cin >> plotCount;
    int id = 1;

    for (int i = 0; i < plotCount; ++i) {
        Plot plot;
        plot.id = id;

        cout << "Input the number of buildings in " << plot.id << " plot\n";
        cin >> buildingsCount;

        for (int j = 0; j < buildingsCount; ++j) {
            cout << "Select the type of building, would you like to add:\n"
            << "1. Dwelling house\n" 
            << "2. Garage\n" 
            << "3. Barn\n"
            << "4. Bath\n";

            int answer;
            cin >> answer;
            
            switch (answer) {
                case houseType::HOUSE: {
                    House house;
                    
                    cout << "Input the house square:\n";
                    cin >> house.square;
                    cout << "Is oven available?\n[y|n]\n";
                    char answer;
                    cin >> answer;

                    if (answer == 'y' || answer == 'Y') {
                        house.isOvenAvaliable = true;
                    } else if (answer == 'n' || answer == 'N') {
                        house.isOvenAvaliable = false;
                    }

                    cout << "Input the floors count\n";
                    cin >> floorsCount;
                    
                    for (int k = 0; k < floorsCount; ++k) {
                        
                        Floor floor;
                        
                        cout << "Input the floor " << k + 1 << " height\n";
                        cin >> floor.height;
                        cout << "Input the room count\n";
                        int roomCount;
                        cin >> roomCount;

                        for (int l = 0; l < roomCount; ++l) {

                            Room room;
                            int type;
                            
                            cout << "Input the room " << l + 1 << " square\n";
                            cin >> room.square;
                            cout << "Select the room type\n"
                            << "1. Bedroom\n" 
                            << "2. Kitchen\n"
                            << "3. Bathroom\n" 
                            << "4. Living room\n"
                            << "5. Children room\n";
                            cin >> type;
                            room.type = (roomType)type;

                            floor.rooms.push_back(room);
                        }
                        house.floors.push_back(floor);
                    }
                    plot.houses.push_back(house);
                    break;
                }
                case houseType::GARAGE: {
                    Garage garage;

                    cout << "Input garage square\n";
                    cin >> garage.square;
                    plot.garages.push_back(garage);
                    break;
                }
                case houseType::BARN: {
                    Barn barn;
                    cout << "Input barn square\n";
                    cin >> barn.square;
                    plot.barns.push_back(barn);
                    break;
                }
                case houseType::BATH: {
                    Bath bath;
                    cout << "Input bath square\n";
                    cin  >> bath.square;
                    cout << "Is oven avaliable?\n";

                    char answer;
                    cin >> answer;

                    if (answer == 'y' || answer == 'Y') {
                        bath.isOvenAvaliable = true;
                    } else if (answer == 'n' || answer == 'N') {
                        bath.isOvenAvaliable = false;
                    }

                    plot.baths.push_back(bath);
                    break;
                }
                default:
                    break;
            }
        }
        plots.push_back(plot);
        id++;
    }

    cout << getVillageInfo(plots) << endl;
    
    for (int i = 0; i < plots.size(); i++) {
        cout << "Plot " << i + 1 << " square is " << getTotalSquare(plots[i]) << " m2" << endl;
    }
}

//27.11.2021 11.52 - Укaзать номер комнаты при вводе ее данных - Done