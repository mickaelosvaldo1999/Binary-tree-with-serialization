#include "intserial.h"

intSerial::intSerial() : serializable() {

}

intSerial::intSerial(int i) : serializable() {

}

intSerial::intSerial(const intSerial& other) {

}

intSerial::~intSerial() {

}

intSerial intSerial::operator=(const intSerial& other) {

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

}

int intSerial::getValue() const {

}

string intSerial::toString() {
    return "testes";
}

void intSerial::fromString(string repr) {

}


unsigned long long int intSerial::size() const {

}
