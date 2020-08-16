#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <deque>
#include <vector>
#include "../structures/structures.h"
#include "Obj.h"
#include "../Render/Render.h"

#define LOG(x) std::cout << x << std::endl

std::vector<std::string> Obj::split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (std::getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

std::vector<int> Obj::split_faces(std::string s, char delim) {
    std::vector<int> result;
    std::string item = "";


    for ( std::string::iterator it=s.begin(); it!=s.end(); ++it) {
        if (*it == delim) {
            try {
                int token = std::stoi(item);
                result.push_back(token);
                item = "";
            }
            catch(std::invalid_argument& e){
            // if no conversion could be performed
                item = "";
            }
        }
        else {
            item += *it;
        }
    }

    try {
        int token = std::stoi(item);
        result.push_back(token);
    }
    catch(std::invalid_argument& e){
    // if no conversion could be performed
    }
    return result;
}

Obj::Obj(std::string filename) {
    std::ifstream file(filename);
    std::string line;
    
    // Get all lines into the deque
    while(std::getline(file, line))
        lines.push_back(line);

    file.close();

    // Split lines in words.
    for (auto &&line: lines) {
        //Separating line into words.
        std::deque<std::string> curr_line;
        std::stringstream ss (line);
        std::string item;

        while (std::getline (ss, item, ' ')) {
            curr_line.push_back (item);
        }

        // Add to structure depending on line prefix.
        if (!curr_line.empty()) {
            std::string prefix = curr_line.front();
            curr_line.pop_front();

            // Vertices
            if (prefix == "v") {
                std::vector<double> vertex;

                for (auto &&word: curr_line) {
                    vertex.push_back(std::stod(word));
                }
                V3 vert;
                if (vertex.size() == 3) {
                    vert.x = vertex[0];
                    vert.y = vertex[1];
                    vert.z = vertex[2];
                }
                else {
                    vert.x = vertex[0];
                    vert.y = vertex[1];
                    vert.z = 0.0;
                }
                vertices.push_back(vert);

            // Normals
            } else if (prefix == "vn") {
                std::vector<double> normal;
                for (auto &&word: curr_line)
                    normal.push_back(std::stod(word));

                normals.push_back(normal);

            // Textures
            } else if (prefix == "vt") {
                std::vector<double> texture;
                for (auto &&word: curr_line)
                    texture.push_back(std::stod(word));

                texcoords.push_back(texture);

            //Faces
            } else if (prefix == "f") {
                std::vector<std::vector<int> > face;
                for (auto &&word: curr_line) {
                    std::vector<int> vals = split_faces(word, '/');
                    face.push_back(vals);
                }

                faces.push_back(face);
                
            }
        }
    }
}

Obj::~Obj() {}
