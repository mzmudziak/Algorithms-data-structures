// Algorytm2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
using namespace std;

struct Point
{
					int x;
					int y;
					int steps = 0;
};

struct Point_compare {
					bool operator() (const Point* leftArg, const Point* rightArg)  const {
										return leftArg->steps < rightArg->steps;
					}
} comparator;

/*
Boolean value determines if there is an obstacle in direction
*/
class Field
{
public:
					bool N = false;
					bool E = false;
					bool S = false;
					bool W = false;
					int ways = 0;
};


class Board
{
private:
					int n; // n x n array
					int p; // obstacle amount
					int m; // endpoint queries #
					Field **board_first;
					Field **board_second;
					vector< Point* > endPoints;
					Point *start;
public:
					Board()
					{
										std::cin >> n;
										setBoards();
										setObstacles();
										setStartingPosition();
										CalculateWays(start);
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
										std::cin >> p;
										int obstacleType;
										int x;
										int y;
										for (int i = 0; i < p;i++)
										{
															std::cin >> obstacleType;
															std::cin >> x;
															std::cin >> y;
															if (obstacleType == 0) // vertical obstacle
															{
																				board_first[x][y].E = true;
																				if (x + 1 < n) {
																									board_first[x + 1][y].W = true;
																				}
															}
															else if (obstacleType == 1) // horizontal obstacle
															{
																				board_first[x][y].S	= true;
																				if (y + 1 < n) {
																									board_first[x][y + 1].N = true;
																				}
															}
										}
					}

					 void setStartingPosition() const
					{				
										std::cin >> start->x;
										std::cin >> start->y;
					}
					void CalculateWays(Point *start)
					{
										cin >> m;
										for (int i = 0; i < m; i++)
										{
															endPoints.push_back(getPoint());
										}
										std::sort(endPoints.begin(), endPoints.end(), comparator);
										
					}
					 void DoWork()
					{
										for (int i = 0;i < n;i++)
										{
															for (int j = 0; j < n; j++)
															{
																					if (!board_first[i][j].N)
																					{
																										if (j - 1 > 0)
																										{
																															board_second[i][j].ways += board_first[i][j - 1].ways;
																															board_second[i][j - 1].ways = 0;
																										}
																					}
																					if (!board_first[i][j].E)
																					{
																										if (i+1 < n)
																										{
																															board_second[i][j].ways += board_first[i+1][j].ways;
																															board_second[i+1][j].ways = 0;
																										}
																					}
																					if (!board_first[i][j].S)
																					{
																										if (j + 1 < n)
																										{
																															board_second[i][j].ways += board_first[i][j+1].ways;
																															board_second[i][j+1].ways = 0;
																										}
																					}
																					if (!board_first[i][j].W)
																					{
																										if (i - 1 < n)
																										{
																															board_second[i][j].ways += board_first[i - 1][j].ways;
																															board_second[i - 1][j].ways = 0;
																										}
																					}
															}
										}
					}
					static Point*getPoint()
					{
										Point *point = new Point();
										cin >> point->steps;
										cin >> point->x;
										cin >> point->y;
										return point;
					}

				
};




int main()
{
					Board *b = new Board();


					return 0;
}

/*

er
3 4
0 0 0
0 0 1
0 1 0
0 1 1
0 0
12
0 0 0
8 3 2
3 2 0
0 5 2
1 3 5
1 5 2
6 2 3
6 7 2
56 12 3
0 1 3
5 0 1
0 3 1


*/