#include <iostream>
#include <windows.h>
#include <process.h>     // _beginthread() i�in gerekli

unsigned int WINAPI ThreadFunction( void * );   // fonksiyon prototipi
using namespace std;
int main()
{

    cout<<"Main Fonksiyonu Basladi \n";

    

	//�pli�imizi olu�turuyoruz. Fonksiyon d�n�� de�eri HANDLE t�r�nde de�ildir.
	//C++ da i�lem yapmak istiyorsak d�n���mleri yapmam�z gerekir.
	// (HANDLE) d�n�� de�erini HANDLE t�r�ne �evirmek i�indir.
	HANDLE hHandle = (HANDLE)_beginthreadex(0,
											0,
											ThreadFunction,
											"Merhaba",
											0,
											0);


	WaitForSingleObject(hHandle,INFINITE);
}

UINT  WINAPI ThreadFunction( void *arg )
{
	cout<<"iplige gonderilen deger......:"<<(char*)arg<<"\n";
	return 0;
}