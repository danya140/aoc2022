#pragma once

#include "helpers.h"

class HeightMap
{
public:
    HeightMap(const std::vector<std::vector<int>>& heightMap);

    int countVisibleTrees();

    int mostScenicView();

private:

    bool isVisible(int x, int y) const;

    bool checkLine(int x, int y, int xStep, int yStep) const;

    void lineScenicScore(int x, int y, int xStep, int yStep, int& score) const;

    int columnsCount() const;
    int rowsCount() const;

private:
    std::vector<std::vector<int>> m_heightMap;

};


