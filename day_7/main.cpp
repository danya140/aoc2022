#include <iostream>

#include <memory>

#include "Folder.h"

#include "helpers.h"

const char* INPUT = "input.txt";

void parseFolder(std::ifstream& fileStream, std::shared_ptr<Folder>& rootFolder)
{
    std::string line;
    if(!std::getline(fileStream, line))
    {
        return;
    }

    while (!containsAll(line, "cd .."))
    {
        if(containsAll(line, "$ cd"))
        {
            std::vector<std::string> folderInfo = split(line, ' ');
            std::shared_ptr<Folder> folder = rootFolder->getFolder(folderInfo.at(2));
            parseFolder(fileStream, folder);
        }
        else if (!containsAll(line, "$ ls"))
        {
            if (containsAll(line.substr(0, 3), "dir"))
            {
                std::vector<std::string> folderInfo = split(line, ' ');
                std::shared_ptr<Folder> childFolder = std::make_shared<Folder>(folderInfo.at(1));

                rootFolder->addFolder(childFolder);
            }
            else
            {
                std::vector<std::string> fileInfo = split(line, ' ');
                int size = std::stoi(fileInfo.at(0));
                File file(size, fileInfo.at(1));

                rootFolder->addFile(file);
            }
        }

        if(!std::getline(fileStream, line))
        {
            return;
        }
    }
}

std::vector<std::string> readInput()
{
    std::ifstream file(INPUT);

    std::vector<std::string> inputData;

    std::shared_ptr<Folder> rootFolder = std::make_shared<Folder>("/");
    if(file.is_open())
    {
        std::string line;
        std::getline(file, line);
        parseFolder(file, rootFolder);
    }

    return inputData;
}

int main()
{
    START_TIMER(point_1)

    std::vector<std::string> input = readInput();
    std::cout << "Answer: " << std::endl;

    STOP_TIMER(point_1)
    return 0;
}
