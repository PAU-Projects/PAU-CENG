select ParcaID from TEDARIK;

select ParcaAdi, Agirlik from PARCA where Renk='kirmizi';

select ParcaAdi, Renk from PARCA where ParcaID=(select ParcaID from TEDARIK where ProjeID=(select ProjeID from PROJE where ProjeAdi='J2'));

select ParcaAdi, Renk from PARCA where ParcaID=(select ParcaID from TEDARIK where ProjeID=(select ProjeID from PROJE where Sehir='Londra'));


select count(*) from TEDARIKCI

--select TedarikciAdi from TEDARIKCI where TedarikciID=(select TedarikciId from TEDARIK where ParcaID=(select ParcaID from PARCA where Renk='K�rm�z�'))
--Parcalar tablosunda birden fazla k�rm�z� renkli parca oldu�u i�in "Joinle" yapu�lmal�

--1) P2 par�as�n� tedarik eden tedarik�i adi
--2) P5 par�as�n� tedarik eden tedarik�i ad� ve kullan�ld��� proje adlar�