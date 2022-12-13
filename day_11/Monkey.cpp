#include "Monkey.h"

const int WORRY_LEVEL_DIVIDER = 3;

Monkey::Monkey()
    : m_inspectCounter(0)
{}

ThrownItems Monkey::checkItems()
{
    ThrownItems thrownItems;
    for (int i = 0; i < m_items.size(); ++i)
    {
        unsigned long long int worryLevel = calculateWorryLevel(i);
        int newDestination = testItem(worryLevel);

        thrownItems.push_back({newDestination, worryLevel});
        m_inspectCounter++;
    }

    m_items.clear();

    return thrownItems;
}

int Monkey::testItem(unsigned long long int worryLevel) const
{
    if (worryLevel % m_test.second)
    {
        return m_falseDestination;
    }
    else
    {
        return m_trueDestination;
    }
}

unsigned long long int Monkey::calculateWorryLevel(int itemIndex) const
{
    unsigned long long int worryLevel = m_items.at(itemIndex);

    unsigned long long int newLevel;
    unsigned long long int left;
    unsigned long long int right;
    if (std::get<0>(m_operation) == "old")
    {
        left = worryLevel;
    }
    else
    {
        left = std::stoi(std::get<0>(m_operation));
    }

    if (std::get<2>(m_operation) == "old")
    {
        right = worryLevel;
    }
    else
    {
        right = std::stoi(std::get<2>(m_operation));
    }

    switch (std::get<1>(m_operation))
    {
        case '+':
            newLevel = left + right;
            break;
        case '-':
            newLevel = left - right;
            break;
        case '*':
            newLevel = left * right;
            break;
        case '/':
            newLevel = left / right;
            break;
    }

    newLevel = newLevel / WORRY_LEVEL_DIVIDER;
    return newLevel;
}

void Monkey::acceptThrownItem(unsigned long long int worryLevel)
{
    m_items.push_back(worryLevel);
}

void Monkey::setNumber(int mNumber)
{
    m_number = mNumber;
}
void Monkey::setItems(const std::vector<unsigned long long int> &mItems)
{
    m_items = mItems;
}
void Monkey::setOperation(const Operation &mOperation)
{
    m_operation = mOperation;
}
void Monkey::setTest(const TestCondition &mTest)
{
    m_test = mTest;
}
void Monkey::setTrueDestination(int mTrueDestination)
{
    m_trueDestination = mTrueDestination;
}
void Monkey::setFalseDestination(int mFalseDestination)
{
    m_falseDestination = mFalseDestination;
}

int Monkey::getNumber() const
{
    return m_number;
}

int Monkey::getInspectCounter() const
{
    return m_inspectCounter;
}

std::vector<unsigned long long int> Monkey::getItems() const
{
    return m_items;
}

void Monkey::printState() const
{
    std::cout << "Monkey " << m_number << std::endl;

    std::string items = vector2String(m_items, ",");
    std::cout << "Items: " << items << std::endl;
    std::cout << "Inspect count: " << m_inspectCounter << std::endl;
}
