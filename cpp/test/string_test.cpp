#include <iostream>
#include "string.hpp"

using namespace dev;

int main ()
{
    String s1("hello");
    String s2(s1);
    s1 = s2;
    s1.Length();
    s1.Cstr();

    std::cout << "s2 is:" << s1.Cstr() << std::endl;

    std::cout << s1 << std::endl;

    bool isEqual = s1 == s2;
    std::cout << "s1 == s2: " << std::boolalpha << isEqual << std::endl; //std::boolalpha display boolean values as "true" or "false"

    bool isLiteralEqual = "123" == s1;
    std::cout << "\"123\" == s1: " << std::boolalpha << isLiteralEqual << std::endl;

    bool isLiteralEqual2 = s1 == "123";
    std::cout << "s1 == \"123\": " << std::boolalpha << isLiteralEqual2 << std::endl;

    bool isGreater = s1 > s2;
    std::cout << "s1 > s2: " << std::boolalpha << isGreater << std::endl;

    bool isLess = s1 < s2;
    std::cout << "s1 < s2: " << std::boolalpha << isLess << std::endl;

    const char *s3 = "hello";
    const char *s4 = "hi";

    bool isEqual2 = s3 == s4;
    std::cout << "s3 == s4: " << std::boolalpha << isEqual2 << std::endl;


    std::cin >> s1;
    std::cout << "s1 is:" << s1.Cstr() << std::endl;

    return 0;
}
