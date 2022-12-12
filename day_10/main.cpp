#include <iostream>

#include "helpers.h"

#include "Processor.h"

const char* INPUT = "input.txt";

Instructions readInput()
{
    std::ifstream file(INPUT);

    Instructions inputData;

    if(file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::vector<std::string> lineParts = split(line, ' ');
            std::string instructionName = lineParts.at(0);
            int number = 0;
            if (instructionName == "addx")
            {
                number = std::stoi(lineParts.at(1));
            }
            inputData.push_back({instructionName, number});
        }
    }

    return inputData;
}

int main()
{
    START_TIMER(point_1)

    Instructions input = readInput();
    Processor cpu(input);
    cpu.process();
    std::vector<int> poi = cpu.getPoi();

    int answer = std::accumulate(poi.begin(),  poi.end(), 0);
    std::cout << "Sum of all poi: " << answer << std::endl;

    cpu.printImage();

    STOP_TIMER(point_1)
    return 0;
}
