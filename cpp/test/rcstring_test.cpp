#include <iostream> //std:cout

#include "rcstring.hpp" //string class decleration
#include "utilities.hpp" 

void TestCtor(void);
void TestAssignmentOperator(void);
void TestComparisonOperators(void);
void TestLength(void);
void TestIsShared(void);
void TestIndexOperator(void);
void TestCCtor(void);
void TesConversionOperator(void);

int main ()
{
    TestCtor();
    TestAssignmentOperator();
    TestComparisonOperators();
    TestLength();
    TestIsShared();
    TestIndexOperator();
    TestCCtor();
    TesConversionOperator();

    return 0;
}

void TestCtor(void)
{
    HEADER(Constructor);
    dev::RCString s1("yotam");
    
    TEST(0 == strcmp(s1.ToCStr(), "yotam"), TestCtor);
}

void TestAssignmentOperator(void)
{
    HEADER(Operator=);
    dev::RCString s1("yotam");
    dev::RCString s2("sasson");

    s1 = s2;
    TEST(0 == strcmp(s1.ToCStr(), "sasson"), TestOperator=);

    s1 = "ohad";
    TEST(0 == strcmp(s1.ToCStr(), "ohad"), TestOperator=);
}

void TestComparisonOperators(void)
{
    HEADER(Comparison Operators);
    dev::RCString s1("yotam");
    dev::RCString s2("yotam");

    TEST(true == (s1 == s2), TestOperator==);

    dev::RCString s3("yotamsasson");
    TEST(true == (s1 < s3), TestOperator<);

    TEST(true == (s3 > s1), TestOperator>);

    TEST(true == (s1 != s3), TestOperator!=);
}

void TestLength(void)
{
    HEADER(Length Method);

    dev::RCString s1("yotam");
    TEST(5 == s1.Length(), TestLength);

    dev::RCString s2("yotamsasson");
    TEST(11 == s2.Length(), TestLength);
}

void TestIsShared(void)
{
    HEADER(IsShared Method);

    dev::RCString s1("yotam");
    TEST(false == s1.IsShared(), TestIsShared);

    dev::RCString s2("sasson");
    s2 = s1;
    TEST(true == s1.IsShared(), TestIsShared);

    dev::RCString s3("ohad");
    s1 = s3;
    TEST(false == s2.IsShared(), TestIsShared);

    dev::RCString s4("darya");
    TEST(false == s4.IsShared(), TestIsShared);
}

void TestIndexOperator(void)
{
    HEADER(Index Operator);
    dev::RCString s1("yotam");
    char c = 'c';
    s1[2] = c;
    TEST(0 == strcmp(s1.ToCStr(), "yocam"), TestOperator[]);

    char y = s1[0];
    TEST(true == (y == 'y'), TestOperator[]);

    dev::RCString s2("sasson");
    s2 = s1;
    char t = 't';
    s2[2] = t;
    TEST(0 == strcmp(s1.ToCStr(), "yocam"), TestOperator[]);
    TEST(0 == strcmp(s2.ToCStr(), "yotam"), TestOperator[]);

    const dev::RCString& s4 = s2;
    char m = s4[4];
    TEST(true == (m == 'm'), TestConstOperator[]);
}

void TestCCtor(void)
{
    HEADER(Copy Constructor);
    dev::RCString s1("yotam");
    dev::RCString s2(s1);

    TEST(true == s1.IsShared(), TestCCtor);
    TEST(true == s2.IsShared(), TestCCtor);
    TEST(0 == strcmp(s2.ToCStr(), "yotam"), TestCCtor);

    dev::RCString s3 = s2;
    TEST(true == s3.IsShared(), TestCCtor);
    TEST(0 == strcmp(s3.ToCStr(), "yotam"), TestCCtor);

    s2 = "ohad";
    s3 = s2;
    TEST(true != s1.IsShared(), TestCCtor);
}

void TesConversionOperator(void)
{
    HEADER(Conversion Operator);

    dev::RCString s1("yotam");
    const char* s2 = s1;

    TEST(0 == strcmp(s2, "yotam"), TestOperator());
}
