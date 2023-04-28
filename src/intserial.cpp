#include "intserial.h"
#include <iostream>

/***
                                __________________________________________________
                                |                                                |
                                |         PROGRAMMING TECHNIQUES CHALLENGE       |
                                |----------------------------------------------- |
                                |      BINARY TREE IN DISK WITH MONETARY TYPE    |
                                |------------------------------------------------|
                                |       AUTHOR: MICKAEL OSVALDO DE OLIVEIRA      |
                                |       AUTHOR: FILIPE ANDRADE COELHO            |
                                |________________________________________________|

***/

intSerial::intSerial() : serializable() {

}

int intSerial::empty() {
    return 0;
}
intSerial::intSerial(int i) : serializable() {
    value = i;
}

intSerial::intSerial(const intSerial &other) {
    setValue(other.getValue());
}

intSerial::~intSerial() {

}

intSerial intSerial::operator=(const intSerial &other) {
    value = other.getValue();
    return true;
}

bool intSerial::operator==(const intSerial &other) const {
    return value == other.getValue();
}


bool intSerial::operator<(const intSerial &other) const {
    return value < other.getValue();
}

bool intSerial::operator!=(const intSerial &other) const {
    return value != other.getValue();
}

intSerial intSerial::operator+(const intSerial& other) const {
    return false;
}

intSerial intSerial::operator-(const intSerial& other) const {
    return false;
}

intSerial intSerial::operator*(const intSerial& other) const {
    return false;
}

intSerial intSerial::operator/(const intSerial& other) const {
    return false;
}

intSerial intSerial::operator++() {
    return false;
}

intSerial intSerial::operator--() {
    return false;
}

void intSerial::setValue(int v) {
    value = v;
}

int intSerial::getValue() const {
    return value;
}

string intSerial::toString() {
    string aux;
    aux.insert(0,sizeof(int), '\0');
    aux.replace(0, sizeof(int), reinterpret_cast<char*>(&value), sizeof(value));
    return aux;
}

void intSerial::fromString(string repr) {
    int pos = 0;
    repr.copy(reinterpret_cast<char*>(&value), sizeof(int), pos);
}


unsigned long long int intSerial::size() const {
    return sizeof(int);
}
