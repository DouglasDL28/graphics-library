#pragma once

struct color {
    color();
    color(unsigned char red, unsigned char green, unsigned char blue);
    unsigned char r, g, b;
};

struct V2 {
    double x, y;
    V2();
    V2(double X, double Y);
};

struct V3 {
    double x, y, z;
    V3();
    V3(double X, double Y, double Z);
};

struct V4 {
    double x, y, z, w;
    V4();
    V4(double X, double Y, double Z, double W);
};