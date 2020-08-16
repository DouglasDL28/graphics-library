#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <deque>
#include "Obj.h"

#define LOG(x) std::cout << x << std::endl

Obj::Obj(std::string filename) {
    std::ifstream file(filename);
    std::string line;

    // Get all lines into the deque
    while(std::getline(file, line))
        lines.push_back(line);

    // Split lines in words.
    for (auto &&line: lines) {
        std::deque<std::string> curr_line;
        std::string word = "";

        for (auto &&x: line) {
            if (line.at(0) == '#')
                break;
            if (x == ' ') {
                curr_line.push_back(word);
                word = "";
            }
            else
                word += x;
        }

        if (!curr_line.empty()) {
            std::string prefix = curr_line.front();
            curr_line.pop_front();

            if (prefix == "v") {
                std::deque<float> vertex;
                for (auto &&word: curr_line) 
                    vertex.push_back(std::stof(word));

                vertices.push_back(vertex);

            } else if (prefix == "vn") {
                std::deque<float> normal;
                for (auto &&word: curr_line)
                    normal.push_back(std::stof(word));

                normals.push_back(normal);

            } else if (prefix == "vt") {
                std::deque<float> texture;
                for (auto &&word: curr_line)
                    texture.push_back(std::stof(word));

                texcoords.push_back(texture);

            } else if (prefix == "f") {
                std::deque< std::deque<int> > face;
                for (auto &&word: curr_line) {
                    std::deque<int> vals;
                    std::string str = "";

                    for (auto &&x: word) {
                        if (x == '/') {
                            vals.push_back(std::stoi(str));
                            str = "";
                        }
                        else
                            str += x;
                    }
                    face.push_back(vals);
                }
                faces.push_back(face);
            }
        }
    }

    file.close();
}

Obj::~Obj() {}

void Obj::read() {}