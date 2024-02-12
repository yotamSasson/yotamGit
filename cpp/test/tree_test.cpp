#include <iostream> //cout
#include "tree.hpp"

using namespace dev;

int main ()
{
    Tree t1("/Users/yotamsasson/Documents/Git/yotamGit");
    //t1.Print(0);

    Tree *t2 = t1.Clone();
    t2->Print();
    
    delete t2;
    
    return 0;
}
