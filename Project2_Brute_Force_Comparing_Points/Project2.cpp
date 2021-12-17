// Project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand, RAND_MAX */
#include <time.h>       /* time */
#include <list>
#include <array>
#include <chrono>
using namespace std;
struct Point
{
public:
	int x = 0;
	int y = 0;
	Point()
	{
		x = 0;
		y = 0;
	}
	Point(int xval, int yval)
	{
		x = xval;
		y = yval;
	}
	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
	double dist(Point j)
	{
		int xval = j.getX();
		int yval = j.getY();
		return sqrt((pow((xval - x), 2) + pow((yval - y), 2)));
	}
};
void setPix(int** array, int x, int y, int color)
{
	if (x < 800 && x >= 0 && y < 800 && y >= 0)
	{
		array[x][y] = color;
	}
}
bool compX(Point i, Point j)
{
	return j.getX() > i.getX();
}
void fillRandom(double* arr)
{
	for (int i = 0; i < sizeof(arr); i++)
		arr[i] = (double)rand() / RAND_MAX;
	return;
}
void bresen(int x1, int y1, int x2, int y2, int** array)
{
	bool first = false;
	bool sec = false;
	if (abs(y2 - y1) > abs(x2 - x1))
	{
		first = true;
		int x = x1;
		int y = x2;
		x1 = y1;
		y1 = x;
		x2 = y2;
		y2 = y;
	}
	if (x1 > x2)
	{
		sec = true;
		int x = x1;
		x1 = x2;
		x2 = x;
		int y = y1;
		y1 = y2;
		y2 = y;
	}

	int dx, dy;
	int x, y;
	dx = x2 - x1;
	dy = y2 - y1;
	bool k = false;

	if (dy < 0)
	{
		dy = abs(dy);
		y = -1;
		k = true;
	}
	else
		y = 1;
	if (dx < 0)
	{
		dx = abs(dx);
		x = -1;
		k = true;
	}
	else
		x = 1;

	/*if (k)
	{
		dy = 2 * dy;
		dx = 2 * dx;
	}*/

	int j = y1;
	int e = dy - dx;
	double m = dy / dx;
	//cout << "first "<<first << " sec " << sec;
	for (int i = x1; i < x2; i += x)
	{
		if (first)
			setPix(array, j, i, 1);
		else
			setPix(array, i, j, 1);
		if (e >= 0)
		{
			j += y;
			e -= dx;
		}
		e += dy;
	}
}
double* iter(Point* points, int pointNum)
{
	sort(points, points + pointNum, compX);
	double** distArray = new double* [pointNum];
	for (int i = 0; i < pointNum; i++)
	{
		distArray[i] = new double[pointNum];
	}
	/*
	double mindist = points[1].dist(points[0]);
	int minx = points[0].getX();
	int miny = points[0].getY();
	int minx2 = points[1].getX();
	int miny2 = points[1].getY();
	*/
	double mindist = 10000000;
	int minx = 0, miny = 0, minx2 = 0, miny2 = 0;
	for (int i = 0; i < pointNum; i++)
	{
		for (int j = i; j < pointNum; j++)
		{
			distArray[i][j] = (points[i]).dist(points[j]);
			if (distArray[i][j] < mindist && distArray[i][j] != 0)
			{
				minx = points[i].getX();
				miny = points[i].getY();
				minx2 = points[j].getX();
				miny2 = points[j].getY();
				mindist = distArray[i][j];
			}
			/*if (mindist == 0)
			{
				minx = points[i].getX();
				miny = points[i].getY();
				minx2 = points[j].getX();
				miny2 = points[j].getY();
				mindist = distArray[i][j];
			}*/
		}
	}
	double* ret = new double[5]{ (double)minx, (double)miny, (double)minx2,(double)miny2,mindist };
	return ret;
}
int main()
{
	int** array = new int* [800];
	const int pointNum = 10;
	for (int i = 0; i < 800; i++)
	{
		array[i] = new int[800];
	}
	srand(time(NULL));

	Point points[pointNum];
	int intx[pointNum];
	int inty[pointNum];
	for (int i = 0; i < pointNum; i++)
	{
		intx[i] = (int)(((double)rand() / RAND_MAX)*800);
		inty[i] = (int)(((double)rand() / RAND_MAX) * 800);
		points[i] = Point(intx[i], inty[i]);
		setPix(array, intx[i], inty[i], 1);
	}
	sort(points, points + pointNum, compX);
	//cout << "points : " << endl;
	for (int i = 0; i < pointNum; i++)
	{
		//cout << points[i].getX() << " " << points[i].getY() << endl;
	}
	int midPoint = (int)(pointNum / 2);
	Point leftCut = Point(points[midPoint - 1].getX(), points[midPoint - 1].getY());
	Point rightCut = Point(points[midPoint].getX(), points[midPoint].getY());
	midPoint = (leftCut.getX() + rightCut.getX()) / 2;
	bresen(midPoint, 0, midPoint, 800, array);
	auto start = chrono::steady_clock::now();
	double* iterMin = iter(points, pointNum);
	auto end = chrono::steady_clock::now();
	setPix(array, iterMin[0], iterMin[1], 100);
	setPix(array, iterMin[2], iterMin[3], 100);
	
	cout << "time: " << chrono::duration_cast<chrono::microseconds>(end - start).count();

	string s1 = "0 0 0 ";
	string s2 = "1 0 0 ";
	string s3 = "1 1 1 ";
	ofstream file;
	file.open("Project2_Output.ppm");
	file << "P3 800 800 1" << endl;
	for (int j = 0; j < 800; j++)
	{
		for (int i = 0; i < 800; i++)
		{
			if (array[i][j] == 1)
			{
				file << s1;
			}
			else if (array[i][j] == 100)
			{
				file << s2;
			}
			else
			{
				file << s3;
			}
		}
		file << endl;
		file.flush();
	}
	file.flush();
	file.close();

	//deleting array from heap at end
	for (int j = 0; j < 800; j++)
	{
		delete[] array[j];
	}
	delete[] array;

	return 0;
}