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
    cout<<"Pos"<<endl;
    Itree.posorden();
    cout<<"In"<<endl;
    Itree.inorden();
    cout<<"Pre"<<endl;
    Itree.preorden();
    string archivo = "Salid.dot";
    Itree.dot(archivo);

    Itree.deleteNode(5,8);
    string archivo2 = "Salid2.dot";
    Itree.dot(archivo2);


    Itree.insert(5,8);
    string archivo3 = "Salid3.dot";
    Itree.dot(archivo3);

    bool Encontrado = Itree.search(5,8);
    if (Encontrado == true)
    {
        cout<<endl<<"Existe y esta vivo"<<endl;
    }else{
        cout<<endl<<"No hay nada manito"<<endl;
    }


    
    return 0;
}