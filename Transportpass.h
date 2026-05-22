#ifndef TRANSPORTPASS_H
#define TRANSPORTPASS_H

#include "student.h"
#include "vehicle.h"
#include "route.h"
#include "bill.h"

class TransportPass {
private:
    int passId;
    Student* student;
    Vehicle* vehicle;
    Route* route;
    Bill* bill;

public:
    TransportPass(Student* s, Vehicle* v, Route* r, Bill* b) {
        passId  = rand() % 9000 + 1000;
        student = s;
        vehicle = v;
        route   = r;
        bill    = b;
    }
    ~TransportPass() {}

    void display() {
        cout << "\n========== TRANSPORT PASS ==========\n";
        cout << "Pass ID: " << passId << "\nStudent: " << student->getName();
        cout << "\nRoute: " << route->getStart() << " -> " << route->getEnd();
        cout << "\nVehicle: " << vehicle->getType() << " | " << vehicle->getNumber();
        bill->display();
        cout << "====================================\n";
    }

    Student* getStudent() { return student; }
    Bill*    getBill()    { return bill; }
};

#endif