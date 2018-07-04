#include <map>
#include <vector>
#include <algorithm>
#include <iostream> // do maina
#include <functional> // do wi¹zania funkcji

using namespace std;

//sortowanie z u¿yciem funktora
class Compare
{
	int num;
public:
	explicit Compare(int num) : num(num) {} // konstruktor, który okreœla po jakiej cyfrze sortujemy
	bool operator()(int a, int b) // fuktor przyjmuj¹cy dwie liczby
	{
		map<int, int> mapA; // tworzymy dwie mapy
		map<int, int> mapB;
		while (a > 0)
		{
			mapA[a % 10]++; // zapisujemy kolejne cyfry do mapy i zwiêkszamy licznik
			a /= 10; 
		}
		while (b > 0)
		{
			mapB[b % 10]++;
			b /= 10;
		}
		return mapA[num] < mapB[num]; // porownujemy odpowiednie liczniki z obu map i od razu zwracamy wynik tego porównania

	}
};

void foo6(vector<int>::iterator iter1, vector<int>::iterator iter2, int num)
{
	if (num > 9 || num < 0) throw num;
	Compare compare(num); // tworzymy obiekt
	sort(iter1, iter2, compare); // przekazujemy obiekt - funktor uruchamia siê ju¿ sam
}


//sortowanie z u¿yciem lambdy
void foo6v2(vector<int>::iterator iter1, vector<int>::iterator iter2, int num)
{
	if (num > 9 || num < 0) throw num;
	Compare compare(num);
	sort(iter1, iter2, [num](int a, int b) // w nawiasam kwadratowych mówimu do jakis zmiennych ma mieæ dostêp nasza lambda
		//w nawiasach okr¹g³ych definiujemy parametry tak jak w zwyk³ej funkcji
		//w klamrach cia³o naszej funkcji
	{
		//robi dokladnie to co funktor
		map<int, int> mapA; 
		map<int, int> mapB;
		while (a > 0)
		{
			mapA[a % 10]++; 
			a /= 10;
		}
		while (b > 0)
		{
			mapB[b % 10]++;
			b /= 10;
		}
		return mapA[num] < mapB[num];
	});
}

// sortowanie z u¿yciem funkcji wi¹zanej

bool comparator(int a, int b, int num) // fuktor przyjmuj¹cy dwie liczby
{
	map<int, int> mapA; // tworzymy dwie mapy
	map<int, int> mapB;
	while (a > 0)
	{
		mapA[a % 10]++; // zapisujemy kolejne cyfry do mapy i zwiêkszamy licznik
		a /= 10;
	}
	while (b > 0)
	{
		mapB[b % 10]++;
		b /= 10;
	}
	return mapA[num] < mapB[num]; // porownujemy odpowiednie liczniki z obu map i od razu zwracamy wynik tego porównania
}

void foo6v3(vector<int>::iterator iter1, vector<int>::iterator iter2, int num)
{
	if (num > 9 || num < 0) throw num;
	auto f = bind(comparator, placeholders::_1, placeholders::_2, num);//takie ustawianie na sztywno wartoœci wybranych
	//parametrów. np tu num jest przypisany na sta³e, wiêc z funkcji 3 argumentowej robi sie funkcja 2 argumentowa
	sort(iter1, iter2, f); // przekazujemy funkcjê do funkcji 
}



int main()
{
	//test zadanie 6 - tylko wyœwietlanie
	{
		vector<int> vec{ 1,2,3,412,342,66666666,6534,654,654,66,43,33,5,6,7,12 };
		foo6(vec.begin(), vec.end(), 6);
		for (auto x : vec)
		{
			cout << x << " ";
		}
		endl(cout);  //cout<<endl; albo cout<<"\n";

		foo6v2(vec.begin(), vec.end(), 6);
		for (auto x : vec)
		{
			cout << x << " ";
		}
		endl(cout);

		foo6v3(vec.begin(), vec.end(), 6);
		for (auto x : vec)
		{
			cout << x << " ";
		}
		endl(cout);
	}

	return 0;
}

