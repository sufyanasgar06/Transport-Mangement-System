#ifndef BUS_H
#define BUS_H

#include "Vehicle.h"

class Bus : public Vehicle {
public:
    Bus();
    Bus(int, string, int);
    ~Bus();
    
    double getFee() override;
    string getType() override;
    void display() override;
};

#endif