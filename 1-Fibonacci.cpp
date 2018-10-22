/*
Program pobiera na wejsciu liczbe N od 0 do 100 000, a na standardowym wyjsciu podaje N-ty wyraz Ciagu fibonacciego.
*/

#include <iostream>
using namespace std;

int main()
{
    int num;
    cin >> num;
    int arraySize;
    if(num <4) // Ilosc cyfr w ciagu zwieksza sie co 4 lub 5 liczb fibonacciego. Dla mniejszych niz 4, bylo by to mniej niz 1 jako rozmiar tablicy
    {
        arraySize = 1;
    }
    else
    {
        arraySize = num/4;
    }
    int fib[arraySize];
    int prev[arraySize];
    int next[arraySize];
    int x=0,carry=0;
    for (int i=0; i<arraySize; i++) // zerowanie tablic przed wykonywaniem na nich dzialan
    {
        prev[i] = 0;
        next[i] = 0;
        fib[i] = 0;
    }
    prev[0] = 0; // ustawienie pierwszego i drugiego elementu ciagu fibonacciego, na poczatku zawsze sa takies
    next[0] = 1;
    int buffer = 0; // bufor aby zapisywac  w nim dodane liczby i sprawdzac czy trzeba uzywac przeniesienia
    for (int i=0; i<num-1; i++)
    {

        for (int j=0; j<arraySize; j++)
        {
            buffer = prev[j] + next[j] + carry;
            if (buffer > 9)
            {

                fib[j] = buffer - 10;
                carry = 1;
            }
            else
            {
                fib[j] = buffer;
                carry = 0;
            }
            buffer = 0; // czyszczenie bufora przed nastepnym dodawaniem
        }

        for (int x=0; x<arraySize; x++) // po skonczeniu dodawania, zamien miejscami tablice next -> prev oraz fib -> next
        {
            prev[x] = next[x];
            next[x] = fib[x];
        }
    }
    bool zeroViewer = false; // Nie wyswietlaj zer dopoki nie trafisz na jakas liczbe. Usuwa to zera wiodace
    for (int i=arraySize-1; i>=0; i--)
    {
        if (num==0) // jesli chcesz zerowa liczbe fibonacciego to wyswietl zero
        {
            cout << 0;
        }
        else if (num==1) // jesli chcesz pierwsza liczbe fibonacciego to wyswietl ja!
        {
            cout << 1;
        }
        else if (fib[i] != 0) // Jesli trafiles na liczbe rozna od zera, to zacznij wyswietlac wyniki
        {
            zeroViewer = true;
        }
        if (zeroViewer == true)
        {
            cout <<fib[i];
        }
    }
    return 0;
}
