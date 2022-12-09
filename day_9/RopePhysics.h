#pragma once

#include "helpers.h"

#include "Knot.h"

#include <map>

class RopePhysics
{
public:
    RopePhysics(const std::vector<std::pair<char, int>>& moves, int knotCount);

    void simulateRope();

    int getUniqueVisitedPositions();

    void printState();

private:
    void moveKnot(Knot& previousKnot, Knot& currentKnot, char direction);

private:
    Knot m_head;

    std::vector<Knot> m_knots;

    std::vector<std::pair<char, int>> m_moves;

    std::map<std::pair<int, int>, int> m_visitMap;

    int m_knotCount;
};


