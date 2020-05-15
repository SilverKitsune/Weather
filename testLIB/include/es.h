#ifndef ES_H
#define ES_H
#include<reader.h>

class ES :public Reader
{
public:
    ES(){};
    virtual ~ES(){};
    virtual void readSec(ifstream *file);
};


#endif // ES_H
