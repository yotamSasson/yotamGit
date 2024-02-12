#ifndef MY_PROJECT_RCSTRING_HPP
#define MY_PROJECT_RCSTRING_HPP

#if cplusplus >= 201103L 
// noexcept is defined, do nothing
#else
#define noexcept throw()
#endif // #if cplusplus >= 201103L

#include <cassert> //assert
#include <cstddef> //size_t
#include <cstring> //strlen, strcpy
#include <ostream>


namespace dev
{

class RCString
{
public: 
    RCString(const char* s_ = ""); // Non explicit on purpose
    RCString(const RCString& other_);
    RCString& operator=(const RCString& other_);
    operator char*() const;
    ~RCString() throw();
    inline char& operator[](size_t indx_);
    inline const char& operator[](size_t indx_) const;
    inline const char *ToCStr() const;
    inline size_t Length() const;
    inline bool IsShared() const;

private:

   struct m_rcString_t
    {
        size_t counter;
        char data[1];
    };

    m_rcString_t *m_sptr;
};

std::ostream& operator<<(std::ostream& os_, const RCString& rcsObj_);

inline bool operator==(const RCString& lhs_, const RCString& rhs_);
inline bool operator!=(const RCString& lhs_, const RCString& rhs_);
inline bool operator>(const RCString& lhs_, const RCString& rhs_);
inline bool operator<(const RCString& lhs_, const RCString& rhs_);


/************************* Member Functions ***************************/

inline const char *RCString::ToCStr() const
{
    return m_sptr->data;
}

inline size_t RCString::Length() const
{
    return strlen(m_sptr->data);
}

inline bool RCString::IsShared() const
{
    return  (1 < m_sptr->counter);
}

/********************** Comparison Operators ************************/
inline bool operator==(const RCString& lhs_, const RCString& rhs_)
{
    return (0 == strcmp(lhs_.ToCStr(), rhs_.ToCStr()));
}

inline bool operator!=(const RCString& lhs_, const RCString& rhs_)
{
    return !(lhs_ == rhs_);
}

inline bool operator>(const RCString& lhs_, const RCString& rhs_)
{
    return (0 < strcmp(lhs_.ToCStr(), rhs_.ToCStr()));
}

inline bool operator<(const RCString& lhs_, const RCString& rhs_)
{
    return (0 > strcmp(lhs_.ToCStr(), rhs_.ToCStr()));
}

/************************ operators ************************/
inline char& RCString::operator[](size_t indx_)
{
    assert(indx_ < this->Length());
    
    RCString temp(this->ToCStr());
    std::swap(m_sptr, temp.m_sptr);

    return m_sptr->data[indx_];   
}

inline const char& RCString::operator[](size_t indx_) const
{
    assert(indx_ < this->Length());

    return m_sptr->data[indx_];
}

}

#endif //MY_PROJECT_RCSTRING_HPP
