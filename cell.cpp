#include "cell.h"
#include <iostream>
#include <stdlib.h>

const double DTDX = 0.05;
const double DTDY = 0.05;

void
Cell::initialize(const Solution &initial, const Cell *north, const Cell *east,
        const Cell *south, const Cell *west) {
    center = initial;
    center.applyFG(centerF, centerG);
    this->north = north;
    this->east = east;
    this->south = south;
    this->west = west;
}

void
Cell::updateMidpoints() {
    if (east)
        ((east->center + center) * 0.5 - (east->centerF - centerF) * 0.5 * DTDX).applyF(rightF);
    else
        rightF = center.edgeF();
    if (north)
        ((north->center + center) * 0.5 - (north->centerG - centerG) * 0.5 * DTDY).applyG(topG);
    else
        topG = center.edgeG();
}

Solution
Cell::updateCenter() {
    Solution bottomG = (south ? south->topG : center.edgeG());
    Solution leftF = (west ? west->rightF : center.edgeF());
    center = center - (rightF - leftF) * DTDX - (topG - bottomG) * DTDY;
    center.scale(1, 0.99); // very mild decay of velocity
    center.applyFG(centerF, centerG);
    return center;
}

void
Cell::copyCenter(Solution &target) const {
    target = center;
}
