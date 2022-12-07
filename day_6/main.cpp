#include <iostream>

#include <deque>

#include "helpers.h"

const char* INPUT = "input.txt";

std::string readInput()
{
    std::ifstream file(INPUT);

    std::string inputData;

    if(file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            inputData = line;
        }
    }

    return inputData;
}

int findMarker(const std::string& input, int characters)
{
    std::deque<char> marker;
    for (int i = 0; i < input.size(); ++i)
    {
        if (marker.size() == characters)
        {
            return i;
        }

        std::deque<char>::iterator it = std::find(marker.begin(), marker.end(), input.at(i));
        if (it != marker.end())
        {
            int index = std::distance(it,marker.end());
            for (int j = 0; j < index; ++j)
            {
                marker.pop_back();
            }
        }

        marker.push_front(input.at(i));
    }

    return -1;
}

int main()
{
    START_TIMER(point_1)

    std::string input = readInput();
    std::cout << "Start of packet marker: " << findMarker(input, 4) << std::endl;
    std::cout << "Start of message marker: " << findMarker(input, 14) << std::endl;

    STOP_TIMER(point_1)
    return 0;
}
