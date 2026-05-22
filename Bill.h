#ifndef BILL_H
#define BILL_H

#include <iostream>
using namespace std;

class Bill {
private:
    int studentId;
    double amount;
    bool paid;

public:
    Bill() : studentId(0), amount(0), paid(false) {}
    Bill(int id, double a) : studentId(id), amount(a), paid(false) {}

    void display() {
        cout << "\n========== BILL ==========\n";
        cout << "Student ID: " << studentId << "\nAmount: Rs." << amount;
        cout << "\nStatus: " << (paid ? "PAID" : "UNPAID") << "\n==========================\n";
    }

    void pay()              { paid = true; }
    int getStudentId()      { return studentId; }
    double getAmount()      { return amount; }
    bool isPaid()           { return paid; }
};

#endif