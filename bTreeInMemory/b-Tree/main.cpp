#include <iostream>
#include <tree.h>
#include <node.h>
#define degree 3
using namespace std;

int main()
{

    tree<int> arvore(degree);
    arvore.insert(12);
    arvore.insert(8);
    arvore.insert(14);
    arvore.insert(10);
    arvore.insert(16);
    arvore.print();
    arvore.insert(17);
    arvore.print();
    return 0;
}
