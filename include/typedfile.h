#ifndef TYPEDFILE_H
#define TYPEDFILE_H

#include <fstream>
#include <type_traits>
#include <string>
using namespace std;

const ios::openmode mode = ios::in | ios::out | ios::ate | ios::binary;

template <class T>
class typedFile : private fstream {
   static_assert(is_base_of<serializable, T>::value, "T must be serializable");
   public:
      typedFile();
      typedFile(const string name, const string type);
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
    string name,type;
    fstream mFile;

   protected:
      header head;
      bool readHeader(header &h);
      bool writeHeader(header &h);
      unsigned long long int index2pos(unsigned long long int i);
      unsigned long long int pos2index(unsigned long long int p);
};

template <class T>
typedFile<T>::typedFile() : fstream() {

}

template <class T>
typedFile<T>::typedFile(const string name, const string type) : fstream(name.c_str(), mode) {
    this->name = name;
    this->type = type;
}

template <class T>
typedFile<T>::~typedFile() {

}

template <class T>
void typedFile<T>::open() {
    mFile.open(name,mode);
    if (!this->isOpen()) {
        mFile.open(name, ios::out);
        this->close();
        mFile.open(name,mode);
        if (!this->isOpen()) {
            cerr << "Não foi possivel abrir o arquivo. Problema com FSTREAM";
        };
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

}

template <class T>
bool typedFile<T>::writeRecord(record<T> &r, unsigned long long int i) {

}

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

}

template <class T>
bool typedFile<T>::writeHeader(header &h) {

}

template <class T>
unsigned long long int typedFile<T>::index2pos(unsigned long long int i) {

}

template <class T>
unsigned long long int typedFile<T>::pos2index(unsigned long long int p) {

}
#endif // TYPEDFILE_H
