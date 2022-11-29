#ifndef __NODE_H__
#define __NODE_H__
#include "Interval.h"
#include <string.h>
#include <iostream>
#include <fstream>
class Node
{
private:
    Interval* intervalo;
    int max;
    Node* der;
    Node* izq;

public:
    Node();
    Node(int,int);
    ~Node();

    void setIntervalo(int,int);
    void setMax(int);
    void setDerecha(Node*);
    void setIzquierdo(Node*);

    Node* getDerecha();
    Node* getIzquierda();
    int getMax();
    Interval* getIntervalo();

    void dot(std::ostream &file){
        file<<"node_"<<intervalo->getLow()<<"_"<<intervalo->getHigh()<<" [label = \"<l> | <m> "<< intervalo->getLow()<<"_"<<intervalo->getHigh() <<" | <r>\"];\n";
        if(izq){
            file<<"node_"<<intervalo->getLow()<<"_"<<intervalo->getHigh()<<":l -> node_"<<izq->intervalo->getLow()<<"_"<<izq->intervalo->getHigh() <<":m;\n";
        }
        if(der){
            file<<"node_"<<intervalo->getLow()<<"_"<<intervalo->getHigh()<<":r -> node_"<<der->intervalo->getLow()<<"_"<<der->intervalo->getHigh()<<":m;\n";
        }
    }
};

Node::Node()
{
    this->intervalo = nullptr;
    this->der = nullptr;
    this->izq = nullptr;
}

Node::Node(int MinI,int MaxI)
{
    setIntervalo(MinI,MaxI);
    this->der = nullptr;
    this->izq = nullptr;
    this->max = MaxI;
}


Node* Node::getDerecha(){return this->der;}
Node* Node::getIzquierda(){return this->izq;}
int Node::getMax(){return this->max;}
Interval* Node::getIntervalo(){return this->intervalo;}

void Node::setDerecha(Node* nuevo){this->der=nuevo;return;}
void Node::setIzquierdo(Node* nuevo){this->izq=nuevo;return;}
void Node::setMax(int nuevo){this->max=nuevo;return;}
void Node::setIntervalo(int min,int max){
    if(min>max){
        Interval* nuevoI = new Interval(max,min);
        this->intervalo = nuevoI;
        return;
    }else{
        Interval* nuevoI = new Interval(min,max);
        this->intervalo = nuevoI;
        return;      
    }

}




Node::~Node()
{
    
}
#endif
