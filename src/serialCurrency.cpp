#include "serialCurrency.h"
#include <iostream>

serialCurrency::serialCurrency() : serializable() {

}

int serialCurrency::empty() {
    return 0;
}
serialCurrency::serialCurrency(int i) : serializable() {
    value = i;
}

serialCurrency::serialCurrency(const serialCurrency &other) {
    setValue(other.getValue());
}

serialCurrency::~serialCurrency() {

}

serialCurrency serialCurrency::operator=(const serialCurrency &other) {
    value = other.getValue();
}

bool serialCurrency::operator==(const serialCurrency &other) const {
    return value == other.getValue();
}


bool serialCurrency::operator<(const serialCurrency &other) const {
    return value < other.getValue();
}

bool serialCurrency::operator!=(const serialCurrency &other) const {
    return value != other.getValue();
}

serialCurrency serialCurrency::operator+(const serialCurrency& other) const {

}

serialCurrency serialCurrency::operator-(const serialCurrency& other) const {

}

serialCurrency serialCurrency::operator*(const serialCurrency& other) const {

}

serialCurrency serialCurrency::operator/(const serialCurrency& other) const {

}

serialCurrency serialCurrency::operator++() {

}

serialCurrency serialCurrency::operator--() {

}

void serialCurrency::setValue(int v) {
    value = v;
}

int serialCurrency::getValue() const {
    return value;
}

string serialCurrency::toString() {
    string aux;
    aux.insert(0,sizeof(int), '\0');
    aux.replace(0, sizeof(int), reinterpret_cast<char*>(&value), sizeof(value));
    return aux;
}

void serialCurrency::fromString(string repr) {
    int pos = 0;
    repr.copy(reinterpret_cast<char*>(&value), sizeof(int), pos);
}


unsigned long long int serialCurrency::size() const {
    return sizeof(int);
}
