#include "header.h"
#include <iostream>
#include <string>
header::header() : serializable() {
   //ctor
}

header::header(const header &h) {
   // cpy ctor
   type = h.getType();
   firstDeleted = h.getFirstDeleted();
   firstValid = h.getFirstValid();
   version = h.getVersion();
}

header::~header() {
   //dtor
}

int header::getSizeHeader() {
    return sizeHeader;
}
bool header::verify(string type, int v) {
    //Verificar se o tipo e versão é compativel!!.
    if (v == this->version) {
        this->version = v;
        if (type == "BTR") {
            this->type = type;
            this->sizeHeader = 23;
            this->sizeBody = 80;
            return true;
        } else if (type == "MIK") {
            this->type = type;
            this->sizeHeader = 30;
            this->sizeBody = 80;
            return true;
        } else {
            cerr << "Tipo " << type <<" não encontrado!!" << endl;
            return false;
        }
    }
      else {
        cerr << "Vesão " << v <<" não compatível!!" << endl;
        return false;
    }
    return false;
}
header header::operator=(const header &h) {
   header aux(h);
   if (this == &h)
      return *this;

   type = h.getType();
   firstDeleted = h.getFirstDeleted();
   firstValid = h.getFirstValid();
   version = h.getVersion();

   return aux;
}

bool header::operator==(const header &h) {
   return type == h.getType() && version == h.getVersion() &&
          firstDeleted == h.getFirstDeleted() &&
          firstValid == h.getFirstValid();
}

unsigned long long int header::getFirstDeleted() const {
   return firstDeleted;
}

void header::setFirstDeleted(unsigned long long int r) {
   firstDeleted = r;
}

unsigned long long int header::getFirstValid() const {
   return firstValid;
}

void header::setFirstValid(unsigned long long int r) {
   firstValid = r;
}

string header::getType() const {
   return type;
}

void header::setType(string t) {
   type = t.substr(0, 3);
}

unsigned int header::getVersion() const {
   return version;
}

void header::setVersion(unsigned int v) {
   version = v;
}

string header::toString() {
   //Escrever string do cabeçalho!!
   string aux;
   unsigned int pos = 0;
   aux.insert(0,sizeHeader, '\0');
   pos +=3;
   aux.replace(0,pos,type);
   aux.replace(pos,pos+sizeof(version), reinterpret_cast<char*>(&version), sizeof(version));
   pos += sizeof(version);
   aux.replace(pos,pos+sizeof(firstValid), reinterpret_cast<char*>(&firstValid), sizeof(firstValid));
   pos += sizeof(firstValid);
   aux.replace(pos,pos+sizeof(firstDeleted), reinterpret_cast<char*>(&firstDeleted), sizeof(firstDeleted));
   pos += sizeof(firstValid);
   aux.resize(sizeHeader);
   return aux;
}

void header::fromString(string repr) {
   //Verificar se a versão do cabeçalho do arquivo é compativel
   int pos = 0;
   auto v = version;
   string t = repr.substr(pos, 3);
   pos += 3;
   cout << repr << endl;
   repr.copy(reinterpret_cast<char*>(&v), sizeof(v), pos);
   if (!this->verify(t,v)) {
        cout << "Uma versão diferente do arquivo foi encontrada, tenha certeza da compatibilidade antes de proceder!!" << endl;
   }
   pos += sizeof(version);
   repr.copy(reinterpret_cast<char*>(&firstValid), sizeof(firstValid), pos);
   pos += sizeof(firstValid);
   repr.copy(reinterpret_cast<char*>(&firstDeleted), sizeof(firstDeleted), pos);
}

unsigned long long int header::size() const {
   return type.length() + sizeof(version) + sizeof(firstValid) + sizeof(firstDeleted);
}
