#ifndef TREE_H
#define TREE_H
#include <node.h>
#include <typedfile.h>
#include "record.h"
#include <string>
#include <algorithm>

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
        bool loopRemove(unsigned long long int i,T value);
        bool isFull(node<T> i);
        bool isEmpty(node<T> i);
        vector<node<T>> splitChild(node<T> i);
        node<T> mergeChild(node<T> keyA, node<T> keyB);
        bool readNode(node<T> &n, unsigned long long int i);
        bool writeNode(node<T> n, unsigned long long int i);
        bool removeNode(unsigned long long int k);
        bool remove(T value);
        void sortChild(node<T> n);
        unsigned long long int insertNode(node<T> n);
        bool search(T value);
        bool searchLoop(unsigned long long int k, T value);
        bool isOpen();
        void close();

    protected:

    private:
        typedFile<node<T>> arq{"tree.dat", "BTR", 1};
        int minDegree;
        unsigned long long int rootKey;

};


template <class T>
vector<node<T>> tree<T>::splitChild(node<T> i) {
    //definindo vetores auxiliares
    vector<T> aux;
    vector<unsigned long long int> auxA;

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

    //verificação otimizada de nó não folha
    if (!tempA.isLeaf()) {
        copy(keys.begin(), keys.begin() + (((2*minDegree))/2), back_inserter(auxA));
        tempA.setKeys(auxA);

        auxA.clear();
        copy(keys.begin() + (((2*minDegree))/2), keys.end(), back_inserter(auxA));
        tempB.setKeys(auxA);
    }

    //limpando daddos
    i.clear();
    //inserindo valores
    i.appendValue(temp[(((2*minDegree)-1)/2)]);

    //criando vetor de sada
    vector<node<T>> tempC;
    tempC.push_back(i);
    tempC.push_back(tempA);
    tempC.push_back(tempB);
    cout << endl << "####### " << tempA.print() << tempB.print() << endl;
    return tempC;
}

template <class T>
node<T> tree<T>::mergeChild(node<T> keyA, node<T> keyB) {
    //Juntando os dois nodes
    for (auto i : keyB.getValues()) {
        keyA.appendValue(i);
    }

    for (auto i : keyB.getKeys()) {
        keyA.appendChild(i);
    }

    //sortChild(keyA);
    return keyA;

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
                readNode(root,j);
                temp.push_back(root);
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
bool tree<T>::writeNode(node<T> n, unsigned long long int i) {
    record<node<T>> r;
    r.setData(n);
    arq.writeRecord(r,i);
    return true;
}

template <class T>
bool tree<T>::removeNode(unsigned long long int i) {
    arq.deleteRecord(i);
    return true;
}

template <class T>
void tree<T>::sortChild(node<T> n) {

    vector<node<T>> aux;
    node<T> temp;
    for (auto i : n.getKeys()) {
        readNode(temp,i);
        aux.push_back(temp);
    }

    sort(aux.begin(), aux.end());

    int counter = 0;
    for (auto i : n.getKeys()) {
        writeNode(aux[counter], i);
        counter++;
    }
}

template <class T>
bool tree<T>::insert(T k) {

        if (!search(k)) {
        //carregando a raiz
        node<T> root;
        readNode(root,rootKey);
        //Verificando se a raiz está cheia
        if (isFull(root) && root.isLeaf()) {
            //inserindo nova raiz
            vector<node<T>> aux;
            aux = splitChild(root);
            aux[0].appendChild(insertNode(aux[1]));
            aux[0].appendChild(insertNode(aux[2]));
            writeNode(aux[0],rootKey);

        }
    //Começando a recurssão pela raiz
    return loopInsert(rootKey,k);
    }
    else {
        cerr << endl << "Não é possível inserir duplicatas: " << k.getValue() << endl;
        return false;
    }
}

template <class T>
bool tree<T>::loopInsert(unsigned long long int k, T value) {
    //lendo registro
    node<T> n;
    readNode(n,k);


    if (n.isLeaf()) {
            //o nó é folha
            n.appendValue(value);
            writeNode(n,k);
            return true;
            }
        else {

        //declarando variável do nó abaixo
        node<T> nBelow;

        int counter = 0;
        for (auto i : n.getValues()) {
            //valor menor possui mesmo índice

            if (value < i || i == n.getValues().back()) {

                unsigned long long int keys;
                if (value < i) {
                    //verificando maior chave
                    keys = n.getKeys()[counter];
                    readNode(nBelow,keys);

                    }
                //caso especial, o valor é maior que todos os outros
                else if (i == n.getValues().back()) {
                    //verificando maior chave
                    keys = n.getKeys().back();
                    readNode(nBelow,keys);
                    }

                //a página abaixo está cheia
                if (isFull(nBelow)) {
                    //fazendo o split
                    vector<node<T>> inserter;
                    inserter = splitChild(nBelow);

                    n.appendValue(inserter[0].getValues()[0]);
                    writeNode(inserter[1],keys);
                    n.appendChild(insertNode(inserter[2]));
                    writeNode(n,k);
                    sortChild(n);
                    return loopInsert(k,value);

                }
                else {
                    return loopInsert(keys,value);
                }
            }
            //controle de contagem de i
            counter += 1;
        }
    }
    return false;
}

template <class T>
bool tree<T>::remove(T k) {
    if (search(k)) {
        //carregando a raiz
        node<T> root;
        readNode(root,rootKey);
        //Começando a recurssão pela raiz
        return loopRemove(rootKey,k);
    }
    else {
        cerr << endl << "O valor descrito não existe: " << k.getValue() << endl;
        return false;
    }
}


template <class T>
bool tree<T>::loopRemove(unsigned long long int k, T value) {

     //lendo registro
    node<T> n;
    readNode(n,k);
    n.print();
    if (n.isLeaf()) {
            //o nó é folha
            n.removeValue(value);
            writeNode(n,k);
            return true;
            }

        else {

        //declarando variável do nó abaixo
        node<T> nBelow;
        node<T> nBelowSide;

        int counter = 0;
        for (auto i : n.getValues()) {
            //valor menor possui mesmo índice

            if (value < i || i == n.getValues().back() || value == i) {

                unsigned long long int keys;

                //Valor está na página interna
                if (value == i) {
                    //pegando chave do nó
                    keys = n.getKeys()[counter];
                    readNode(nBelow,keys);
                    readNode(nBelowSide,n.getKeys()[counter + 1]);

                    if (isEmpty(nBelow)) {
                        if (isEmpty(nBelowSide)) {
                            //merge
                            //jogando valores do merge para dentro do primeiro nó
                            nBelow = mergeChild(nBelow,nBelowSide);
                            //caso especial da raiz
                            if (k == rootKey) {
                                writeNode(nBelow,k);
                                removeNode(n.getKeys()[counter]);
                                removeNode(n.getKeys()[counter + 1]);
                                return true;
                            } else {
                                //caso da chave ordinária
                                n.removeChild(n.getKeys()[counter + 1]);
                                writeNode(nBelow,keys);
                                n.removeValue(value);
                                writeNode(n,k);
                                return true;

                            }
                        } else {
                            //removendo valor do nó cheio ao lado
                            n.removeValue(value);
                            n.appendValue(nBelowSide.getValues()[0]);
                            writeNode(n,k);
                            return loopRemove(n.getKeys()[counter + 1],nBelowSide.getValues()[0]);
                        }
                    } else {
                        //removendo nó cheio ao lado
                        n.removeValue(value);
                        n.appendValue(nBelow.getValues().back());
                        writeNode(n,k);
                        return loopRemove(n.getKeys()[counter],nBelow.getValues().back());

                    }

                }

                //valor está abaixo
                else if (value < i) {
                    //verificando chave chave
                    keys = n.getKeys()[counter];
                    readNode(nBelow,keys);
                    readNode(nBelowSide,n.getKeys()[counter + 1]);

                    }
                //caso especial, o valor é maior que todos os outros
                else if (i == n.getValues().back()) {
                    //verificando maior chave
                    keys = n.getKeys()[counter + 1];
                    readNode(nBelow,keys);
                    readNode(nBelowSide,n.getKeys()[counter]);
                    }

                //a página abaixo está cheia
                //Split preventivo
                if (isEmpty(nBelow)) {
                    readNode(nBelowSide,n.getKeys()[counter + 1]);

                    /***
                    //fazendo o split
                    vector<node<T>> inserter;
                    cout << endl << "merge";
                    inserter = splitChild(nBelow);

                    n.appendValue(inserter[0].getValues()[0]);
                    writeNode(inserter[1],keys);
                    n.appendChild(insertNode(inserter[2]));
                    writeNode(n,k);
                    sortChild(n);
                    return loopRemove(k,value);
                    ***/

                }
                else {
                    return loopRemove(keys,value);
                }
            }
            //controle de contagem de i
            counter += 1;
        }
    }
    return false;
}

template <class T>
bool tree<T>::search(T value) {
    //carregando a raiz
    return searchLoop(rootKey,value);
}

template <class T>
bool tree<T>::searchLoop(unsigned long long int k, T value) {
    //lendo registro
    node<T> n;
    readNode(n,k);

    if (n.isLeaf()) {
            for (auto i : n.getValues()) {
                if (i == value) {
                    return true;
                }
            }
            return false;
            }
        else {

        //declarando variável do nó abaixo

        int counter = 0;
        for (auto i : n.getValues()) {
            //valor menor possui mesmo índice

            if (value < i || i == n.getValues().back() || value == i) {

                unsigned long long int keys;
                if (value == i) {
                    return true;
                    }
                else if (value < i) {
                    //verificando maior chave
                    keys = n.getKeys()[counter];
                }
                //caso especial, o valor é maior que todos os outros
                else if (i == n.getValues().back()) {
                    //verificando maior chave
                    keys = n.getKeys().back();
                    }
                return searchLoop(keys,value);
            }
            //controle de contagem de i
            counter += 1;
        }
    }
    cerr << endl << "ERRO NA BUSCA" << endl;
    return false;
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
            rootKey = insertNode(root);
        } else {
            //Raiz existe
            rootKey = arq.getFirstValid();
;        }
    } else {
      cout << "Não foi possível abrir o arquivo!" << endl;
      }
}

template <class T>
unsigned long long int tree<T>::insertNode(node<T> n) {
    record<node<T>> r;
    r.setData(n);
    return arq.insertRecord(r);
}

template <class T>
bool tree<T>::isOpen() {
    return arq.isOpen();
}

template <class T>
tree<T>::~tree() {
    //ctor
}
#endif // TREE_H
