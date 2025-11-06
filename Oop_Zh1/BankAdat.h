#pragma once

#include <stdexcept>
using namespace std;


typedef struct tagBANK_RECORD
{
	char szamlaSzam[32];
	char devizaNem[8];
	char ertekNap[16];
	char tranzTip[32];
	char PartnerNeve[128];
	char PartnerSzamlaszama[32];
	double osszeg;
	char kozlemeny[256];
	int	besorolas;
} BANK_RECORD;


class CBankException : public exception
{
private:
	int value;
public:
	CBankException(int val) : value(val) {}
	const char* what() const noexcept override {
		return "fájl megnyitás hiba";
	}
	int getWalue() const {
		return value;
	}

};

class CBankAdat
{
public :
	CBankAdat();
	~CBankAdat();	
	void InitData();
	int	ReadDataFile(char *pFileName);
	int AddData(BANK_RECORD* pRec);

	double PartnerSum(char* pFN, int fileOut);

	double BesorolSum(int besr, int fileOut);

	int NumRecords() { return m_nRecords; };
private:
	BANK_RECORD* m_pAdatRecords;
	int	m_nRecords;
};

