#pragma once

#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <algorithm>
struct student
{
    QString name;
    int group;

    student() : name(""), group(0) {}
    student(const student& X) : name(X.name), group(X.group) {}

    friend bool operator< (const student& A, const student&  B)
    {
        if(A.name == B.name)
        {
            return A.group < B.group;
        }
        return A.name < B.name;
    }
    friend bool operator> (const student& A, const student&  B)
    {
        if(A.name == B.name)
        {
            return A.group > B.group;
        }
        return A.name > B.name;
    }
    friend bool operator== (const student& A, const student&  B)
    {
        return (A.name == B.name) && (A.group == B.group);
    }
    friend bool operator!= (const student& A, const student&  B)
    {
        return !(A == B);
    }

    friend QTextStream& operator>> (QTextStream& in, student& obj)
    {
        in >> obj.name >> obj.group;
        return in;
    }
    friend QTextStream& operator<< (QTextStream& out, const student& obj)
    {
        out << obj.name << " " << obj.group << Qt::endl;
        return out;
    }
    friend QDataStream& operator>> (QDataStream& in, student& obj)
    {
        in >> obj.name >> obj.group;
        return in;
    }
    friend QDataStream& operator<< (QDataStream& out, const student& obj)
    {
        out << obj.name << obj.group;
        return out;
    }
};

template <typename T>
class mset
{
    T* a;
    int n;
public:

    mset() : a(nullptr), n(0) {}
    ~mset()
    {
        delete[] a;
    }
    mset(int n_)
    {
        a = new T[n_];
        this->n = n_;
    }
    mset(const mset<T>& x)
    {
        n = x.n;
        a = new T[n];
        for (int i = 0; i < n; i++)
            this->a[i] = x.a[i];
    }
    mset(mset<T>&& other) : a(other.a), n(other.n)
    {
        other.a = nullptr;
        other.n = 0;
    }

    mset<T>& operator=(const mset<T>& x)
    {
        if (this != &x)
        {
            delete[] a;

            n = x.n;
            a = new T[n];
            for (int i = 0; i < n; i++)
            {
                a[i] = x.a[i];
            }
        }
        return *this;
    }
    mset<T>& operator=(mset<T>&& x)
    {
        if (this != &x)
        {
            delete[] a;
            a = x.a;
            n = x.n;
            x.a = nullptr;
            x.n = 0;
        }
        return *this;
    }

    T& operator[](int i) const
    {
        return a[i];
    }

    int size() const
    {
        return n;
    }

    friend mset<T> operator+(const mset<T>& x, const mset<T>& y)
    {
        int i = 0, j = 0, k = 0;
        mset<T> z(x.n + y.n);
        while(i < x.n && j < y.n)
        {
            if(x.a[i] < y.a[j])
                z.a[k++] = x.a[i++];
            else if(x.a[i] > y.a[j])
            {
                z.a[k++] = y.a[j++];
            }
            else
            {
                z.a[k++] = y.a[j++];
                i++;
            }
        }
        while(i < x.n)
        {
            z.a[k++] = x.a[i++];
        }
        while(j < y.n)
        {
            z.a[k++] = y.a[j++];
        }
        z.n = k;
        return z;
    }
    friend mset<T> operator^(const mset<T>& x, const mset<T>& y)
    {
        int i = 0, j = 0, k = 0;
        mset<T> z(x.n + y.n);
        while(i < x.n && j < y.n)
        {
            if(x.a[i] < y.a[j])
            {
                i++;
            }
            else if(x.a[i] > y.a[j])
            {
                j++;
            }
            else
            {
                z.a[k++] = x.a[i++];
                j++;
            }
        }
        z.n = k;
        return z;
    }
    friend mset<T> operator|(const mset<T>& x, const mset<T>& y)
    {
        int i = 0, j = 0, k = 0;
        mset<T> z(x.n + y.n);
        while(i < x.n && j < y.n)
        {
            if(x.a[i] < y.a[j])
                z.a[k++] = x.a[i++];
            else if(x.a[i] > y.a[j])
            {
                z.a[k++] = y.a[j++];
            }
            else
            {
                i++;
                j++;
            }
        }
        while(i < x.n)
        {
            z.a[k++] = x.a[i++];
        }
        while(j < y.n)
        {
            z.a[k++] = y.a[j++];
        }
        z.n = k;
        return z;
    }
    friend mset<T> operator-(const mset<T>& x, const mset<T>& y)
    {
        int i = 0, j = 0, k = 0;
        mset<T> z(x.n);
        while(i < x.n && j < y.n)
        {
            if(x.a[i] < y.a[j])
                z.a[k++] = x.a[i++];
            else if(x.a[i] > y.a[j])
            {
                j++;
            }
            else
            {
                i++;
                j++;
            }
        }
        while(i < x.n)
        {
            z.a[k++] = x.a[i++];
        }
        z.n = k;
        return z;
    }

    friend QTextStream & operator>>(QTextStream& in, mset<T>& x)
    {
        in >> x.n;
        x.a = new T[x.n];
        for(int i = 0; i < x.n; i++)
        {
            in >> x.a[i];
        }
        std::sort(x.a, x.a + x.n, [](const T& a, const T& b) { return a < b; });
        return in;
    }
    friend QTextStream & operator<<(QTextStream& out, const mset<T>& x)
    {
        out << x.n << Qt::endl;
        for(int i = 0; i < x.n; i++)
        {
            out << x.a[i] << " ";
        }
        out << Qt::endl;
        return out;
    }
    friend QDataStream & operator>>(QDataStream& in, mset<T>& x)
    {
        in >> x.n;
        x.a = new T[x.n];
        for(int i = 0; i < x.n; i++)
        {
            in >> x.a[i];
        }
        //сортировка для выполнения операций
        std::sort(x.a, x.a + x.n);
        return in;
    }
    friend QDataStream & operator<<(QDataStream& out, const mset<T>& x)
    {
        out << x.n;
        for(int i = 0; i < x.n; i++)
        {
            out << x.a[i];
        }
        return out;
    }

};
