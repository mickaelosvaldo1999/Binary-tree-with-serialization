#ifndef RECORD_H
#define RECORD_H

#include <string>
#include "serializable.h"

using namespace std;

template <class T>
class record : public serializable {
   static_assert(is_base_of<serializable, T>::value, "T must be serializable");
   public:
      record();
      record(T d);
      record(const record<T> &other);
      virtual ~record();
      record<T> operator=(const record<T> &other);
      bool operator==(const record<T> &other);
      T getData() const;
      void setData(T d);
      unsigned long long int getNext() const;
      void setNext(unsigned long long int n);
      bool isDeleted() const;
      void del();
      void undel();
      virtual string toString();
      virtual void fromString(string repr);
      virtual unsigned long long int size() const;
   protected:
      T data;
      bool deleted = false;
      unsigned long long int next = 0;
};

template <class T>
record<T>::record() : serializable() {

}

template <class T>
record<T>::record(T d) : serializable() {
    //Seta a data quando o construtor é iniciado
    data = d;
}

template <class T>
record<T>::record(const record<T> &other) {
    //Construtor quando uma record inteira é utilizada como parametro
    data = other.getData();
    deleted = other.isDeleted();
    next = other.getNext();
}

template <class T>
record<T>::~record() {

}

template <class T>
record<T> record<T>::operator=(const record<T> &other) {
    //Sobrecarga com operador de igualdade
    T aux = other.getData();
    data = other.getData();
}

template <class T>
bool record<T>::operator==(const record<T> &other) {

}

template <class T>
T record<T>::getData() const {
    return data;
}


template <class T>
void record<T>::setData(T d) {
    data = d;
}

template <class T>
unsigned long long int record<T>::getNext() const {
    return next;
}

template <class T>
void record<T>::setNext(unsigned long long int n) {
    next = n;
}

template <class T>
bool record<T>::isDeleted() const {
    return deleted;
}

template <class T>
void record<T>::del() {
    deleted = true;
}

template <class T>
void record<T>::undel() {
    deleted = false;
}

template <class T>
string record<T>::toString() {
    //Transformando record em string
    string aux;
    unsigned int pos = 0;
    aux.insert(0,this->size(), '\0');
    pos += sizeof(deleted);
    aux.replace(0,sizeof(deleted),reinterpret_cast<char*>(&deleted), sizeof(deleted));
    aux.replace(pos,pos+sizeof(next),reinterpret_cast<char*>(&next), sizeof(next));
    pos += sizeof(next);
    string temp = data.toString();
    aux.replace(pos,this->size(),data.toString());
    aux.resize(this->size());
    return aux;
}


template <class T>
void record<T>::fromString(string repr) {
    int aux,pos = 0;
    repr.copy(reinterpret_cast<char*>(&deleted), sizeof(deleted), pos);
    pos += 1;
    repr.copy(reinterpret_cast<char*>(&next), sizeof(next), pos);
    pos += sizeof(next);
    repr.copy(reinterpret_cast<char*>(&aux), sizeof(int), pos);
    data.setValue(aux);
    cout << next << " deleted: " << deleted << " dados: " << data.getValue() << endl;
}

template <class T>
unsigned long long int record<T>::size() const {
    //tamanho do
    return sizeof(deleted) + sizeof(next) + sizeof(int);
}

#endif // RECORD_H
