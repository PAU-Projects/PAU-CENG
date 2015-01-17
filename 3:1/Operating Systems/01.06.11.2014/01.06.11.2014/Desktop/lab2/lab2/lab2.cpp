// lab2.cpp : Defines the entry point for the console application.
#include "stdafx.h"
//CreateProsess fonksiyonun ilk parametresini bo� girmek yerine
//direkt olarak �al��t�r�lacak program�n ad�n� yazmay� deneyin
//Yolu do�ru yazmay� unutmay�n
#include <windows.h>
#include <stdio.h>
//main fonksiyonun ilk parametresi ikinci parametrenin ka� adet eleman� oldu�unu belirtir.
//�kinci parametre bir string dizisidir. C dilinde karakter dizileri "char *" �eklinde tan�mlan�r.
int main(int argc,char *argv[])
{
	//argv[0]  bu prosesin tam yolunu bar�nd�racakt�r.
	//Bu i�letim sistemi taraf�ndan girilir.
	//argv de�eri Command Line Arguments ad� ile an�l�r
	//Olu�turulacak prosesin ba�lang�� bilgilerini belirleyen
	//struct yani yap�d�r. fonksiyonu olmayan s�n�f gibi d���n�lebilir.
	//as�l ismi STARTUPINFO dur. fakat bu yap� 16bit karakter d�zenine g�re tasarlanm��t�r.
	//Bu y�zden bir 8-bit lik karakter d�zenine g�re tasarlanm�� olan STARTUPINFOA ile 
	//�al��aca��z.

	printf("Process'in tam yolu: %s\n\n\n", argv[0]);
	printf("Maine gelen dizinin 1. indexi: %s\n\n\n", argv[1]);
	STARTUPINFOA si;
	 
	//Olu�turulan prosesin daha sonradan kontrol edilebilmesi i�in gereken
	//bilgiler ile doldurulur. CreateProsess e�er do�ru d�nerse bu parametrenin
	//i�erisini de gerekli bilgiler ile dolduracakt�r.
	PROCESS_INFORMATION pi;

	//C dilinde bir de�i�ken olu�turuldu�unda ilk de�er olarak atand��� haf�za alan�nda 
	//ne varsa onu al�r. Bu sa�ma sapan bir de�er olabilir. Bu y�zden kullanmadan �nce
	//haf�za alan�n� s�f�rlamal�y�z. A�a��daki fonksiyon bu i�i g�r�r.
	// & i�areti si de�i�keni ile beraber kullan�ld���nda adres belirtir. si de�i�keninin
	//adresini ikinci parametre de ise si de�i�keninin haf�zada kaplad��� alan girilmi�tir.
	printf("Si'nin size		: %i\n" ,sizeof(si));
	printf("Pi'nin size		: %i\n\n", sizeof(pi));
	ZeroMemory( &si, sizeof(si) );
    //si yap�s�n�n ilk parametresi yap�n�n kendi boyutunu bekler.
	//sizeof fonksiyonu yap�lar�n haf�zada ne kadar yer kaplad���n� belirler.
	
	si.cb = sizeof(si);
    
	//�imdide ikinci yap�n�n adres alan�n� s�f�rl�yoruz
	ZeroMemory( &pi, sizeof(pi) );
	//argc 2 den k���k ise prosesimiz �zerine ba�ka bir proses s�r�klenmemi� demektir.
	//Yani proses klasik y�ntemle �zerine �ift t�klanarak �al��t�r�lm��t�r.
	//Bir program�n �st�ne �ift t�klanarak �al��t�r�ld���nda argc 1 olacakt�r.
    if( argc <2 )
    {
        printf("Girilen Tek Parametre: %s \n", argv[0]);
        return 0;
    }
	//Fonskyionun asl� CreateProsess dir. Fakat biz 8-bit karakterler
	//kulland���m�zdan dolay� CreateProsessA versiyonu kullan�yoruz.
	//�ki fonksiyon aras�ndaki tek fark karakter sistemidir.

    if( !CreateProcessA( NULL,  // �al��t�r�lacak program�n ad�
        argv[1],				// Command line arguments
        NULL,					// Process handle kal�t�msal de�il
        NULL,					// Thread handle kal�t�msal de�il
        FALSE,					// Process in kernel objeleri kal�t�msal de�il
		CREATE_NEW_CONSOLE,					// Olu�turulma bayra�� yok
        NULL,					// Ana processin �evre de�i�kenlerini kullan
        NULL,					// Ana processin klas�r�n� varsay�lan klas�r olarak kullan
        &si,					// STARTUPINFO yap�s�na adresi
        &pi )					// PROCESS_INFORMATION yap�s�na adresi
    ) 
    
	{
        printf( "CreateProcess Hatali(%d).\n", GetLastError() );
        return 0;
    }

	//a�a��daki fonksiyon prosesimizi istenen olay ger�ekle�ene kadar 
	//beklemeye alacakt�r. A�a��daki istenen olay ise
	//olu�turulan �ocuk prosesin bitmesini beklemekitir.
	//ilk parametresi olu�turdu�umuz prosesin handle de�eridir.
	//�kinci parametre ise bekleme durumunu belirtmektedir.
	//INFINITE de�eri proses bitene kadar beklememizz gerekti�ini s�ylemektedir.
   
	WaitForSingleObject( pi.hProcess, INFINITE );
	
	
	
	printf("Sonunda Process bitti");
    Sleep(10000);
	
	// �ocuk process in handle lar�n� sonland�r. 
	//Bu sayede �ocuk proses ve ona ait threading kernel nesnelerinin sayac� 1 azalt�lacakt�r.
	//��nk� bu proses art�k onlar� kullanmad���n� belirtti
	CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );

	scanf("%i", &argc);
}