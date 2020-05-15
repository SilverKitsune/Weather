#ifndef IS_H
#define IS_H
#include <reader.h>

class IS : public Reader
{
public:
    IS(){}
    ~IS(){}
    void readSec(ifstream*);
private:
    long totalLength;
    int editNumber;
};

#endif // IS_H
