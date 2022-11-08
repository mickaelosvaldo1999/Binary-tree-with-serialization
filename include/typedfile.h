#ifndef TYPEDFILE_H
#define TYPEDFILE_H

#include <fstream>
#include <type_traits>
#include <string>
#include <header.h>
#include <intserial.h>
using namespace std;

const ios::openmode mode = ios::in | ios::out | ios::ate | ios::binary;

template <class T>
class typedFile : private fstream {
   static_assert(is_base_of<serializable, T>::value, "T must be serializable");
   public:
      typedFile();
      typedFile(const string name, const string type,int ver);
      virtual ~typedFile();
      void open();
      bool isOpen();
      void close();
      void clear();
      bool readRecord(record<T> &r, unsigned long long int i);
      bool writeRecord(record<T> &r, unsigned long long int i);
      bool insertRecord(record<T> &r);
      bool deleteRecord(unsigned long long int i);
      unsigned long long int getFirstValid();
      unsigned long long int getFirstDeleted();
      unsigned long long int search(T data);

    private:
    //variáveis essenciais
    string name,type;
    int version;
    fstream mFile;
    //Cabeçalho da classe
    header rosetta;

   protected:
      bool readHeader(header &h);
      bool writeHeader(header &h);
      unsigned long long int index2pos(unsigned long long int i);
      unsigned long long int pos2index(unsigned long long int p);
};

template <class T>
typedFile<T>::typedFile() : fstream() {

}

template <class T>
typedFile<T>::typedFile(const string name, const string type, int ver) : fstream(name.c_str(), mode) {
    //setando parâmetros essenciais
    this->name = name;
    this->type = type;
    this->version = ver;
    //verificando a compatibilidade do header
    this->open();
}

template <class T>
typedFile<T>::~typedFile() {

}

template <class T>
void typedFile<T>::open() {
    //Verificando se o arquivo existe.
    mFile.open(name,mode);
    if (!this->isOpen()) {
        //Se não existe ele precisa ser criado e o cabeçalho deve ser escrito
        mFile.open(name, ios::out);
        this->close();
        mFile.open(name,mode);
        if (!this->isOpen()) {
            //Se a biblioteca falhar de maneira geral o programa deve ser fechado.
            cerr << "Não foi possivel abrir o arquivo. Problema com FSTREAM";
        }
        else {
            //Se o arquivo foi aberto então o cabeçalho deve ser escrito
            this->writeHeader(rosetta);
            this->close();
            this->open();
            }
    } else {
        //Se o arquivo foi acerto então o cabeçalho deve ser lido
        this->readHeader(rosetta);
    };
}

template <class T>
bool typedFile<T>::isOpen() {
    return mFile.is_open();
;}

template <class T>
void typedFile<T>::close() {
    mFile.close();
}

template <class T>
void typedFile<T>::clear() {

}

template <class T>
bool typedFile<T>::readRecord(record<T> &r, unsigned long long int i) {
    char *aux = new char[r.size()];
    mFile.seekg(this->index2pos(i), ios::beg);
    mFile.read(aux, r.size());
    //Passando a string sem truncar com o tamanho pré-determinado
    r.fromString(string(aux, r.size()));
}

template <class T>
bool typedFile<T>::writeRecord(record<T> &r, unsigned long long int i) {
    if (i == 0) {
        //Verificando ultima posição do arquivo
        mFile.seekp(0, ios::end);
        //setando  record para pegar o ultimo válido
        r.setNext(rosetta.getFirstValid());
        rosetta.setFirstValid(this->pos2index(mFile.tellp()));
        //escrevendo de fato no arquivo
        mFile.write(r.toString().c_str(),r.size());
        this->writeHeader(rosetta);
        return true;
    } else {
        //Verificando primeiro valor válido
        r.setNext(rosetta.getFirstValid());
        rosetta.setFirstValid(i);
        //escrevendo de fato o registro
        mFile.seekp(this->index2pos(1));
        mFile.write(r.toString().c_str(),r.size());
        this->writeHeader(rosetta);
        return true;
    }
    return false;
};

template <class T>
bool typedFile<T>::insertRecord(record<T> &r) {
    if (rosetta.getFirstDeleted() == 0) {
        cout << "########## -- firstdeleted = 0" << endl;
        return this->writeRecord(r,0);
    } else {
        //Reciclando valor do registro
        unsigned long long int newR = rosetta.getFirstDeleted();
        //Adicionando novo registro a lista de deletados.
        record<T> aux;
        this->readRecord(aux,rosetta.getFirstDeleted());
        rosetta.setFirstDeleted(aux.getNext());
        //Reciclando registro.
        this->writeRecord(r,newR);
    }
}

template <class T>
bool typedFile<T>::deleteRecord(unsigned long long int i) {

}

template <class T>
unsigned long long int typedFile<T>::getFirstValid() {
    return rosetta.getFirstValid();
}

template <class T>
unsigned long long int typedFile<T>::getFirstDeleted() {
    return rosetta.getFirstDeleted();
}

template <class T>
unsigned long long int typedFile<T>::search(T data) {

}

template <class T>
bool typedFile<T>::readHeader(header &h) {
    //lendo cabeçalho do arquivo
    mFile.seekg(0, ios::beg);
    char *aux = new char[rosetta.size()];
    mFile.read(aux, rosetta.size());
    rosetta.fromString(string(aux, rosetta.size()));
    return true;
}

template <class T>
bool typedFile<T>::writeHeader(header &h) {
    //escrevendo primeiro cabeçalho
    string aux = rosetta.toString();
    mFile.seekp(0);
    mFile.write(aux.c_str(), rosetta.size());
    return true;
}

template <class T>
unsigned long long int typedFile<T>::index2pos(unsigned long long int i) {
    return (rosetta.size() + ((i - 1)*13));
}

template <class T>
unsigned long long int typedFile<T>::pos2index(unsigned long long int i) {
    return ((i - rosetta.size()) / 13) + 1;
}
#endif // TYPEDFILE_H
