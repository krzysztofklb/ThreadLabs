#include <conio.h>
#include <iostream>
#include <omp.h> 

using namespace std;

int main() {

	int lproc, nr_watku=0, irob;


	lproc = omp_get_num_procs();

	cout << "liczba procesorow: " << lproc << endl;
	irob = omp_get_max_threads();
	cout << "maksymalna liczba watkow: " << irob << endl;
	irob = omp_get_nested();
	cout << "zagniezdzenie watkow: " << irob << endl;
	omp_set_nested(2);
	irob = omp_get_nested();
	cout << "zlecone zagniezdzenie watkow: " << irob << endl;

	irob = omp_get_dynamic();
	cout << "dynamiczne przydzialy: " << irob << endl;
	//omp_set_dynamic(18);

	irob = omp_get_dynamic();
	cout << "zlecone dynamiczne przydzialy: " << irob << endl;

	omp_set_num_threads(16);
	irob = omp_get_max_threads();
	cout << "zlecone max threads: " << irob << endl;

#pragma omp parallel private(nr_watku) num_threads(17)
	{
		nr_watku = omp_get_thread_num();
#pragma omp critical
		{
			cout << "numer watku:" << nr_watku << endl;

		};
#pragma omp barrier
#pragma omp single
//#pragma omp master
		{
			irob = omp_get_num_threads();
			cout << "liczba watkow: " << irob << endl;
			nr_watku = omp_get_thread_num();
			printf("wiadomosc od watku: %d \n", nr_watku);
		};
	};

	cout << "nacisnij klawisz ...";
	_getch();
	return 0;
}
