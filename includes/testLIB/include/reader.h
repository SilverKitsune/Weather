#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <QDebug>

using namespace std;

class Reader
{
public:
    Reader(){};
    ~Reader(){};

    long secLength(char a, char b, char c)
    {
        return ((unsigned char)a<<16)+((unsigned char)b<<8)+(unsigned char)c;
    }

    int int2(char a, char b)
    {
        //int res = ((unsigned char)a<<8)+(unsigned char)b;
        return  ((unsigned char)a<<8)+(unsigned char)b;
    }

};

#endif // READER_H
