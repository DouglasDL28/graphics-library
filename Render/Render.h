#pragma once
#include "../structures/structures.h"

class Render {
private:
    unsigned int width, height;
    unsigned int vp_x, vp_y;
    unsigned int vp_width, vp_height;
    color curr_color;
    color **window;
    double **zbuffer;

public:
    Render();
    Render(unsigned int width, unsigned int height);
    ~Render();

    void glInit();

    /* Color pixel in given x and y values with the current color. */
    void glVertexCoord(unsigned int x, unsigned int y);

    /* Initialice window and zbuffer */
    void glCreateWindow(unsigned int width, unsigned int height);
    
    /* Clear window and zbuffer to default values */
    void glClear();

    /* Clear window with new current color */
    void glClearColor(float r, float g, float b);

    /* Assign new value for current color */
    void glColor(float r, float g, float b);

    /* Draw a pixel (x, y) in the window */
    void glVertex(float x, float y);

    /* Define view port on window */
    void glViewPort(unsigned int x,unsigned int y, unsigned int width, unsigned int height);
    
    /* Write window data to .bmp file */
    void glFinish();

    /* Draw a line (current color) in window w/ NDC coords */
    void glLine(float x0, float y0, float x1, float y1);

    /* Draw a line (current color) in window w/o NDC coords */
    void glLineCoord(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1);

    /* Draw a polygon (current color) in window */
    void drawPoly(unsigned int points[][2], int& points_len);

    /* Paint polygon (current color) w/ integral-like method */
    void integralPaint(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1);

    /* Load an .obj model (w/ wireframe) */
    void loadModel(std::string filename, V3 translate, V3 scale, bool isWireframe);
    
    /* Draws a triangle */
    void triangle (V3 A, V3 B, V3 C);
    
    /* Draws a triangle with bary_coords */
    void triangle_bc (V3 A, V3 B, V3 C);

    /* Obtain baryCoods u, v, w from triangle */
    V3 baryCoords(V3 A, V3 B, V3 C, V3 P);

    /* Transform vertex with scale and translate */
    V3 transform(V3 vertex, V3 translate, V3 scale);

    /* Draw a flat bottom triangle (should be lambda in triangle func) */
    void flat_bottom_triangle (V3 v1, V3 v2, V3 v3);

    /* Draw a flat top triangle (should be lambda in triangle func) */
    void flat_top_triangle (V3 v1, V3 v2, V3 v3);

    /* Should be in math library */
    V3 vert_substract(V3 v0, V3 v1);

    /* Should be in math library */
    V3 cross_product(V3 v0, V3 v1);

    /* Should be in math library */
    double dot_product(V3 v0, V3 v1);

    V3 normalize(V3 v0);
};
