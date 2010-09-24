#include "model.h"
#include <iostream>
#include <fstream>

void
writeFrame(std::ofstream &file, int width, int height, const Model &model) {
    file << "---" << std::endl;
    int i, j, n = 0;
    for (j = 0; j < height; ++j) {
        for (i = 0; i < width; ++i, ++n)
            file << model[n].h() << " ";
        file << std::endl;
    }
}

int
oldmain(int argc, char **argv) {
}
