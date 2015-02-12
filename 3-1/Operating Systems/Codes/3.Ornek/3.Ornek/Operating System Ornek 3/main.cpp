// Bu programdaki ama� i�letim sisteminde �al��an b�t�n processlerin
// isimlerini ekrana yazd�rmakt�r.Bu i�lem i�in EnuProcess API fonksiyonu kullan�lmaktad�r.
// Fonksiyon sistem �zerinde �al��an b�t�n proseslerin ID de�erlerini yakalayabilir.

#include <windows.h>
#include <stdio.h>
//EnumProcess fonksiyonu psapi.h k�t�phanesi i�erisinde tan�mlanm��t�r.

#include <psapi.h>

//A�a��daki komut sat�r� kodumuzu psapi.lib adl� statik k�t�phaneye ba�lamam�z� sa�lar.
//Statik k�t�phaneler yolu ile psapi.dll dosyas�n� kullanabiliyoruz.
//EnumProcess fonksiyonun g�vdesi b�t�n API fonksiyonlar�nda oldu�u gibi bir DLL dosyas�
//i�indedir. Bu y�zden psapi.dll dosyas� i�erisine ba�lanmak �artt�r.

#pragma comment(lib,"psapi.lib")

//A�a��daki fonksiyon ID si verilen prosesin ismini yazd�r�r.
void ProsesBilgileriniYazdir(DWORD ProcessID)
{
	//Proces ismi maksimum 260 karakter alabilir. MAX_PATH in kar��l��� 260 d�r.
   
	char	ProcessName[MAX_PATH] = "<------Bilinmiyor------>";

    //A�a��daki fonksiyon ID si bilinen procesin handle de�erini d�nd�r�r
	//Ve bunu kendi prosesimizin handle tablosuna kopyalar. Bu sayede art�k
	//di�er prosesin kernel nesnesini kullanabilece�iz. Fonksiyon d�n��
	//de�eri olarak proses �ekirdek nesnesinin handle de�erini d�nd�r�r.
	//�unu unutmamak gerek d�nd�r�len handle de�eri ID si verilen prosesin
	//�ekirdek nesnesine eri�ilebilecek �ekilde ayarlan�r.
    
	HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, ProcessID );

    // Prosesin handle de�erinin al�n�p al�nmad��� kontrol edilir.
	// E�er NULL ise prosesin handle deperi al�namam��t�r.
	// Bunun sebebi prosesin g�venlik ayarlar� olabilir.
    
	if (hProcess != NULL  )
    {
		//Prosesin Mod�llerini yakalamaya geldi s�ra. 
		//Mod�lden kas�t prosesin kulland��� DLL ve kendi exe dosyas�d�r.
		//Zaten mod�l listesinin ilk s�ras�nda prosesin exe dosyas� bulunmakatad�r.
        //�lk olarak mod�l t�r�nde bir de�i�ken olu�turuyoruz.
		//Bir tane mod�l y�klenece�inden hMod[1024] gibi bir dizi tan�mlamad�k.
		HMODULE hMod;
        
		//DWORD long tipinde bir de�i�kendir.Kafan�z kar��mas�n
		
		DWORD cbNeeded;
		
		//A�a��daki fonksiyon prosesin mod�llerini yakalamak i�in kullan�l�r.
		//Fonksiyon if blo�u i�ine al�nm��t�r. Yani e�er fonksiyon false d�nd�r�r ise 
		//isim alma i�lemi ba�ar�lamayacakt�r.
        if ( EnumProcessModules( hProcess,		//Prosesin handle de�eri
								&hMod,			//Mod�l� tutacak de�i�kenin adresi
								sizeof(hMod),	//y�klenecek mod�l�n boyutu. Mod�llerin sadece bir tanesi y�klenecektir.
								&cbNeeded) )	//Fonksiyonun y�kledi�i toplam byte de�eri
        {
			//Yakalanan mod�l�n ismi al
            GetModuleBaseNameA( hProcess,		//Prosesin handle de�eri	
								hMod,			//�smi al�nacak mod�l
								ProcessName,	//�smin y�klenece�i de�i�kenin ad�
								260 );			//ProcessName de�i�keninin eleman say�s�. 260 karakter olarak belirlemi�tik.
        }
    }
	
	//E�er isim <------Bilinmiyor------> ise yazd�rm�yoruz
	//Bunun anlam� mod�l ismi almay� ba�aramam�z demektir.
	if(strcmp(ProcessName,"<------Bilinmiyor------>")!=0)
	{
		printf(ProcessName);
		printf("\n");
	}
	
	//Proses le i�imiz bitti�inde ona ait handle de�erini kapatmal�y�z.
	//Biliyoruzki prosesin �ekirdek nesnesini  handle de�eri sayesinde kulland�k.
	//Bu handle de�eri �uan kodunu yazd���m�z prosesin handle tablosuna eklenmi�tir.
	//E�er bu handle de�erini silmezsek �ekirdek nesnesini hala kullan�yoruz anlam�na gelmektedir.
	// bu y�zden �ekirdek nesnesinin as�l sahibi proses kapansa dahi sistem nesneyi bizim
	// hala kulland���m�z� d���nerek nesneyi kald�rmayacakt�r.
    CloseHandle( hProcess );

}

//DWORD microsft'un long de�i�keni i�in kulland��� isimdir. �a��rmay�n
//B�y�k bir say� de�i�kenidir.

int main(int argc,char *argv[])
{
	DWORD	NumBytes		= 0;//fonksiyonun diziye aktard��� toplam byte de�eri		
	DWORD	NumProcess		= 0;//Proses say�s�n� tutacak olan de�i�ken
	DWORD	ProIndexes[1024];	//Proses indexlerini tutacak olan dizi

	//�ncelikle ProIndexes dizisini s�f�rl�yoruz
	
	ZeroMemory(ProIndexes,sizeof(ProIndexes));


	//Sistemdeki b�t�n processlerin ID de�erlerini dizimize kaydediyoruz
	
	EnumProcesses(ProIndexes,	//dizinin adresi
				  1024,			//dizinin eleman say�s�
				  &NumBytes);	//Diziye y�klenen bilginin byte olarak b�y�kl���
	
	//Diziye y�klenen toplam byte say�s�n� NumBytes De�i�keninden alabiliriz.
	//Her bir proses ID si 4byte d�r. DWORD 4 byte d�r. 
	//E�er NumBytes kadar de�er y�klenmi� ise NumBytes/4 bize proses say�s�n� verir


	NumProcess = NumBytes/sizeof(DWORD);  

	for(int i=0;i<NumProcess;i++)
	{
		//Her bir proses i�in bilgi yazd�ran fonksiyonu �a��r�yoruz.
		ProsesBilgileriniYazdir(ProIndexes[i]);
	}
}
