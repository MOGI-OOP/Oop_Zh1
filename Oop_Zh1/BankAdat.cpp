#include "BankAdat.h"
#include "..\..\MenuTest\MenuTest\_InputUtils.h"
#include <conio.h>
#include <stdio.h>


CBankAdat::CBankAdat()
{
	m_pAdatRecords = nullptr;
	InitData();

}


CBankAdat::~CBankAdat()
{
	InitData();
}


void CBankAdat::InitData()
{
	if (m_pAdatRecords) delete[]m_pAdatRecords;
	m_pAdatRecords = nullptr;
	m_nRecords = 0;
}


int CBankAdat::ReadDataFile(char *pFileName)
{
	FILE* fp;
	char *pChar, pLine[512], pField[256];
	int result, id, nOk=0;
	BANK_RECORD bRec;

	InitData();
	if (FileExists(pFileName) == 0) {
		throw CBankException(0);
		return -1;
	}
	fopen_s(&fp, pFileName, "r");
	if (fp == NULL) {
		throw CBankException(1);
		return -2;
	}

	do {
		result = 0;
		pChar = fgets(pLine, 512, fp);
		pLine[511] = 0;						// biztos ami biztos!
		if (pChar != nullptr) {
			memset(&bRec, 0, sizeof(bRec));
			result = GetStringFieldInt(pLine, 0, 0x09, &id);
			if (result == 0) result = GetStringField(pLine, 1, bRec.szamlaSzam, 32, 0x09);
			if (result == 0) result = GetStringField(pLine, 2, bRec.devizaNem, 8, 0x09);
			if (result == 0) result = GetStringField(pLine, 3, bRec.ertekNap, 16, 0x09);
			if (result == 0) result = GetStringField(pLine, 4, bRec.tranzTip, 32, 0x09);
			if (result == 0) result = GetStringField(pLine, 5, bRec.PartnerNeve, 128, 0x09);
			if (result == 0) result = GetStringField(pLine, 6, bRec.PartnerSzamlaszama, 32, 0x09);
			if (result == 0) result = GetStringFieldDouble(pLine, 7, 0x09, &bRec.osszeg);
			if (result == 0) result = GetStringField(pLine, 8, bRec.kozlemeny, 256, 0x09);
			if (result == 0) result = GetStringFieldInt(pLine, 9, 0x09, &bRec.besorolas);
			if (result == 0) {
				AddData(&bRec);
				nOk++;
			}
			else {
				//printf_s(pLine);
				//result = _getch();
			}
		}
	} while (pChar != nullptr);

	return 0;
}


int CBankAdat::AddData(BANK_RECORD *pRec)
{
	BANK_RECORD* pTempData;
	int i;

	if (m_nRecords < 1) {		// elsö adat
		m_pAdatRecords = new BANK_RECORD[1];
		if (m_pAdatRecords == nullptr) return -1;	// hiba
		m_pAdatRecords[0] = *pRec;
		m_nRecords = 1;
		return 0;
	}
	// további adatok
	pTempData = new BANK_RECORD[m_nRecords];
	if (pTempData == nullptr) return -1;
	for (i = 0; i < m_nRecords; i++) pTempData[i] = m_pAdatRecords[i];
	delete[] m_pAdatRecords;
	m_pAdatRecords = new BANK_RECORD[m_nRecords + 1];
	if (m_pAdatRecords == nullptr) return -1;
	for (i = 0; i < m_nRecords; i++) m_pAdatRecords[i] = pTempData[i];
	m_pAdatRecords[m_nRecords] = *pRec;
	m_nRecords++;
	delete[] pTempData;
}


double	CBankAdat::PartnerSum(char* pFN, int fileOut)
{
	int i;
	double sum = 0.0;

	for (i = 0; i < m_nRecords; i++) {
		if (strstr(m_pAdatRecords[i].PartnerNeve, pFN)) sum = sum + m_pAdatRecords[i].osszeg;
	}
	return sum;
}


double	CBankAdat::BesorolSum(int besr, int fileOut)
{
	int i;
	double sum = 0.0;

	for (i = 0; i < m_nRecords; i++) {
		if (m_pAdatRecords[i].besorolas == besr) sum = sum + m_pAdatRecords[i].osszeg;
	}
	return sum;
}

