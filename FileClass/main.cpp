#include <iostream>
#include <QTextStream>
#include <QDataStream>
#include <QFile>

using namespace Qt;
using namespace std;

class Arr
{
    int* M;
    int count;
public:

    Arr()
    {
        M = nullptr;
        count = 0;
    }

    Arr(int _count)
    {
        count = _count;
        M = new int[count];
    }

    Arr(const Arr& X)
    {
        count = X.count;
        M = new int[count];
        for (int i = 0; i < count; i++)
        {
            M[i] = X.M[i];
        }
    }

    Arr(Arr&& X)
    {
        M = X.M;
        count = X.count;
        X.count = 0;
        X.M = nullptr;
    }

    Arr operator= (Arr& X)
    {
        if (this != &X)
        {
            count = X.count;
            delete[] M;
            M = new int[count];
            for (int i = 0; i < count; i++)
            {
                M[i] = X.M[i];
            }
        }
        return *this;
    }


    Arr& operator= (Arr&& X)
    {
        if (this != &X)
        {
            delete[] M;
            M = X.M;
            count = X.count;
            X.M = nullptr;
            X.count = 0;
        }
        return *this;
    }

    int& operator[] (int x)
    {
        if (x < 0 || x >= count)
            throw ("bad");
        return M[x];
    }

    int& at (int x)
    {
        if (x >= count) throw ("bad");
        return M[x];
    }

    int at (int x) const
    {
        if (x >= count) throw ("bad");
        return M[x];
    }

    ~Arr()
    {
        delete[] M;
    }

    Arr& operator++()
    {
        for (int i = 0; i < count; i++)
            ++M[i];
        return *this;
    }
    Arr operator++(int)
    {
        for (int i = 0; i < count; i++)
            M[i]++;
        return *this;
    }

    void print(Arr& obj)
    {
        for (int i = 0; i < obj.count; i++)
            cout << obj[i] << ' ';
        cout << endl;
    }

    Arr operator-(Arr& obj)
    {
        for (int i = 0; i < obj.count; i++)
            obj[i] = -obj[i];
        return obj;
    }
    Arr operator+(Arr& obj)
    {
        return obj;
    }

    Arr& operator+=(const Arr& obj)
    {
        Arr c(obj);
        if (count == obj.count)
            for (int i = 0; i < count; i++)
                c[i] += M[i];
        if (this != &c)
        {
            for (int i = 0; i < count; i++)
                M[i] = c[i];
        }
        return *this;
    }

    Arr& operator-=(const Arr& obj)
    {
        Arr c(obj);
        if (count == obj.count)
            for (int i = 0; i < count; i++)
                c[i] = M[i] - c[i];
        if (this != &c)
        {
            for (int i = 0; i < count; i++)
                M[i] = c[i];
        }
        return *this;
    }

    Arr& operator*=(const Arr& obj)
    {
        Arr c(obj);
        if (count == obj.count)
            for (int i = 0; i < count; i++)
                c[i] *= M[i];
        if (this != &c)
        {
            for (int i = 0; i < count; i++)
                M[i] = c[i];
        }
        return *this;
    }

    Arr& operator/=(const Arr& obj)
    {
        Arr c(obj);
        if (count == obj.count)
            for (int i = 0; i < count; i++)
            {
                if (c[i] == 0)
                    throw ("bad");
                c[i] = M[i] / c[i];
            }
        if (this != &c)
        {
            for (int i = 0; i < count; i++)
                M[i] = c[i];
        }
        return *this;
    }

    friend Arr operator + (Arr& obj1, Arr& obj2);
    friend Arr operator - (Arr& obj1, Arr& obj2);
    friend Arr operator * (Arr& obj1, Arr& obj2);
    friend Arr operator / (Arr& obj1, Arr& obj2);

    friend bool operator < (Arr& obj1, Arr& obj2);
    friend bool operator > (Arr& obj1, Arr& obj2);
    friend bool operator == (Arr& obj1, Arr& obj2);
    friend bool operator != (Arr& obj1, Arr& obj2);
    friend bool operator <= (Arr& obj1, Arr& obj2);
    friend bool operator >= (Arr& obj1, Arr& obj2);


    friend QTextStream& operator>>(QTextStream& in, Arr& obj);
    friend QTextStream& operator<<(QTextStream& out, Arr& obj);
    friend QDataStream& operator>>(QDataStream& in, Arr& obj);
    friend QDataStream& operator<<(QDataStream& out, Arr& obj);
};

Arr operator+(Arr& obj1, Arr& obj2)
{
    if (obj1.count != obj2.count)
        throw ("bad");
    if (obj1.count == obj2.count)
        for (int i = 0; i < obj1.count; i++)
            obj2[i] += obj1[i];
    return obj2;
}

Arr operator-(Arr& obj1, Arr& obj2)
{
    if (obj1.count == obj2.count)
        for (int i = 0; i < obj1.count; i++)
            obj2[i] -= obj1[i];
    return obj2;
}

Arr operator/(Arr& obj1, Arr& obj2)
{
    if (obj1.count == obj2.count)
        for (int i = 0; i < obj1.count; i++)
        {
            if (obj1[i] == 0)
                throw "bad";
            obj2[i] /= obj1[i];
        }
    return obj2;
}

Arr operator*(Arr& obj1, Arr& obj2)
{
    if (obj1.count == obj2.count)
        for (int i = 0; i < obj1.count; i++)
            obj2[i] *= obj1[i];
    return obj2;
}

bool operator<(Arr& obj1, Arr& obj2)
{
    int count = 0;
    if (obj1.count == obj2.count)
        for (int i = 0; i < obj1.count; i++)
        {
            if (obj1[i] >= obj2[i])
                count++;
            else
                count--;
        }
    if (count >= 0)
        return false;
    else
        return true;
}

bool operator>(Arr& obj1, Arr& obj2)
{
    int count = 0;
    if (obj1.count == obj2.count)
        for (int i = 0; i < obj1.count; i++)
        {
            if (obj1[i] <= obj2[i])
                count++;
            else
                count--;
        }
    if (count >= 0)
        return false;
    else
        return true;
}

bool operator<=(Arr& obj1, Arr& obj2)
{
    int count = 0;
    if (obj1.count == obj2.count)
        for (int i = 0; i < obj1.count; i++)
        {
            if (obj1[i] > obj2[i])
                count++;
            else
                count--;
        }
    if (count >= 0)
        return false;
    else
        return true;
}

bool operator>=(Arr& obj1, Arr& obj2)
{
    int count = 0;
    if (obj1.count == obj2.count)
        for (int i = 0; i < obj1.count; i++)
        {
            if (obj1[i] < obj2[i])
                count++;
            else if (obj1[i] >= obj2[i])
                count--;
        }
    if (count >= 0)
        return false;
    else
        return true;
}

bool operator==(Arr& obj1, Arr& obj2)
{
    int count = 0;
    if (obj1.count == obj2.count)
        for (int i = 0; i < obj1.count; i++)
        {
            if (obj1[i] != obj2[i])
                count++;
            else
                count--;
        }
    if (count >= 0)
        return false;
    else
        return true;
}

bool operator!=(Arr& obj1, Arr& obj2)
{
    int count = 0;
    if (obj1.count == obj2.count)
        for (int i = 0; i < obj1.count; i++)
        {
            if (obj1[i] == obj2[i])
                count++;
            else
                count--;
        }
    if (count >= 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

QTextStream& operator>>(QTextStream& in, Arr& obj)
{
    for(int i = 0; i<obj.count;i++)
        in >> obj[i];
    return in;
}

QTextStream& operator<<(QTextStream& out, Arr& obj)
{
    for (int i = 0; i < obj.count; i++)
        out << obj[i] << " ";
    out << endl;
    return out;
}

QDataStream& operator>>(QDataStream& in, Arr& obj)
{
    for(int i = 0; i<obj.count;i++)
        in >> obj[i];
    return in;
}

QDataStream& operator<<(QDataStream& out, Arr& obj)
{
    for (int i = 0; i < obj.count; i++)
        out << obj[i];
    return out;
}

int main()
{
    //для корректной работы нужно поместить файл input.txt в папку с исполняемы м файлом
    QFile inpTxtFile ("input.txt");
    QFile outpTxtFile ("output.txt");
    QFile inpBinFile ("input.bin");
    QFile outpBinFile ("output.bin");

    inpTxtFile.open(QIODevice::ReadOnly);
    outpTxtFile.open(QIODevice::WriteOnly);
    inpBinFile.open(QIODevice::WriteOnly);
    outpBinFile.open(QIODevice::WriteOnly);

    QTextStream inpTxtStream(&inpTxtFile);
    QTextStream outpTxtStream(&outpTxtFile);
    QDataStream inpDataStream(&inpBinFile);
    QDataStream outpDataStream(&outpBinFile);

    Arr A(5);
    Arr B(5);

    inpTxtStream >> A;
    outpTxtStream << A;
    inpDataStream << A;
    outpDataStream << A;

    inpBinFile.open(QIODevice::ReadOnly);
    inpDataStream >> B;
    outpTxtStream << B;

    inpTxtFile.close();
    outpTxtFile.close();
    inpBinFile.close();
    outpBinFile.close();
    return 0;
}
