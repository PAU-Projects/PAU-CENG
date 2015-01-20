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
	for(int i=0;i<1000;i++)
	{
		if(TryEnterCriticalSection(&cs))
		{
			fprintf(pFile,"%s","111111111111  Thread 111111111111\n");

			LeaveCriticalSection(&cs);
		}
		else
		{
			printf("Thread 1 Critik Alana Giremedi\n");
		}
		Sleep(5);

	}
	return 0;
}
UINT  WINAPI ThreadFunction2( void *arg )
{
	for(int i=0;i<1000;i++)
	{
		if(TryEnterCriticalSection(&cs))
		{
			fprintf(pFile,"%s","22222222222 Thread 222222222222\n");

			LeaveCriticalSection(&cs);
		}
		else
		{
			printf("Thread 2 Critik Alana Giremedi\n");
		}

		Sleep(5);

	}

	return 0;
}