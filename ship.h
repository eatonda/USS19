#ifndef SHIP_H
#define SHIP_H

#include <iostream>

using namespace std; 

class Ship{
    private:
        int size;
        int health;
    public:
        Ship(int size);
        int getSize();
        int getHealth();
};

#endif