#include "Folder.h"

File::File(int size, const std::string& name)
    : m_size(size),
      m_name(name)
{}

int File::getSize() const
{
    return m_size;
}

Folder::Folder(const std::string& name)
    : m_name(name)
{
}

void Folder::addFolder(std::shared_ptr<Folder> folder)
{
    m_folders.push_back(folder);
}

void Folder::addFile(const File &file)
{
    m_files.push_back(file);
}

int Folder::getSize() const
{
    int size = 0;
    for (const File& file : m_files)
    {
        size += file.getSize();
    }

    for (const std::shared_ptr<Folder>& subFolder : m_folders)
    {
        size += subFolder->getSize();
    }

    return size;
}

std::string Folder::getName() const
{
    return m_name;
}

std::shared_ptr<Folder> Folder::getFolder(const std::string &name)
{
    for (const std::shared_ptr<Folder>& folder : m_folders)
    {
        if(folder->getName() == name)
        {
            return folder;
        }
    }
}
