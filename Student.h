#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"

class Student : public User {
private:
    char department[30];
    int semester;
    char status[20];
    int routeId;
    int vehicleId;
    double fee;

public:
    Student() : semester(0), routeId(-1), vehicleId(-1), fee(0) {
        department[0] = '\0';
        strcpy(status, "Not Applied");
    }

    Student(int i, const char* n, const char* p, const char* d, int s)
        : User(i, n, p, "Student"), semester(s), routeId(-1), vehicleId(-1), fee(0) {
        strcpy(department, d);
        strcpy(status, "Not Applied");
    }

    void display() {
        cout << "\n----------------------------------------\n";
        cout << "ID: " << id << "\nName: " << name << "\nDepartment: " << department;
        cout << "\nSemester: " << semester << "\nStatus: " << status;
        if(fee > 0) cout << "\nPending Fee: Rs. " << fixed << setprecision(2) << fee;
        cout << "\n----------------------------------------\n";
    }

    const char* getDepartment() { return department; }
    int getSemester() { return semester; }
    const char* getStatus() { return status; }
    int getRouteId() { return routeId; }
    int getVehicleId() { return vehicleId; }
    double getFee() { return fee; }

    void setStatus(const char* s) { strcpy(status, s); }
    void setRouteId(int r) { routeId = r; }
    void setVehicleId(int v) { vehicleId = v; }
    void setFee(double f) { fee = f; }
    void apply(int rId, int vId) {
        routeId = rId;
        vehicleId = vId;
        strcpy(status, "Pending");
    }
    void approve() { strcpy(status, "Approved"); }
    void reject()  { strcpy(status, "Rejected"); }
    void cancelReg() {
        strcpy(status, "Not Applied");
        routeId = -1;
        vehicleId = -1;
        fee = 0;
    }
};

#endif