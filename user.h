#ifndef USER_H
#define USER_H

#include <cstring>
#include <cctype>

// Forward declaration of helper function
bool comparePassword(const char* input, const char* stored);

class User {
protected:
    int id;
    char name[50];
    char password[20];
    char role[10];

public:
    User() : id(0) {
        name[0] = '\0';
        password[0] = '\0';
        role[0] = '\0';
    }

    User(int i, const char* n, const char* p, const char* r) : id(i) {
        strcpy(name, n);
        strcpy(password, p);
        strcpy(role, r);
    }

    virtual ~User() {}

    int getId() { return id; }
    const char* getName() { return name; }
    const char* getPassword() { return password; }
    const char* getRole() { return role; }

    bool authenticate(const char* p) { return comparePassword(p, password); }
};

#endif