#ifndef MY_PROJECT_LOCK_HPP
#define MY_PROJECT_LOCK_HPP

namespace dev
{

template < class T>
class LockGuard
{
public: 
    explicit LockGuard( T &lock_);
    ~LockGuard();

private:
    T &lock;
    LockGuard(const LockGuard&) = delete;
    LockGuard& operator=(const LockGuard&) = delete;
};

template < class T>
LockGuard<T>::LockGuard( T &lock_) :lock(lock_)
{
    lock.lock();
}

template < class T>
LockGuard<T>::~LockGuard()
{
    lock.unlock(); 
}

}

#endif //MY_PROJECT_LOCK_HPP
