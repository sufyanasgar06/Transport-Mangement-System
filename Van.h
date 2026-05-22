#ifndef VAN_H
#define VAN_H

#include "Vehicle.h"

class Van : public Vehicle {
public:
    Van();
    Van(int, string, int);
    ~Van();
    
    double getFee() override;
    string getType() override;
    void display() override;
};

#endif