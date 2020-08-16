#include <iostream>
#include <string>
#include "Render/Render.h"
#include "structures/structures.h"
#include "Obj/Obj.h"

#define LOG(x) std::cout << x << std::endl

int main(int argc, char const *argv[]) {
    Render r(1000, 500);
    r.glClear();
    r.glClearColor(0.0f, 0.0f, 0.0f);

    r.glColor(1.0f, 0.0f, 1.0f);

    V3 translate(500.0, 100.0, 0.0);
    V3 scale(40.0, 40.0, 0.0);
    r.loadModel("Stone.obj", translate, scale, true);

    r.glFinish();


    std::cout << "Presionar Enter para terminar programa.";
    std::cin.get();

    return 0;
}
