#include <iostream> //cout
#include <cstring>  // strcmp
#include <dirent.h> //DIR

#include "tree.hpp"

namespace dev
{

    class Directory : public IFile
    {
    public:
        explicit Directory(const char *path);
        virtual ~Directory();
        virtual void Print(unsigned int depth = 0) const;
        virtual Directory *Clone() const;

    protected:
        Directory(const Directory &other);

    private:
        std::string m_dir_name;
        std::vector<IFile *> m_tree_vector;
    };

    class File : public IFile
    {
    public:
        explicit File(const char *path);
        virtual ~File();
        virtual File *Clone() const;
        virtual void Print(unsigned int depth = 0) const;

    protected:
        File(const File &other);

    private:
        std::string m_file_name;
    };

    /************************ IFile ************************/
    IFile::IFile() {}
    IFile::~IFile() {}
    IFile::IFile(const IFile &other) { (void)other; }

    /*********************** File ************************/
    File::File(const char *path) : m_file_name(path) {}

    File::~File() {}

    void File::Print(unsigned int depth) const
    {
        for (size_t i = 0; i < depth; i++)
        {
            std::cout << "\u2502" << '\t';
        }

        std::cout << "\u251c\u2500\u2500 " << m_file_name << std::endl;
    }

    File::File(const File &other) : IFile(other), m_file_name(other.m_file_name) {}

    File *File::Clone() const
    {
        return new File(*this);
    }

    /************************ Directory ************************/
    Directory::Directory(const char *path) : m_dir_name(path)
    {
        struct dirent *entry = NULL;
        DIR *dir = opendir(path);

        if (dir)
        {
            try
            {
                while (NULL != (entry = readdir(dir)))
                {
                    if (DT_REG == entry->d_type)
                    {
                        File *f = new File(entry->d_name);
                        m_tree_vector.push_back(f);
                    }
                    else if (DT_DIR == entry->d_type && 0 != strcmp(entry->d_name, ".") && 0 != strcmp(entry->d_name, ".."))
                    {
                        std::string subdir_path = std::string(path) + "/" + std::string(entry->d_name);
                        Directory *subdir = new Directory(subdir_path.c_str());
                        m_tree_vector.push_back(subdir);
                    }
                }
            }
            catch (...)
            {
                for (std::vector<IFile *>::iterator it = m_tree_vector.begin(); it != m_tree_vector.end(); ++it)
                {
                    delete (*it);
                }
                closedir(dir);
                throw;
            }
            closedir(dir);
        }
    }

    Directory::~Directory()
    {
        for (std::vector<IFile *>::iterator it = m_tree_vector.begin(); it != m_tree_vector.end(); ++it)
        {
            delete (*it);
        }
    }

    void Directory::Print(unsigned int depth) const
    {
        for (size_t i = 0; i < depth; i++)
        {
            std::cout << "\u2502" << '\t';
        }

        std::cout << "\u251c\u2500\u2500\x1B[1;34m" << m_dir_name.substr(m_dir_name.find_last_of("/\\") + 1) << "\x1B[0m" << std::endl;
        for (std::vector<IFile *>::const_iterator it = m_tree_vector.begin(); it != m_tree_vector.end(); ++it)
        {
            (*it)->Print(depth + 1);
        }
    }

    Directory::Directory(const Directory &other) : IFile(other), m_dir_name(other.m_dir_name)
    {
        for (std::vector<IFile *>::const_iterator it = other.m_tree_vector.begin(); it != other.m_tree_vector.end(); ++it)
        {
            m_tree_vector.push_back((*it)->Clone());
        }
    }

    Directory *Directory::Clone() const
    {
        return new Directory(*this);
    }
    /************************ Tree **********************/
    Tree::Tree(const char *path) : root_path(new Directory(path)) {}

    Tree::~Tree()
    {
        delete root_path;
    }

    void Tree::Print(unsigned int depth) const
    {
        root_path->Print(depth);
    }

    Tree::Tree(const Tree &other) : IFile(other)
    {
        root_path = (other.root_path->Clone());
    }

    Tree *Tree::Clone() const
    {
        return new Tree(*this);
    }

}
