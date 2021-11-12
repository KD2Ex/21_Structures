#include <iostream>
#include <string>
#include "math.h"
using namespace std;

struct vector {
    double x;
    double y;
    string name;
};

vector add (vector v1, vector v2) {
    vector v;
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    return v;
}

vector substract (vector v1, vector v2) {
    vector v;
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    return v;
}

vector scale (vector v, double c) {
    v.x *= c;
    v.y *= c;
    return v;
}

double length (vector v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

vector normalize (vector v) {
    double l = 1/length(v);
    return scale(v,l);
}

int main() {
    vector v1, v2;
    v1.x = 3;
    v1.y = 4;
    v2.x = 1;
    v2.y = 4;
    vector v = add(v1,v2);
    cout << v.x << " " << v.y << endl;
    v = substract(v,v2);
    cout << v.x << " " << v.y << endl;
    v = normalize(v1);
    cout << v.x << " " << v.y << endl;
}


