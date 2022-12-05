#pragma once

#include <deque>
#include <queue>

#include "helpers.h"

struct Action
{
public:
    Action(int repeats, int from, int to)
        : m_repeats(repeats),
          m_from(from),
          m_to(to)
    {}

    int m_repeats;
    int m_from;
    int m_to;
};

class CargoPort
{

public:
    CargoPort(int version);

    /**
     * Parse line and add crates to stack
     */
    void addCrates(const std::string& line);

    /**
     * Apply all actions assigned to crane
     */
    void applyActions();

    /**
     * Parse action from string
     */
    void addAction(const std::string &line);

    /**
     * Return letters on top for all stacks
     */
    std::string topOfStack();

private:

    /**
     * Apply action without air conditioning
     */
    void applyAction9000(const Action& action);

    /**
     * Apply action with air conditioning, additional cup of tea and crane stack
     */
    void applyAction9001(const Action& action);

private:
    std::vector<std::deque<char>> m_supplies;
    std::queue<Action> m_actions;
    int m_version;
};


