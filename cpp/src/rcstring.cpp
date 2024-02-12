#include <new> //new

#include "rcstring.hpp" //string class decleration

namespace dev
{

 /*********************** Destructor ***************************/
RCString::~RCString() noexcept
{
    --m_sptr->counter;

    if (0 == m_sptr->counter)
    {
        delete m_sptr;
    } 
}

/************************ Constructors ************************/
RCString::RCString(const char *s_): m_sptr(NULL)
{
    assert(NULL != s_);

    m_sptr = static_cast<m_rcString_t*>(operator new(strlen(s_) + offsetof(m_rcString_t , data[1])));
    strcpy(m_sptr->data, s_);
    m_sptr->counter = 1;
}

RCString::RCString(const RCString& other_) : m_sptr(other_.m_sptr)
{
    ++m_sptr->counter;
}

/************************ operators ************************/
RCString& RCString::operator=(const RCString& other_)
{
    ++(other_.m_sptr->counter);

    if (1 == m_sptr->counter)
    {
        delete m_sptr;
    }
    else
    {
        --m_sptr->counter;
    }
    m_sptr = other_.m_sptr;
     
    return *this;
}
RCString::operator char*() const
{
    return m_sptr->data;
}

/************************ Non Member Function ************************/
std::ostream& operator<<(std::ostream& os_, const RCString& rcsObj_)
{
    return os_ << rcsObj_.ToCStr();
}

}
