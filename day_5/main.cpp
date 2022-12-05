#include <iostream>

#include "CargoPort.h"

#include "helpers.h"

const char* INPUT = "input.txt";

CargoPort readInput(int version)
{
    std::ifstream file(INPUT);

    CargoPort port(version);
    if(file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (line.find('[') != std::string::npos)
            {
                port.addCrates(line);
            }
            else if(containsAll(line, "move"))
            {
                port.addAction(line);
            }
        }
    }

    return port;
}

int main()
{
    START_TIMER(point_1)

    CargoPort port9000 = readInput(9000);
    port9000.applyActions();
    std::cout << "CrateMover 9000: "  << port9000.topOfStack() << std::endl;

    CargoPort port9001 = readInput(9001);
    port9001.applyActions();
    std::cout << "CrateMover 9001: "  << port9001.topOfStack() << std::endl;

    STOP_TIMER(point_1)
    return 0;
}
