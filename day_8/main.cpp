#include <iostream>

#include "helpers.h"

#include "HeightMap.h"

const char* INPUT = "input.txt";

std::vector<std::vector<int>> readInput()
{
    std::ifstream file(INPUT);

    std::vector<std::vector<int>> inputData;
    if(file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::vector<int> row;
            for (const char& height : line)
            {
                row.push_back(height - '0');
            }

            inputData.push_back(row);
        }
    }

    return inputData;
}

int main()
{
    START_TIMER(point_1)


    HeightMap heightMap(readInput());
    std::cout << "Number of trees visible: " << heightMap.countVisibleTrees() << std::endl;
    std::cout << "Best scenic score possible: " << heightMap.mostScenicView() << std::endl;

    STOP_TIMER(point_1)
    return 0;
}
