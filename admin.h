#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"

class Admin : public User {
public:
    Admin() : User() {}
    Admin(int i, const char* n, const char* p) : User(i, n, p, "Admin") {}
};

#endif