#include <list>
#include <string>
#include <sstream> 
#include <stdexcept> // do out_of_range
#include <iostream>// do ostream i maina

using namespace std;

class StringList
{
	list<string> listOfStrings;

	//operatory poza klas� musz� by� zaprzyjaznione
	friend StringList operator+(const StringList& stringList,string str);
	friend StringList operator-(const StringList& stringList, string str);

	//do zadania 4
	friend ostream& operator<<(ostream& os, StringList& stringList);
	//przyda�oby si� co� co przechowa nam informacj�, kt�re slowo obecnie mamy przekazywa�
	int pozycja{ 0 };
	string getSlowo(); // metoda kt�ra bedzie zwraca�a nam odpowiednie slowo z listy

};

StringList operator+(const StringList& stringList, string str)
{
	StringList newStringList = stringList; // tworzymy nowy obiekt
	newStringList.listOfStrings.push_back(str); // twoch� d�ugie ale po prostu dodajemy napis do listy
	return newStringList;
}


StringList operator-(const StringList& stringList, string str)
{
	StringList newStringList = stringList;
	// szukamy napisu w liscie. Fukcja find zwraca nam iterator na znaleziony element
	list<string>::iterator iter = find(newStringList.listOfStrings.begin(), newStringList.listOfStrings.end(), str);
	if (iter != newStringList.listOfStrings.end()) // albo iterator za ostatni element ( end() ) je�li nic nie znajdzie
	{
		newStringList.listOfStrings.erase(iter); // usuwamy element z listy
	}
	return newStringList;
}

//zadanie 4

//implentacja naszej metody
//Metoda nieoptymalna ale w miar� �atwa i logiczna i dziala :>
string StringList::getSlowo()
{
	auto iter = listOfStrings.begin(); 
	stringstream ss(*iter);
	string wyraz;
	for (int i = 0; i < pozycja+1; i++) // petla wczytuje wyrazy az nie dojdzie do tego, kt�ry chcemy dostac
	{
		if (!(ss >> wyraz)) // wczytujemy wyraz i je�li si� nie uda przestawiamy sie na nast�pny napis
		{
			iter++; // przestawiamy

			//zadanie 5 ---------------------------------------------------

			//sprawdzamy czy wyszli�my poza zakres listy i je�li tak to rzucamy wyj�tek
			if (iter == listOfStrings.end())
			{
				pozycja = 0;
				throw out_of_range("String List Out Of Range");
				//wracamy na pocz�tek
			}
			//koniec 5 ----------------------------------------------------

			ss = stringstream(*iter); // tworzymy nowy strumien 
			i--; // zmiejszamy licznik, bo w koncu nie uda�o nam si� nic wczytac
		}
	}
	pozycja++; // przestawiamy pozycje o jeden do przodu
	return wyraz; // zwracamy nasz wyraz;

}

//operator<< zawsze zwraca ostream i jako pierwszy parametr przyjmuje ostream
ostream& operator<<(ostream& os, StringList& stringList)
{
	os << stringList.getSlowo(); //Uwaga. U�ywamy naszego "os" a nie cout !!!
	return os;
}


int main()
{
	StringList stringList;
	stringList = stringList + "Ala";
	stringList = stringList + "ma";
	stringList = stringList + "kota";
	stringList = stringList + "i";
	stringList = stringList + "psa";

	stringList = stringList - "psa";
	stringList = stringList - "psa";


	//zadanie 4 i 5
	try
	{
		cout << stringList << endl;
		cout << stringList << endl;
		cout << stringList << endl;
		cout << stringList << endl;
		cout << stringList << endl;
	}
	catch (exception& ex) // �apiemy wyj�tek :)
	{
		cout << ex.what() << endl;
	}
	cout << stringList << endl;

	return 0;
}
