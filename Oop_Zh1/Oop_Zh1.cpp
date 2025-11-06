// Oop_Zh1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdexcept>
#include "..\..\MenuTest\MenuTest\_ProgramMenu.h"
#include "..\..\MenuTest\MenuTest\_InputUtils.h"

#include "BankAdat.h"

using namespace std;

CProgramMenu mainMenu;
CBankAdat bankAdatok;


void AdatTorles()
{
	system("cls");
	bankAdatok.InitData();
	printf("\n\nAdatok torolve...\n\n");
	int ch = _getch();
}

void ReadFile()
{
	char pFN[256];
	int result, chw;

	// a konzol törlése, menü kiírása
	system("cls");
	printf("\n\Bank fájl megadása\n\n");
	printf("Írja be a fájl nevét: ");
	result = InputStr(pFN, 256);
	if (result == 0) strcpy_s(pFN, 256, "c:\\t\\unicredit.txt");
	result = bankAdatok.ReadDataFile(pFN);
	if (result < 0) {
		printf("\nHiba a fájl megadásakor!\n");
	}
	else printf("\n%d tranzakció beolvasva!\n", bankAdatok.NumRecords());

	chw = _getch();
}


void Partner()
{
	char pFN[256];
	int result, chw;
	double sum = 0.0;

	// a konzol törlése, menü kiírása
	system("cls");
	printf("\n\Bank fájl megadása\n\n");
	printf("Írja be a partner nevét: ");
	result = InputStr(pFN, 256);
	if (result) {
		sum = bankAdatok.PartnerSum(pFN, 1);
		printf("\nA tranzakciók összege: %.2lf\n", sum);
	}

	chw = _getch();
}

void Besorolas()
{
	int result, chw, bn;
	double sum = 0.0;

	// a konzol törlése, menü kiírása
	system("cls");
	printf("\n\Besorolas megadása\n\n");
	printf("Írja be a besorolast: ");
	result = InputInt(&bn);
	if (result) {
		sum = bankAdatok.BesorolSum(bn, 1);
		printf("\nA tranzakciók összege: %.2lf\n", sum);
	}

	chw = _getch();
}

int main()
{
	int result, menuSelected = -1;

	mainMenu.AddTitle("Program menü");
	mainMenu.AddMenuItem("Adat törlés");
	mainMenu.AddMenuItem("Adat beolvasás");
	mainMenu.AddMenuItem("Partner tranzakciók");
	mainMenu.AddMenuItem("Besorolás");
	mainMenu.AddMenuItem("Kilépés", 0);
	do {
		SetColor(14, 1);
		menuSelected = mainMenu.ShowMenu();
		switch (menuSelected) {
		case 1: AdatTorles();
			break;
		case 2: ReadFile();
			break;
		case 3: Partner();
			break;
		case 4: Besorolas();
			break;

			//case 5: system("cls");
			//	printf("\n\nString bevitel\n\n");
			//	printf("Írjon be egy stringet: ");
			//	result = InputStr(str, 32);
			//	if (result > 0) printf("\nA beírt string: %s\n", str);
			//	else printf("\nNem sikerült a beolvasás!\n");
			//	ch = _getch();
			//	break;
		}

	} while (menuSelected != 0);

	system("cls");

}

