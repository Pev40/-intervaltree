#include <iostream>
#include "IntervalTree.h"
using namespace std;

int main(){

    IntervalTree Itree = IntervalTree();
    Itree.insert(21,16);
    Itree.insert(25,30);
    Itree.insert(5,8);
    Itree.insert(15,23);
    Itree.insert(17,19);
    Itree.insert(26,26);
    Itree.insert(0,3);
    Itree.insert(6,10);
    Itree.insert(19,20);
    Itree.print();
    string archivo = "Salid.dot";
    Itree.dot(archivo);
    return 0;
}