#include <iostream>
#include <string>
#include "math.h"
using namespace std;

enum Commands {
    ADD,
    SUBSTRACT,
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

Vector substract (Vector v1, Vector v2) {
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

int main() {
    char command;
    cin >> command;

    switch (command) {
    case /* constant-expression */:
        /* code */
        break;
    
    default:
        break;
    }
    
    Vector v1, v2;
    v1.x = 3;
    v1.y = 4;
    v2.x = 1;
    v2.y = 4;
    Vector v = add(v1,v2);
    cout << v.x << " " << v.y << endl;
    v = substract(v,v2);
    cout << v.x << " " << v.y << endl;
    v = normalize(v1);
    cout << v.x << " " << v.y << endl;
}


