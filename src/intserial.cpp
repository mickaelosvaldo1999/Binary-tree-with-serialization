#include "intserial.h"
#include <iostream>
intSerial::intSerial() : serializable() {

}

intSerial::intSerial(int i) : serializable() {
    value = i;
}

intSerial::intSerial(const intSerial &other) {
    this->setValue(other.getValue());
}

intSerial::~intSerial() {

}

intSerial intSerial::operator=(const intSerial &other) {
    value = other.getValue();
}

bool intSerial::operator==(const intSerial &other) const {

}


bool intSerial::operator<(const intSerial &other) const {
    return value < other.getValue();
}

bool intSerial::operator!=(const intSerial &other) const {
    return value != other.getValue();
}

intSerial intSerial::operator+(const intSerial& other) const {

}

intSerial intSerial::operator-(const intSerial& other) const {

}

intSerial intSerial::operator*(const intSerial& other) const {

}

intSerial intSerial::operator/(const intSerial& other) const {

}

intSerial intSerial::operator++() {

}

intSerial intSerial::operator--() {

}

void intSerial::setValue(int v) {
    value = v;
}

int intSerial::getValue() const {
    return this->value;
}

string intSerial::toString() {
    string aux;
    aux.insert(0,sizeof(int), '\0');
    aux.replace(0, sizeof(int), reinterpret_cast<char*>(&value), sizeof(value));
    return aux;
}

void intSerial::fromString(string repr) {

}


unsigned long long int intSerial::size() const {
    return sizeof(int);
}
