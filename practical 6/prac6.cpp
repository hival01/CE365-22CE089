#include <iostream>
#include <cstring>

using namespace std;

string input;
int pos = 0;  // Current position in input

void S();  // Start Symbol
void L();  // List
void Ldash();  // List'

void error() {
    cout << "Error in validation!\n";
    exit(0);
}

void match(char expected) {
    if (input[pos] == expected) {
        pos++;
    } else {
        error();
    }
}

// S → ( L ) | a
void S() {
    if (input[pos] == '(') {
        match('(');
        L();
        match(')');
    } else if (input[pos] == 'a') {
        match('a');
    } else {
        error();
    }
}

// L → S L'
void L() {
    S();
    Ldash();
}

// L' → , S L' | ϵ
void Ldash() {
    if (input[pos] == ',') {  // Handles ", S L'"
        match(',');
        S();
        Ldash();
    }
    // Else, it remains empty (epsilon transition)
}

int main() {
    cout << "Enter expression: ";
    cin >> input;
    input += "$";  // End marker

    S();

    if (input[pos] == '$') {
        cout << "Valid Expression\n";
    } else {
        error();
    }

    return 0;
}
