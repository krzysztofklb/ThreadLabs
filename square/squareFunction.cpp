// helloWorld.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;
int main()

{
	//Deklarujemy zmienne
	float a;
	float b;
	float c;
	float d;
	//Podajemy zmienne
	cout << "Podaj A" << endl;
	cin >> a;
	cout << "Podaj B" << endl;
	cin >> b;
	cout << "Podaj C" << endl;
	cin >> c;

	d = b*b - 4 * a*c;

	if (d>0)
	{
		cout << "x1=" << (-b - sqrt(d)) / 2 * a << endl;
		cout << "x2=" << (-b + sqrt(d)) / 2 * a << endl;
	}

	if (d == 0)
	{
		cout << "x=" << -b / 2 * a << endl;
	}

	if (d<0)
	{
		cout << "Brak Pierwiastków!" << endl;
	}
	system("PAUSE");
	return 0;
}
