#include "CargoPort.h"

CargoPort::CargoPort(int version)
    : m_supplies(std::vector<std::deque<char>>()),
      m_actions(std::queue<Action>()),
      m_version(version)
{

}

void CargoPort::addCrates(const std::string &line)
{
    std::vector<char> crates;
    for (int i = 1; i < line.size(); i += 4)
    {
        crates.push_back(line.at(i));
    }

    for (int i = 0; i < crates.size(); ++i)
    {
        if(i + 1 > m_supplies.size())
        {
            m_supplies.push_back(std::deque<char>());
        }

        if(crates.at(i) != ' ')
        {
            m_supplies.at(i).push_back(crates.at(i));
        }
    }
}

void CargoPort::applyAction9000(const Action &action)
{
    for (int i = 0; i < action.m_repeats; ++i)
    {
        char crate = m_supplies.at(action.m_from).front();
        m_supplies.at(action.m_from).pop_front();

        m_supplies.at(action.m_to).push_front(crate);
    }
}

void CargoPort::applyAction9001(const Action &action)
{
    std::deque<char> craneStack;
    for (int i = 0; i < action.m_repeats; ++i)
    {
        char crate = m_supplies.at(action.m_from).front();
        m_supplies.at(action.m_from).pop_front();
        craneStack.push_back(crate);
    }

    while(!craneStack.empty())
    {
        m_supplies.at(action.m_to).push_front(craneStack.back());
        craneStack.pop_back();
    }
}

void CargoPort::applyActions()
{
    while (!m_actions.empty())
    {
        Action action = m_actions.front();
        m_actions.pop();
        if(m_version == 9000)
        {
            applyAction9000(action);
        }
        else
        {
            applyAction9001(action);
        }
    }
}

std::string CargoPort::topOfStack()
{
    std::string result;

    for (const std::deque<char>& stack : m_supplies)
    {
        result += stack.front();
    }

    return result;
}

void CargoPort::addAction(const std::string &line)
{
    std::vector<std::string> splitedLine = split(line, ' ');

    int repeats = std::stoi(splitedLine.at(1));
    int from = std::stoi(splitedLine.at(3)) - 1;
    int to = std::stoi(splitedLine.at(5)) - 1;

    m_actions.push(Action(repeats, from, to));
}
