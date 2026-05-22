#ifndef ROUTE_H
#define ROUTE_H

#include <iostream>
using namespace std;

class Route {
private:
    int id;
    char start[50];
    char end[50];
    double distance;
    int vehicleId;
    int studentCount;

public:
    Route() : id(0), distance(0), vehicleId(-1), studentCount(0) {
        start[0] = '\0';
        end[0] = '\0';
    }
    Route(int i, const char* s, const char* e, double d)
        : id(i), distance(d), vehicleId(-1), studentCount(0) {
        strcpy(start, s);
        strcpy(end, e);
    }

    void display() {
        cout << "Route " << id << ": " << start << " -> " << end;
        cout << " | " << distance << "km | Students: " << studentCount;
        if(vehicleId != -1) cout << " | Vehicle ID: " << vehicleId;
        cout << endl;
    }

    int getId()             { return id; }
    const char* getStart()  { return start; }
    const char* getEnd()    { return end; }
    double getDistance()    { return distance; }
    int getVehicleId()      { return vehicleId; }
    int getStudentCount()   { return studentCount; }

    void setVehicleId(int v){ vehicleId = v; }
    void addStudent()       { studentCount++; }
    void removeStudent()    { if(studentCount > 0) studentCount--; }
};

#endif