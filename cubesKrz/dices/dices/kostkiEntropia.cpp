#include <iostream>
#include <ctime>
#include <windows.h>

using namespace std;

double calcEntropy(int* counter)
{
	int sum = 0;

#pragma omp parallel for default(none) shared (counter)	
	for (int i = 0; i<6; i++)sum += counter[i];
	
	double ans = 0.5*log(2 * sum* 3.14) + sum*log(sum) - sum;
	

	for (int i = 0; i<6; i++)
	{
		if (0 == counter[i]) continue;
		ans -= (0.5*log(2 * counter[i] * 3.14) + counter[i] * log(counter[i]) - counter[i]);
	}
	return ans;
}

void delay(int miliseconds) {
	clock_t endwait;
	endwait = clock() + miliseconds * (CLOCKS_PER_SEC / 1000);
	while (clock() < endwait) {}
}

int main()
{
	double entropy;
	int dices[600];
	int eyeNumber[6] = { 0,0,0,0,0,0 };

	clock_t start = clock();

	int randomDice;
	int knockCount = 1000;
	int usedDices = 30; //podbite kostki

#pragma omp parallel for default(none) shared (dices)
	for (int i = 0; i < 600; i++) {
		dices[i] = 6;
	}

	for (int n = 1; n <= knockCount; n++) {

#pragma omp parallel for default(none) shared (dices) 
		for (int m = 0; m < usedDices; m++) {
			delay(1);
			randomDice = rand() % 600;
			dices[randomDice] = rand() % 6 + 1;
		}

#pragma omp parallel for default(none) shared (eyeNumber) 
		for (int k = 0; k <= 5; k++) {//zerujemy kostki
			delay(1);
			eyeNumber[k] = 0;
		}

#pragma omp parallel for default(none) shared (dices) 
		for (int l = 1; l <= 600; l++) {
			switch (dices[l]) {
			case  1:
				eyeNumber[0]++; break;
			case  2:
				eyeNumber[1]++; break;
			case  3:
				eyeNumber[2]++; break;
			case  4:
				eyeNumber[3]++; break;
			case  5:
				eyeNumber[4]++; break;
			case  6:
				eyeNumber[5]++; break;
			}
		}


		delay(1);
		entropy = calcEntropy(eyeNumber);
		printf("etap %5d :", n);
		printf("%5d", eyeNumber[0]);
		printf("%5d", eyeNumber[1]);
		printf("%5d", eyeNumber[2]);
		printf("%5d", eyeNumber[3]);
		printf("%5d", eyeNumber[4]);
		printf("%5d", eyeNumber[5]);

		printf("  entropia = %5f\n", entropy);

	}

	printf("Czas wykonywania: %lu ms\n", clock() - start);

	system("pause");
	return 0;
}