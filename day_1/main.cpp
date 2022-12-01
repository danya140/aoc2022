#include <iostream>
#include <fstream>

#include "helpers.h"

std::vector<int> readInput()
{
    std::ifstream file("input.txt");

    std::vector<int> inputData;

    if(file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            if(line.empty())
            {
                inputData.push_back(-1);
            }
            else
            {
                inputData.push_back(std::stoi(line));
            }
        }
    }

    inputData.push_back(-1); // indicate trailing elf in list

    return inputData;
}

/**
 * Calculate how much calories each elf carrying
 */
std::vector<int> elfsCalories(const std::vector<int>& list)
{
    std::vector<int> result;
    int currentElfCalories = 0;
    for (int calories : list)
    {
        if (calories == -1)
        {
            result.push_back(currentElfCalories);
            currentElfCalories = 0;
            continue;
        }
        currentElfCalories += calories;
    }

    std::sort(result.begin(), result.end());
    return result;
}

int calculateBiggestCalories(const std::vector<int>& list)
{
    std::vector<int> calories = elfsCalories(list);
    return calories.back();
}

int calculateTop3Sum(const std::vector<int>& list)
{
    std::vector<int> calories = elfsCalories(list);

    int result = 0;
    for (int i = 0; i < 3; ++i)
    {
        result += calories.back();
        calories.pop_back();
    }

    return result;
}


int main()
{
    START_TIMER(point_1)

    std::vector<int> input = readInput();
    std::cout << "Biggest calories elf carrying: " << calculateBiggestCalories(input) << std::endl;
    std::cout << "Sum of top 3 calories elf carrying: " << calculateTop3Sum(input) << std::endl;

    STOP_TIMER(point_1)
    return 0;
}
