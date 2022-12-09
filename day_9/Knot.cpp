#include "Knot.h"

Knot::Knot(int number)
    : m_number(number)
{

}

void Knot::savePosition()
{
    m_oldX = m_x;
    m_oldY = m_y;
}

int Knot::getX() const
{
    return m_x;
}

int Knot::getY() const
{
    return m_y;
}

int Knot::getOldX() const
{
    return m_oldX;
}

int Knot::getOldY() const
{
    return m_oldY;
}

int Knot::getNumber() const
{
    return m_number;
}

void Knot::setPosition(int x, int y)
{
    savePosition();
    m_x = x;
    m_y = y;
}

void Knot::move(char direction)
{

    if (direction == 'D')
    {
        setPosition(m_x, m_y + 1);
    }
    else if(direction == 'U')
    {
        setPosition(m_x, m_y - 1);
    }
    else if(direction == 'R')
    {
        setPosition(m_x + 1, m_y);
    }
    else if(direction == 'L')
    {
        setPosition(m_x - 1, m_y);
    }
}

bool operator<(const Knot& left, const Knot& right)
{
    return left.getNumber() < right.getNumber();
}
