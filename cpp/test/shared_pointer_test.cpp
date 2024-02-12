#include <iostream>
#include <new> //new

#include "shared_pointer.hpp"
#include "utilities.hpp" 

using namespace dev;

class B
{
public:
    B(int x = 0): b_num(x){};
    virtual ~B(){}
    virtual void Foo(){std::cout << "B Foo " <<  std::endl;}
    virtual int GetNum(){return b_num;}
private:
    int b_num;
};

class D : public B
{
public: 
    D(int x = 0): d_num(x){};
    void Foo(){std::cout << "D Foo " <<  std::endl;}
    int GetNum(){return d_num;}
private:
    int d_num;
};

class C 
{
public: 
    void Foo(){std::cout << "C Foo " <<  std::endl;}
    int GetNum(){return c_num;}
private:
    int c_num;
};


void TestAssignmentOperator(void);
void TestCopyConstructor(void);
void TestDereferencesOperator(void);

int main ()
{
    TestAssignmentOperator();
    TestCopyConstructor();
    TestDereferencesOperator();

    B *b2 = nullptr;
    SharedPtr<B> sb3(b2);//empty shared pointer

    //SharedPtr<D> sd2= new SharedPtr<D>(); cannot create shared_ptr on the heap

    //C *c1 = new C;
    //SharedPtr<D>sd1(c1); C is not convertible to D

    return 0;
}

void TestAssignmentOperator()
{
    HEADER(Assignment Operator);

    B *b = new B(2);
    D *d = new D(9);
    SharedPtr<B> sb1(b);
    SharedPtr<D>sd1(d);

    sb1 = sd1;
    TEST(sb1.Get() == sd1.Get(), TestOperator=);

    SharedPtr<D>sd2(new D(11));
    sd2 = sd1;
    TEST(sd2.Get() == sd1.Get(), TestOperator=);

    sd2 = sd2;//self assignment
    TEST(sd2.Get() == sd1.Get(), TestOperator=);    
}

void TestCopyConstructor()
{
    HEADER(Copy Constructor);

    B *b = new B(9);
    SharedPtr<B>sb1(b);
    SharedPtr<B>sb2(sb1);

    TEST(sb2.Get() == sb1.Get(), TestCCtor);

    SharedPtr<B>sb3(sb2);
    TEST(sb3.Get() == sb2.Get(), TestCCtor);

    D *d = new D(3);
    SharedPtr<D>sd2(d);
    SharedPtr<B>sb4(sd2);
    TEST(sd2.Get() == sb4.Get(), TestCCtor);
}

void TestDereferencesOperator()
{
    HEADER(Dereferences Operator);

    D *d = new D(3);
    SharedPtr<D>sd1(d);

    TEST(sd1->GetNum() == 3, TestOperator->);

    D *d1 = new D(1);
    SharedPtr<D>sd2(d1);
    SharedPtr<B>sb1(sd2);

    TEST(sb1->GetNum() == 1, TestOperator->);

    D d2 = *sd1;
    TEST(d2.GetNum() == sd1->GetNum(), TestOperator*);

    B b1 = *sd1;
    TEST(b1.GetNum() == 0, TestOperator*);

    B *b2 = new B(2);
    SharedPtr<B>sb2(b2);
    B &b3 = *sb2;
    B b4(3);
    b3 = b4;

    TEST(sb2->GetNum() == 3, TestOperator*);
}

