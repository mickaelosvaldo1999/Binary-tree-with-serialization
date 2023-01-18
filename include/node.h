#ifndef NODE_H
#define NODE_H
#include <vector>
#include <iostream>
#include <string.h>
#include <iterator>
#include <sstream>
#include <algorithm>
using namespace std;

template <class T>
class node
{
    public:
        node();
        node(bool i);
        void appendChild(node<T> i);
        void clear();
        vector<T> getValues();
        void setValues(vector<T> i);
        vector<unsigned long long int> getKeys();
        void setKeys(vector<unsigned long long int> i);
        string print();
        bool appendValue(T k);
        int sizeValues();
        bool isLeaf();
        void setLeaf(bool i);
        virtual ~node();
        bool operator<(const node<T> &other) const;

    protected:

    private:
    bool leaf = false;
    vector<T> values;
    vector<unsigned long long int> keys;

};

template <class T>
void node<T>::clear() {
    values.clear();
    keys.clear()
;}

template <class T>
bool node<T>::operator<(const node<T> &other) const {
    return values[0] < other.getValues()[0];
}

template <class T>
void node<T>::appendChild(node<T> i) {
    keys.push_back(i);
    //sort(keys.begin(), keys.end());
}

template <class T>
string node<T>::print() {
    stringstream result;
    copy(values.begin(), values.end(), ostream_iterator<T>(result, " "));
    string aux = result.str().c_str();
    aux = "[ " + aux + "]";
    return aux;
}

template <class T>
vector<T> node<T>::getValues() {
    return values;
}

template <class T>
void node<T>::setValues(vector<T> i) {
    values = i;
}

template <class T>
vector<unsigned long long int> node<T>::getKeys() {
    return keys;
}


template <class T>
void node<T>::setKeys(vector<unsigned long long int> i) {
    keys = i;
}

template <class T>
bool node<T>::appendValue(T k) {
    //Agregando o valor
    values.push_back(k);
    //ordenando o vetor
    sort(values.begin(), values.end());
}

template <class T>
bool node<T>::isLeaf() {
    return leaf;
}

template <class T>
void node<T>::setLeaf(bool i) {
    leaf = i;
}

template <class T>
int node<T>::sizeValues() {
    return values.size();
}

template <class T>
node<T>::node()
{
    //ctor
}

template <class T>
node<T>::node(bool i)
{
    leaf = i;
}

template <class T>
node<T>::~node()
{
    //dtor
}
#endif // NODE_H
