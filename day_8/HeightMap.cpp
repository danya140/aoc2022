#include "HeightMap.h"

HeightMap::HeightMap(const std::vector<std::vector<int>> &heightMap)
    : m_heightMap(heightMap)
{

}

int HeightMap::countVisibleTrees()
{
    int result = 0;

    for (int y = 0; y < columnsCount(); ++y)
    {
        for (int x = 0; x < rowsCount(); ++x)
        {
            if (isVisible(x, y))
            {
                ++result;
            }
        }
    }

    return result;
}

bool HeightMap::isVisible(int x, int y) const
{
    bool topVisible = checkLine(x, y, 0, -1);
    bool bottomVisible = checkLine(x, y, 0, 1);
    bool leftVisible = checkLine(x, y, -1, 0);
    bool rightVisible = checkLine(x, y, 1, 0);

    return topVisible || bottomVisible || leftVisible || rightVisible;
}

bool HeightMap::checkLine(int x, int y, int xStep, int yStep) const
{
    int pointHeight = m_heightMap[y][x];
    int currentX = x + xStep;
    int currentY = y + yStep;

    while (currentX != -1 && currentY != -1 && currentX != columnsCount() && currentY != rowsCount())
    {
        int currentHeight = m_heightMap[currentY][currentX];
        if(currentHeight >= pointHeight)
        {
            return false;
        }

        currentX += xStep;
        currentY += yStep;
    }

    return true;
}

int HeightMap::mostScenicView()
{
    int biggestScenicScore = 0;

    for (int y = 0; y < columnsCount(); ++y)
    {
        for (int x = 0; x < rowsCount(); ++x)
        {
            int topScore = 0;
            lineScenicScore(x, y, 0, -1, topScore);
            int bottomScore = 0;
            lineScenicScore(x, y, 0, 1, bottomScore);
            int leftScore = 0;
            lineScenicScore(x, y, -1, 0, leftScore);
            int rightScore = 0;
            lineScenicScore(x, y, 1, 0, rightScore);

            int totalScore = topScore * bottomScore * leftScore * rightScore;

            if(totalScore > biggestScenicScore)
            {
                biggestScenicScore = totalScore;
            }
        }
    }

    return biggestScenicScore;
}

void HeightMap::lineScenicScore(int x, int y, int xStep, int yStep, int &score) const
{
    int pointHeight = m_heightMap[y][x];
    int currentX = x + xStep;
    int currentY = y + yStep;

    while (currentX != -1 && currentY != -1 && currentX != columnsCount() && currentY != rowsCount())
    {
        int currentHeight = m_heightMap[currentY][currentX];
        if(currentHeight >= pointHeight)
        {
            score++;
            return;
        }

        currentX += xStep;
        currentY += yStep;
        score++;
    }
}

int HeightMap::columnsCount() const
{
    return m_heightMap.at(0).size();
}

int HeightMap::rowsCount() const
{
    return m_heightMap.size();
}
