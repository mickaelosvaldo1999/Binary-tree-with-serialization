#ifndef TREE_H
#define TREE_H
#include <node.h>
#include <typedfile.h>
#include <string>

using namespace std;
template <class T>
class tree
{
    public:
        tree(int i);
        virtual ~tree();
        bool insert(T k);
        void print();
        bool loopInsert(unsigned long long int, T k);
        bool isFull(node<T> i);
        bool isEmpty(node<T> i);
        void splitChild(node<T> &i);
        bool readNode(node<T> &n, unsigned long long int i);
        unsigned long long int writeNode(node<T> n, unsigned long long int i);
        void close();

    protected:

    private:
        typedFile<node<T>> arq{"tree.dat", "BTR", 1};
        int minDegree;
        unsigned long long int rootKey;

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
    //vetores auxiliares
    bool aux = true;
    vector<node<T>> level;
    vector<node<T>> temp;
    //carregando a raiz
    node<T> root;
    readNode(root,rootKey);
    level.push_back(root);

    //printando a linha
    string line = "";
    while (aux) {
        for (node<T> i : level) {
            line += i.print();
            for (auto j : i.getKeys()) {
                temp.push_back(j);
            }
        }
        cout << line << endl;
        line = "";
        level = temp;
        temp.clear();
        if (level.size() == 0) {
            aux = false;
        }
    }
}


template <class T>
bool tree<T>::readNode(node<T> &n, unsigned long long int i) {
    record<node<T>> r;
    arq.readRecord(r,i);
    n = r.getData();
    return true;
}
template <class T>
unsigned long long int tree<T>::writeNode(node<T> n, unsigned long long int i) {
    record<node<T>> r;
    r.setData(n);
    arq.writeRecord(r,i);
    return 2;
}


template <class T>
bool tree<T>::insert(T k) {
    //carregando a raiz
    node<T> root;
    readNode(root,rootKey);
    //Verificando se a raiz não está cheia
    if (isFull(root)) {
        cout << endl << "Fudeu" << endl;
        //splitChild(root);

    }
    //Começando a recurssão pela raiz
    return loopInsert(rootKey,k);
}

template <class T>
bool tree<T>::loopInsert(unsigned long long int k, T value) {
    //lendo registro
    node<T> node;
    readNode(node,k);

    if (node.isLeaf()) {
            cout << endl << "append de " << value.getValue();
            node.appendValue(value);
            writeNode(node,k);
            cout << endl << node.print();
            return true;
            }
        else {
        cout << endl << "TODO" << endl;
        for (auto i : node.getValues()) {
            if (value < i) {
                cout << "menor que ";
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
void tree<T>::close() {
    arq.close();
}

template <class T>
tree<T>::tree(int i) {
    minDegree = i;
    if (arq.isOpen()) {
        //Raiz não existe
        if (arq.getFirstValid() == 0) {
            //carregando a raiz
            node<T> root;
            root.setLeaf(true);
            record<node<T>> r;
            r.setData(root);
            arq.insertRecord(r);
            rootKey = 1;
        } else {
            //Raiz existe
            rootKey = arq.getFirstValid();
;        }
    } else {
      cout << "Não foi possível abrir o arquivo!" << endl;
      }
}

template <class T>
tree<T>::~tree() {
    //ctor
}
#endif // TREE_H
