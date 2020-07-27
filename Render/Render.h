#pragma once

class Render {
private:
    unsigned int width, height;
    unsigned int vp_x, vp_y;
    unsigned int vp_width, vp_height;
    unsigned char curr_color [3];
    unsigned char ***window;

public:
    Render();
    Render(unsigned int width, unsigned int height);
    ~Render();

    void glInit(); 
    void glVertexCoord(unsigned int x, unsigned int y);
    void glCreateWindow(unsigned int width, unsigned int height);
    void glClear();
    void glClearColor(float r, float g, float b);
    void glVertex(float x, float y);
    void glViewPort(unsigned int x,unsigned int y, unsigned int width, unsigned int height);
    void glColor(float r, float g, float b);
    void glFinish();
    //Bressenham Line Algorith
    void glLine(float x0, float y0, float x1, float y1);
    void glLineCoord(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1);
    void drawPoly(unsigned int points[][2], int& points_len);
    void integralPaint(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1);
    void loadModel(std::string filename, int translate[2], int scale[2]);
};
