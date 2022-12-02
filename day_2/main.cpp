#include <iostream>


#include "helpers.h"

const char* INPUT = "input.txt";

enum SHAPE
{
    ROCK = 1,
    PAPER = 2,
    SCISSORS = 3
};

enum RESULT
{
    LOST = 0,
    DRAW = 3,
    WON = 6
};

typedef std::pair<SHAPE, SHAPE> Round;
typedef std::pair<SHAPE, RESULT> RoundResult;

SHAPE encodeShape(char shape)
{
    if (shape == 'A' || shape == 'X')
    {
        return ROCK;
    }
    else if (shape == 'B' || shape == 'Y')
    {
        return PAPER;
    }
    else
    {
        return SCISSORS;
    }
}

RESULT encodeResultShape(char result)
{
    if (result == 'X')
    {
        return LOST;
    }
    else if (result == 'Y')
    {
        return DRAW;
    }
    else
    {
        return WON;
    }
}

std::vector<Round> readInput1()
{
    std::ifstream file(INPUT);

    std::vector<Round> inputData;

    if(file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            Round currentRound;
            currentRound.first = encodeShape(line.at(0));
            currentRound.second = encodeShape(line.at(2));
            inputData.push_back(currentRound);
        }
    }

    return inputData;
}

std::vector<RoundResult> readInput2()
{
    std::ifstream file(INPUT);

    std::vector<RoundResult> inputData;

    if(file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            RoundResult currentRound;
            currentRound.first = encodeShape(line.at(0));
            currentRound.second = encodeResultShape(line.at(2));
            inputData.push_back(currentRound);
        }
    }

    return inputData;
}

SHAPE winningShape(SHAPE shape)
{
    if (shape == ROCK)
    {
        return PAPER;
    }
    else if(shape == PAPER)
    {
        return SCISSORS;
    }
    else
    {
        return ROCK;
    }
}

SHAPE losingShape(SHAPE shape)
{
    if (shape == ROCK)
    {
        return SCISSORS;
    }
    else if(shape == PAPER)
    {
        return ROCK;
    }
    else
    {
        return PAPER;
    }
}

RESULT roundResult(SHAPE enemy, SHAPE me)
{
    if (enemy == me)
    {
        return DRAW;
    }
    else if(me == winningShape(enemy))
    {
        return WON;
    }

    return LOST;
}

int calculateTotalScore(const std::vector<Round>& input)
{
    int score = 0;
    for (const Round& currentRound : input)
    {
        RESULT result = roundResult(currentRound.first, currentRound.second);

        score += int(result) + int(currentRound.second);
    }

    return score;
}

SHAPE predictMove(SHAPE enemy, RESULT result)
{
    if (result == DRAW)
    {
        return enemy;
    }
    else if(result == WON)
    {
        return winningShape(enemy);
    }
    else
    {
        return losingShape(enemy);
    }
}

int predictMoveScore(const std::vector<RoundResult>& input)
{
    int score = 0;
    for (const RoundResult& currentRound : input)
    {
        SHAPE result = predictMove(currentRound.first, currentRound.second);
        score += int(result) + int(currentRound.second);
    }

    return score;
}


int main()
{
    START_TIMER(point_1)

    std::vector<Round> input1 = readInput1();
    std::cout << "Match score: " << calculateTotalScore(input1) << std::endl;

    std::vector<RoundResult> input2 = readInput2();
    std::cout << "Match score: " << predictMoveScore(input2) << std::endl;

    STOP_TIMER(point_1)
    return 0;
}
