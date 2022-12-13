#include <iostream>

#include "helpers.h"

#include "Monkey.h"

const char* INPUT = "input_example.txt";

enum LINES
{
    MONKEY_NUMBER,
    STARTING_ITEMS,
    OPERATION,
    TEST,
    TRUE_DESTINATION,
    FALSE_DESTINATION,
    EMPTY
};

std::vector<Monkey> readInput()
{
    std::ifstream file(INPUT);

    std::vector<Monkey> inputData;

    if(file.is_open())
    {
        std::string line;
        int lineNumber = MONKEY_NUMBER;
        Monkey monkey;
        while (std::getline(file, line))
        {
            switch (lineNumber)
            {
                case MONKEY_NUMBER:
                {
                    std::vector<std::string> lineParts = split(line, ' ');
                    std::string number = lineParts.at(1);
                    number = number.substr(0, number.size() - 1);
                    monkey.setNumber(std::stoi(number));
                }
                    break;
                case STARTING_ITEMS:
                {
                    std::vector<std::string> lineParts = split(line, ':');
                    std::vector<std::string> itemString = split(lineParts.at(1), ',');

                    std::vector<unsigned long long int> items;
                    for (const std::string& item : itemString)
                    {
                        items.push_back(std::stoi(item));
                    }
                    monkey.setItems(items);
                }
                    break;
                case OPERATION:
                {
                    std::vector<std::string> lineParts = split(line, '=');
                    std::vector<std::string> operators = split(lineParts.at(1), ' ');
                    Operation operation = {operators.at(0), operators.at(1).at(0), operators.at(2)};

                    monkey.setOperation(operation);
                }
                    break;
                case TEST:
                {
                    std::vector<std::string> testConditions = split(split(line, ':').at(1), ' ');
                    TestCondition testCondition = {testConditions.at(0), std::stoi(testConditions.at(2))};
                    monkey.setTest(testCondition);
                }
                    break;
                case TRUE_DESTINATION:
                {
                    std::vector<std::string> lineParts = split(line, ' ');
                    monkey.setTrueDestination(std::stoi(lineParts.back()));
                }
                    break;
                case FALSE_DESTINATION:
                {
                    std::vector<std::string> lineParts = split(line, ' ');
                    monkey.setFalseDestination(std::stoi(lineParts.back()));
                }
                    break;
                case EMPTY:
                {
                    lineNumber = -1;
                    inputData.push_back(monkey);
                    monkey = Monkey();
                }
                    break;
            }

            lineNumber++;
        }
        inputData.push_back(monkey);
    }

    return inputData;
}

void passItems(std::vector<Monkey>& input, const ThrownItems& items)
{
    for (const ThrownItem& item : items)
    {
        input.at(item.first).acceptThrownItem(item.second);
    }
}

void round(std::vector<Monkey>& input)
{
    for (Monkey& monkey : input)
    {
        ThrownItems items = monkey.checkItems();
        passItems(input, items);
    }
}

void printMonkeyState(std::vector<Monkey>& input)
{
    for (const Monkey& monkey : input)
    {
        monkey.printState();
    }
}

unsigned long long int mostActiveMonkey(std::vector<Monkey>& input, int rounds)
{
    for (int i = 0; i < rounds; ++i)
    {
        round(input);

//        std::cout << "After round " << i + 1 << std::endl;
//        printMonkeyState(input);
//        std::cout << std::endl;
    }

    std::vector<unsigned long long int> monkeyLevel;
    for (const Monkey& monkey : input)
    {
        monkeyLevel.push_back(monkey.getInspectCounter());
    }

    std::sort(monkeyLevel.begin(),  monkeyLevel.end());

    return monkeyLevel.back() * monkeyLevel.at(monkeyLevel.size() - 2);
}

int main()
{
    START_TIMER(point_1)

    std::vector<Monkey> input = readInput();
//    std::cout << "Level of monkey business after 20 rounds: " << mostActiveMonkey(input, 20) << std::endl;
    std::cout << "Level of monkey business after 10000 rounds: " << mostActiveMonkey(input, 20) << std::endl;

    STOP_TIMER(point_1)
    return 0;
}
