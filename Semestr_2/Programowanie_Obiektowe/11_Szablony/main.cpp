#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

//zadanie 1
template<typename T>
T& foo(T* begin, T* end)
{
    T* min = begin;
    for(T* i = begin;i <=end;i++)
    {
        if(*i < *min) min = i;
    }
    return *min;
}

//zadanie 2
template<>
string& foo<string>(string* begin, string* end)
{
    string* min = begin;
    for(string* i = begin; i <= end;++i)
    {
        if(lexicographical_compare(i->begin(),i->end(),min->begin(),min->end(),[](char a, char b)->bool{
                return tolower(a) < tolower(b);
        }))
        {
            min = i;
        }
    }
    return *min;
}

//zadanie 3
//nice :>
template <template<typename ...> class C, typename T>
T& foo3(C<T>& con)
{
    T &min = *con.begin();
    for(auto i = con.begin();i!=con.end();++i)
    {
        if(*i < min) min = *i;
    }
    return min;
}

//zadanie 4

template <typename T, int size>
class Klasa
{
    T tab[size];
public:
    int getSize(){return size;}
    T& operator[](int index);
    const T& operator[](int index) const;
    //zadanie 5
    template<typename R>
    void Add(const R& a)
    {
        for(int i = 0; i<size;i++)
            tab[i] += a;
    }
};

template <typename T, int size>
T& Klasa<T,size>::operator[](int index)
{
    return tab[index];
}

template <typename T, int size>
const T& Klasa<T,size>::operator[](int index) const
{
    return tab[index];
}




int main()
{
    //test zadanie 1
    int* tab = new int [5]{1,2,3,4,5};
    double * t = new double[3]{1.2,4.5,3.3};
    double x = foo<int>(tab+2,tab+4);
    cout<<x<<endl;

    delete[] tab;
    delete[] t;

    //test zadanie 2
    string * s = new string[4]{"Bla","AAabc","kota","AAaAAaaaaaaaaaaaaaaa"};

    cout<<foo<string>(s,s+3)<<endl;

    delete[] s;

    //test zadanie 3

    vector<int> vec{2,3,5,7,2,4,7,89};
    cout<<foo3<vector,int>(vec)<<endl;

    //test zadanie 4
    Klasa<int,3> klasa;
    klasa[0] = 1;
    klasa[1] = 2;
    klasa[2] = 45;
    cout<<klasa[2]<<endl;

    //test zadanie 5
    klasa.Add(3);
    cout<<klasa[2]<<endl;



    return 0;
}

