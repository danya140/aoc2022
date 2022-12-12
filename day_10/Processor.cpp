#include "Processor.h"

const int POI_STEP = 40;

const int PIXELS_IN_ROW = 40;

Processor::Processor(const Instructions &instructions)
    : m_instructions(instructions),
      m_currentPoi(20),
      m_x(1),
      m_cycle(1),
      m_spriteCenter(1)
{
    for (int i = 0; i <= 6; ++i)
    {
        m_image.push_back("");
    }
}

void Processor::process()
{
    for (int i = 0; i < m_instructions.size(); ++i)
    {
        cycle(m_instructions.at(i));
    }
}

void Processor::cycle(const Instruction& instruction)
{
    int cycles;
    if (instruction.first == "noop")
    {
        cycles = 1;
    }
    else
    {
        cycles = 2;
    }

    while (cycles)
    {
        savePoi();

        draw();

        cycles--;
        m_cycle++;
        if (instruction.first != "noop" && cycles == 0)
        {
            m_x += instruction.second;
        }

        m_spriteCenter = m_x;
    }
}

void Processor::draw()
{
    int row = (m_cycle-1)/PIXELS_IN_ROW;
    int column = m_cycle - PIXELS_IN_ROW * row-1;

    if (m_spriteCenter - 1 <= column && column <= m_spriteCenter + 1)
    {
        m_image.at(row) += "#";
    }
    else
    {
        m_image.at(row) += ".";
    }
}

void Processor::savePoi()
{
    if (m_cycle == m_currentPoi)
    {
        m_poi.push_back(m_x * m_cycle);
        m_currentPoi += POI_STEP;
    }
}

std::vector<int> Processor::getPoi()
{
    return m_poi;
}

void Processor::printImage()
{
    for (const std::string& row : m_image)
    {
        std::cout<< row << std::endl;
    }
}
