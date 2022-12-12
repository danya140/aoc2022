#pragma once

#include "helpers.h"

typedef std::pair<std::string, int> Instruction;
typedef std::vector<Instruction> Instructions;

class Processor
{

public:
    Processor(const Instructions& instructions);

    void process();

    std::vector<int> getPoi();

    void printImage();

private:
    void savePoi();

    void cycle(const Instruction& instruction);

    void draw();

private:

    int m_x;
    int m_cycle;
    std::vector<int> m_poi;

    int m_currentPoi;

    Instructions m_instructions;

    int m_spriteCenter;
    std::vector<std::string> m_image;
};


