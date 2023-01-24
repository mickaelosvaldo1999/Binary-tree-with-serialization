#ifndef HEADER_H
#define HEADER_H

#include "serializable.h"

/***
                                __________________________________________________
                                |                                                |
                                |     TRABALHO DE TÉCNICAS DE PROGRAMAÇÃO        |
                                |----------------------------------------------- |
                                |   ÁRVORE B EM DISCO COM TIPO SERIALCURRENCY    |
                                |------------------------------------------------|
                                |AUTOR: MICKAEL OSVALDO DE OLIVEIRA - RA:0059793 |
                                |AUTOR: FILIPE ANDRADE COELHO - RA:0022130       |
                                |________________________________________________|

***/


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

      virtual string toXML() {return "NotImplemented";};
      virtual void fromXML(string repr) {};
      virtual string toCSV() {return "NotImplemented";};
      virtual void fromCSV(string repr) {};
      virtual string toJSON() {return "NotImplemented";};
      virtual void fromJSON(string repr) {};
   protected:
      //Dados do cabeçalho
      string type = "BTR";
      unsigned int version = 1;
      unsigned long long int firstValid = 0;
      unsigned long long int firstDeleted = 0;
};

#endif // HEADER_H
