#include "cell.h"
#include <iostream>

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
        ((center + east->center - (east->centerF - centerF)) * 0.5).applyF(rightF);
    else
        rightF = Solution::edgeF(center.h());
    if (north)
        ((center + north->center - (north->centerG - centerG)) * 0.5).applyG(topG);
    else
        topG = Solution::edgeG(center.h());
}

Solution
Cell::updateCenter() {
    Solution bottomG = (south ? south->topG : Solution::edgeG(center.h()));
    Solution leftF = (west ? west->rightF : Solution::edgeF(center.h()));
    center = center + leftF - rightF + bottomG - topG;
    center.applyFG(centerF, centerG);
    return center;
}

void
Cell::copyCenter(Solution &target) const {
    target = center;
}
