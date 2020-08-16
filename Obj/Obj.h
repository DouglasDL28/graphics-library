#pragma once

#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include "../structures/structures.h"
#include "../Render/Render.h"

class Obj {
private:
    std::deque<std::string> lines;

public:
    std::vector<V3> vertices;
    std::vector<std::vector<double> > normals;
    std::vector<std::vector<double> > texcoords;
    std::vector<std::vector< std::vector<int> > > faces;
    Obj(std::string filename);
    ~Obj();

    std::vector<std::string> split(const std::string &s, char delim);

    std::vector<int> split_faces(std::string s, char delim);
};