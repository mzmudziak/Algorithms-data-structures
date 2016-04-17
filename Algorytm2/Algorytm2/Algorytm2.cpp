// Algorytm2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


int main()
{
					return 0;
}
class Field
{
public:
					bool N;
					bool E;
					bool S;
					bool W;
					int ways = 0;
};
class Board
{
private:
					int n; // n x n
					int p; // Liczba plotkow
					Field **board;
public:
					Board()
					{
										std::cin >> n;
										board = new Field*[n];
										for (int i = 0; i < n; i++)
										{
															board[i] = new Field[n];
										}
										setObstacles();
					}
					void setObstacles()
					{
										std::cin >> p;
										int obstacle;
										int x;
										int y;
										for (int i = 0; i < p;i++)
										{
															std::cin >> obstacle;
															std::cin >> x;
															std::cin >> y;
															if (obstacle == 0)
															{

															}
															else if (obstacle == 1)
															{

															}
										}
					}
};