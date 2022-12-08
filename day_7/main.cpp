#include <iostream>

#include <memory>

#include "Folder.h"

#include "helpers.h"

const char* INPUT = "input.txt";

const long long int TOTAL_SIZE = 70000000;
const long long int UPDATE_SIZE = 30000000;

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

std::shared_ptr<Folder>readInput()
{
    std::ifstream file(INPUT);

    std::shared_ptr<Folder> rootFolder = std::make_shared<Folder>("/");
    if(file.is_open())
    {
        std::string line;
        std::getline(file, line);
        parseFolder(file, rootFolder);
    }

    return rootFolder;
}

void printFoldersSize(std::shared_ptr<Folder> rootFolder, int level)
{
    std::string tab;
    for (int i = 0; i < level; ++i)
    {
        tab += "\t";
    }

    std::cout << tab << rootFolder->getName() << " size:" << rootFolder->getSize() << std::endl;
    for (const std::shared_ptr<Folder>& folder : rootFolder->getFolders())
    {
        printFoldersSize(folder, level + 1);
    }
}

long long int foldersSmallerThan(std::shared_ptr<Folder> rootFolder, int limit, long long int& totalSize)
{
    for (const std::shared_ptr<Folder>& folder : rootFolder->getFolders())
    {
        foldersSmallerThan(folder, limit, totalSize);
    }

    long long int rootSize = rootFolder->getSize();
    if(rootSize <= limit)
    {
        totalSize += rootSize;
    }

    return totalSize;
}

long long int needFreedUp(std::shared_ptr<Folder> rootFolder)
{
    return UPDATE_SIZE - (TOTAL_SIZE - rootFolder->getSize());
}

void foldersBiggerThan(std::shared_ptr<Folder> rootFolder, long long int limit, std::vector<int>& sizes)
{
    for (const std::shared_ptr<Folder>& folder : rootFolder->getFolders())
    {
        foldersBiggerThan(folder, limit, sizes);
    }

    long long int rootSize = rootFolder->getSize();
    if(rootSize >= limit)
    {
        sizes.push_back(rootSize);
    }
}

int findOptimalFolderForDeletion(std::shared_ptr<Folder> rootFolder)
{
    std::vector<int> sizes;
    foldersBiggerThan(rootFolder, needFreedUp(rootFolder), sizes);
    std::sort(sizes.begin(),  sizes.end());

    return sizes.front();
}

int main()
{
    START_TIMER(point_1)

    std::shared_ptr<Folder> input = readInput();
//    printFoldersSize(input, 0);

    long long int totalSize = 0;
    foldersSmallerThan(input, 100000, totalSize);
    std::cout << "Total size of all folders smaller than 100000: " << totalSize << std::endl;

    std::cout << "Need to freed up " << needFreedUp(input) << std::endl;
    std::cout << "Size of folder optimal for deletion " << findOptimalFolderForDeletion(input) << std::endl;

    STOP_TIMER(point_1)
    return 0;
}
