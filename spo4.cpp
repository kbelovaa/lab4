// spo4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <time.h>

using namespace std;

LONG a[20];

void thread1()
{
	srand(time(NULL));
	while (true)
	{
		Sleep(1000);
		for (int i = 0; i < 20; i++)
		{
			LONG k = rand() % 300 - 150;
			InterlockedExchange(&a[i], k);
		}
		for (int i = 0; i < 20; i++)
		{
			cout << a[i] << " ";
		}
		cout << endl;
		
	}
}

void thread2()
{
	while (true)
	{
		for (int i = 0; i < 20; i++)
		{
			if (a[i] < 0)
			{
				a[i] = 0;
			}
		}
	}
}

int main()
{
	HANDLE hTh1; DWORD IDTh1;
	hTh1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread1, NULL, 0, &IDTh1);
	if (hTh1 == NULL) return GetLastError();
	
	HANDLE hTh2; DWORD IDTh2;
	hTh2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread2, NULL, 0, &IDTh2);
	if (hTh2 == NULL) return GetLastError();

	cin.get();
	TerminateThread(hTh1, 0); CloseHandle(hTh1);
	TerminateThread(hTh2, 0); CloseHandle(hTh2);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
