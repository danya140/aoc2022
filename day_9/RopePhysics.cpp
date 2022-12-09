#include "RopePhysics.h"

RopePhysics::RopePhysics(const std::vector<std::pair<char, int>> &moves, int knotCount)
    : m_moves(moves),
      m_head(Knot(0)),
      m_knotCount(knotCount)
{
    for (int i = 0; i < knotCount; ++i)
    {
        m_knots.push_back(Knot(i+1));
    }

    std::pair<int, int> pos = {m_knots.back().getX(), m_knots.back().getY()};
    m_visitMap[pos] = 1;
}

void RopePhysics::simulateRope()
{
    for (const std::pair<char, int>& move : m_moves)
    {
        for (int i = 0; i < move.second; ++i)
        {
            //Move head
            m_head.move(move.first);

            //Move knots
            Knot previousKnot = m_head;
            for (Knot& knot : m_knots)
            {
                moveKnot(previousKnot, knot, move.first);
                previousKnot = knot;
                printState();
            }
        }
    }
}


void RopePhysics::moveKnot(Knot& previousKnot, Knot& currentKnot, char direction)
{
    //Check touching
    bool isTouching = abs(previousKnot.getX() - currentKnot.getX()) <= 1 && abs(previousKnot.getY() - currentKnot.getY()) <= 1;
    if (!isTouching)
    {
        //Calc next position

        currentKnot.move(direction);

        currentKnot.setPosition(previousKnot.getOldX(), previousKnot.getOldY());
        if (currentKnot.getNumber() == m_knotCount)
        {
            std::pair<int, int> pos = {currentKnot.getX(), currentKnot.getY()};
            std::map<std::pair<int, int>, int>::iterator it = m_visitMap.find(pos);
            if (it != m_visitMap.end())
            {
                it->second++;
            }
            else
            {
                m_visitMap[pos] = 1;
            }
        }
    }
}


void RopePhysics::printState()
{
    for (int y = -5; y < 5; ++y)
    {
        for (int x = 0; x < 5; ++x)
        {
            bool clean = true;

            if (x == 0 && y == 0)
            {
                clean &= false;
                std::cout << "s";
            }

            if (x == m_head.getX() && y == m_head.getY())
            {
                clean &= false;
                std::cout << "H";
            }

            for (int i = 0; i < m_knots.size(); ++i)
            {
                if (x == m_knots.at(i).getX() && y == m_knots.at(i).getY() && clean)
                {
                    std::cout << m_knots.at(i).getNumber();
                    clean &= false;
                }
            }

            if (clean)
            {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int RopePhysics::getUniqueVisitedPositions()
{
//    int result = m_visitMap.size();
//    if (m_visitMap.find({0,0}) == m_visitMap.end())
//    {
//        result++; // add start position if n
//    }
    return m_visitMap.size();
}
