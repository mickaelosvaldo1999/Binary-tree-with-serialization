#ifndef TYPEDFILE_H
#define TYPEDFILE_H

#include <fstream>
#include <type_traits>
#include <string>
#include <header.h>
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
      bool writeRecord(record<T> &r);
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
    char *aux = new char[rosetta.getSizeBody()];
    mFile.seekg(rosetta.getRecordPosition(i));
    mFile.read(aux, rosetta.getSizeBody());
    //Passando a string sem truncar com o tamanho pré-determinado
    r.fromString(string(aux, rosetta.getSizeBody()));
}

template <class T>
bool typedFile<T>::writeRecord(record<T> &r) {
    cout << r.toString(rosetta.getSizeBody()).c_str() << endl;
    mFile.write(r.toString(rosetta.getSizeBody()).c_str(),rosetta.getSizeBody());
}

template <class T>
bool typedFile<T>::writeRecord(record<T> &r, unsigned long long int i) {
    mFile.seekp(rosetta.getRecordPosition(i));
    mFile.write(r.toString(rosetta.getSizeBody()).c_str(),rosetta.getSizeBody());
};

template <class T>
bool typedFile<T>::insertRecord(record<T> &r) {

}

template <class T>
bool typedFile<T>::deleteRecord(unsigned long long int i) {

}

template <class T>
unsigned long long int typedFile<T>::getFirstValid() {

}

template <class T>
unsigned long long int typedFile<T>::getFirstDeleted() {

}

template <class T>
unsigned long long int typedFile<T>::search(T data) {

}

template <class T>
bool typedFile<T>::readHeader(header &h) {
    //lendo cabeçalho do arquivo
    mFile.seekg(0);
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
    this->close();
    this->open();
    return true;
}

template <class T>
unsigned long long int typedFile<T>::index2pos(unsigned long long int i) {

}

template <class T>
unsigned long long int typedFile<T>::pos2index(unsigned long long int p) {

}
#endif // TYPEDFILE_H
