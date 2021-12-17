// Project5.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <vector>
#include <map>
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
double *iter15(vector<Point> points, int pointNum)
{
	sort(points.begin(), points.end(), compX);
	double **distArray = new double *[pointNum];
	for (int i = 0; i < pointNum; i++)
	{
		distArray[i] = new double[pointNum];
	}
	double mindist = 10000000;
	int minx = 0, miny = 0, minx2 = 0, miny2 = 0;
	for (int i = 0; i < pointNum-1; i++)
	{
		for (int j = i; j < std::min(i+15,pointNum); j++)
		{
			distArray[i][j] = (points.at(i)).dist(points.at(j));
			if (distArray[i][j] < mindist && distArray[i][j] != 0)
			{
				minx = points.at(i).getX();
				miny = points.at(i).getY();
				minx2 = points.at(j).getX();
				miny2 = points.at(j).getY();
				mindist = distArray[i][j];
			}
		}
	}
	double *ret = new double[5]{(double)minx, (double)miny, (double)minx2, (double)miny2, mindist};
	return ret;
}
double *iter(vector<Point> points, int pointNum)
{
	sort(points.begin(), points.end(), compX);
	double **distArray = new double *[pointNum];
	for (int i = 0; i < pointNum; i++)
	{
		distArray[i] = new double[pointNum];
	}
	double mindist = 10000000;
	int minx = 0, miny = 0, minx2 = 0, miny2 = 0;
	for (int i = 0; i < pointNum; i++)
	{
		for (int j = i; j < pointNum; j++)
		{
			distArray[i][j] = (points.at(i)).dist(points.at(j));
			if (distArray[i][j] < mindist && distArray[i][j] != 0)
			{
				minx = points.at(i).getX();
				miny = points.at(i).getY();
				minx2 = points.at(j).getX();
				miny2 = points.at(j).getY();
				mindist = distArray[i][j];
			}
		}
	}
	double *ret = new double[5]{(double)minx, (double)miny, (double)minx2, (double)miny2, mindist};
	return ret;
}
double* recurReg(vector<Point> points, int pointNum)
{
	//BASE CASE
	if (pointNum <= 3)
	{
		return iter(points, pointNum);
	}
	//SORT POINTS AND SPLIT INTO LEFT AND RIGHT TO RECUR
	sort(points.begin(), points.end(), compX);
	//Point *left = new Point[(int)(pointNum / 2)];
	//Point *right = new Point[(int)(pointNum / 2) + pointNum % 2];
	vector<Point> left;
	vector<Point> right;
	int rightCount = int(pointNum / 2);
	for (int i = 0; i < int(pointNum / 2); i++)
	{
		left.push_back(points.at(i));
		right.push_back(points.at(rightCount));
		rightCount += 1;
	}
	if (pointNum % 2 != 0)
	{
		right.push_back(points.at(rightCount));
	}

	double *leftMin = recurReg(left, (int)(pointNum / 2));
	double *rightMin = recurReg(right, (int)(pointNum / 2) + pointNum % 2);

	//CHOOSING WIDTH OF DSTRIP
	double *returnedMin;
	vector<Point> dstripList;
	if (leftMin[4] < rightMin[4])
	{
		returnedMin = leftMin;
	}
	else
	{
		returnedMin = rightMin;
	}
	//ADDING POINTS TO DSTRIP
	int y1 = (int)((left.at(left.size()-1).getX()));
	int y2 = (int)((right.at(0).getX()));
	int mid = (int)((y1 + y2) / 2);
	for (int i = mid - (int)(returnedMin[4]); i <= mid + (int)(returnedMin[4]); i++)
	{
		for (int p = 0; p < pointNum; p++)
		{
			if (points.at(p).getX() == i)
			{
				dstripList.push_back(points.at(p));
			}
		}
	}
	/*
	Point *dstrip = new Point[dstripList.size()];
	copy(dstripList.begin(), dstripList.end(), dstrip);*/
	double *minFinal = iter(dstripList, dstripList.size());
	//cout << "return" << endl;
	if (returnedMin[4] < minFinal[4])
		return returnedMin;
	return minFinal;
}
double* recurFast(vector<Point> points, int pointNum)
{
	//BASE CASE
	if (pointNum <= 3)
	{
		return iter(points, pointNum);
	}
	//SORT POINTS AND SPLIT INTO LEFT AND RIGHT TO RECUR
	sort(points.begin(), points.end(), compX);

	//Point *left = new Point[(int)(pointNum / 2)];
	//Point *right = new Point[(int)(pointNum / 2) + pointNum % 2];
	vector<Point> left;
	vector<Point> right;
	int rightCount = int(pointNum / 2);
	for (int i = 0; i < int(pointNum / 2); i++)
	{
		left.push_back(points.at(i));
		right.push_back(points.at(i));
		rightCount += 1;
	}
	if (pointNum % 2 != 0)
	{
		right.push_back(points.at(rightCount));
	}

	double *leftMin = recurFast(left, (int)(pointNum / 2));
	double *rightMin = recurFast(right, (int)(pointNum / 2) + pointNum % 2);
	//CHOOSING WIDTH OF DSTRIP
	double *returnedMin;
	vector<Point> dstripList;
	if (leftMin[4] < rightMin[4])
	{
		returnedMin = leftMin;
	}
	else
	{
		returnedMin = rightMin;
	}
	//ADDING POINTS TO DSTRIP
	int y1 = (int)((left.at(left.size()-1).getX()));
	int y2 = (int)((right.at(0).getX()));
	int mid = (int)((y1 + y2) / 2);
	for (int i = mid - (int)(returnedMin[4]); i <= mid + (int)(returnedMin[4]); i++)
	{
		for (int p = 0; p < pointNum; p++)
		{
			if (points.at(p).getX() == i)
			{
				dstripList.push_back(points.at(p));
			}
		}
	}
	/*Point *dstrip = new Point[dstripList.size()];
	copy(dstripList.begin(), dstripList.end(), dstrip);
	sort(dstrip, dstrip + dstripList.size(), compY);*/
	double *minFinal = iter15(dstripList, dstripList.size());
	//cout << "returnend" << endl;
	if (returnedMin[4] < minFinal[4])
	{
		return returnedMin;
	}
	return minFinal;
}
map<pair<int,int>,vector<Point>> makeDict(vector<Point> points, int pointNum, double ogMin)
{
	double invSize = 2/ogMin;
	map <pair<int,int>, vector<Point>> posToPoints;
	int x,y = 0;
	for(int i = 0; i < pointNum; i++)
	{
		x = points[i].getX();
		y = points[i].getY();
		pair<int,int> curr((int)(x*invSize), (int)(y*invSize));
		if(posToPoints.count(curr))
		{
			posToPoints[curr].push_back(points[i]);
		}
		else
		{
			posToPoints[curr] = vector<Point>{(points[i])};
		}
	}
	return posToPoints;
}
vector<Point> iterLinear(vector<Point> points, int pointNum)
{
	//ORDERING POINTS RANDOMLY
    int randPoint;
    for(int i = 0; i < pointNum; i ++)
    {
        randPoint = rand() % pointNum;
        std::swap(points[i],points[randPoint]);
	}
	double originalMinDist = points[0].dist(points[1]);
	double invSqrSize = 2/originalMinDist;
	map<pair<int,int>, vector<Point>> posToPoints = makeDict(vector<Point>{points[0],points[1]}, 2, originalMinDist);
	int upperLim = 800*invSqrSize;
	Point first = points[0];
	Point sec = points[1];
	//MAKE DICTIONARY
	//FOR LOOP
	int x,y = 0;
	for(int i = 0; i < pointNum; i ++)
	{
		x = points[i].getX();
		y = points[i].getY();
		int currSqX = (int)(x*invSqrSize);
		int currSqY = (int)(y*invSqrSize);
		pair<int,int> currCoord(currSqX, currSqY);

		vector<Point> pointsToCheck;
		for(int a = -2; a <= 2; a++)
		{
			for(int b = -2; b <= 2; b++)
			{
				pair<int,int> p (currSqX+a,currSqY+b);
				if(posToPoints.count(p))
				{
					for(Point k: posToPoints[p])
					{
						pointsToCheck.push_back(k);
					}
				}
			}
		}
		for(Point k: pointsToCheck)
		{
			double newMin = k.dist(points[i]);
			if(newMin != 0 && newMin < originalMinDist)
			{
				vector<Point> newPointVec;
				int num = 0;
				for(int z = 0; z <= i; z++)
				{
					newPointVec.push_back(points[z]);
					num ++;
				}
				posToPoints = makeDict(newPointVec, num, newMin);
				originalMinDist = newMin;
				first = points[i];
				sec = k;
				invSqrSize = 2/newMin;
				upperLim = 800*invSqrSize;
			}
			else
			{
				if(posToPoints.count(currCoord))
				{
					posToPoints[currCoord].push_back(points[i]);
				}
				else
				{
					posToPoints[currCoord] = vector<Point>{points[i]};
				}
			}
		}
	}
	//cout << "LAST: " << originalMinDist << endl;
	vector<Point> ret({first,sec});
	return ret;
}
int main()
{
    int pList[] = {10,100,500,1000,2000,5000,10000,50000,100000,500000,1000000};
    long sumIter = 0;
    long sumRecur = 0;
    long sumRecurFast = 0;
    const int pointNum = 1000000;
	vector<Point> points;
    for(int a = 0; a < 1; a++)
    {
        vector<Point> points;
		for (int i = 0; i < pointNum; i++)
		{
			points.push_back(Point((int)(((double)rand() / RAND_MAX) * 800), (int)(((double)rand() / RAND_MAX) * 800)));
		}
		sort(points.begin(), points.end(), compX);

        auto start = chrono::steady_clock::now();
        iterLinear(points, pointNum);
        auto end = chrono::steady_clock::now();
	    sumIter += chrono::duration_cast<chrono::microseconds>(end - start).count();

        /*start = chrono::steady_clock::now();
        recurReg(points, pointNum);
        end = chrono::steady_clock::now();
        sumRecur += chrono::duration_cast<chrono::microseconds>(end - start).count();
		
        start = chrono::steady_clock::now();
        recurFast(points, pointNum);
        end = chrono::steady_clock::now();
        sumRecurFast += chrono::duration_cast<chrono::microseconds>(end - start).count();*/	
    }
    //cout << "iterative: " << (double)(sumIter)/100 << endl;
    //cout << "recursive: " << (double)(sumRecur)/100 << endl;
    cout << " fast: " << (double)(sumIter) << endl;
}