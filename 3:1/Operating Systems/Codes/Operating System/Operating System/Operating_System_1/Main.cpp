
#include <windows.h>
#include <stdio.h>

//main fonksiyonun ilk parametresi ikinci parametrenin ka� adet eleman� oldu�unu belirtir.
//�kinci parametre bir string dizisidir. C dilinde karakter dizileri "char *" �eklinde tan�mlan�r.
//
int main(int argc, char *argv[])
{
	for(int i=0;i<60;i++)
	{
		printf("%i....Merhaba \n",i);
		Sleep(100);//Prosesin ana threadini 100 milisaniye bekleme moduna al�r
	}
}