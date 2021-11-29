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

string getVectorInfo (Vector vec) {
    return vec.name + "\nx: " + to_string(vec.x) + "\ny: " + to_string(vec.y);
}

int main() {
    int inputCommand;
    Vector v1, v2, vecResult;
    double vecLength = 0;

    cout << "Input the number of operation:\n"
    << "1. Add\n"
    << "2. Subtract\n"
    << "3. Scale\n"
    << "4. Length\n"
    << "5. Normalize\n";
    cin >> inputCommand;

    switch (inputCommand) {
        case Commands::ADD:
            cout << "Enter the name of the first vector:\n";
            cin >> v1.name;
            cout << "Enter the coordinates of the first vector:\n";
            cin >> v1.x >> v1.y;

            cout << "Enter the name of the second vector:\n";
            cin >> v2.name;
            cout << "Enter the coordinates of the second vector:\n";
            cin >> v2.x >> v2.y;

            vecResult = add(v1, v2);
            vecResult.name = v1.name + " + " + v2.name;

            cout << "Result vector:\n" << getVectorInfo(vecResult);
            break;
        case Commands::LENGTH:
            cout << "Enter the name of the vector:\n";
            cin >> v1.name;
            cout << "Enter the coordinates of the vector:\n";
            cin >> v1.x >> v1.y;

            vecLength = length(v1);

            cout << v1.name << " length is: " << vecLength;
            break;
        case Commands::SUBTRACT:
            cout << "Enter the name of the first vector:\n";
            cin >> v1.name;
            cout << "Enter the coordinates of the first vector:\n";
            cin >> v1.x >> v1.y;

            cout << "Enter the name of the second vector:\n";
            cin >> v2.name;
            cout << "Enter the coordinates of the second vector:\n";
            cin >> v2.x >> v2.y;

            vecResult = subtract(v1, v2);
            vecResult.name = v1.name + " - " + v2.name;
            cout << "Result vector:\n" << getVectorInfo(vecResult);
            break;
        case Commands::SCALE:
            double number;
            cout << "Enter the name of the vector:\n";
            cin >> v1.name;
            cout << "Enter the coordinates of the vector:\n";
            cin >> v1.x >> v1.y;
            cout << "Enter the number by which you want to multiply the vector:\n";
            cin >> number;

            vecResult = scale(v1, number);
            vecResult.name = v1.name;
            cout << "Result vector:\n " << getVectorInfo(vecResult);
            break;
        case Commands::NORMALIZE:
            cout << "Enter the name of the vector:\n";
            cin >> v1.name;
            cout << "Enter the coordinates of the vector:\n";
            cin >> v1.x >> v1.y;
            vecResult = normalize(v1);
            vecResult.name = v1.name;
            cout << "Result vector:\n " << getVectorInfo(vecResult);
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


