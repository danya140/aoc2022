#pragma once

#include <tuple>
#include "helpers.h"

typedef std::tuple<std::string, char, std::string> Operation;

typedef std::pair<std::string, int> TestCondition;

typedef std::pair<int, unsigned long long int> ThrownItem;
typedef std::vector<ThrownItem> ThrownItems;

class Monkey
{
public:
    Monkey();

    ThrownItems checkItems();

    void acceptThrownItem(unsigned long long int item);

    void setNumber(int mNumber);
    void setItems(const std::vector<unsigned long long int> &mItems);
    void setOperation(const Operation &mOperation);
    void setTest(const TestCondition &mTest);
    void setTrueDestination(int mTrueDestination);
    void setFalseDestination(int mFalseDestination);
    int getNumber() const;
    int getInspectCounter() const;
    std::vector<unsigned long long int> getItems() const;

    void printState() const;

private:

    unsigned long long int calculateWorryLevel(int itemIndex) const;
    int testItem(unsigned long long int worryLevel) const;

private:
    int m_number;
    std::vector<unsigned long long int> m_items;

    Operation m_operation;
    TestCondition m_test;

    int m_trueDestination;
    int m_falseDestination;

    int m_inspectCounter;
};


