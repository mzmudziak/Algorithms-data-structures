// algorytm 4 - akcja ratunkowa.cpp : Defines the entry point for the console application.
// Michał Żmudziak

#include <iostream>
using namespace std;

struct item
{
	int x;
	int y;
	item* next = NULL;
};

class queue
{
private:
	item* first;
	item* last;
public:
	queue() :first(NULL), last(NULL) {}
	~queue() {}
	void enqueue(int tx, int ty) {
		item* temp = new item;
		temp->x = tx;
		temp->y = ty;
		if (first == NULL)
		{
			first = last = temp;
		}
		else
		{
			last->next = temp;
			last = temp;
		}
	}
	item dequeue() {
		if (first == NULL)
		{
			item fk;
			fk.x = -2; // "item" nie moze byc nullem, wiec zwracam sobie item z x,y takimi, ze pozniej bede wiedzial ze jest on poza zakresem (w sensie taki nigdy nie bedzie sie
			fk.y = -2; // liczyl przy iterowaniu po tablicach, bede go traktowal jakby nie istnial
			return fk;
		}
		else
		{
			item* temp = first;
			item t;
			t.x = temp->x;
			t.y = temp->y;
			first = first->next;
			delete temp;
			return t;
		}
	}
	bool isEmpty()
	{
		return first == NULL;
	}
};

class map
{
private:
	int x;
	int y;
	int **area;
	int targetX;
	int targetY;
	int lifesaverX;
	int lifesaverY;
public:
	map()
	{
		cin >> x;
		cin >> y;
		area = new int*[x];
		for (int i = 0; i < y; i++)
		{
			area[i] = new int[y];
		}
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				area[i][j] = 0;
			}
		}
		getObstacles();
		getPositions();
	}
	void getObstacles()// wstawianie scian
	{
		int amountOfObstacles;
		int obstacle;
		for (int i = 0; i < x; i++)
		{
			cin >> amountOfObstacles;
			for (int j = 0; j < amountOfObstacles; j++)
			{
				cin >> obstacle;
				area[i][obstacle] = 1;
			}
		}
	}
	void getPositions() // wstawianie gornika i ratownika poczatkowego
	{
		cin >> targetY;// wspolrzedne odwrocone bo u mnie X to jest oś góra- dół a Y to lewo-prawo
		cin >> targetX;
		cin >> lifesaverY;
		cin >> lifesaverX;
		area[targetX][targetY] = 2;
		area[lifesaverX][lifesaverY] = 0;
	}
	void FloodFill()// '9' - ratownik, '2' - górnik, '0' - pole wolne, '1' - pole ze ścianą
	{
		queue qFill; // kolejka wolnych miejsc do wypelnienia
		queue qDel; // kolejka scian do usuniecia
		item nP;
		item nD;
		qFill.enqueue(lifesaverX, lifesaverY);
		bool found = false;
		int e = 0;
		while (!found) // dopoki nie znaleziono gornika, w sumie bezuzyteczne bo gdy znaleziono to jest return
		{
			while (!qFill.isEmpty())
			{
				nP = qFill.dequeue();
				if (!(nP.x < 0 || nP.x > x - 1 || nP.y < 0 || nP.y > y - 1))
				{
					if (area[nP.x][nP.y] == 2)   // Czy znaleziono gornika?
					{
						found = true;
						cout << e << endl;
						return;
					}
					else if (area[nP.x][nP.y] == 1)   // Czy sciana do usuniecia
					{
						qDel.enqueue(nP.x, nP.y); // Dodaj do usuniecia
					}
					else if (area[nP.x][nP.y] == 0)   // Czy mozna tam dojsc bez usuwania?
					{
						area[nP.x][nP.y] = 9; // No to wstaw tam ratownika
						qFill.enqueue(nP.x, nP.y - 1); // dodaj do sprawdzania elementy dookola
						qFill.enqueue(nP.x, nP.y + 1);
						qFill.enqueue(nP.x - 1, nP.y);
						qFill.enqueue(nP.x + 1, nP.y);
					}
				}
			}
			while (!qDel.isEmpty()) // gdy juz wypelniono wszystkie wolne miejsca to usuwaj sciany i dodawaj do sprawdzania wszystko dookola
			{
				nD = qDel.dequeue();
				area[nD.x][nD.y] = 9; // wstawianie ratownikow na sciany
				qFill.enqueue((nD.x), (nD.y - 1)); // dodaj do sprawdzania elementy dookola
				qFill.enqueue((nD.x), (nD.y + 1));
				qFill.enqueue((nD.x - 1), (nD.y));
				qFill.enqueue((nD.x + 1), (nD.y));
			}
			e++; // gdy usunieto wszystkie sciany, to dodaj licznik "faz usuwania scian"
		}
	}
};

int main()
{
	map a;
	a.FloodFill();
	return 0;
}
