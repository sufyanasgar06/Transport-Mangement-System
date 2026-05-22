#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

// Password comparison function
bool comparePassword(const char* input, const char* stored) {
    char tempInput[20];
    char tempStored[20];
    strcpy(tempInput, input);
    strcpy(tempStored, stored);
    
    for(int i = 0; tempInput[i]; i++) {
        tempInput[i] = toupper(tempInput[i]);
    }
    for(int i = 0; tempStored[i]; i++) {
        tempStored[i] = toupper(tempStored[i]);
    }
    return strcmp(tempInput, tempStored) == 0;
}

void toUpperCase(char* str) {
    for(int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

bool isPositiveInt(int num) {
    return num > 0;
}

bool isPositiveDouble(double num) {
    return num > 0;
}

int getValidIntInput(const char* prompt, bool allowZero = false) {
    int value;
    while(true) {
        cout << prompt;
        cin >> value;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[ERROR] Please enter a valid number!\n";
        } else if(value < 0) {
            cout << "[ERROR] Value cannot be negative! Please try again.\n";
        } else if(value == 0 && !allowZero) {
            cout << "[ERROR] Value must be greater than 0! Please try again.\n";
        } else {
            return value;
        }
    }
}

double getValidDoubleInput(const char* prompt) {
    double value;
    while(true) {
        cout << prompt;
        cin >> value;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[ERROR] Please enter a valid number!\n";
        } else if(value < 0) {
            cout << "[ERROR] Value cannot be negative! Please try again.\n";
        } else if(value == 0) {
            cout << "[ERROR] Value must be greater than 0! Please try again.\n";
        } else {
            return value;
        }
    }
}

void getValidStringInput(const char* prompt, char* output, int maxLen) {
    while(true) {
        cout << prompt;
        cin >> output;

        bool valid = true;
        for(int i = 0; output[i]; i++) {
            if(!isalpha(output[i]) && !isspace(output[i])) {
                valid = false;
                break;
            }
        }

        if(strlen(output) == 0) {
            cout << "[ERROR] Input cannot be empty! Please try again.\n";
        } else if(!valid) {
            cout << "[ERROR] Only letters allowed! Please try again.\n";
        } else {
            break;
        }
    }
}

void getValidPassword(const char* prompt, char* output) {
    while(true) {
        cout << prompt;
        cin >> output;

        if(strlen(output) < 3) {
            cout << "[ERROR] Password must be at least 3 characters! Please try again.\n";
        } else {
            break;
        }
    }
}

void printHeader(const char* title) {
    cout << "\n========================================\n";
    cout << "        " << title << "\n";
    cout << "========================================\n";
}

#endif