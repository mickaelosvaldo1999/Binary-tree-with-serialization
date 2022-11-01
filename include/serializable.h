#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H
#include <string>
using namespace std;

class serializable {
   public:
      serializable() {}
      virtual ~serializable() {}
      virtual string toString() = 0;
      virtual void fromString(string repr) = 0;
      virtual unsigned long long int size() const = 0;
};

#endif // SERIALIZABLE_H
