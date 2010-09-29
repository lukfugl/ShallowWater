#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include <iostream>

class Solution {
public:
    // constructors
    Solution();
    Solution(double h);
    Solution(double h, double uh, double vh);
    Solution(const Solution &other);

    // arithmetic
    Solution operator+(const Solution &other) const;
    Solution operator-(const Solution &other) const;
    Solution operator*(double scalar) const;
    void scale(double ah, double au);
    Solution &operator=(const Solution &other);

    // calculation of F and G
    void applyF(Solution &F);
    void applyG(Solution &G);
    void applyFG(Solution &F, Solution &G);
    Solution edgeF() const;
    Solution edgeG() const;

    // access
    double h() const;
    double u() const;
    double v() const;

private:
    double m_h, m_uh, m_vh;

    friend std::ostream& operator<<(std::ostream &os, const Solution &solution);
};

std::ostream& operator<<(std::ostream &os, const Solution &solution);

#endif // __SOLUTION_H__
