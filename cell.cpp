#include "cell.h"
#include <iostream>

static int i = 0, j = 0;

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
    std::cout << "updating midpoints for " << i << ", " << j << std::endl;
    std::cout << "center        : " << center  << std::endl;
    std::cout << "centerF       : " << centerF << std::endl;
    if (east) {
        std::cout << "east->center  : " << east->center  << std::endl;
        std::cout << "east->centerF : " << east->centerF << std::endl;
    }
    else {
        std::cout << "east->center  : " << "none" << std::endl;
        std::cout << "east->centerF : " << "none" << std::endl;
    }
    if (north) {
        std::cout << "north->center : " << north->center  << std::endl;
        std::cout << "north->centerG: " << north->centerG << std::endl;
    }
    else {
        std::cout << "north->center : " << "none" << std::endl;
        std::cout << "north->centerG: " << "none" << std::endl;
    }
    if (east)
        ((center + east->center - (east->centerF - centerF)) * 0.5).applyF(rightF);
    else
        rightF = Solution::edgeF(center.h());
    if (north)
        ((center + north->center - (north->centerG - centerG)) * 0.5).applyG(topG);
    else
        topG = Solution::edgeG(center.h());
    std::cout << "new rightF    : " << rightF << std::endl;
    std::cout << "new topG      : " << topG   << std::endl;
    i = (i + 1) % 10;
    if (i == 0)
        j = (j + 1) % 10;
}

Solution
Cell::updateCenter() {
    std::cout << "updating midpoints for " << i << ", " << j << std::endl;
    std::cout << "center     : " << center  << std::endl;
    std::cout << "topG       : " << topG    << std::endl;
    std::cout << "rightF     : " << rightF  << std::endl;
    Solution bottomG = (south ? south->topG : Solution::edgeG(center.h()));
    std::cout << "bottomG    : " << bottomG << std::endl;
    Solution leftF = (west ? west->rightF : Solution::edgeF(center.h()));
    std::cout << "leftF      : " << leftF   << std::endl;
    center = center + leftF - rightF + bottomG - topG;
    center.applyFG(centerF, centerG);
    std::cout << "new center : " << center  << std::endl;
    std::cout << "new centerF: " << centerF << std::endl;
    std::cout << "new centerG: " << centerG << std::endl;
    i = (i + 1) % 10;
    if (i == 0)
        j = (j + 1) % 10;
    return center;
}

void
Cell::copyCenter(Solution &target) const {
    target = center;
}
