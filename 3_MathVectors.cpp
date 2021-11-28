#include <iostream>
#include <string>
#include "math.h"
using namespace std;

enum Commands {
    ADD = 1,
    SUBTRACT,
    SCALE,
    LENGTH,
    NORMALIZE
};

struct Vector {
    double x;
    double y;
    string name;
};

Vector add (Vector v1, Vector v2) {
    Vector v;
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    return v;
}

Vector subtract (Vector v1, Vector v2) {
    Vector v;
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    return v;
}

Vector scale (Vector v, double c) {
    v.x *= c;
    v.y *= c;
    return v;
}

double length (Vector v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

Vector normalize (Vector v) {
    double l = 1/length(v);
    return scale(v,l);
}

string printVectorInfo (Vector vec) {
    return vec.name + "\nx: " + vec.x + "\ny:" + vec.y;
}

int main() {
    int command;
    Vector v1, v2, vecResult;
    double vecLength = 0;

    cout << "Input the number of operation:\n"
    << "1. Add\n"
    << "2. Subtract\n"
    << "3. Scale\n"
    << "4. Length\n"
    << "5. Normalize\n";
    cin >> command;

    switch (command) {
        case Commands::ADD:
            cout << "Input the coordinates of ";
            cin >> v1.x >> v1.y >> v2.x >> v2.y;
            vecResult = add(v1, v2);
            vecResult.name = "v1 + v2";
            cout << "Result vector:\n" << printVectorInfo(vecResult);
            break;
        case Commands::LENGTH:
            cin >> v1.x >> v1.y;
            vecLength = length(v1);
            cout << "Vector length is: " << vecLength;
            break;
        case Commands::SUBTRACT:
            cin >> v1.x >> v1.y >> v2.x >> v2.y;
            vecResult = subtract(v1, v2);
            vecResult.name = "v1 - v2";
            cout << "Result vector:\n" << printVectorInfo(vecResult);
            break;
        case Commands::SCALE:
            double number;
            cin >> v1.x >> v1.y >> number;
            vecResult = scale(v1, number);
            cout << "Result vector:\n " << printVectorInfo(vecResult);
            break;
        case Commands::NORMALIZE:
            cin >> v1.x >> v1.y;
            vecResult = normalize(v1);
            cout << "Result vector:\n " << printVectorInfo(vecResult);
            break;
        default:
            cout << "Wrong operation";
            break;
    }
//
//    Vector v1, v2;
//    v1.x = 3;
//    v1.y = 4;
//    v2.x = 1;
//    v2.y = 4;
//    Vector v = add(v1,v2);
//    cout << v.x << " " << v.y << endl;
//    v = substract(v,v2);
//    cout << v.x << " " << v.y << endl;
//    v = normalize(v1);
//    cout << v.x << " " << v.y << endl;
}


