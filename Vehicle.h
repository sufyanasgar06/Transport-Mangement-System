#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
using namespace std;

class Vehicle {
protected:
    int id;
    char number[20];
    int capacity;
    int occupied;
    int routeId;

public:
    Vehicle() : id(0), capacity(0), occupied(0), routeId(-1) {
        number[0] = '\0';
    }
    Vehicle(int i, const char* n, int c) : id(i), capacity(c), occupied(0), routeId(-1) {
        strcpy(number, n);
    }
    virtual ~Vehicle() {}

    virtual double getFee() = 0;
    virtual const char* getType() = 0;
    virtual void display() {
        cout << "ID: " << id << " | Number: " << number << " | Capacity: " << capacity;
        cout << " | Fee: Rs." << getFee() << " | Available: " << (capacity - occupied) << endl;
    }

    bool hasSeat() { return occupied < capacity; }
    void addPassenger()    { if(hasSeat()) occupied++; }
    void removePassenger() { if(occupied > 0) occupied--; }

    int getId()           { return id; }
    const char* getNumber() { return number; }
    int getCapacity()     { return capacity; }
    int getOccupied()     { return occupied; }
    int getRouteId()      { return routeId; }
    void setRouteId(int r){ routeId = r; }
};

class Bus : public Vehicle {
public:
    Bus() : Vehicle() {}
    Bus(int i, const char* n, int c) : Vehicle(i, n, c) {}
    double getFee() override      { return 5000; }
    const char* getType() override { return "Bus"; }
};

class Van : public Vehicle {
public:
    Van() : Vehicle() {}
    Van(int i, const char* n, int c) : Vehicle(i, n, c) {}
    double getFee() override      { return 3500; }
    const char* getType() override { return "Van"; }
};

#endif