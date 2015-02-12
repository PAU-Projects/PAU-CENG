#include <iostream>
#include <windows.h>
#include <process.h>     
using namespace std;

UINT WINAPI ThreadFunction1( void * );   
UINT WINAPI ThreadFunction2( void * );  

long global = 0;
FILE *pFile;
CRITICAL_SECTION cs;
int main()
{

    cout<<"Main Fonksiyonu Ba�lad� \n";

	HANDLE hHandle[2];

	pFile = fopen("Deneme.txt","w");
	hHandle[0] = (HANDLE)_beginthreadex(0,
											0,
											ThreadFunction1,
											0,
											0,
											0);
	hHandle[1] = (HANDLE)_beginthreadex(0,
											0,
											ThreadFunction2,
											0,
											0,
											0);
	//A�a��daki fonskiyon birden fazla ipli�in beklenmesi i�in kullan�labilir
	//�lk parametre beklenecek iplik say�s�. �kinci parametre iplik handle dizisi
	//���nc� parametre beklemenin b�t�n iplikleri etkileyip etkilemiyece�i
	//Son parametre bekleme s�resi.
	WaitForMultipleObjects(2,hHandle,true,INFINITE);
	DeleteCriticalSection(&cs);
	fclose(pFile);
}

UINT  WINAPI ThreadFunction1( void *arg )
{
	InitializeCriticalSection(&cs);
	EnterCriticalSection(&cs);
	for(int i=0;i<1000;i++)
	{
		fprintf(pFile,"%s","Thread....1\n");
	}
	Sleep(50);
	//LeaveCriticalSection(&cs);
	return 0;
}
UINT  WINAPI ThreadFunction2( void *arg )
{
	EnterCriticalSection(&cs);
	for(int i=0;i<1000;i++)
	{
		fprintf(pFile,"%s","Thread....2\n");
	}
	Sleep(50);
	LeaveCriticalSection(&cs);

	return 0;
}