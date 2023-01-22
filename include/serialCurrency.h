#ifndef SERIALCURRENCY_H
#define SERIALCURRENCY_H

#include "serializable.h"

class serialCurrency : serializable {
   public:
      serialCurrency();
      serialCurrency(string i);
      serialCurrency(const serialCurrency& other);
      virtual ~serialCurrency();

      serialCurrency operator=(const serialCurrency& other);
      bool operator==(const serialCurrency &other) const;
      bool operator<(const serialCurrency &other) const;
      bool operator!=(const serialCurrency &other) const;
      serialCurrency operator+(const serialCurrency& other) const;
      serialCurrency operator-(const serialCurrency& other) const;
      serialCurrency operator*(const serialCurrency& other) const;
      serialCurrency operator/(const serialCurrency& other) const;
      serialCurrency operator++();
      serialCurrency operator--();
      void setValue(int v);
      string getValue() const;
      virtual string toString();
      virtual void fromString(string repr);
      virtual unsigned long long int size() const;
      string empty();
      int getx() const;
      void setx(int);
      unsigned short int gety() const;
      void sety(unsigned short int);

      virtual string toXML() {return "NotImplemented";};
      virtual void fromXML(string repr) {};
      virtual string toCSV() {return "NotImplemented";};
      virtual void fromCSV(string repr) {};
      virtual string toJSON() {return "NotImplemented";};
      virtual void fromJSON(string repr) {};

   protected:
      int value = 999;
      int x;
      unsigned short int y;
};

#endif // SERIALCURRENCY_H
