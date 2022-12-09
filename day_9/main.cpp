#include <iostream>

#include "helpers.h"

#include "RopePhysics.h"

const char* INPUT = "input_example.txt";

std::vector<std::pair<char, int>> readInput()
{
    std::ifstream file(INPUT);

    std::vector<std::pair<char, int>> inputData;

    if(file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::vector<std::string> stringParts = split(line, ' ');
            char direction = stringParts.at(0).at(0);
            int moves = std::stoi(stringParts.at(1));
            inputData.push_back({direction, moves});
        }
    }

    return inputData;
}

int main()
{
    START_TIMER(point_1)

    std::vector<std::pair<char, int>> input = readInput();
    RopePhysics physics(input, 1);
    physics.simulateRope();
    std::cout << "Number of positions 1 knot rope tail visited at least once: " << physics.getUniqueVisitedPositions() << std::endl;

//    RopePhysics knotPhysics(input, 9);
//    knotPhysics.simulateRope();
//    std::cout << "Number of positions 9 knot rope tail visited at least once: " << knotPhysics.getUniqueVisitedPositions() << std::endl;

    STOP_TIMER(point_1)
    return 0;
}
