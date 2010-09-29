#include "solution.h"
#include <iostream>

const double HALFG = 10;

Solution::Solution()
    : m_h(1), m_uh(0), m_vh(0) {
}

Solution::Solution(double h)
    : m_h(h), m_uh(0), m_vh(0) {
}

Solution::Solution(double h, double uh, double vh)
    : m_h(h), m_uh(uh), m_vh(vh) {
}

Solution::Solution(const Solution &other)
    : m_h(other.m_h), m_uh(other.m_uh), m_vh(other.m_vh) {
}

Solution
Solution::operator+(const Solution &other) const {
    return Solution(m_h + other.m_h, m_uh + other.m_uh, m_vh + other.m_vh);
}

Solution
Solution::operator-(const Solution &other) const {
    return Solution(m_h - other.m_h, m_uh - other.m_uh, m_vh - other.m_vh);
}

Solution
Solution::operator*(double scalar) const {
    return Solution(m_h * scalar, m_uh * scalar, m_vh * scalar);
}

void
Solution::scale(double ah, double au) {
    m_h *= ah;
    m_uh *= au;
    m_vh *= au;
}

Solution&
Solution::operator=(const Solution &other) {
    this->m_h = other.m_h;
    this->m_uh = other.m_uh;
    this->m_vh = other.m_vh;
    return *this;
}

void
Solution::applyF(Solution &F) {
    double u = (m_h == 0 ? 0 : (m_uh / m_h));
    double uvh = u * m_vh;
    double half_gh2 = HALFG * m_h * m_h;
    F = Solution(m_uh, u * m_uh + half_gh2, uvh);
}

void
Solution::applyG(Solution &G) {
    double v = (m_h == 0 ? 0 : (m_vh / m_h));
    double uvh = v * m_uh;
    double half_gh2 = HALFG * m_h * m_h;
    G = Solution(m_vh, uvh, v * m_vh + half_gh2);
}

void
Solution::applyFG(Solution &F, Solution &G) {
    double u = (m_h == 0 ? 0 : (m_uh / m_h));
    double v = (m_h == 0 ? 0 : (m_vh / m_h));
    double uvh = u * m_vh;
    double half_gh2 = HALFG * m_h * m_h;
    F = Solution(m_uh, u * m_uh + half_gh2, uvh);
    G = Solution(m_vh, uvh, v * m_vh + half_gh2);
}

Solution
Solution::edgeF() const {
    return Solution(0, HALFG * m_h * m_h, 0);
}

Solution
Solution::edgeG() const {
    return Solution(0, 0, HALFG * m_h * m_h);
}

double
Solution::h() const {
    return m_h;
}

double
Solution::u() const {
    return (m_h == 0 ? 0 : m_uh / m_h);
}

double
Solution::v() const {
    return (m_h == 0 ? 0 : m_vh / m_h);
}

std::ostream&
operator<<(std::ostream &os, const Solution &solution)
{
    os  << "< " << solution.m_h
        << ", " << solution.m_uh
        << ", " << solution.m_vh
        << " >";
    return os;
}
