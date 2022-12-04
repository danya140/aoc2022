#include <iostream>

#include "helpers.h"

const char* INPUT = "input.txt";

const int PRIORITY_LOWER_SHIFT = 96;
const int PRIORITY_UPPER_SHIFT = 38;

std::vector<std::string> readInput()
{
    std::ifstream file(INPUT);

    std::vector<std::string> inputData;

    if(file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            inputData.push_back(line);
        }
    }

    return inputData;
}

char findIntersection(const std::string& left, const std::string& right)
{
    for (char i : left)
    {
        if(right.find(i) != std::string::npos)
        {
            return i;
        }
    }

    return 0;
}

int calculatePriorities(const std::vector<std::string>& input)
{
    int result = 0;
    for (const std::string& rucksack : input)
    {
        std::string first = rucksack.substr(0, rucksack.size()/2);
        std::string second = rucksack.substr(rucksack.size()/2, rucksack.size() - rucksack.size()/2);

        char intersection = findIntersection(first, second);
        if(std::islower(intersection))
        {
            result += intersection - PRIORITY_LOWER_SHIFT;
        }
        else
        {
            result += intersection - PRIORITY_UPPER_SHIFT;
        }
    }

    return result;
}

char findCommonItem(const std::string& first, const std::string& second, const std::string& third)
{
    for (char i : first)
    {
        if(second.find(i) != std::string::npos && third.find(i) != std::string::npos)
        {
            return i;
        }
    }

    return 0;
}

int calculateGroupPriority(const std::vector<std::string>& input)
{
    int result = 0;

    std::vector<std::string> group;
    for (const std::string& i : input)
    {
        group.push_back(i);
        if(group.size() == 3)
        {
            char intersection = findCommonItem(group.at(0), group.at(1), group.at(2));
            if(std::islower(intersection))
            {
                result += intersection - PRIORITY_LOWER_SHIFT;
            }
            else
            {
                result += intersection - PRIORITY_UPPER_SHIFT;
            }

            group.clear();
        }
    }

    return result;
}

int main()
{
    START_TIMER(point_1)
    std::vector<std::string> input = readInput();

    std::cout << "Total priority: " << calculatePriorities(input) << std::endl;
    std::cout << "Total group priority: " << calculateGroupPriority(input) << std::endl;

    STOP_TIMER(point_1)
    return 0;
}
