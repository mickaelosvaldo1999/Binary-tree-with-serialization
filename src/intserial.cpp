#include "intserial.h"
#include <iostream>
intSerial::intSerial() : serializable() {

}

intSerial::intSerial(int i) : serializable() {
    value = i;
}

intSerial::intSerial(const intSerial &other) {

}

intSerial::~intSerial() {

}

intSerial intSerial::operator=(const intSerial &other) {
    value = other.getValue();
    cout << "mudou " << value << endl;
}

bool intSerial::operator==(const intSerial &other) const {

}

bool intSerial::operator<(const intSerial &other) const {

}

bool intSerial::operator<=(const intSerial &other) const {

}

bool intSerial::operator>(const intSerial &other) const {

}

bool intSerial::operator>=(const intSerial &other) const {

}

bool intSerial::operator!=(const intSerial &other) const {

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
    return value;
}

string intSerial::toString() {
    string aux;
    cout << "== " << value << endl;
    aux.insert(0,sizeof(int), '\0');
    aux.replace(0, sizeof(int), reinterpret_cast<char*>(&value), sizeof(value));
    cout << "== " << aux << endl;
    return aux;
}

void intSerial::fromString(string repr) {

}


unsigned long long int intSerial::size() const {

}
