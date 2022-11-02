#ifndef HEADER_H
#define HEADER_H

#include "serializable.h"


class header : public serializable {
   public:
      header();
      header(const header &h);
      virtual ~header();
      header operator=(const header &h);
      bool operator==(const header &h);
      bool verify(string type, int v);
      unsigned long long int getFirstDeleted() const;
      int getSizeHeader();
      void setFirstDeleted(unsigned long long int r);
      unsigned long long int getFirstValid() const;
      void setFirstValid(unsigned long long int r);
      string getType() const;
      void setType(string t);
      unsigned int getVersion() const;
      void setVersion(unsigned int v);
      virtual string toString();
      virtual void fromString(string repr);
      virtual unsigned long long int size() const;
   protected:
      //Dados do cabeçalho
      string type;
      unsigned int version = 1;
      unsigned long long int firstValid = 12;
      unsigned long long int firstDeleted = 93;
      //Tradução para que o cabeçalho indique todas as estruturas a serem seguidas
      unsigned int sizeHeader, sizeBody;
};

#endif // HEADER_H
