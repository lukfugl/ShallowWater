#ifndef __CELL_H__
#define __CELL_H__

#include "solution.h"

class Cell {
public:
    // setup
    void initialize(const Solution &initial, const Cell *north,
            const Cell *east, const Cell *south, const Cell *west);

    // update methods
    void updateMidpoints();
    Solution updateCenter();

    // access
    void copyCenter(Solution &target) const;

private:
    // neighbors
    const Cell *north;
    const Cell *east;
    const Cell *south;
    const Cell *west;

    // vectors
    Solution center;
    Solution centerF, centerG;
    Solution rightF, topG;
};

#endif // __CELL_H__
