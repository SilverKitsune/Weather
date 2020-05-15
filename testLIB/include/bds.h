#ifndef BDS_H
#define BDS_H
#include <reader.h>
#include <vector>
#include <QList>

class BDS:public Reader
{
protected:
    struct Data {
        long sectionLength;
        int flag;
        bool simplePack;
        bool fPoint;
        bool mapPoint;
        bool addflag;
        int E;
        float refValue;
        size_t bit;
        QList<float> pointData;
    };
public:
    friend struct uniData;
    BDS(){};
    ~BDS(){};

    void readSec(ifstream *file, Data* d, int D, string type);
//    BDS & operator =(const BDS&obj)
//    {
//        refValue = obj.refValue;
//       /* Ni = obj.Ni;
//        Nj=obj.Nj;
//        La1=obj.La1;
//        Lo1=obj.Lo1;
//        La2=obj.La2;
//        Lo2=obj.Lo2;*/
//        return *this;
//    }
    /*!
     * \brief Вычисляет референсное значение
     * \param октеты 7-10
     */
    void ref(float *,char a, char b, char c, char d);

    //https://www.geeksforgeeks.org/bitwise-and-of-n-binary-strings/

    void simple(ifstream *file,Data* d, int D, string type);

    void finishData(size_t bit, string data, vector<float>* dataF );
};

#endif // BDS_H
