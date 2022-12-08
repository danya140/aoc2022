#pragma once

#include "helpers.h"
#include <memory>

struct File
{
public:
    File(int size, const std::string& name);

    int getSize() const;

private:
    int m_size;
    std::string m_name;
};

class Folder
{
public:
    Folder(const std::string& name);

    void addFolder(std::shared_ptr<Folder> folder);

    void addFile(const File& file);

    int getSize() const;
    std::string getName() const;

    std::vector<std::shared_ptr<Folder>> getFolders() const;

    std::shared_ptr<Folder> getFolder(const std::string& name);

private:
    std::vector<std::shared_ptr<Folder>> m_folders;
    std::vector<File> m_files;
    std::string m_name;
};


