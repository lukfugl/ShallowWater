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
    std::string base(argv[1]);
    Model model(10, 10, base + ".in");

    std::ofstream outfile;
    outfile.open((base + ".out").c_str());
    for (int n = 1; n <= 10; ++n) {
        model.step();
        writeFrame(outfile, 10, 10, model);
    }
    outfile.close();

    return 0;
}
