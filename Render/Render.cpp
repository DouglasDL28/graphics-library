#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Render.h"
#include "../Obj/Obj.h"

#define LOG(x) std::cout << x << std::endl

Render::Render()
    : width(0), height(0), vp_x(0), vp_y(0), vp_width(0), vp_height(0)
{
    // width = 0;
    // height = 0;
    // vp_x = 0;
    // vp_y = 0;
    // vp_width = 0;
    // vp_height = 0;

    curr_color[0] = 255;
    curr_color[1] = 255;
    curr_color[2] = 255;
}

Render::Render(unsigned int width, unsigned int height)
    : width(width), height(height), vp_x(0), vp_y(0), vp_width(width-1), vp_height(height-1)
{
    // this->width = width;
    // this->height = height;
    // vp_x = 0;
    // vp_y = 0;
    // vp_width = 0;
    // vp_height = 0;

    // BLACK
    curr_color[0] = 0;
    curr_color[1] = 0;
    curr_color[2] = 0;
};

Render::~Render() {}

void Render::glVertexCoord(unsigned int x, unsigned int y) {
    window[y][x][0] = curr_color[0];
    window[y][x][1] = curr_color[1];
    window[y][x][2] = curr_color[2];
}

void Render::glCreateWindow(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;

    // Assign current color values in matrix
    this->window = new unsigned char** [height];
    for (unsigned int y = 0; y < height; y++) {
        window[y] = new unsigned char* [width];
        for (unsigned int x = 0; x < width; x++) {
            window[y][x] = new unsigned char [3];          
            glVertexCoord(x, y);
        }
    }
}

void Render::glClear() {
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            glVertexCoord(x, y);
        }  
    }
}

void Render::glClearColor(float r, float g, float b) {

    curr_color[0] = (unsigned char) static_cast<int>(b * 255);
    curr_color[1] = (unsigned char) static_cast<int>(g * 255);
    curr_color[2] = (unsigned char) static_cast<int>(r * 255);

    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            glVertexCoord(x, y);
        }
    }
}

void Render::glColor(float r, float g, float b) {

    curr_color[0] = (unsigned char) static_cast<int>(b * 255);
    curr_color[1] = (unsigned char) static_cast<int>(g * 255);
    curr_color[2] = (unsigned char) static_cast<int>(r * 255);
}

void Render::glVertex(float x, float y) {

    unsigned int temp_x = static_cast<int>(((x + 1) * vp_width / 2) + vp_x);
    unsigned int temp_y = static_cast<int>(((y + 1) * vp_height / 2) + vp_y);

    glVertexCoord(temp_x, temp_y);
}

void Render::glViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {

    if (x > this->width) {
        vp_x = this->width;
    } else {
        vp_x = x;
    }

    if (y > this->height) {
        vp_y = this->height;
    } else {
        vp_y = y;
    }

    /* Defining viewport width */
    if ((x + width) >= this->width) {
        vp_width = this->width - x - 1;
    }
    else {
        vp_width = width;
    }
    /* Defining viewport height */
    if ((y + height) >= this->height) {
        vp_height = this->height - y - 1;
    }
    else {
        vp_height = height;
    }  
}

void Render::glFinish() {
    LOG("Empezando escritura...");
    std::ofstream myfile;

    char B = 'B';
    char M = 'M';
    unsigned short int one = 1;
    unsigned short int word = 0;
    unsigned int dword = 0;
    unsigned int twenty_four = 24;
    unsigned int fourty = 40;
    unsigned int data_offset = 14 + 40;
    unsigned int file_size = 14 + 40 + width * height * 3;
    unsigned int pixels =  width * height * 3;


    myfile.open("image.bmp", std::ios::out | std::ios::binary | std::ios::trunc);

    if(myfile.is_open()) {
        //BITMAP FILE HEADER (14 bytes)
        myfile.write((char*) &B, sizeof(char));
        myfile.write((char*) &M, sizeof(char));
        myfile.write((char*) &file_size, sizeof(unsigned int));
        myfile.write((char*) &word, sizeof(unsigned short int));
        myfile.write((char*) &word, sizeof(unsigned short int));
        myfile.write((char*) &data_offset, sizeof(unsigned int));

        // TODO: BITMAPINFOHEADER
        myfile.write( (char*) &fourty, sizeof(unsigned int));
        myfile.write( (char*) &width, sizeof(unsigned int));
        myfile.write( (char*) &height, sizeof(unsigned int));
        myfile.write( (char*) &one, sizeof(unsigned short int));
        myfile.write( (char*) &twenty_four, sizeof(unsigned short int));
        myfile.write( (char*) &dword, sizeof(unsigned int));
        myfile.write( (char*) &pixels, sizeof(unsigned int));
        myfile.write( (char*) &dword, sizeof(unsigned int));
        myfile.write( (char*) &dword, sizeof(unsigned int));
        myfile.write( (char*) &dword, sizeof(unsigned int));
        myfile.write( (char*) &dword, sizeof(unsigned int));

        // TODO: PIXEL DATA
        for (unsigned int y = 0; y < height; y++) {
            for (unsigned int x = 0; x < width; x++) {
                myfile.write((char*) window[y][x], 3);
            }
        }    
    }

    myfile.close();
    LOG("Escritura de image.bmp terminada");
}

void Render::glLine(float x0, float y0, float x1, float y1) {

    unsigned int x0_ = static_cast<int>(((x0 + 1) * vp_width / 2) + vp_x);
    unsigned int x1_ = static_cast<int>(((x1 + 1) * vp_width / 2) + vp_x);
    unsigned int y0_ = static_cast<int>(((y0 + 1) * vp_height / 2) + vp_y);
    unsigned int y1_ = static_cast<int>(((y1 + 1) * vp_height / 2) + vp_y);

    unsigned int dx = std::abs(static_cast<int>(x1_ - x0_));
    unsigned int dy = std::abs(static_cast<int>(y1_ - y0_));

    bool steep = dy > dx;

    if (steep) {
        unsigned int temp_x0 = x0_;
        x0_ = y0_;
        y0_ = temp_x0;
        unsigned int temp_x1 = x1_;
        x1_ = y1_;
        y1_ = temp_x1;
    }

    if (x0_ > x1_) {
        unsigned int temp_x0 = x0_;
        x0_ = x1_;
        x1_ = temp_x0;
        unsigned int temp_y0 = y0_;
        y0_ = y1_;
        y1_ = temp_y0;
    }

    dx = std::abs(static_cast<int>(x1_ - x0_));
    dy = std::abs(static_cast<int>(y1_ - y0_));
    
    float offset = 0;
    float limit = 0.5f;

    float m = (float) dy / (float) dx;
    unsigned int y = y0_;

    for (unsigned int x = x0_; x <= x1_; x++) {
        if (steep)
            glVertexCoord(y, x);
        else
            glVertexCoord(x, y);

        offset += m;
        if (offset >= limit) {
            y += (y0_ < y1_) ? 1 : -1;
            limit++;
        } 
    }
}

void Render::glLineCoord(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1) {
    unsigned int dx = std::abs(static_cast<int>(x1 - x0));
    unsigned int dy = std::abs(static_cast<int>(y1 - y0));

    bool steep = dy > dx;

    if (steep) {
        unsigned int temp_x0 = x0;
        x0 = y0;
        y0 = temp_x0;
        unsigned int temp_x1 = x1;
        x1 = y1;
        y1 = temp_x1;
    }

    if (x0 > x1) {
        unsigned int temp_x0 = x0;
        x0 = x1;
        x1 = temp_x0;
        unsigned int temp_y0 = y0;
        y0 = y1;
        y1 = temp_y0;
    }

    dx = std::abs(static_cast<int>(x1 - x0));
    dy = std::abs(static_cast<int>(y1 - y0));

    float offset = 0;
    float limit = 0.5f;

    float m = (float) dy / (float) dx;
    unsigned int y = y0;

    for (unsigned int x = x0; x <= x1; x++) {
        if (steep)
            glVertexCoord(y, x);
        else
            glVertexCoord(x, y);

        offset += m;
        if (offset >= limit) {
            y += (y0 < y1) ? 1 : -1;
            limit++;
        } 
    }
}

void Render::drawPoly (unsigned int points[][2], int& points_len){
    for (unsigned int i = 0; i < points_len; i++) {
        unsigned int* v0 = points[i];
        unsigned int* v1 = points[(i + 1) % points_len];

        integralPaint(v0[0], v0[1], v1[0], v1[1]);
    }
}

void Render::integralPaint(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1) {
    unsigned int dx = std::abs(static_cast<int>(x1 - x0));
    unsigned int dy = std::abs(static_cast<int>(y1 - y0));

    unsigned int BLACK[3] = {0, 0, 0};

    bool steep = dy > dx;

    if (steep) {
        unsigned int temp_x0 = x0;
        x0 = y0;
        y0 = temp_x0;
        unsigned int temp_x1 = x1;
        x1 = y1;
        y1 = temp_x1;
    }

    if (x0 > x1) {
        unsigned int temp_x0 = x0;
        x0 = x1;
        x1 = temp_x0;
        unsigned int temp_y0 = y0;
        y0 = y1;
        y1 = temp_y0;
    }

    dx = std::abs(static_cast<int>(x1 - x0));
    dy = std::abs(static_cast<int>(y1 - y0));

    float offset = 0;
    float limit = 0.5f;

    float m = (float) dy / (float) dx;
    unsigned int y = y0;

    unsigned int prev_x;
    unsigned int prev_y;

    for (unsigned int x = x0; x <= x1; x++) {
        bool horizontal = false;
        unsigned int temp_x = x;
        unsigned int temp_y = y;

        if (steep) {
            temp_x = y;
            temp_y = x;
        }

        if (x > x0) {
            if (prev_y == temp_y && prev_x == (temp_x-1))
                horizontal = true;
        }
        prev_x = temp_x;
        prev_y = temp_y;

        /* In case there is no color in coord we paint, else we return the color to default (BLACK) */
        for (int x_val = temp_x; x_val >= 0; x_val--) {
            int n = memcmp(BLACK, window[temp_y][x_val], sizeof(BLACK)); //Check color is BLACK at [temp_y][x]
            bool empty = n == 0;

            if (horizontal) {
                glVertexCoord(temp_x, temp_y);
                break;
            }
            
            if (empty) {
                glVertexCoord(x_val, temp_y);
            } else {
                window[temp_y][x_val][0] = 0;
                window[temp_y][x_val][1] = 0;
                window[temp_y][x_val][2] = 0;
            }
        }

        offset += m;
        if (offset >= limit) {
            y += (y0 < y1) ? 1 : -1;
            limit++;
        }
    }
}

void Render::loadModel(std::string filename, int translate[2], int scale[2]) {
    Obj model = Obj(filename);

    for (auto &&face : model.faces) {
        for (int i = 0; i < face.size(); i++) {
                std::deque<float> v0 = model.vertices[ face[i][0] - 1 ];
                std::deque<float> v1 = model.vertices[ face[(i + 1) % face.size()][0] - 1 ];

                unsigned int x0 = static_cast<int>(v0[0] * scale[0] + translate[0]);
                unsigned int y0 = static_cast<int>(v0[1] * scale[1] + translate[1]);
                unsigned int x1 = static_cast<int>(v1[0] * scale[0] + translate[0]);
                unsigned int y1 = static_cast<int>(v1[1] * scale[1] + translate[1]);

                glLineCoord(x0, y0, x1, y1);
        }
    }
}