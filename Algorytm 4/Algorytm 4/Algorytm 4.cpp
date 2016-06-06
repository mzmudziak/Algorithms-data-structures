// Algorytm 4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <algorithm>
#include <stack>

class Point
{
private:
	int x;
	int y;
public:

	Point(int x, int y)
		: x(x),
		  y(y)
	{
	}

	Point()
	{
	}

	void setX(int arg)
	{
		x = arg;
	}

	void setY(int arg)
	{
		y = arg;
	}

	int getX()
	{
		return x;
	}

	int getY()
	{
		return y;
	}

	bool operator<(Point* other)
	{
		if (x < other->getX())
		{
			return true;
		}
		else if (x == other->getX())
		{
			if (y < other->getY())
			{
				return true;
			}
			else return false;
		}
		else return false;
	}
};

static Point* minPoint;

static int determinant(Point* p, Point* q, Point* r)
{
	return p->getX() * q->getY()
		+ p->getY() * r->getX()
		+ q->getX() * r->getY()
		- q->getY() * r->getX()
		- p->getX() * r->getY()
		- q->getX() * p->getY();
}

bool sortByDet(Point* p, Point* q)
{
	Point* start = minPoint;
	int det = determinant(start, p, q);
	if (det < 0)
	{
		return false;
	}
	if (det > 0)
	{
		return true;
	}
	if (p->getY() > q->getY())
	{
		return false;
	}
	return true;
}

class Board
{
private:
	int n;
	int m;
	vector<Point*> points;
	stack<Point*> halo;	
public:

	Point* getPoint()
	{
		Point* p = new Point();;
		int temp;
		cin >> temp;
		p->setX(temp);
		cin >> temp;
		p->setY(temp);
		return p;
	}

	void getBoard()
	{
		int minY = 2147483647;
		int minX = 2147483647;
		for (int i = 0; i < n; i++)
		{
			Point* newPoint = getPoint();
			if (newPoint->getY() < minY)
			{
				minPoint = newPoint;
				minY = newPoint->getY();
				minX = newPoint->getX();
			}
			else if (newPoint->getY() == minY)
			{
				if (newPoint->getX() < minX)
				{
					minPoint = newPoint;
					minX = newPoint->getX();
					minY = newPoint->getY();
				}
			}
			points.push_back(newPoint);
		}
	}

	void checkPointForMinY(Point* checked_point)
	{
		getPoint();
	}


	void GrahamScan()
	{
		halo.push(points[0]);
		halo.push(points[1]);
		halo.push(points[2]);
		for (int i=3;i<points.size();i++)
		{
			Point *top = halo.top();
			halo.pop();
			Point *underTheTop = halo.top();
			halo.push(top);
			while (determinant(underTheTop, top, points[i]) <0)
			{
				halo.pop();
			}
			halo.push(points[i]);
		}
	}


	void getCheckedPointsAndCheckThemOnTheFly()
	{
		for (int i = 0; i < m; i++)
		{
			Point* checkedPoint = getPoint();
			//checkpoint here
		}
	}

	void swapMinPointWithFront()
	{
		for (vector<Point*>::iterator it = points.begin(); it != points.end(); it++)
		{
			if ((*it) == minPoint)
			{
				Point* tmp = points.front();
				points.front() = (*it);
				(*it) = tmp;
			}
		}
	}

	Board()
	{
		cin >> n;
		getBoard();
		swapMinPointWithFront();
		std::sort(points.begin() + 1, points.end(), sortByDet);
		GrahamScan();
		cin >> m;
		getCheckedPointsAndCheckThemOnTheFly();
	}
};

int main()
{
	Board* b = new Board();
	return 0;
}

/*
10
10 -10
9 -9
8 -8
7 -7
6 -6
5 -5
4 -4
3 -3
2 -2
1 -1
0 0
-1 1
-2 2
-3 3
-4 4
-5 5
-6 6
-7 7
-8 8
-9 9
-10 10





*/

