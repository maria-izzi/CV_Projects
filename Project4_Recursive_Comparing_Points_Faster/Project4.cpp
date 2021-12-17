// Project4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <stdio.h>  /* printf, scanf, puts, NULL */
#include <stdlib.h> /* srand, rand, RAND_MAX */
#include <time.h>   /* time */
#include <list>
#include <array>
#include <chrono>
using namespace std;
struct Point
{
public:
	int x;
	int y;
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
void setPix(int **array, int x, int y, int color)
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
bool compY(Point i, Point j)
{
	return j.getY() > i.getY();
}
void fillRandom(double *arr)
{
	for (int i = 0; i < sizeof(arr); i++)
		arr[i] = (double)rand() / RAND_MAX;
	return;
}
void bresen(int x1, int y1, int x2, int y2, int **array)
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
double *iter15(Point *points, int pointNum)
{
	sort(points, points + pointNum, compX);
	double **distArray = new double *[pointNum];
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
		for (int j = i; j < i + 15; j++)
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
	double *ret = new double[5]{(double)minx, (double)miny, (double)minx2, (double)miny2, mindist};
	return ret;
}
double *iter(Point *points, int pointNum)
{
	sort(points, points + pointNum, compX);
	double **distArray = new double *[pointNum];
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
	double *ret = new double[5]{(double)minx, (double)miny, (double)minx2, (double)miny2, mindist};
	return ret;
}
double *recur(Point *points, int pointNum, int **arr)
{
	//BASE CASE
	if (pointNum <= 3)
	{
		return iter(points, pointNum);
	}
	//SORT POINTS AND SPLIT INTO LEFT AND RIGHT TO RECUR
	sort(points, points + pointNum, compX);
	Point *left = new Point[(int)(pointNum / 2)];
	Point *right = new Point[(int)(pointNum / 2) + pointNum % 2];
	int rightCount = int(pointNum / 2);
	for (int i = 0; i < int(pointNum / 2); i++)
	{
		left[i] = points[i];
		right[i] = points[rightCount];
		rightCount += 1;
	}
	if (pointNum % 2 != 0)
	{
		right[int(pointNum / 2)] = points[rightCount];
	}
	for (int i = 0; i < (int)(pointNum / 2); i++)
	{
		//cout << i << " left x: " << left[i].getX() << " y: " << left[i].getY() << endl;
	}
	for (int i = 0; i < (int)(pointNum / 2) + pointNum % 2; i++)
	{
		//cout << i << " right x: " << right[i].getX() << " y: " << right[i].getY() << endl;
	}
	//cout << endl;

	double *leftMin = recur(left, (int)(pointNum / 2), arr);
	double *rightMin = recur(right, (int)(pointNum / 2) + pointNum % 2, arr);

	//CHOOSING WIDTH OF DSTRIP
	double *returnedMin;
	list<Point> dstripList;
	if (leftMin[4] < rightMin[4])
	{
		returnedMin = leftMin;
	}
	else
	{
		returnedMin = rightMin;
	}
	//cout << "returned x1: " << returnedMin[0] << " y1: " << returnedMin[1] << endl;
	//cout << "returned x2: " << returnedMin[2] << " y2: " << returnedMin[3] << endl;

	//ADDING POINTS TO DSTRIP
	int y1 = (int)((left[(int)(pointNum / 2) + 1].getX()));
	int y2 = (int)((right[0].getX()));
	int mid = (int)((y1 + y2) / 2);
	//cout << "mid: " << mid << endl;

	for (int i = mid - (int)(returnedMin[4]); i <= mid + (int)(returnedMin[4]); i++)
	{
		for (int p = 0; p < pointNum; p++)
		{
			if (points[p].getX() == i)
			{
				dstripList.push_back(points[p]);
			}
		}
	}
	Point *dstrip = new Point[dstripList.size()];
	copy(dstripList.begin(), dstripList.end(), dstrip);
	sort(dstrip, dstrip + dstripList.size(), compY);
	for (int p = 0; p < dstripList.size(); p++)
	{
		//cout << "point dstrip list: " << dstrip[p].getX() << " " << dstrip[p].getY() << endl;
	}
	double *minFinal = iter15(dstrip, dstripList.size());
	if (returnedMin[4] < minFinal[4])
	{
		return returnedMin;
	}
	return minFinal;
}
int main()
{
	int **array = new int *[800];
	const int pointNum = 50000;
	for (int i = 0; i < 800; i++)
	{
		array[i] = new int[800];
	}
	srand(time(NULL));

	Point points[pointNum];
	double doublex[pointNum];
	double doubley[pointNum];
	fillRandom(doublex);
	fillRandom(doubley);
	int intx[pointNum];
	int inty[pointNum];
	for (int i = 0; i < pointNum; i++)
	{
		intx[i] = (int)(((double)rand() / RAND_MAX) * 800);
		inty[i] = (int)(((double)rand() / RAND_MAX) * 800);
		points[i] = Point(intx[i], inty[i]);
		setPix(array, intx[i], inty[i], 1);
	}
	//int n = sizeof(points) / sizeof(points[0]);
	sort(points, points + pointNum, compX);
	cout << "points : " << endl;
	for (int i = 0; i < pointNum; i++)
	{
		//cout << points[i].getX() << ",";
	}
	cout << endl;
	for (int i = 0; i < pointNum; i++)
	{
		//cout << points[i].getY() << ",";
	}
	cout << endl;
	int midPoint = (int)(pointNum / 2);
	Point leftCut = Point(points[midPoint - 1].getX(), points[midPoint - 1].getY());
	Point rightCut = Point(points[midPoint].getX(), points[midPoint].getY());
	//cout << "leftVals:" << leftCut.getX() << " " << leftCut.getY() << endl;
	//cout << "rightVals:" << rightCut.getX() << " " << rightCut.getY() << endl;
	midPoint = (leftCut.getX() + rightCut.getX()) / 2;
	//cout << "midpoint: " << midPoint << endl;
	bresen(midPoint, 0, midPoint, 800, array);
	cout << "RECURRING" << endl;
	double *iterMin = iter(points, pointNum);
	auto start = chrono::steady_clock::now();
	double *recurMin = recur(points, pointNum, array);
	auto end = chrono::steady_clock::now();
	cout << "recur mindist: " << recurMin[4] << endl;
	cout << "recur x1: " << recurMin[0] << " y1: " << recurMin[1] << endl;
	cout << "recur x2: " << recurMin[2] << " y2: " << recurMin[3] << endl;
	cout << "iter mindist: " << iterMin[4] << endl;
	cout << "iter x1: " << iterMin[0] << " y1: " << iterMin[1] << endl;
	cout << "iter x2: " << iterMin[2] << " y2: " << iterMin[3] << endl;
	list<Point> dstripList;
	//MAKE RECUR MIN
	for (int i = midPoint - (int)(recurMin[4]); i <= midPoint + (int)(recurMin[4]); i++)
	{
		for (int p = 0; p < pointNum; p++)
		{
			if (points[p].getX() == i)
			{
				//cout << "hello" << endl;
				dstripList.push_back(points[p]);
			}
		}
	}
	Point *dstrip = new Point[dstripList.size()];
	copy(dstripList.begin(), dstripList.end(), dstrip);
	double *minFinal = iter(dstrip, dstripList.size());
	cout << "final 1: " << minFinal[0] << " " << minFinal[1] << endl;
	cout << "final 2: " << minFinal[2] << " " << minFinal[3] << endl;
	cout << "final dist: " << minFinal[4] << endl;
	if (recurMin[4] < minFinal[4])
	{
		setPix(array, recurMin[0], recurMin[1], 100);
		setPix(array, recurMin[2], recurMin[3], 100);
	}
	else
	{
		setPix(array, minFinal[0], minFinal[1], 100);
		setPix(array, minFinal[2], minFinal[3], 100);
	}
	cout << "time: " << chrono::duration_cast<chrono::microseconds>(end - start).count();
	string s1 = "1 1 1 ";
	string s2 = "1 0 0 ";
	string s3 = "0 0 0 ";
	ofstream file;
	file.open("Project4_Output.ppm");
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

/*double* leftMin = recur(left, (int)(pointNum/2), arr);
	double* rightMin = recur(right, (int)(pointNum / 2) + pointNum % 2, arr);
	double* returnedMin;
	list<Point> dstripList;
	if (leftMin[4] < rightMin[4])
	{
		returnedMin = leftMin;
	}
	else
		returnedMin = rightMin;
	cout << "returned x1: " << returnedMin[0] << " y1: " << returnedMin[1] << endl;
	cout << "returned x2: " << returnedMin[2] << " y2: " << returnedMin[3] << endl;
	int mid = (int)((returnedMin[3] + returnedMin[1]) / 2);
	cout << "mid: " << mid << endl;

	bresen(0, mid, 800, mid, arr);
	for (int i = mid - (int)(returnedMin[4])+50; i <= mid + (int)(returnedMin[4]) +50; i++)
	{
		for (int p = 0; p < pointNum; p++)
		{
			if (array[p].getY() == i)
			{
				//cout << "hello" << endl;
				dstripList.push_back(array[p]);
			}
		}
	}
	Point* dstrip = new Point[dstripList.size()];
	copy(dstripList.begin(), dstripList.end(), dstrip);
	cout << "size: " << dstripList.size() << endl;
	for (int p = 0; p < dstripList.size(); p++)
	{
		cout << "point dstrip list: " << dstrip[p].getX() << " " << dstrip[p].getY() << endl;
	}
	double* minFinal = iter(dstrip, dstripList.size());
	if (returnedMin[4] < minFinal[4])
		return returnedMin;
	return minFinal;*/