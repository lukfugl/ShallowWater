#ifndef __MODEL_H__
#define __MODEL_H__

#include "solution.h"
#include "cell.h"

class Model {
public:
    Model(int width, int height, std::string filename);
    ~Model();

    void step();
    const Solution &operator[](int n) const;

private:
    Solution *solutions;
    Cell* cells;
    int count;
};

#endif // __MODEL_H__
