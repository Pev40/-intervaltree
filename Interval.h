#ifndef __INTERVAL_H__
#define __INTERVAL_H__


class Interval
{
private:
        int low;
        int high;
public:
    Interval();
    Interval(int,int);
    int getLow();
    int getHigh();
    void setLow(int);
    void setHigh(int);
    ~Interval();
};

Interval::Interval(){}

Interval::Interval(int low , int high){
    this->low = low;
    this->high = high;
}

int Interval::getLow(){return this->low;}

int Interval::getHigh(){return this->high;}

void Interval::setHigh(int nuevo){this->high = nuevo;return;}

void Interval::setLow(int nuevo){this->low = nuevo;return;}

Interval::~Interval(){}





#endif