// Algorytm2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Point
{
	int x;
	int y;
	int steps;
	int order;

	Point(int a, int b, int c, int d)
	{
		x = a;
		y = b;
		steps = c;
		order = d;
	}

	Point()
	{
		x = 0;
		y = 0;
		steps = 0;
		order = 0;
	}

	Point(const Point* otherPoint)
	{
		x = otherPoint->x;
		y = otherPoint->y;
		steps = otherPoint->steps;
		order = otherPoint->order;
	}
};

struct Result
{
	long long ways;
	int order;

	Result(long long a, int b)
	{
		ways = a;
		order = b;
	}

	Result()
	{
		ways = -1;
		order = -1;
	}
};

struct Point_compare
{
	bool operator()(const Point* leftArg, const Point* rightArg) const
	{
		return leftArg->steps < rightArg->steps;
	}
} bySteps;

struct Result_compare
{
	bool operator()(const Result* left_point, const Result* right_point) const
	{
		return left_point->order < right_point->order;
	}
} byOrder;

class Field
{
public:
	bool N = false;
	bool E = false;
	bool S = false;
	bool W = false;
	long long ways = 0;
};


class Board
{
private:
	int n; // n x n array
	int p; // obstacle amount
	int m; // endpoint queries #
	int maxSteps = 0; // maximum amount of steps
	Field** board_first;
	Field** board_second;
	Point start;
	vector<Point*> endPoints;
	vector<Result*> result;

public:
	Board()
	{
		cin >> n;
		setBoards(); // Allocates boards with n x n size
		setObstacles(); // Sets obstacles on both boards based on user input
		setStartingPosition(); // Gets starting position
		getEndPoints(); // gets a vector of end points, sorts it and stores an in order unsorted vector of endpoints
		ProcessData(); // xd
		ListResults();
	}

	void setBoards()
	{
		board_first = new Field*[n];
		board_second = new Field*[n];
		for (int i = 0; i < n; i++)
		{
			board_first[i] = new Field[n];
			board_second[i] = new Field[n];
		}
	}

	void setObstacles()
	{
		cin >> p;
		int obstacleType;
		int x;
		int y;
		for (int i = 0; i < p; i++)
		{
			cin >> obstacleType;
			cin >> x;
			cin >> y;
			if (obstacleType == 0) // vertical obstacle
			{
				board_first[x][y].E = true;
				board_second[x][y].E = true;
				if (x + 1 < n)
				{
					board_first[x][y + 1].W = true;
					board_second[x][y + 1].W = true;
				}
			}
			else if (obstacleType == 1) // horizontal obstacle
			{
				board_first[x][y].S = true;
				board_second[x][y].S = true;
				if (y + 1 < n)
				{
					board_first[x + 1][y].N = true;
					board_second[x + 1][y].N = true;
				}
			}
		}
	}

	void setStartingPosition()
	{
		cin >> start.x;
		cin >> start.y;
		board_first[start.x][start.y].ways = 1;
	}


	void getEndPoints()
	{
		cin >> m;
		for (int i = 0; i < m; i++)
		{
			endPoints.push_back(getPoint(i));
		}
		std::sort(endPoints.begin(), endPoints.end(), bySteps);
	}

	Point* getPoint(int order)
	{
		Point* point = new Point();
		cin >> point->steps;
		cin >> point->x;
		cin >> point->y;
		point->order = order;
		if (point->steps > maxSteps)
		{
			maxSteps = point->steps;
		}
		return point;
	}

	void ProcessData()
	{
		for (int i = 0; i <= maxSteps; i++)
		{
			Step();
			CheckForResults(i);
			FlipBoards();
		}
	}

	void CheckForResults(int i)
	{
		while (endPoints.begin() != endPoints.end() && endPoints.front()->steps == i)
		{
			Result* r = new Result(board_first[endPoints.front()->x][endPoints.front()->y].ways % 1000000007, endPoints.front()->order);
			result.push_back(r);
			endPoints.erase(endPoints.begin());
		}
	}

	void Step()
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (!board_first[i][j].N)
				{
					if (i - 1 >= 0)
					{
						board_second[i][j].ways += board_first[i - 1][j].ways % 1000000007;
					}
				}
				if (!board_first[i][j].E)
				{
					if (j + 1 < n)
					{
						board_second[i][j].ways += board_first[i][j + 1].ways % 1000000007;
					}
				}
				if (!board_first[i][j].S)
				{
					if (i + 1 < n)
					{
						board_second[i][j].ways += board_first[i + 1][j].ways % 1000000007;
					}
				}
				if (!board_first[i][j].W)
				{
					if (j - 1 >= 0)
					{
						board_second[i][j].ways += board_first[i][j - 1].ways % 1000000007;
					}
				}
			}
		}
	}

	void FlipBoards()
	{
		Field** tmpBoard;
		tmpBoard = board_first;
		board_first = board_second;
		board_second = tmpBoard;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				board_second[i][j].ways = 0;
			}
		}
	}

	void ListResults()
	{
		sort(result.begin(), result.end(), byOrder);
		for (vector<Result*>::iterator it = result.begin(); it != result.end(); it++)
		{
			cout << (*it)->ways % 1000000007 << endl;
		}
	}
};

int main()
{
	Board* b = new Board();
	return 0;
}

