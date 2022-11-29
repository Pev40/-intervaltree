#ifndef __INTERVALTREE_H__
#define __INTERVALTREE_H__
#include "Node.h"
#include <iostream>
#include <vector>
#include <fstream>
class IntervalTree
{
private:
    Node *head;

public:
    IntervalTree();
    IntervalTree(int, int);
    void insert(int, int);
    void print();
    void print(Node *);
    void dot(std::string);
    void dot(std::ofstream &file, Node* current);
    ~IntervalTree();
};

IntervalTree::IntervalTree()
{
    this->head = nullptr;
}

IntervalTree::IntervalTree(int min, int maxI)
{
    Node *nuevoNodo = new Node(min, maxI);
    if (head == nullptr)
    {
        this->head = nuevoNodo;
        return;
    }
}

void IntervalTree::insert(int min, int max)
{
    if (head == nullptr)
    {
        Node *nuevoNodo = new Node(min, max);
        this->head = nuevoNodo;
        return;
    }
    Node *nuevoNodo = new Node(min, max);
    Node *actual = head;
    Node *aux = nullptr;
    std::vector<Node *> lista;
    while (actual != nullptr)
    {
        lista.push_back(actual);
        aux = actual;
        if (min < actual->getIntervalo()->getLow())
        {
            actual = actual->getIzquierda();
        }
        else
        {
            actual = actual->getDerecha();
        }
    }
    if (aux->getIntervalo()->getLow() > min)
    {
        aux->setIzquierdo(nuevoNodo);
    }
    else
    {
        aux->setDerecha(nuevoNodo);
    }

    for (int i = 0; i < lista.size(); i++)
    {
        if (lista[i]->getIzquierda() == nullptr || lista[i]->getDerecha() == nullptr)
        {
            if (lista[i]->getIzquierda() == nullptr)
            {
                lista[i]->setMax(std::max(lista[i]->getMax(), lista[i]->getDerecha()->getMax()));
            }
            else if (lista[i]->getDerecha() == nullptr)
            {
                lista[i]->setMax(std::max(lista[i]->getMax(), lista[i]->getIzquierda()->getMax()));
            }
        }else{
              lista[i]->setMax(std::max(std::max(lista[i]->getMax(), lista[i]->getIzquierda()->getMax()), lista[i]->getDerecha()->getMax()));
        }            
    }
}

void IntervalTree::print(Node *actual)
{
    if (actual == nullptr)
    {
        return;
    }
    std::cout << "<" << actual->getIntervalo()->getLow() << "," << actual->getIntervalo()->getHigh() << " max=" << actual->getMax() << ">" << std::endl;
    print(actual->getIzquierda());
    print(actual->getDerecha());
}

void IntervalTree::print()
{
    print(head);
    return;
}

    // Plotting a Tree
void IntervalTree::dot(std::string filename){
    std::ofstream mydot;
    mydot.open(filename, std::ios::out);
    mydot << "digraph g {\n";
    mydot << "node [shape=record, height=0.1];\n";
    dot(mydot, this->head);
    mydot << "}";
    mydot.close();
}
void IntervalTree::dot(std::ofstream &file, Node* current){
    if (current==nullptr)
    {
        return;
    }else{
        current->dot(file);
        dot(file, current->getIzquierda());
        dot(file, current->getDerecha());
    }
}



IntervalTree::~IntervalTree()
{
}

#endif