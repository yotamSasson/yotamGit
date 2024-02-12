#ifndef MY_PROJECT_STRING_HPP
#define MY_PROJECT_STRING_HPP

#include <cstddef> //size_t
#include <iostream> // Include the iostream header

namespace dev
{

class String
{
public:
    /*
    * Default ctor for a String
    */
    String(const char *str_ = "");

    /*
    * CopyCtor for a String from a String object
    */
    String(const String& str_);

    /*
    * Dtor a String object
    */
    ~String();

    /*
    * Assignment operator for a String object
    */
    String& operator=(const String& str_);
    
    /*
    * Indexing operator for a String object
    */
    char& operator[](size_t index_);

    /*
    * Returns the lenght of a String object
    */
    size_t Length() const;

    /*
    * Returns a const char * type string wrapped in String object
    */
    const char *Cstr() const;

    void Set(char * s_);

private:
    char *m_str;
};

std::ostream& operator<<(std::ostream& os_, const String& rhsObj_);
std::istream& operator>>(std::istream& is_, String& rhsObj_);

bool operator==(const String& lhsObj_, const String& rhsObj_);
bool operator>(const String& lhsObj_, const String& rhsObj_);
bool operator<(const String& lhsObj_, const String& rhsObj_);
}

#endif //MY_PROJECT_STRING_HPP
