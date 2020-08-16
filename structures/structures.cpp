#include "structures.h"

color::color(){};

color::color(unsigned char red, unsigned char green, unsigned char blue) : r(red), g(green), b(blue) {};

V2::V2() {};

V2::V2(double X, double Y) : x(X), y(Y) {};

V3::V3() {};

V3::V3(double X, double Y, double Z) : x(X), y(Y), z(Z) {};

V4::V4() {};

V4::V4(double X, double Y, double Z, double W) : x(X), y(Y), z(Z), w(W) {};