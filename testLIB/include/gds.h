#ifndef GDS_H
#define GDS_H
#include <reader.h>

class GDS: public Reader
{
protected:
    struct Data{
        long sectionLength;
        int NV;
        int PV_LV;
        string DataType;
        int Ni;
        int Nj;
        int La1;
        int Lo1;
        int flags;
        int La2;
        int Lo2;
        int Di;
        int Dj_N;
        int scanFlags;
    };
public:
    friend struct uniData;
    GDS(){};
    ~GDS(){};

//    GDS & operator =(const GDS&obj)
//    {
//        DataType = obj.DataType;
//        Ni = obj.Ni;
//        Nj=obj.Nj;
//        La1=obj.La1;
//        Lo1=obj.Lo1;
//        La2=obj.La2;
//        Lo2=obj.Lo2;
//        return *this;
//    }
    void readSec(ifstream *file, Data* d);

    string dataType(char dataType);

    void typeLanLon(ifstream *file, Data* d);

    //int getPointCnt(){return Ni*Nj;}
};

#endif // GDS_H
