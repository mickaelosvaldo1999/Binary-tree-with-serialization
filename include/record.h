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
      virtual string toString(unsigned int i);
      virtual void fromString(string repr);
      virtual unsigned long long int size() const;
   protected:
      T data;
      unsigned int getSize;
      bool deleted = true;
      unsigned long long int next = 1313;
};

template <class T>
record<T>::record() : serializable() {

}

template <class T>
record<T>::record(T d) : serializable() {
    data = d;
    cout << "//" << data.getValue() << endl;
}

template <class T>
record<T>::record(const record<T> &other) {

}

template <class T>
record<T>::~record() {

}

template <class T>
record<T> record<T>::operator=(const record<T> &other) {
    T aux = other.getData();
    cout << "-[]" << aux.getValue();
    cout << "comparado " << data.getValue() << other.getData().getValue();
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

}

template <class T>
void record<T>::setNext(unsigned long long int n) {

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
    //Classe legado
}

template <class T>
string record<T>::toString(unsigned int i){
    // i diz o tamanho do registro
    getSize = i;
    string aux;
    unsigned int pos = 0;
    //preciso arrumar o insert
    aux.insert(0,i, '\0');
    pos += sizeof(deleted);
    aux.replace(0,sizeof(deleted),reinterpret_cast<char*>(&deleted), sizeof(deleted));
    aux.replace(pos,pos+sizeof(next),reinterpret_cast<char*>(&next), sizeof(next));
    pos += sizeof(next);
    string temp = data.toString();
    aux.replace(pos,i,temp);
    aux.resize(i);
    return aux;
};

template <class T>
void record<T>::fromString(string repr) {
    int pos = 0;
    repr.copy(reinterpret_cast<char*>(&deleted), sizeof(deleted), pos);
    pos += 1;
    repr.copy(reinterpret_cast<char*>(&next), sizeof(next), pos);
    pos += sizeof(next);
    string teste = repr.substr(pos, getSize);
    cout << next << " deleted: " << deleted << " dados: " << teste << endl;
}

template <class T>
unsigned long long int record<T>::size() const {
    //tamanho do
    return sizeof(deleted) + sizeof(next) + sizeof(int);
}

#endif // RECORD_H
