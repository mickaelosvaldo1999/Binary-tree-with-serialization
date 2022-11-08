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
      unsigned long long int getFirstDeleted() const;
      unsigned long long int getRecordPosition(unsigned int i);
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
      string type = "BTR";
      unsigned int version = 1;
      unsigned long long int firstValid = 0;
      unsigned long long int firstDeleted = 0;
};

#endif // HEADER_H
