#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#include "utilis.h"
#include "user.h"
#include "student.h"
#include "admin.h"
#include "vehicle.h"
#include "route.h"
#include "bill.h"
#include "transportpass.h"

using namespace std;

// ==================== DYNAMIC ARRAYS ====================

Student** students = nullptr;
int studentCount = 0;
int studentCapacity = 10;

Admin** admins = nullptr;
int adminCount = 0;
int adminCapacity = 5;

Vehicle** vehicles = nullptr;
int vehicleCount = 0;
int vehicleCapacity = 10;

Route** routes = nullptr;
int routeCount = 0;
int routeCapacity = 10;

TransportPass** passes = nullptr;
int passCount = 0;
int passCapacity = 10;

Bill** bills = nullptr;
int billCount = 0;
int billCapacity = 10;

// ==================== ARRAY MANAGEMENT FUNCTIONS ====================

void resizeStudents() {
    studentCapacity *= 2;
    Student** newArr = new Student*[studentCapacity];
    for(int i = 0; i < studentCount; i++) newArr[i] = students[i];
    delete[] students;
    students = newArr;
}

void addStudent(Student* s) {
    if(studentCount >= studentCapacity) resizeStudents();
    students[studentCount++] = s;
}

void resizeAdmins() {
    adminCapacity *= 2;
    Admin** newArr = new Admin*[adminCapacity];
    for(int i = 0; i < adminCount; i++) newArr[i] = admins[i];
    delete[] admins;
    admins = newArr;
}

void addAdmin(Admin* a) {
    if(adminCount >= adminCapacity) resizeAdmins();
    admins[adminCount++] = a;
}

void resizeVehicles() {
    vehicleCapacity *= 2;
    Vehicle** newArr = new Vehicle*[vehicleCapacity];
    for(int i = 0; i < vehicleCount; i++) newArr[i] = vehicles[i];
    delete[] vehicles;
    vehicles = newArr;
}

void addVehicle(Vehicle* v) {
    if(vehicleCount >= vehicleCapacity) resizeVehicles();
    vehicles[vehicleCount++] = v;
}

void removeVehicleAt(int index) {
    delete vehicles[index];
    for(int i = index; i < vehicleCount - 1; i++) vehicles[i] = vehicles[i + 1];
    vehicleCount--;
}

void resizeRoutes() {
    routeCapacity *= 2;
    Route** newArr = new Route*[routeCapacity];
    for(int i = 0; i < routeCount; i++) newArr[i] = routes[i];
    delete[] routes;
    routes = newArr;
}

void addRoute(Route* r) {
    if(routeCount >= routeCapacity) resizeRoutes();
    routes[routeCount++] = r;
}

void removeRouteAt(int index) {
    delete routes[index];
    for(int i = index; i < routeCount - 1; i++) routes[i] = routes[i + 1];
    routeCount--;
}

void addPass(TransportPass* p) {
    if(passCount >= passCapacity) {
        passCapacity *= 2;
        TransportPass** newArr = new TransportPass*[passCapacity];
        for(int i = 0; i < passCount; i++) newArr[i] = passes[i];
        delete[] passes;
        passes = newArr;
    }
    passes[passCount++] = p;
}

void addBill(Bill* b) {
    if(billCount >= billCapacity) {
        billCapacity *= 2;
        Bill** newArr = new Bill*[billCapacity];
        for(int i = 0; i < billCount; i++) newArr[i] = bills[i];
        delete[] bills;
        bills = newArr;
    }
    bills[billCount++] = b;
}

// ==================== UNIQUENESS CHECKS ====================

bool isUniqueStudentId(int id) {
    for(int i = 0; i < studentCount; i++) {
        if(students[i]->getId() == id) return false;
    }
    return true;
}

bool isUniqueVehicleId(int id) {
    for(int i = 0; i < vehicleCount; i++) {
        if(vehicles[i]->getId() == id) return false;
    }
    return true;
}

bool isUniqueRouteId(int id) {
    for(int i = 0; i < routeCount; i++) {
        if(routes[i]->getId() == id) return false;
    }
    return true;
}

int getNextStudentId() {
    int maxId = 0;
    for(int i = 0; i < studentCount; i++) {
        if(students[i]->getId() > maxId) maxId = students[i]->getId();
    }
    return maxId + 1;
}

// ==================== VIEW FUNCTIONS ====================

void viewVehicles() {
    if(vehicleCount == 0) {
        cout << "No vehicles available.\n";
        return;
    }
    for(int i = 0; i < vehicleCount; i++) vehicles[i]->display();
}

void viewRoutes() {
    if(routeCount == 0) {
        cout << "No routes available.\n";
        return;
    }
    for(int i = 0; i < routeCount; i++) routes[i]->display();
}

// ==================== SIGN UP FUNCTION ====================

void signUp() {
    printHeader("STUDENT SIGN UP");

    int id = getNextStudentId();
    char name[50], password[20], department[30];
    int semester;

    getValidStringInput("Name: ", name, 50);
    getValidPassword("Password: ", password);
    getValidStringInput("Department: ", department, 30);
    semester = getValidIntInput("Semester: ", false);

    Student* newStudent = new Student(id, name, password, department, semester);
    addStudent(newStudent);

    cout << "\n[SUCCESS] Account created successfully!\n";
    cout << "Your Student ID is: " << id << "\n";
    cout << "Use this ID to login.\n";
}

// ==================== VEHICLE MANAGEMENT ====================

void addVehicleMenu() {
    int type, id, cap;
    char num[20];

    cout << "1. Bus\n2. Van\nChoice: ";
    cin >> type;
    while(type != 1 && type != 2) {
        cout << "[ERROR] Invalid choice! Enter 1 for Bus or 2 for Van: ";
        cin >> type;
    }

    id = getValidIntInput("Vehicle ID: ", false);
    while(!isUniqueVehicleId(id)) {
        cout << "[ERROR] Vehicle ID already exists! Please enter a different ID.\n";
        id = getValidIntInput("Vehicle ID: ", false);
    }

    getValidStringInput("Vehicle Number: ", num, 20);
    cap = getValidIntInput("Capacity: ", false);

    if(type == 1)
        addVehicle(new Bus(id, num, cap));
    else
        addVehicle(new Van(id, num, cap));

    cout << "\n[SUCCESS] Vehicle added!\n";
}

void removeVehicleMenu() {
    if(vehicleCount == 0) {
        cout << "\n[ERROR] No vehicles to remove!\n";
        return;
    }

    int id;
    viewVehicles();
    id = getValidIntInput("Enter Vehicle ID to remove: ", false);

    for(int i = 0; i < vehicleCount; i++) {
        if(vehicles[i]->getId() == id) {
            removeVehicleAt(i);
            cout << "\n[SUCCESS] Vehicle removed!\n";
            return;
        }
    }
    cout << "\n[ERROR] Vehicle not found!\n";
}

// ==================== ROUTE MANAGEMENT ====================

void addRouteMenu() {
    int id;
    char start[50], end[50];
    double dist;

    id = getValidIntInput("Route ID: ", false);
    while(!isUniqueRouteId(id)) {
        cout << "[ERROR] Route ID already exists! Please enter a different ID.\n";
        id = getValidIntInput("Route ID: ", false);
    }

    getValidStringInput("Start Point: ", start, 50);
    getValidStringInput("End Point: ", end, 50);
    dist = getValidDoubleInput("Distance (km): ");

    addRoute(new Route(id, start, end, dist));
    cout << "\n[SUCCESS] Route added!\n";
}

void removeRouteMenu() {
    if(routeCount == 0) {
        cout << "\n[ERROR] No routes to remove!\n";
        return;
    }

    int id;
    viewRoutes();
    id = getValidIntInput("Enter Route ID to remove: ", false);

    for(int i = 0; i < routeCount; i++) {
        if(routes[i]->getId() == id) {
            removeRouteAt(i);
            cout << "\n[SUCCESS] Route removed!\n";
            return;
        }
    }
    cout << "\n[ERROR] Route not found!\n";
}

void assignVehicle() {
    if(routeCount == 0) {
        cout << "\n[ERROR] No routes available! Please add routes first.\n";
        return;
    }
    if(vehicleCount == 0) {
        cout << "\n[ERROR] No vehicles available! Please add vehicles first.\n";
        return;
    }

    int routeId, vehicleId;

    cout << "\n--- Routes ---\n";
    viewRoutes();
    routeId = getValidIntInput("Select Route ID: ", false);

    cout << "\n--- Vehicles ---\n";
    viewVehicles();
    vehicleId = getValidIntInput("Select Vehicle ID: ", false);

    Route*   route   = nullptr;
    Vehicle* vehicle = nullptr;

    for(int i = 0; i < routeCount; i++)   if(routes[i]->getId()   == routeId)   route   = routes[i];
    for(int i = 0; i < vehicleCount; i++) if(vehicles[i]->getId() == vehicleId) vehicle = vehicles[i];

    if(route && vehicle) {
        route->setVehicleId(vehicleId);
        vehicle->setRouteId(routeId);
        cout << "\n[SUCCESS] Vehicle assigned to route!\n";
    } else {
        cout << "\n[ERROR] Invalid route or vehicle ID!\n";
    }
}

// ==================== APPLICATION MANAGEMENT ====================

void viewApplications() {
    bool found = false;
    for(int i = 0; i < studentCount; i++) {
        if(strcmp(students[i]->getStatus(), "Pending") == 0) {
            students[i]->display();
            found = true;
        }
    }
    if(!found) cout << "No pending applications.\n";
}

void approveReject() {
    bool hasPending = false;
    for(int i = 0; i < studentCount; i++) {
        if(strcmp(students[i]->getStatus(), "Pending") == 0) {
            hasPending = true;
            break;
        }
    }

    if(!hasPending) {
        cout << "\n[INFO] No pending applications to process!\n";
        return;
    }

    int id, choice;
    viewApplications();

    id = getValidIntInput("\nEnter Student ID: ", false);

    Student* target = nullptr;
    for(int i = 0; i < studentCount; i++) {
        if(students[i]->getId() == id && strcmp(students[i]->getStatus(), "Pending") == 0) {
            target = students[i];
            break;
        }
    }

    if(!target) {
        cout << "\n[ERROR] Student not found or no pending request!\n";
        return;
    }

    choice = getValidIntInput("1. Approve\n2. Reject\nChoice: ", true);
    while(choice != 1 && choice != 2) {
        cout << "[ERROR] Invalid choice! Enter 1 or 2.\n";
        choice = getValidIntInput("Choice: ", true);
    }

    if(choice == 1) {
        Route*   route   = nullptr;
        Vehicle* vehicle = nullptr;

        for(int i = 0; i < routeCount; i++)   if(routes[i]->getId()   == target->getRouteId())   route   = routes[i];
        for(int i = 0; i < vehicleCount; i++) if(vehicles[i]->getId() == target->getVehicleId()) vehicle = vehicles[i];

        if(route && vehicle && vehicle->hasSeat()) {
            target->approve();
            vehicle->addPassenger();
            route->addStudent();
            target->setFee(vehicle->getFee());

            Bill* bill = new Bill(target->getId(), vehicle->getFee());
            addBill(bill);
            TransportPass* pass = new TransportPass(target, vehicle, route, bill);
            addPass(pass);

            cout << "\n[SUCCESS] Application Approved! Transport Pass Generated!\n";
        } else {
            cout << "\n[ERROR] No seats available on this route!\n";
        }
    } else {
        target->reject();
        cout << "\n[INFO] Application Rejected!\n";
    }
}

// ==================== REPORTS ====================

void generateReports() {
    printHeader("REPORTS");

    double total = 0;
    int paidCount = 0, unpaidCount = 0;
    for(int i = 0; i < billCount; i++) {
        if(bills[i]->isPaid()) {
            total += bills[i]->getAmount();
            paidCount++;
        } else {
            unpaidCount++;
        }
    }

    cout << "\n[REVENUE REPORT]\n";
    cout << "----------------------------------------\n";
    cout << "Total Bills: "   << billCount   << endl;
    cout << "Paid Bills: "    << paidCount   << endl;
    cout << "Unpaid Bills: "  << unpaidCount << endl;
    cout << "Total Revenue: Rs. " << fixed << setprecision(2) << total << endl;

    cout << "\n[VEHICLE UTILIZATION]\n";
    cout << "----------------------------------------\n";
    for(int i = 0; i < vehicleCount; i++) {
        cout << vehicles[i]->getType() << " " << vehicles[i]->getNumber() << ": ";
        cout << vehicles[i]->getCapacity() - vehicles[i]->getOccupied()
             << "/" << vehicles[i]->getCapacity() << " seats available\n";
    }

    cout << "\n[ROUTE USAGE]\n";
    cout << "----------------------------------------\n";
    for(int i = 0; i < routeCount; i++) {
        cout << routes[i]->getStart() << " -> " << routes[i]->getEnd() << ": ";
        cout << routes[i]->getStudentCount() << " students registered\n";
    }

    cout << "\n[STUDENT REGISTRATION STATUS]\n";
    cout << "----------------------------------------\n";
    int approved = 0, pending = 0, rejected = 0, notApplied = 0;
    for(int i = 0; i < studentCount; i++) {
        const char* status = students[i]->getStatus();
        if(strcmp(status, "Approved")    == 0) approved++;
        else if(strcmp(status, "Pending")  == 0) pending++;
        else if(strcmp(status, "Rejected") == 0) rejected++;
        else notApplied++;
    }
    cout << "Total Students: " << studentCount << endl;
    cout << "Approved: "       << approved     << endl;
    cout << "Pending: "        << pending      << endl;
    cout << "Rejected: "       << rejected     << endl;
    cout << "Not Applied: "    << notApplied   << endl;
}

// ==================== FILE HANDLING ====================

void saveData() {
    ofstream file("transport_data.txt");

    file << "#STUDENTS\n" << studentCount << "\n";
    for(int i = 0; i < studentCount; i++) {
        file << students[i]->getId()       << "|"
             << students[i]->getName()     << "|"
             << students[i]->getPassword() << "|"
             << students[i]->getDepartment()<< "|"
             << students[i]->getSemester() << "|"
             << students[i]->getStatus()   << "|"
             << students[i]->getRouteId()  << "|"
             << students[i]->getVehicleId()<< "|"
             << students[i]->getFee()      << "\n";
    }

    file << "#VEHICLES\n" << vehicleCount << "\n";
    for(int i = 0; i < vehicleCount; i++) {
        file << vehicles[i]->getType()    << "|"
             << vehicles[i]->getId()      << "|"
             << vehicles[i]->getNumber()  << "|"
             << vehicles[i]->getCapacity()<< "|"
             << vehicles[i]->getRouteId() << "|"
             << vehicles[i]->getOccupied()<< "\n";
    }

    file << "#ROUTES\n" << routeCount << "\n";
    for(int i = 0; i < routeCount; i++) {
        file << routes[i]->getId()          << "|"
             << routes[i]->getStart()       << "|"
             << routes[i]->getEnd()         << "|"
             << routes[i]->getDistance()    << "|"
             << routes[i]->getVehicleId()   << "|"
             << routes[i]->getStudentCount()<< "\n";
    }

    file << "#BILLS\n" << billCount << "\n";
    for(int i = 0; i < billCount; i++) {
        file << bills[i]->getStudentId()        << "|"
             << bills[i]->getAmount()           << "|"
             << (bills[i]->isPaid() ? 1 : 0)   << "\n";
    }

    file.close();
}

void loadData() {
    ifstream file("transport_data.txt");
    if(!file.is_open()) {
        cout << "\n[INFO] No saved data found. Using default data.\n";
        return;
    }

    for(int i = 0; i < studentCount; i++) delete students[i];
    for(int i = 0; i < vehicleCount; i++) delete vehicles[i];
    for(int i = 0; i < routeCount;   i++) delete routes[i];
    for(int i = 0; i < passCount;    i++) delete passes[i];
    
    studentCount = vehicleCount = routeCount = passCount = billCount = 0;

    string line, tag;
    int count;

    auto split = [](const string& s, char delim) {
        vector<string> tokens;
        string tok;
        for(char c : s) {
            if(c == delim) { tokens.push_back(tok); tok.clear(); }
            else           { tok += c; }
        }
        if(!tok.empty()) tokens.push_back(tok);
        return tokens;
    };

    file >> tag >> count;
    file.ignore();
    if(tag == "#STUDENTS") {
        for(int i = 0; i < count; i++) {
            getline(file, line);
            auto t = split(line, '|');
            if(t.size() < 9) continue;
            int    id       = stoi(t[0]);
            int    sem      = stoi(t[4]);
            int    routeId  = stoi(t[6]);
            int    vehicleId= stoi(t[7]);
            double fee      = stod(t[8]);
            Student* s = new Student(id, t[1].c_str(), t[2].c_str(), t[3].c_str(), sem);
            s->setStatus(t[5].c_str());
            s->setRouteId(routeId);
            s->setVehicleId(vehicleId);
            s->setFee(fee);
            addStudent(s);
        }
    }

    file >> tag >> count;
    file.ignore();
    if(tag == "#VEHICLES") {
        for(int i = 0; i < count; i++) {
            getline(file, line);
            auto t = split(line, '|');
            if(t.size() < 6) continue;
            int id       = stoi(t[1]);
            int cap      = stoi(t[3]);
            int routeId  = stoi(t[4]);
            int occupied = stoi(t[5]);
            Vehicle* v;
            if(t[0] == "Bus") v = new Bus(id, t[2].c_str(), cap);
            else               v = new Van(id, t[2].c_str(), cap);
            v->setRouteId(routeId);
            for(int j = 0; j < occupied; j++) v->addPassenger();
            addVehicle(v);
        }
    }

    file >> tag >> count;
    file.ignore();
    if(tag == "#ROUTES") {
        for(int i = 0; i < count; i++) {
            getline(file, line);
            auto t = split(line, '|');
            if(t.size() < 6) continue;
            int    id        = stoi(t[0]);
            double dist      = stod(t[3]);
            int    vehicleId = stoi(t[4]);
            int    sc        = stoi(t[5]);
            Route* r = new Route(id, t[1].c_str(), t[2].c_str(), dist);
            r->setVehicleId(vehicleId);
            for(int j = 0; j < sc; j++) r->addStudent();
            addRoute(r);
        }
    }

    if(file >> tag >> count) {
        file.ignore();
        if(tag == "#BILLS") {
            for(int i = 0; i < count; i++) {
                getline(file, line);
                auto t = split(line, '|');
                if(t.size() < 3) continue;
                int    sid  = stoi(t[0]);
                double amt  = stod(t[1]);
                bool   paid = (stoi(t[2]) == 1);
                Bill* b = new Bill(sid, amt);
                if(paid) b->pay();
                addBill(b);
            }
        }
    }

    for(int i = 0; i < studentCount; i++) {
        Student* s = students[i];
        if(strcmp(s->getStatus(), "Approved") != 0) continue;

        Vehicle* v = nullptr;
        Route*   r = nullptr;
        Bill*    b = nullptr;

        for(int j = 0; j < vehicleCount; j++)
            if(vehicles[j]->getId() == s->getVehicleId()) { v = vehicles[j]; break; }
        for(int j = 0; j < routeCount; j++)
            if(routes[j]->getId() == s->getRouteId()) { r = routes[j]; break; }
        for(int j = 0; j < billCount; j++)
            if(bills[j]->getStudentId() == s->getId()) { b = bills[j]; break; }

        if(v && r && b) {
            TransportPass* pass = new TransportPass(s, v, r, b);
            addPass(pass);
        }
    }

    file.close();
}

// ==================== STUDENT PANEL ====================

void studentPanel(Student* s) {
    int choice;
    do {
        cout << "\n========================================\n";
        cout << "        WELCOME " << s->getName() << "\n";
        cout << "========================================\n";
        cout << "  1. View Routes\n";
        cout << "  2. Apply for Transport\n";
        cout << "  3. View My Status\n";
        cout << "  4. Cancel Registration\n";
        cout << "  5. Pay Fee\n";
        cout << "  6. Logout\n";
        cout << "========================================\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                viewRoutes();
                break;

            case 2:
            {
                if(strcmp(s->getStatus(), "Not Applied") != 0) {
                    cout << "\n[ERROR] You have already applied! Status: " << s->getStatus() << endl;
                    break;
                }
                if(routeCount == 0) {
                    cout << "\n[ERROR] No routes available!\n";
                    break;
                }
                viewRoutes();
                int routeId = getValidIntInput("\nSelect Route ID: ", false);

                Route* route = nullptr;
                for(int i = 0; i < routeCount; i++) {
                    if(routes[i]->getId() == routeId) route = routes[i];
                }
                if(!route) {
                    cout << "\n[ERROR] Invalid route!\n";
                    break;
                }

                int vehicleId = route->getVehicleId();
                if(vehicleId == -1) {
                    cout << "\n[ERROR] No vehicle assigned to this route yet!\n";
                    break;
                }

                Vehicle* vehicle = nullptr;
                for(int i = 0; i < vehicleCount; i++) {
                    if(vehicles[i]->getId() == vehicleId) vehicle = vehicles[i];
                }
                if(!vehicle || !vehicle->hasSeat()) {
                    cout << "\n[ERROR] No seats available on this route!\n";
                    break;
                }

                s->apply(routeId, vehicleId);
                cout << "\n[SUCCESS] Application submitted! Waiting for admin approval.\n";
                break;
            }

            case 3:
                s->display();
                if(strcmp(s->getStatus(), "Approved") == 0) {
                    for(int i = 0; i < passCount; i++) {
                        if(passes[i]->getStudent() == s) {
                            passes[i]->display();
                            break;
                        }
                    }
                }
                break;

            case 4:
                if(strcmp(s->getStatus(), "Approved") != 0) {
                    cout << "\n[ERROR] No active registration to cancel!\n";
                    break;
                }
                {
                    char confirm;
                    cout << "Are you sure you want to cancel? (y/n): ";
                    cin >> confirm;
                    if(confirm == 'y' || confirm == 'Y') {
                        for(int i = 0; i < vehicleCount; i++) {
                            if(vehicles[i]->getId() == s->getVehicleId()) vehicles[i]->removePassenger();
                        }
                        for(int i = 0; i < routeCount; i++) {
                            if(routes[i]->getId() == s->getRouteId()) routes[i]->removeStudent();
                        }
                        s->cancelReg();
                        cout << "\n[SUCCESS] Registration cancelled successfully!\n";
                    }
                }
                break;

            case 5:
            {
                bool foundBill = false;
                for(int i = 0; i < billCount; i++) {
                    if(bills[i]->getStudentId() == s->getId() && !bills[i]->isPaid()) {
                        bills[i]->display();
                        char confirm;
                        cout << "Pay now? (y/n): ";
                        cin >> confirm;
                        if(confirm == 'y' || confirm == 'Y') {
                            bills[i]->pay();
                            s->setFee(0);
                            cout << "\n[SUCCESS] Payment successful! Thank you.\n";
                        }
                        foundBill = true;
                        break;
                    }
                }
                if(!foundBill) {
                    cout << "\n[INFO] No pending bills found!\n";
                }
                break;
            }

            case 6:
                cout << "\n[INFO] Logging out...\n";
                break;

            default:
                cout << "\n[ERROR] Invalid choice! Please enter 1-6.\n";
        }
    } while(choice != 6);
}

// ==================== ADMIN PANEL ====================

void adminPanel(Admin* a) {
    int choice;
    do {
        cout << "\n========================================\n";
        cout << "        ADMIN PANEL - " << a->getName() << "\n";
        cout << "========================================\n";
        cout << "  1. Add Vehicle\n";
        cout << "  2. Remove Vehicle\n";
        cout << "  3. View Vehicles\n";
        cout << "  4. Add Route\n";
        cout << "  5. Remove Route\n";
        cout << "  6. View Routes\n";
        cout << "  7. Assign Vehicle to Route\n";
        cout << "  8. View Applications\n";
        cout << "  9. Approve/Reject\n";
        cout << " 10. Generate Reports\n";
        cout << " 11. Save Data\n";
        cout << " 12. Load Data\n";
        cout << " 13. Logout\n";
        cout << "========================================\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:  addVehicleMenu();   break;
            case 2:  removeVehicleMenu();break;
            case 3:  viewVehicles();     break;
            case 4:  addRouteMenu();     break;
            case 5:  removeRouteMenu();  break;
            case 6:  viewRoutes();       break;
            case 7:  assignVehicle();    break;
            case 8:  viewApplications(); break;
            case 9:  approveReject();    break;
            case 10: generateReports();  break;
            case 11: saveData(); cout << "\n[SUCCESS] Data saved!\n"; break;
            case 12: loadData(); cout << "\n[SUCCESS] Data loaded successfully!\n"; break;
            case 13: cout << "\n[INFO] Logging out...\n"; break;
            default: cout << "\n[ERROR] Invalid choice! Please enter 1-13.\n";
        }
    } while(choice != 13);
}

// ==================== MAIN ====================

int main() {
    srand(time(0));

    students = new Student*[studentCapacity];
    admins   = new Admin*[adminCapacity];
    vehicles = new Vehicle*[vehicleCapacity];
    routes   = new Route*[routeCapacity];
    passes   = new TransportPass*[passCapacity];
    bills    = new Bill*[billCapacity];

    printHeader("UNIVERSITY TRANSPORT MANAGEMENT SYSTEM");

    addAdmin(new Admin(100, "Admin", "admin123"));

    ifstream checkFile("transport_data.txt");
    bool fileExists = checkFile.is_open();
    checkFile.close();

    if(fileExists) {
        loadData();
    } else {
        cout << "\n[INFO] No saved data found. Loading default data...\n";

        addStudent(new Student(1, "Sufyan", "123", "CS", 3));
        addStudent(new Student(2, "Ali",    "456", "CS", 4));
        addStudent(new Student(3, "Sara",   "789", "EE", 2));

        addVehicle(new Bus(10, "LEA-100", 50));
        addVehicle(new Van(20, "LEA-200", 15));
        addVehicle(new Bus(30, "LEA-300", 45));

        addRoute(new Route(1, "Johar Town", "UET Lahore", 15.5));
        addRoute(new Route(2, "Valencia",   "UET Lahore", 12.0));
        addRoute(new Route(3, "Model Town", "UET Lahore", 10.0));

        routes[0]->setVehicleId(10); vehicles[0]->setRouteId(1);
        routes[1]->setVehicleId(20); vehicles[1]->setRouteId(2);
        routes[2]->setVehicleId(30); vehicles[2]->setRouteId(3);

        cout << "[INFO] Default data loaded. Use admin panel to save.\n";
    }

    int choice, id;
    char password[20];
    bool running = true;

    while(running) {
        cout << "\n========================================\n";
        cout << "               MAIN MENU                \n";
        cout << "========================================\n";
        cout << "  1. Sign Up (Student)\n";
        cout << "  2. Sign In\n";
        cout << "  3. Exit\n";
        cout << "========================================\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                signUp();
                break;

            case 2:
            {
                cout << "\nEnter ID: ";
                cin >> id;
                cout << "Password: ";
                cin >> password;

                bool found = false;

                for(int i = 0; i < adminCount; i++) {
                    if(admins[i]->getId() == id && admins[i]->authenticate(password)) {
                        adminPanel(admins[i]);
                        found = true;
                        break;
                    }
                }

                if(!found) {
                    for(int i = 0; i < studentCount; i++) {
                        if(students[i]->getId() == id && students[i]->authenticate(password)) {
                            studentPanel(students[i]);
                            found = true;
                            break;
                        }
                    }
                }

                if(!found) cout << "\n[ERROR] Invalid ID or Password!\n";
                break;
            }

            case 3:
                saveData();
                printHeader("THANK YOU");
                cout << "\nExiting system...\n";
                running = false;
                break;

            default:
                cout << "\n[ERROR] Invalid choice! Please enter 1, 2, or 3.\n";
        }
    }

    for(int i = 0; i < studentCount; i++) delete students[i];
    for(int i = 0; i < adminCount;   i++) delete admins[i];
    for(int i = 0; i < vehicleCount; i++) delete vehicles[i];
    for(int i = 0; i < routeCount;   i++) delete routes[i];
    for(int i = 0; i < passCount;    i++) delete passes[i];
    for(int i = 0; i < billCount;    i++) delete bills[i];

    delete[] students;
    delete[] admins;
    delete[] vehicles;
    delete[] routes;
    delete[] passes;
    delete[] bills;

    return 0;
}