// lab_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <pch.h>
#include <thread>
#include <mutex>
#include <iostream>
#include <ctime>

const int massCount = 50000001;
const int threadCount = 4;
using namespace std;
double massMax;
mutex locker;

void Calculator(double *mass, int numThread, double *result)
{
	printf_s("Thread #%i started\n", numThread);
	int column = numThread - 1;
	result[column] = 0;
	for (int i = column; i < massCount; i += threadCount)
	{
		result[column] += mass[i];
		if (massMax < mass[i]) {
			locker.lock();
			if (massMax < mass[i])
			{
				massMax = mass[i];
			}

			locker.unlock();
		}
	}
	printf_s("Thread #%i stopped\n", numThread);
}

int main()
{
	double *mass = new double[massCount];
	double *massSumm = new double[threadCount];
	for (int i = 0; i < massCount; ++i)
	{
		mass[i] = (rand() % 100 + 1) / (float)(rand() % 100 + 1); 
	}
	thread *massThreads = new thread[threadCount];
	long int start = clock();
	for (int i = 0; i < threadCount; i++)
	{
		massThreads[i] = thread(Calculator, mass, i + 1, massSumm);
	}
	for (int i = 0; i < threadCount; i++)
	{
		massThreads[i].join();
	}
	double summ = 0;
	for (int i = 0; i < threadCount; i++)
	{
		summ += massSumm[i];
	}
	long int end = clock();
	printf_s("Summ %f \n", summ);
	printf_s("Max %f \n", massMax);
	printf_s("Time %f sec\n", (end - start) / (float)CLOCKS_PER_SEC);
	system("pause");
	return 0;
}
