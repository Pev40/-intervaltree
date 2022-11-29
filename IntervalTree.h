#ifndef __INTERVALTREE_H__
#define __INTERVALTREE_H__
#include "Node.h"
#include <iostream>
#include <vector>
#include <fstream>
/*
Implentación en base a la Sección 14.3 del Libro de INTRODUCTIÓN TO ALGORITHNS 3TH
29/11/2022
AED 2022B
*/
class IntervalTree
{
private:
    Node *head;
    int count;

public:
    // CONSTRUCTORES
    IntervalTree();
    IntervalTree(int, int);
    // Insertar
    void insert(int, int);
    // Impresion
    void print();
    void print(Node *);
    // Verificar Arbol Esperado
    void preorden(Node *);
    void inorden(Node *);
    void posorden(Node *);
    void preorden();
    void inorden();
    void posorden();
    // Eliminar un nodo de rango
    void deleteNode(Node *, int, int);
    void deleteNode(int, int);
    Node *levantarDerecha(Node *);
    Node *levantarIzquierda(Node *);
    // Graficar con Grafiph
    void dot(std::string);
    void dot(std::ofstream &file, Node *current);
    // Buscar un nodo
    bool search(Node *, int, int);
    bool search(int, int);
    // Contar cantidad de Nodos
    int countNodes();
    ~IntervalTree();
};

IntervalTree::IntervalTree()
{
    this->head = nullptr;
    this->count = 0;
}

IntervalTree::IntervalTree(int min, int maxI)
{
    Node *nuevoNodo = new Node(min, maxI);
    if (head == nullptr)
    {
        this->head = nuevoNodo;
        this->count = 1;
        return;
    }
}

void IntervalTree::insert(int min, int max)
{
    if (head == nullptr)
    {
        Node *nuevoNodo = new Node(min, max);
        this->head = nuevoNodo;
        this->count = 1;
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
        }
        else
        {
            lista[i]->setMax(std::max(std::max(lista[i]->getMax(), lista[i]->getIzquierda()->getMax()), lista[i]->getDerecha()->getMax()));
        }
    }
    this->count++;
}

void IntervalTree::preorden(Node *actual)
{
    if (actual != nullptr)
    {
        std::cout << "<" << actual->getIntervalo()->getLow() << "-" << actual->getIntervalo()->getHigh() << " >" << std::endl;
        preorden(actual->getIzquierda());
        preorden(actual->getDerecha());
    }
    return;
}

void IntervalTree::inorden(Node *actual)
{
    if (actual != nullptr)
    {
        inorden(actual->getIzquierda());
        std::cout << "<" << actual->getIntervalo()->getLow() << "-" << actual->getIntervalo()->getHigh() << " >" << std::endl;
        inorden(actual->getDerecha());
    }
    return;
}

void IntervalTree::posorden(Node *actual)
{
    if (actual != nullptr)
    {
        posorden(actual->getIzquierda());
        std::cout << "<" << actual->getIntervalo()->getLow() << "-" << actual->getIntervalo()->getHigh() << " >" << std::endl;
        posorden(actual->getDerecha());
    }
    return;
}

void IntervalTree::preorden()
{
    preorden(this->head);
    return;
}
void IntervalTree::inorden()
{
    inorden(this->head);
    return;
}
void IntervalTree::posorden()
{
    posorden(this->head);
    return;
}

// Plotting a Tree
void IntervalTree::dot(std::string filename)
{
    std::ofstream mydot;
    mydot.open(filename, std::ios::out);
    mydot << "digraph g {\n";
    mydot << "node [shape=record, height=0.1];\n";
    dot(mydot, this->head);
    mydot << "}";

    mydot.close();
}
void IntervalTree::dot(std::ofstream &file, Node *current)
{
    if (current == nullptr)
    {
        return;
    }
    else
    {
        current->dot(file);
        dot(file, current->getIzquierda());
        dot(file, current->getDerecha());
    }
}

// Eliminar un rango

Node *IntervalTree::levantarDerecha(Node *actual)
{
    if (actual->getDerecha() == nullptr)
    {
        return actual;
    }
    return levantarDerecha(actual->getDerecha());
}

Node *IntervalTree::levantarIzquierda(Node *actual)
{
    if (actual->getIzquierda() == nullptr)
    {
        return actual;
    }
    return levantarIzquierda(actual->getIzquierda());
}

void IntervalTree::deleteNode(Node *actual, int min, int max)
{
    // Casos Base
    if (actual == nullptr)
    {
        std::cout << "No existe el rango" << std::endl;
        // std::cout<<"Arbol Vacio"<<std::endl
        return;
    }
    if (min == actual->getIntervalo()->getLow() && max == actual->getIntervalo()->getHigh())
    {
        // std::cout<<"Se Encontro"<<std::endl;
        if (actual->getDerecha() != nullptr)
        {
            // std::cout<<"Caso1"<<std::endl;
            Node *derechaExtremo = levantarDerecha(actual->getDerecha());
            actual->getIntervalo()->setHigh(derechaExtremo->getIntervalo()->getHigh());
            actual->getIntervalo()->setLow(derechaExtremo->getIntervalo()->getLow());
            derechaExtremo = nullptr;
            // delete derechaExtremo;
        }

        if (actual->getIzquierda() != nullptr)
        {
            // std::cout<<"Caso2"<<std::endl;
            Node *izquierdaExtremo = levantarIzquierda(actual->getIzquierda());
            actual->getIntervalo()->setHigh(izquierdaExtremo->getIntervalo()->getHigh());
            actual->getIntervalo()->setLow(izquierdaExtremo->getIntervalo()->getLow());
            izquierdaExtremo = nullptr;
            // delete izquierdaExtremo;
        }
        else
        {
            // std::cout<<"Me elimine"<<std::endl;
            delete actual;
        }
        count--;
        return;
    }
    //
    if (actual->getIntervalo()->getLow() <= min)
    {
        // std::cout<<"Derecha"<<std::endl;
        return deleteNode(actual->getDerecha(), min, max);
    }
    if (actual->getIntervalo()->getLow() >= min)
    {
        // std::cout<<"Izquierda"<<std::endl;
        return deleteNode(actual->getIzquierda(), min, max);
    }
}

void IntervalTree::deleteNode(int min, int max)
{
    if (max < min)
    {
        int temp = min;
        max = min;
        min = temp;
    }
    deleteNode(this->head, min, max);
    return;
}

bool IntervalTree::search(Node *actual, int min, int max)
{
    if (actual->getIntervalo()->getLow() <= max && actual->getIntervalo()->getHigh() >= max)
    {
        return true;
    }
    if (actual->getIntervalo()->getLow() <= min && actual->getIntervalo()->getHigh() >= min)
    {
        return true;
    }
    if (actual->getDerecha() != nullptr || actual->getIzquierda() != nullptr)
    {
        if (actual->getIzquierda() != nullptr && actual->getIzquierda()->getMax() > min)
        {
            return search(actual->getIzquierda(), min, max);
        }
        if (actual->getDerecha() != nullptr)
        {
            return search(actual->getDerecha(), min, max);
        }
    }

    return false;
}

bool IntervalTree::search(int min, int max)
{
    return search(this->head, min, max);
}

int IntervalTree::countNodes(){return this->count;}

IntervalTree::~IntervalTree()
{
}

#endif