#include <iostream>
#include <ctime>
#include <windows.h>

using namespace std;

double calcEntropy(int* counter)
{
	int sum = 0;

	for (int i = 0; i<6; i++)sum += counter[i];
	
	double ans = 0.5*log(2 * sum* 3.14) + sum*log(sum) - sum;
	
#pragma omp parallel for default(none) shared (counter)	reduction(-:ans)
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
	int diecesCount = 600;
	int dices[600];
	int eyeNumber[6] = { 0,0,0,0,0,0 };

	clock_t start = clock();

	int randomDice;
	int knockCount = 800;
	int usedDices = 30; //podbite kostki
	int endSum;

#pragma omp parallel for default(none) shared (dices)
	for (int i = 0; i <= diecesCount; i++) {
		dices[i] = 6;
	}

//#pragma omp parallel for default(none) private (eyeNumber) shared (dices)
	for (int n = 1; n <= knockCount; n++) {

#pragma omp parallel for default(none) private (randomDice) shared (dices) 
		for (int m = 0; m < usedDices; m++) {
			delay(1);
			randomDice = rand() % diecesCount;
			dices[randomDice] = rand() % 6 + 1;
		}

#pragma omp parallel for default(none) shared (eyeNumber) 
		for (int k = 0; k <= 5; k++) {//zerujemy kostki
			delay(1);
			eyeNumber[k] = 0;
		}

#pragma omp parallel for default(none) shared (eyeNumber)
		for (int l = 1; l <= diecesCount; l++) {
#pragma omp critical
			if (dices[l] == 1) eyeNumber[0]++;
#pragma omp critical
			if (dices[l] == 2) eyeNumber[1]++;
#pragma omp critical
			if (dices[l] == 3) eyeNumber[2]++;
#pragma omp critical
			if (dices[l] == 4) eyeNumber[3]++;
#pragma omp critical
			if (dices[l] == 5) eyeNumber[4]++;
#pragma omp critical
			if (dices[l] == 6) eyeNumber[5]++;
		}


		delay(1);
		entropy = calcEntropy(eyeNumber);
		endSum = 0;
		for (int g = 0; g < 6; g++) {
			endSum += eyeNumber[g];
		}
		
#pragma omp critical
		printf(" | etap %5d :", n);
#pragma omp critical
		printf(" 1ki: %4d", eyeNumber[0]);
#pragma omp critical
		printf(" 2ki:  %4d", eyeNumber[1]);
#pragma omp critical
		printf(" 3ki: %4d", eyeNumber[2]);
#pragma omp critical
		printf(" 4ki: %4d", eyeNumber[3]);
#pragma omp critical
		printf(" 5ki: %4d", eyeNumber[4]);
#pragma omp critical
		printf(" 6ki: %4d", eyeNumber[5]);
#pragma omp critical
		printf(" suma =%4d", endSum);
#pragma omp critical
		printf(" entropia = %5f\n", entropy);

	}

	printf("Czas wykonywania: %lu ms\n", clock() - start);

	system("pause");
	return 0;
}