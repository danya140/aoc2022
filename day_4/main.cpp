#include <iostream>

#include "helpers.h"

const char* INPUT = "input.txt";

typedef std::pair<int, int> Range;
typedef std::pair<Range, Range> Pair;

std::vector<Pair> readInput()
{
    std::ifstream file(INPUT);

    std::vector<Pair> inputData;

    if(file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::vector<std::string> ranges = split(line, ',');
            std::vector<std::string> firstRangeString = split(ranges.at(0), '-');
            std::vector<std::string> secondRangeString = split(ranges.at(1), '-');

            Range first;
            first.first = std::stoi(firstRangeString.at(0));
            first.second = std::stoi(firstRangeString.at(1));

            Range second;
            second.first = std::stoi(secondRangeString.at(0));
            second.second = std::stoi(secondRangeString.at(1));

            inputData.push_back({first, second});
        }
    }

    return inputData;
}

bool checkFullIntersection(const Pair& pair)
{
    return pair.first.first >= pair.second.first && pair.first.second <= pair.second.second
            || pair.first.first <= pair.second.first && pair.first.second >= pair.second.second;
}

int countFullyIntersectedRanges(const std::vector<Pair>& input)
{
    int count = 0;
    for (const Pair& pair : input)
    {
        if (checkFullIntersection(pair))
        {
            count++;
        }
    }

    return count;
}

bool checkOverlap(const Pair& pair)
{
    return pair.second.first <= pair.first.first && pair.first.first <= pair.second.second
            || pair.first.first <= pair.second.first && pair.second.first <= pair.first.second;
}

int countOverlappingRanges(const std::vector<Pair>& input)
{
    int count = 0;
    for (const Pair& pair : input)
    {
        if (checkOverlap(pair))
        {
            count++;
        }
    }

    return count;
}

int main()
{
    START_TIMER(point_1)

    std::vector<Pair> input = readInput();
    std::cout << "Number of fully intersected ranges: " << countFullyIntersectedRanges(input) << std::endl;
    std::cout << "Number of overlapping ranges: " << countOverlappingRanges(input) << std::endl;

    STOP_TIMER(point_1)
    return 0;
}
