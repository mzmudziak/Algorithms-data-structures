// Algorytm3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

/*
Dane wejœciowe

w pierwszym wierszu liczba ró¿nych nomina³ów (N)
nastêpnie N wierszy z dwoma liczbami
wielkoœæ nomina³u (kwota),
liczba pieniêdzy o tym nominale
na koniec 2 liczby
kwota do rozmiany,
tryb pracy: 1 = monety rozró¿nialne, 0 = monety nierozró¿nialne
Wszystkie wielkoœci s¹ liczbami ca³kowitymi, wiêkszymi od 0, mieszcz¹cymi siê w typie ca³kowitym 4-bajtowym bez znaku.


*/

class CashUnit
{
private:
	int value;
	int quantity;
public:
	CashUnit(int value, int quantity)
		: value(value),
		  quantity(quantity)
	{
	}

	CashUnit()
	{
		this->value = 0;
		this->quantity = 0;
	}

	int getValue() const
	{
		return value;
	}

	int getQuantity() const
	{
		return quantity;
	}
};

class Change
{
private:
	int denomQuantity;
	int sum;
	int mode;
	int possibilites = 0;
	std::vector<CashUnit*> cashUnits;
	int *maxSum;
public:
	void readData()
	{
		cin >> denomQuantity;
		int val;
		int quant;
		for (int i = 0; i < denomQuantity; i++)
		{
			cin >> val;
			cin >> quant;
			CashUnit* cu = new CashUnit(val, quant);
			addCUnit(cu);
		}
		cin >> sum;
		cin >> mode;
		maxSum = new int[denomQuantity];
		getMaxSum();
	}

	void addCUnit(CashUnit* cashUnit)
	{
		cashUnits.push_back(cashUnit);
	}

	void listStuff()
	{
		cout << "denomQuantity: " << denomQuantity << endl;
		cout << "sum: " << sum << endl;
		cout << "mode: " << mode << endl;
		for (vector<CashUnit*>::iterator it = cashUnits.begin(); it != cashUnits.end(); it++)
		{
			cout << "V: " << (*it)->getValue() << " Q: " << (*it)->getQuantity() << endl;
		}
		for (int i = 0; i < denomQuantity; i++)
		{
			cout << "Ms: " << maxSum[i]  << endl;
		}
	}


	void getPossibilites(int currentValue, int tmpSum)
	{
	cout << "CurrVal: " << cashUnits[currentValue]->getValue() << " tmpSum: " << tmpSum << endl;
		for (int i = 0; i <= cashUnits[currentValue]->getQuantity(); i++)
		{
			int nowaSuma = tmpSum + i * cashUnits[currentValue]->getValue();
			cout << "NowaSuma: " << nowaSuma << " (" << tmpSum << "+ " <<i << "*" <<  cashUnits[currentValue]->getValue() <<")" << endl;
			if (nowaSuma == sum)
			{
				possibilites++;
				return;
			}
			if (nowaSuma <= sum)
			{
				int newVal = currentValue + 1;
				if (newVal < denomQuantity)
				{
					if (nowaSuma + maxSum[newVal] >= sum)
					getPossibilites(newVal, nowaSuma);
				}
			}
		}
	}

	void getMaxSum()
	{
		maxSum[denomQuantity - 1] = cashUnits[denomQuantity - 1]->getValue() * cashUnits[denomQuantity - 1]->getQuantity();
		for (int i = denomQuantity-2; i >= 0; i--)
		{
			maxSum[i] = maxSum[i+1] + cashUnits[i]->getValue() * cashUnits[i]->getQuantity();
		}
	}

	void listPossibilites() const
	{
		cout << possibilites << endl;
	}

	static int factorial(int n) {
		int factor = 1;
		for (int i = 1; i <= n; i++) {
			factor *= i;
		}
		return factor;
	}

	static int newtonsBinomial(int n, int k) {
		return factorial(n) / (factorial(k) * factorial(n - k));
	}

};

int main()
{
	Change* change = new Change();
	change->readData();
	change->listStuff();
	change->getPossibilites(0, 0);
	change->listPossibilites();
	return 0;
}

