#include "model.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>

Model::Model(int width, int height, std::string filename) {
    count = width * height;
    cells = new Cell[count];
    solutions = new Solution[count];
    Cell *north, *east, *south, *west;
    std::ifstream file;
    file.open(filename.c_str());
    int i, j, n = 0;
    double h;
    for (j = 0; j < height; ++j) {
        for (i = 0; i < width; ++i, ++n) {
            file >> h;
            solutions[n] = Solution(h, 0, 0);
            north = (j == height-1 ? NULL : &cells[n+width]);
            east = (i == width-1 ? NULL : &cells[n+1]);
            south = (j == 0 ? NULL : &cells[n-width]);
            west = (i == 0 ? NULL : &cells[n-1]);
            cells[n].initialize(solutions[n], north, east, south, west);
        }
    }
    file.close();
}

Model::~Model() {
    delete[] cells;
    delete[] solutions;
}

void
Model::step() {
    // first half: update midpoints
    for (int n = 0; n < count; ++n)
        cells[n].updateMidpoints();
    // second half: update centers and read them off
    for (int n = 0; n < count; ++n)
        solutions[n] = cells[n].updateCenter();
}

const Solution &Model::operator[](int n) const {
    return solutions[n];
}
