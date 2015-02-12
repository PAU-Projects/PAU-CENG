//Bu programdaki ama� ��letim sistemi �zerinde �al��an b�t�n
//prosesleri ve bunlara ait b�t�n mod�lleri yazd�rmakt�r.
//bir �nceki �rnekte kodun b�y�k  bir b�l�m�n� tek tek anlatt���m i�in
//Bu programda yorum say�s� azal�yor.
//Fonksiyonlar�n sonunda A de�eri g�r�nce �a��rmay�n bu onlar�n 8 bitlik karakter 
//sisteminde �al��t���n� g�sterir.
//GetProcessNameA �rne�inde oldu�u gibi

#include <windows.h>
#include <stdio.h>
#include <psapi.h>

#pragma comment(lib,"psapi.lib")

//Proseslerin mod�l listesini sadece konsole yazmaktansa bir txt dosyas� i�erisine yazd�raca��z.
//A�a��daki global de�i�ken dosya kontrol� i�in gereklidir.

FILE *File;
void PrintProcessInformation(DWORD ProcessID)
{
	//Proces ismi maksimum 260 karakter alabilir.
    char ProcessName[MAX_PATH] = "<------Bilinmiyor------>";

    // Proces handle de�eri al�n�yor.
	// Baz� proseslerin handle de�eri al�namaz
    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, ProcessID );

    // Prosesin handle de�eri al�n�p al�nmad��� kontrol edilir.

    if (hProcess != NULL  )
    {
		//Var olan b�t�n mod�lleri alaca��m�zdan  1024 kapasiteli bir dizi olu�turdum
		//Umal�mki 1024 den fazla mod�l olmas�n :)
        HMODULE hMod[1024]; 

		DWORD NumBytes;
		//Proses'in ilk Mod�l�n� yakala
        if ( EnumProcessModules(hProcess, 
								hMod, 
								sizeof(hMod), //1024 adet hMod oldu�unu bu paraametre ile belirtiyoruz. Bu sayede fonksiyon buldu�u b�t�n mod�lleri y�kleyecektir.
								&NumBytes) )
        {
			
			DWORD NumModule		= NumBytes/sizeof(HMODULE);
			
			//Yakalanan mod�l�n ismi al
			GetModuleBaseNameA( hProcess, hMod[0], ProcessName, 
							   sizeof(ProcessName)/sizeof(char) );
			
			printf("\n----------------------------------------------------------------------\n");
			
			//A�a��daki fonksiyonu hat�rlamad�ysan�z a��klayay�m. Ayn� printf gibi davran�r.
			//sadeece ekrana yazaca��na dosyaya yazar yaz�s�n�.
			//�lk parametre dosyay� kontrol eden de�i�kendir.
			
			fprintf(File,"\n----------------------------------------------------------------------\n");
			
			printf(ProcessName);
			fprintf(File,ProcessName);
			
			printf("\n----------------------------------------------------------------------\n");
			fprintf(File,"\n----------------------------------------------------------------------\n");
			for(int i = 1;i<NumModule; i++)
			{

				char ModuleName[MAX_PATH] = "isimsiz";
				
				//Yakalanan mod�l�n ismi al
				
				GetModuleBaseNameA( hProcess, hMod[i], ModuleName, 
								   sizeof(ModuleName)/sizeof(char) );
				printf("\n----->");
				fprintf(File,"\n----->");
				printf(ModuleName);
				fprintf(File,ModuleName);

			}

        }
    }

    CloseHandle( hProcess );

}


int main(int argc,char *argv[])
{
	DWORD	NumBytes		= 0;		
	DWORD	NumProcess		= 0;
	DWORD	ProIndexes[1024];
	
	//A�a��daki fonksiyon "ProsesModulListesi.txt" ad�ndan bir dosya olu�turup kullan�ma a�acakt�r.
	//bu dosyaya File de�i�keni ile eri�ece�iz.
	//   "..\\"  anlam� bir �nceki klas�r demektir. (daha ne kadar derine giderim bilemiyorum)
	// E�er bir tane \ kullan�rsan�z escape karakteri anlam�na gelmektedir. bu y�zden iki tane kullan�yoruz.
	// derleyici bir tane \ olarak alg�lar .
	
	File = fopen("..\\ProsesModulListesi.txt","w");
	
	
	//�ncelikle ProIndexes dizinini s�f�rl�yoruz
	ZeroMemory(ProIndexes,sizeof(ProIndexes));


	//Sistemdeki b�t�n processlerin ID de�erlerini dizinimize kaydediyoruz
	EnumProcesses(ProIndexes,	//dizinin adresi
				  1024,			//dizinin eleman say�s�
				  &NumBytes);	//Diziye y�klenen bilginin byte olarak b�y�kl���
	
	//Diziye y�klenen bilgi byte olarak gelmi� durumda
	//Her bir bilgi 4byte yani DWORD
	//B�l�m i�lemi sonucunda diziye ka� eleman y�klenmi� oldu�unu bulaca��z.

	NumProcess = NumBytes/sizeof(DWORD);  

	for(int i=0;i<NumProcess;i++)
	{
		PrintProcessInformation(ProIndexes[i]);
	}
	///dosyay� kontrol eden de�i�keni kapat�yoruz
	fclose(File);
}
//Konsolumuzun buffer k�s�tland�rmas� y�z�nden b�t�n yaz�lar� g�rememekteyiz.

