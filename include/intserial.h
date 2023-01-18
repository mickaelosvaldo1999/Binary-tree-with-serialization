#ifndef INTSERIAL_H
#define INTSERIAL_H

#include "serializable.h"

class intSerial : serializable {
   public:
      intSerial();
      intSerial(int i);
      intSerial(const intSerial& other);
      virtual ~intSerial();
      intSerial operator=(const intSerial& other);
      bool operator==(const intSerial &other) const;
      bool operator<(const intSerial &other) const;
      bool operator!=(const intSerial &other) const;
      intSerial operator+(const intSerial& other) const;
      intSerial operator-(const intSerial& other) const;
      intSerial operator*(const intSerial& other) const;
      intSerial operator/(const intSerial& other) const;
      intSerial operator++();
      intSerial operator--();
      void setValue(int v);
      int getValue() const;
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
      int value = 999;
};

#endif // INTSERIAL_H
