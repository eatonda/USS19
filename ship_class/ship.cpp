#include <iostream>
#include "ship.h"

using namespace std;

Ship::Ship(int length){
    size = length;
    health = size;
}

int Ship::getSize(){
    return size;
}

int Ship::getHealth(){
    return health;
}

int main(){
    Ship s(4);
    cout << "Ship size: " << s.getSize() << endl;
    cout << "Ship health: " <<s.getHealth() << endl;
    
    return 0;
}