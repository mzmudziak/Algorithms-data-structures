// Algorytm3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
using namespace std;

class CashUnit
{
public:
	int value;
	int quantity;

	CashUnit(int value, int quantity)
		: value(value),
		  quantity(quantity)
	{
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
	int* maxSum;
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
		getMaxSum(); // Mala tablica na przechowywanie danych w celu optymalizacji
	}

	void addCUnit(CashUnit* cashUnit)
	{
		cashUnits.push_back(cashUnit);
	}

	void getPossibilites(int currentValue, int tmpSum, int posCount)
	{
		cout<< "Teraz sprawdzam w rekurencji: " << cashUnits[currentValue]->value << "\nAktualna suma: " << tmpSum << endl;
		for (int i = 0; i <= cashUnits[currentValue]->quantity; i++)
		{
			int newSum = tmpSum + i * cashUnits[currentValue]->value;
			if (newSum > sum )
			{
				return;
			}
			cout << "Nowa suma: " << newSum << " (" << tmpSum << " + " << "(" << i << "*" << cashUnits[currentValue]->value << ")" << endl;
				if (newSum == sum)
				{
					cout << "Wow! Suma " << newSum << " jest rowna poszukiwanej sumie " << sum << endl;

					possibilites++;
					cout << "Teraz zliczylem juz " << possibilites << " takich mozliwosci!" << endl;
					cout << "Spierdalam szukac nowej sumy.." << endl<<endl << endl;
					return;
				}

				if (newSum < sum && currentValue + 1 < denomQuantity && newSum + maxSum[currentValue + 1] >= sum)
				{
					cout << "Uhh.. Moja suma " << newSum << " jest nadal mniejsza niz " << sum << " - lepiej szukam dalej!" << endl << endl;
					getPossibilites(currentValue + 1, newSum, posCount);
				}
			}
		}

		void getPossibilitesMode1(int currentValue, int tmpSum, int posCount)
			{
				for (int i = 0; i <= cashUnits[currentValue]->quantity; i++) // p
				{
					int newSum = tmpSum + i * cashUnits[currentValue]->value;
					if (newSum == sum)
					{
						possibilites += posCount * newtonsBinomial(cashUnits[currentValue]->quantity, i);
						return;
					}
					if (newSum < sum && // Czy suma nie wykracza za poszukiwan¹
						currentValue + 1 < denomQuantity //czy nie wychodzê za wymiar wektora po wejsciu w rekurencjê ni¿ej?
						&& newSum + maxSum[currentValue + 1] >= sum) // czy dalsze wyniki maj¹ mo¿liwoœæ dania wyniku?
					{
						int newposCount = posCount * newtonsBinomial(cashUnits[currentValue]->quantity, i); // zliczaj mo¿liwoœci dojœ
						getPossibilitesMode1(currentValue + 1, newSum, newposCount);
					}
				}
			}


		void getMaxSum() // Funkcja w celu optymalizacji, przechowuje tablicê maksymalnych wartoœci osi¹galnych przez ni¿sze nomina³y
			{
				maxSum[denomQuantity - 1] = cashUnits[denomQuantity - 1]->value * cashUnits[denomQuantity - 1]->quantity;
				for (int i = denomQuantity - 2; i >= 0; i--)
				{
					maxSum[i] = maxSum[i + 1] + cashUnits[i]->value * cashUnits[i]->quantity;
				}
			}

		void listPossibilites() const
			{
				cout << possibilites << endl;
			}

		int factorial(int n) const
			{
				int f = 1;
				for (int i = 1; i <= n; i++)
				{
					f *= i;
				}
				return f;
			}

		int newtonsBinomial(int n, int k) const
			{
				return factorial(n) / (factorial(k) * factorial(n - k));
			}

		int getMode() const
			{
				return mode;
			}
	};

	int main()
	{
		Change change;
		change.readData();
		if (change.getMode() == 1)
		{
			change.getPossibilitesMode1(0, 0, 1);
		}
		else
		{
			change.getPossibilites(0, 0, 1);
		}
		change.listPossibilites();
		return 0;
	}

