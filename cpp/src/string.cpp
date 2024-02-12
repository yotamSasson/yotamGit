#include <cstring> //strlen, strcpy, strcmp
#include <utility> //swap
#include <cassert> //assert

#include "string.hpp" //string class decleration

namespace dev
{

/************************ Inline Function ************************/

inline void AssignStr(char* &s_, const char *str_)
{
    assert(NULL != str_);

    s_ = new char[strlen(str_) + 1];
    strcpy(s_, str_);
}

inline int StrCmp(const char *lhs_, const char *rhs_)
{
    assert(NULL != lhs_);
    assert(NULL != rhs_);

    return strcmp(lhs_, rhs_);
}

/************************ Constructors ************************/
String::String(const char *str_): m_str(NULL)
{
    assert(NULL != str_);

    AssignStr(m_str, str_);
}

String::String(const String& str_)
{
    AssignStr(m_str, str_.m_str);
}

/************************ destructor ************************/
String::~String()
{
    delete[] m_str;
}

/************************ operator ************************/
String& String::operator=(const String& str_)
{
    String temp(str_);
    std::swap(m_str, temp.m_str); //page 261 in the basic book item 11
    
    return *this; 
}

char& String::operator[](size_t index_)
{
    return m_str[index_];
}

/************************ Member Function ************************/
size_t String::Length() const
{
    return strlen(m_str);
}

const char* String::Cstr() const 
{
    return  m_str;
}

void String::Set(char * s_)
{
    String temp(s_);
    std::swap(m_str, temp.m_str); 
}

/************************ Non Member Function ************************/
std::ostream& operator<<(std::ostream& os_, const String& rhsObj_)
{
    return os_ << rhsObj_.Cstr();
}

bool operator==(const String& lhsObj_, const String& rhsObj_) 
{
    return 0 == StrCmp(lhsObj_.Cstr(), rhsObj_.Cstr());
}

bool operator>(const String& lhsObj_, const String& rhsObj_)
{
    return 0 < StrCmp(lhsObj_.Cstr(), rhsObj_.Cstr());
}

bool operator<(const String& lhsObj_, const String& rhsObj_)
{
    return 0 > StrCmp(lhsObj_.Cstr(), rhsObj_.Cstr());
}

std::istream& operator>>(std::istream& is_, String& rhsObj_)
{
    char temp_str[256];
    is_ >> temp_str;
    rhsObj_.Set(temp_str);
    return is_;
}

}

