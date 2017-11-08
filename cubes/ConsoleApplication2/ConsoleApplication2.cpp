// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <omp.h>


void delay(int miliseconds);
using namespace std;

int main()
{
	int czas = clock();
	double entropia = 0.00;
	srand(time(NULL));
	int kostka[600];
	int oczkaKostki[6] = { 0,0,0,0,0,0 };
	int losowanieKostki = 0;
	int losowanieOczka = 0;
	int liczbaKostek = 600;
	int i, j;


	cout << "Start programu..." << endl;



	for (int i = 0; i < liczbaKostek; i++) kostka[i] = 6;

	for (int i = 0; i < 100; i++) {
		cout << "\n\Proba " << i + 1 << " : ";

		for (int i = 0; i < liczbaKostek; i++)
		{
			losowanieKostki = rand() % 20;			// prawdopodobienstwo przewrocenia kostki - losowanie kostek
			if (losowanieKostki == 1)
			{
				losowanieOczka = rand() % 6 + 1;	// losowanie oczek
				kostka[i] = losowanieOczka;
			}
		}


		// liczenie kostki z dana liczba oczek

		for (int j = 0; j < 6; j++)
		{
			oczkaKostki[j] = 0;
			delay(3);
		}


		for (int i = 0; i < liczbaKostek; i++) {
			for (int j = 1; j < 7; j++)
			{

				if (kostka[i] == j)
					oczkaKostki[j - 1]++;
			}
		}



		for (int j = 0; j < 6; j++)
		{
			printf("  %5d  ", oczkaKostki[j]);
			//cout << "Ilosc " << j + 1 << ": " << oczkaKostki[j] << " | ";
			//cout << oczkaKostki[j] << "   ";
		}
		entropia = log(liczbaKostek) * (liczbaKostek + 1.0 / 2.0) - liczbaKostek + ((log(2) + log(3.1415)) / 2);



		for (int j = 0; j < 6; j++) {
			if (oczkaKostki[j] > 2) {
				entropia -= log(oczkaKostki[j]) * (oczkaKostki[j] + 1.0 / 2) + ((log(2) + log(3.1415)) / 2) - oczkaKostki[j];
			}
		}
		cout << " | Entropia: " << entropia;
	}


	cout << "\n\nCzas trwania obliczen: " << clock() - czas << "ms" << endl;
	system("pause");

	return 0;
}


void delay(int miliseconds) {
	clock_t endwait;
	endwait = clock() + miliseconds * (CLOCKS_PER_SEC / 1000);
	while (clock() < endwait) {}
}