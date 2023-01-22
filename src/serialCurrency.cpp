#include "serialCurrency.h"
#include <iostream>
#include <string>
#include <sstream>


serialCurrency::serialCurrency() : serializable() {

}

string serialCurrency::empty() {
    return "0.00";
}
serialCurrency::serialCurrency(string i) : serializable() {
    //convertendo strings para valores inteiros
    string integer,fractional;
    int controller = i.find('.');
    //verificando se possui parte fracionária
    if (controller == -1) {
         integer = i.substr(0,i.size());
         fractional = "0";
    } else {
        integer = i.substr(0,controller);
        fractional = i.substr(controller + 1,i.size());
    }
    //convertendo para valores utilizaveis
    x = stoi(integer);
    y = stoi(fractional);

    //tratando inconsistências
    while (y > 100) {
        x += 1;
        y -= 100;
    }

}

serialCurrency::serialCurrency(const serialCurrency &other) {
    x = other.getx();
    y = other.gety();
}

serialCurrency::~serialCurrency() {

}

serialCurrency serialCurrency::operator=(const serialCurrency &other) {
    x = other.getx();
    y = other.gety();
}

bool serialCurrency::operator==(const serialCurrency &other) const {
    return getValue() == other.getValue();
}

bool serialCurrency::operator<<(const serialCurrency &other) {
    setValue(other.getValue());
    return true;
}

bool serialCurrency::operator>>(serialCurrency &other) const {
    other.setValue(getValue());
    return true;
}



bool serialCurrency::operator<(const serialCurrency &other) const {
//laço de retorno
    if (x < other.getx()) {
        return true;
    }
    else if (x == other.getx()) {
        if (y < other.gety()) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool serialCurrency::operator!=(const serialCurrency &other) const {
    return getValue() != other.getValue();
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

void serialCurrency::setValue(string i) {
     //convertendo strings para valores inteiros
    string integer,fractional;
    int controller = i.find('.');
    //verificando se possui parte fracionária
    if (controller == -1) {
         integer = i.substr(0,i.size());
         fractional = "0";
    } else {
        integer = i.substr(0,controller);
        fractional = i.substr(controller + 1,i.size());
    }
    //convertendo para valores utilizaveis
    x = stoi(integer);
    y = stoi(fractional);

    //tratando inconsistências
    while (y > 100) {
        x += 1;
        y -= 100;
    }
}

string serialCurrency::getValue() const {
    //converte os valores inteiros para string
    string aux;
    ostringstream os;
    os << x;
    os << ".";
    if (y < 10) {
        os << "0";
    }
    os << y;
    return os.str();

}

int serialCurrency::getx() const {
    return x;
}

void serialCurrency::setx(int i) {
    x = i;
}

unsigned short int serialCurrency::gety() const {
    return y;
}

void serialCurrency::sety(unsigned short int i) {
    y = i;
}

string serialCurrency::toString() {
    string aux;
    int pos = 0;
    aux.insert(0,size(), '\0');
    aux.replace(pos, sizeof(x), reinterpret_cast<char*>(&x), sizeof(x));
    pos += sizeof(x);
    aux.replace(pos, sizeof(y), reinterpret_cast<char*>(&y), sizeof(y));
    return aux;
}

void serialCurrency::fromString(string repr) {
    int pos = 0;
    repr.copy(reinterpret_cast<char*>(&x), sizeof(x), pos);
    pos += sizeof(x);
    repr.copy(reinterpret_cast<char*>(&y), sizeof(y), pos);

}


unsigned long long int serialCurrency::size() const {
    return sizeof(x) + sizeof(y);
}
