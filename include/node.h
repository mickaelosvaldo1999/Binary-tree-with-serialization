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
        string toString();
        void fromString(string repr);
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
        unsigned long long int size();


    protected:

    private:
        T dataSet;
        bool leaf = true;
        vector<T> values;
        vector<unsigned long long int> keys;

};

template <class T>
string node<T>::toString() {
    values.push_back(2);
    values.push_back(3);
    values.push_back(4);
    keys.push_back(6);
    unsigned long long int temp;
    string aux;
    unsigned int pos = 0;
    aux.insert(0,this->size(), '/0');
    pos += sizeof(leaf);
    aux.replace(0,sizeof(leaf),reinterpret_cast<char*>(&leaf), sizeof(leaf));

    for (auto i : values) {
        aux.replace(pos,i.size(),i.toString());
        dataSet = i;
        pos += i.size();
    }

    if (values.size() < 5) {
        for (auto i = values.size(); i < 5 ; i++) {
            aux.replace(pos,dataSet.size(),dataSet.toString());
            pos += dataSet.size();
        }
    }

    for (auto i : keys) {
        aux.replace(pos,sizeof(i),reinterpret_cast<char*>(&i), sizeof(i));
        temp = i;
        pos += sizeof(i);
    }
    if (keys.size() < 6) {
        for (auto i = keys.size(); i < 6; i++) {
            aux.replace(pos,sizeof(temp),reinterpret_cast<char*>(&temp), sizeof(temp));
            pos += sizeof(unsigned long long int);
        }
    }

    cout << endl << pos << endl;
    cout << endl << this->size();
    aux.resize(this->size());
    return aux;
}

template <class T>
void node<T>::fromString(string repr) {
    int aux,pos = 0;
    unsigned long long int temp,tempb;
    repr.copy(reinterpret_cast<char*>(&leaf), sizeof(leaf), pos);
    pos += sizeof(leaf);
    cout << endl << "essa folha é " << leaf << endl;

    for (int i = 0; i < 5; i++) {
       repr.copy(reinterpret_cast<char*>(&aux), sizeof(int), pos);
       pos += dataSet.size();
       cout << endl << aux << endl;
    }
    cout << endl << "----------------" << endl;
    for (int i = 0; i < 6; i++) {
       repr.copy(reinterpret_cast<char*>(&temp), sizeof(temp), pos);
       pos += sizeof(temp);
       if (temp != tempb) {
        values.push_back(temp);
       }
       tempb = temp;
    }

    for (auto i : keys) {
        cout << endl << i << endl;
    }
}

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
unsigned long long int node<T>::size() {
    return sizeof(leaf) + (sizeof(int) * 5) + (sizeof(unsigned long long int) * 6);
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
