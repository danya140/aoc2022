#pragma once


class Knot
{
public:
    Knot(int number);

    int getX() const;
    int getY() const;
    int getOldX() const;
    int getOldY() const;
    int getNumber() const;
    void move(char direction);

    void setPosition(int x, int y);

private:
    void savePosition();

private:
    int m_x = 0;
    int m_y = 0;
    int m_number;
    int m_oldX;
    int m_oldY;

};

bool operator<(const Knot& left, const Knot& right);
