#ifndef __INTERVALTREE_H__
#define __INTERVALTREE_H__
#include "Node.h"
#include <vector>
class IntervalTree
{
private:
    Node* head;

public:
    IntervalTree();
    IntervalTree(int,int);
    void insert(int,int);
    ~IntervalTree();
};

IntervalTree::IntervalTree()
{
    this->head = nullptr;
}

IntervalTree::IntervalTree(int min,int maxI){
    Node* nuevoNodo = new Node(min,maxI);
    if(head == nullptr){
        this->head = nuevoNodo;
        return;
    }
}

void IntervalTree::insert(int min, int max){
    if(head == nullptr){
        Node* nuevoNodo = new Node(min,max);
        this->head = nuevoNodo;
        return;
    }
    Node* nuevoNodo = new Node(min,max);
    Node* actual = head;
    Node* aux = nullptr;
    std::vector<Node*> lista;
    while (actual != nullptr)
    {
        lista.push_back(actual);
        aux = actual;
        if(min < actual->getIntervalo()->getLow()){
            actual = actual->getIzquierda();
        }else{
            actual = actual->getDerecha();
        }
    }
    if(aux->getIntervalo()->getLow() > min){
        aux->setIzquierdo(nuevoNodo);
    }else{
        aux->setDerecha(nuevoNodo);
    }
    

}

IntervalTree::~IntervalTree()
{
}

#endif