#pragma once

#include <iostream>
#include <deque>
#include <vector>
#include <string>

class Obj {
private:
    std::deque<std::string> lines;

public:
    std::deque< std::deque<float> > vertices;
    std::deque< std::deque<float> > normals;
    std::deque< std::deque<float> > texcoords;
    std::deque< std::deque< std::deque<int> > > faces;
    Obj(std::string filename);
    ~Obj();

    void read();
}; 