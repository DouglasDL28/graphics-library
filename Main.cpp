#include <iostream>
#include <string>
#include "Render/Render.h"
#include "Obj/Obj.h"

#define LOG(x) std::cout << x << std::endl

int main(int argc, char const *argv[]) {
    Render r;
    r.glCreateWindow(1000, 500);
    r.glClear();
    r.glClearColor(0.0f, 0.0f, 0.0f);

    r.glColor(1.0f, 0.0f, 1.0f);

    // int translate[2] = {500,150};
    // int scale[2] = {30,30};
    // r.loadModel("Stone.obj", translate, scale);

    /* Poly 1 */
    unsigned int poly1 [][2] = {
        {165, 380}, {185, 360},
        {180, 330}, {207, 345},
        {233, 330}, {230, 360},
        {250, 380}, {220, 385},
        {205, 410}, {193, 383}
        };
    int poly1_len = sizeof(poly1) / sizeof(poly1[0]);
    r.drawPoly(poly1, poly1_len);

    /* Poly 2 */
    unsigned int poly2[][2] = {
        {321, 335}, {288, 286},
        {339, 251}, {374, 302},
    };
    int poly2_len = sizeof(poly2) / sizeof(poly2[0]);
    r.drawPoly(poly2, poly2_len);

    /* Poly 3 */
    unsigned int poly3[][2] = {{377, 249}, {411, 197}, {436, 249}};
    int poly3_len = sizeof(poly3) / sizeof(poly3[0]);
    r.drawPoly(poly3, poly3_len);

    /* Poly 4 */
    unsigned int poly4[][2] = {
        {413, 177}, {448, 159},
        {502, 88}, {553, 53},
        {535, 36}, {676, 37},
        {660, 52}, {750, 145},
        {761, 179}, {672, 192},
        {659, 214}, {615, 214},
        {632, 230}, {580, 230},
        {597, 215}, {552, 214},
        {517, 144}, {466, 180}
        };
    int poly4_len = sizeof(poly4) / sizeof(poly4[0]);
    r.drawPoly(poly4, poly4_len);

    /* Poly 5 */
    unsigned int poly5[][2] = {
        {682, 175}, {708, 120},
        {735, 148}, {739, 170}
        };
    int poly5_len = sizeof(poly5) / sizeof(poly5[0]);
    r.drawPoly(poly5, poly5_len);

    r.glFinish();


    std::cout << "Presionar Enter para terminar programa.";
    std::cin.get();

    return 0;
}