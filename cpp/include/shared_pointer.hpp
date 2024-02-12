#ifndef MY_PROJECT_SHARED_POINTER
#define MY_PROJECT_SHARED_POINTER

#include <new> //new

namespace dev
{

template < typename T>
class SharedPtr
{
public:
    template <typename Y>
    friend class SharedPtr;

    template< typename Y > 
    SharedPtr(Y* ptr = nullptr);

    template< typename Y >
    SharedPtr(SharedPtr<Y>& other);

    ~SharedPtr();

    template< typename Y >
    SharedPtr<T>& operator=(SharedPtr<Y>& other);

    T& operator*() const;
    T* operator->() const;
    T* Get() const;


private:
    T  *ptr_;
    size_t *refCount_;
    void CleanUp();
};


/************************ constructor ************************/
template < typename T>
template< typename Y >
SharedPtr<T>::SharedPtr(Y *ptr) : ptr_(ptr), refCount_(new size_t(1)){}

template < typename T>
template< typename Y >
SharedPtr<T>::SharedPtr(SharedPtr<Y>& other) : ptr_(other.ptr_), refCount_(other.refCount_)
{
    ++(*refCount_);
}

/************************ Destructor ************************/
template < typename T>
SharedPtr<T>::~SharedPtr()
{
    CleanUp();
}

/************************* Operator ***************************/
template < typename T>
T& SharedPtr<T>::operator*() const
{
    return *ptr_;
}

template < typename T>
T* SharedPtr<T>::operator->() const
{
    return ptr_;
}

template < typename T>
template< typename Y >
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<Y>& other)
{
    ++(*other.refCount_);

    CleanUp();

   ptr_ = other.ptr_;
   refCount_ = other.refCount_;

   return *this;
}
/************************ Member Function ************************/
template < typename T>
T* SharedPtr<T>::Get() const
{
    return ptr_;
}

template < typename T>
void SharedPtr<T>::CleanUp()
{
    if (0 == --(*refCount_))
    {
        delete ptr_;
        delete refCount_;
    } 
}
}

#endif //MY_PROJECT_SHARED_POINTER
