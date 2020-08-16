#include <iostream>
#include <functional>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "Render.h"
#include "../Obj/Obj.h"
#include "../structures/structures.h"

#define LOG(x) std::cout << x << std::endl

Render::Render()
    : width(0), height(0), vp_x(0), vp_y(0), vp_width(0), vp_height(0)
{
    curr_color = color(255, 255, 255);
}

Render::Render(unsigned int width, unsigned int height)
    : width(width), height(height), vp_x(0), vp_y(0), vp_width(width-1), vp_height(height-1)
{
    // BLACK
    curr_color = color(0, 0, 0);

    glCreateWindow(width, height);
};

Render::~Render() {}

void Render::glVertexCoord(unsigned int x, unsigned int y) {
    window[y][x] = curr_color;
}

void Render::glCreateWindow(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
    glClear();
    glViewPort(0, 0, width, height);
}

void Render::glClear() {
    // Assign current color values in matrix
    this->window = new color* [height];
    for (unsigned int y = 0; y < height; y++) {
        window[y] = new color [width];
        for (unsigned int x = 0; x < width; x++) {
            glVertexCoord(x, y);
        }
    }

    // Create zbuffer with negative values
    this->zbuffer = new double* [height];
    for (unsigned int y = 0; y < height; y++) {
        zbuffer[y] = new double [width];
        for (unsigned int x = 0; x < width; x++) {
            zbuffer[y][x] = -100.0;
        }
    }
}

void Render::glClearColor(float r, float g, float b) {

    curr_color.r = (unsigned char) static_cast<int>(b * 255);
    curr_color.g = (unsigned char) static_cast<int>(g * 255);
    curr_color.b = (unsigned char) static_cast<int>(r * 255);

    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            glVertexCoord(x, y);
        }
    }
}

void Render::glColor(float r, float g, float b) {

    curr_color.r = (unsigned char) static_cast<int>(b * 255);
    curr_color.g = (unsigned char) static_cast<int>(g * 255);
    curr_color.b = (unsigned char) static_cast<int>(r * 255);
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
                myfile.write((char*) &window[y][x], 3);
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

    color BLACK = color(0, 0, 0);

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
            int n = memcmp(&BLACK, &window[temp_y][x_val], sizeof(BLACK)); //Check color is BLACK at [temp_y][x]
            bool empty = n == 0;

            if (horizontal) {
                glVertexCoord(temp_x, temp_y);
                break;
            }
            
            if (empty) {
                glVertexCoord(x_val, temp_y);
            } else {
                window[temp_y][x_val].r = 0;
                window[temp_y][x_val].g = 0;
                window[temp_y][x_val].b = 0;
            }
        }

        offset += m;
        if (offset >= limit) {
            y += (y0 < y1) ? 1 : -1;
            limit++;
        }
    }
}

void Render::loadModel(std::string filename, V3 translate, V3 scale, bool isWireframe = false) {
    Obj model = Obj(filename);

    V3 light(0.0, 0.0, 1.0);

    for (auto &&face : model.faces) {
        if (isWireframe) {
            for (int i = 0; i < face.size(); i++) {
                V3 v0 = model.vertices[ face[i][0] - 1 ];
                V3 v1 = model.vertices[ face[(i + 1) % face.size()][0] - 1 ];

                unsigned int x0 = static_cast<int>(v0.x * scale.x + translate.x);
                unsigned int y0 = static_cast<int>(v0.y * scale.y + translate.y);
                unsigned int x1 = static_cast<int>(v1.x * scale.x + translate.x);
                unsigned int y1 = static_cast<int>(v1.y * scale.y + translate.y);

                glLineCoord(x0, y0, x1, y1);
            }
        }
        else {
            V3 v0 = model.vertices[ face[0][0] - 1 ];
            V3 v1 = model.vertices[ face[1][0] - 1 ];
            V3 v2 = model.vertices[ face[2][0] - 1 ];

            V3 t_v0 = transform(v0, translate, scale);
            V3 t_v1 = transform(v1, translate, scale);
            V3 t_v2 = transform(v2, translate, scale);

            V3 normal = cross_product(vert_substract(t_v1, t_v0), vert_substract(t_v2, t_v0));

            normal = normalize(normal);

            double intensity = dot_product(normal, light);
            
            LOG(intensity);

            curr_color = color((char)static_cast<int>(intensity * 255), (char)static_cast<int>(intensity * 255), (char)static_cast<int>(intensity * 255));

            if (intensity >= 0.0)
                triangle_bc(v0, v1, v2);

            if (face.size() > 3) {
                V3 v3 = model.vertices[ face[3][0] - 1 ];
                v3 = transform(v3, translate, scale);

                if (intensity >= 0.0)
                    triangle_bc(v0, v2, v3);
            }
        }
    }
}

void Render::triangle (V3 A, V3 B, V3 C) {
    if (A.y > B.y) {
        std::swap(A.x, B.x);
        std::swap(A.y, B.y);
    }
    if (A.y > C.y) {
        std::swap(A.x, C.x);
        std::swap(A.y, C.y);
    }
    if (B.y > C.y) {
        std::swap(B.x, C.x);
        std::swap(B.y, C.y);
    }
    if (A.y == C.y)
        return;

    if(A.y == B.y)
        flat_bottom_triangle(A, B, C);
    
    else if (B.y == C.y)
        flat_top_triangle(A, B, C);

    else {
        int x4 = static_cast<int>(A.x + (C.x - A.x)/(C.y - A.y) * (B.y - A.y));
        V3 D(x4, B.y, 0.0f);
        flat_bottom_triangle(D, B, C);
        flat_top_triangle(A, B, D);
    }
};

void Render::triangle_bc (V3 A, V3 B, V3 C) {
    int minX = static_cast<int>(std::min(std::min(A.x, B.x), C.x));
    int minY = static_cast<int>(std::min(std::min(A.y, B.y), C.y));
    int maxX = static_cast<int>(std::max(std::max(A.x, B.x), C.x));
    int maxY = static_cast<int>(std::max(std::max(A.y, B.y), C.y));

    for (int y = minY; y < maxY; y++) {
        for (int x = minX; x < maxX; x++) {

            V3 XY(static_cast<double>(x), static_cast<double>(y), 0.0);
            V3 coords = baryCoords(A, B, C, XY);

            double u = coords.x;
            double v = coords.y;
            double w = coords.z;

            if (u >= 0 && v >= 0 && w >= 0) {
                double z = (A.z * u) + (B.z * v) + (C.z * w);

                if (x >= 0 && y >= 0) {
                    if (z > zbuffer[y][x]) {
                        glVertexCoord(x, y);
                        zbuffer[y][x] = z;
                    }
                }
            }
        }
    }
};

V3 Render::baryCoords(V3 A, V3 B, V3 C, V3 P) {
    V3 coords;

    try {
        double u = ( ((B.y - C.y)*(P.x - C.x) + (C.x - B.x)*(P.y - C.y) ) / ((B.y - C.y)*(A.x - C.x) + (C.x - B.x)*(A.y - C.y)) );

        double v = ( ((C.y - A.y)*(P.x - C.x) + (A.x - C.x)*(P.y - C.y) ) / ((B.y - C.y)*(A.x - C.x) + (C.x - B.x)*(A.y - C.y)) );

        double w = 1 - u - v;

        //Asign values to array
        coords.x = u;
        coords.y = v;
        coords.z = w;
    }
    catch(const std::exception& e) {
        coords.x = -1.0;
        coords.y = -1.0;
        coords.z = -1.0;
    }
    
    return coords;
};

V3 Render::transform(V3 vertex, V3 translate, V3 scale) {
    V3 v3;
    v3.x = vertex.x * scale.x + translate.x;
    v3.y = vertex.y * scale.y + translate.y;
    v3.z = vertex.z * scale.z + translate.z;

    return v3;
};

void Render::flat_bottom_triangle (V3 v1, V3 v2, V3 v3) {
    for (int y = static_cast<int>(v1.y); y < static_cast<int>(v3.y); y++) {
        int xi = static_cast<int>(v1.x + (v3.x - v1.x)/(v3.y = v1.y) * (y - v1.y));
        int xf = static_cast<int>(v2.x + (v3.x - v2.x)/(v3.y = v2.y) * (y - v2.y));

        if (xi > xf) {
            int temp_xi = xi;
            xi, xf = xf, temp_xi;
        }

        for (int x = xi; x < xf; x++)
            glVertexCoord(x, y); 
    }
};

void Render::flat_top_triangle (V3 v1, V3 v2, V3 v3) {
    for (int y = static_cast<int>(v1.y); y < static_cast<int>(v3.y); y++) {
        int xi = static_cast<int>(v2.x + (v1.x - v2.x)/(v1.y = v2.y) * (y - v2.y));
        int xf = static_cast<int>(v3.x + (v1.x - v3.x)/(v1.y = v3.y) * (y - v3.y));

        if (xi > xf) {
            int temp_xi = xi;
            xi, xf = xf, temp_xi;
        }

        for (int x = xi; x < xf; x++)
            glVertexCoord(x, y); 
    }
};

V3 Render::vert_substract(V3 v0, V3 v1) {
    V3 result;
    
    result.x = v0.x - v1.x;
    result.y = v0.y - v1.y;
    result.z = v0.z - v1.z;

    return result;
};

V3 Render::cross_product(V3 A, V3 B) {
    V3 result;

    result.x = (A.y * B.z) - (A.z * B.y);
    result.y = (A.x * B.z) - (A.z * B.x);
    result.z = (A.x * B.y) - (A.y * B.x);

    return result;
};

double Render::dot_product(V3 v0, V3 v1) {
    double res = (v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z);
    return res;
};

V3 Render::normalize(V3 v0) {
    V3 normalized;
    double norma = (v0.x * v0.x) + (v0.y * v0.y) + (v0.z * v0.z);
    norma = std::sqrt(norma);

    normalized.x = v0.x / norma;
    normalized.x = v0.y / norma;
    normalized.x = v0.z / norma;

    return normalized;
 };



