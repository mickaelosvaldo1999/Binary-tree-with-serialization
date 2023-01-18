#ifndef TREE_H
#define TREE_H
#include <node.h>

template <class T>
class tree
{
    public:
        tree(int i);
        virtual ~tree();
        bool insert(T k);
        void print();
        bool loopInsert(node<T> &i, T k);
        bool isFull(node<T> i);
        bool isEmpty(node<T> i);
        void splitChild(node<T> &i);


    protected:

    private:
        int minDegree;
        node<T> root;

};

template <class T>
void tree<T>::splitChild(node<T> &i) {
    //definindo vetores auxiliares
    vector<T> aux;
    vector<node<T>> auxA;
    auto temp = i.getValues();
    auto keys = i.getKeys();
    node<T> tempA(i.isLeaf());
    node<T> tempB(i.isLeaf());
    i.setLeaf(false);

    //copiando valores e chaves
    copy(temp.begin(), temp.begin() + (((2*minDegree)-1)/2), back_inserter(aux));
    tempA.setValues(aux);
    aux.clear();
    copy(temp.begin() + (((2*minDegree)-1)/2) + 1, temp.end(), back_inserter(aux));
    tempB.setValues(aux);

    if (!tempA.isLeaf()) {
        copy(keys.begin(), keys.begin() + (((2*minDegree))/2), back_inserter(auxA));
        tempA.setKeys(auxA);

        auxA.clear();
        copy(keys.begin() + (((2*minDegree))/2), keys.end(), back_inserter(auxA));
        tempB.setKeys(auxA);
    }

    //limpando daddos
    i.clear();
    //inserindo chaves
    i.appendValue(temp[(((2*minDegree)-1)/2)]);
    i.appendChild(tempA);
    i.appendChild(tempB);
    //cout << "--";

}

template <class T>
void tree<T>::print() {
    bool aux = true;
    vector<node<T>> level;
    vector<node<T>> temp;
    level.push_back(root);
    string line = "";
    while (aux) {
        for (node<T> i : level) {
            line += i.print();
            for (auto j : i.getKeys()) {
                temp.push_back(j);
            }
        }
        cout << endl << line;
        line = "";
        level = temp;
        temp.clear();
        if (level.size() == 0) {
            aux = false;
        }
    }
}

template <class T>
bool tree<T>::insert(T k) {
    //Verificando se a raiz não está cheia
    if (isFull(root)) {
        cout << endl << "Fudeu" << endl;
        splitChild(this->root);
    }
    //Começando a recurssão pela raiz
    loopInsert(this->root,k);
}

template <class T>
bool tree<T>::loopInsert(node<T> &node, T value) {
    if (node.isLeaf()) {
            cout << endl << "append de " << value;
            node.appendValue(value);
            cout << endl << node.print();
;    } else {
        cout << endl << "TODO" << endl;
        for (auto i : node.getValues()) {
            if (value < i) {
                cout << "menor que " << i;
            } else if (i == node.getValues().back()) {
                auto k = node.getKeys().back();
                if (isFull(k)) {
                    cout << endl << "Split";
                }
                else {
                    return loopInsert(k,value);
                }
            }
        }
    }
}

template <class T>
bool tree<T>::isFull(node<T> i) {
    if (i.sizeValues() == (2 * minDegree) - 1) {
        return true;
    }

    else {
        return false;
    }
}

template <class T>
bool tree<T>::isEmpty(node<T> i) {
    if (i.sizeValues() == (minDegree - 1)) {
        return true;
    }

    else {
        return false;
    }
}

template <class T>
tree<T>::tree(int i) {
    minDegree = i;
    root.setLeaf(true);
    std::cout << isEmpty(root);
    cout << root.isLeaf();
}

template <class T>
tree<T>::~tree() {
    //ctor
}
#endif // TREE_H
