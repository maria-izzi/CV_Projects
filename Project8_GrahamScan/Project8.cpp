// Project7.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <stack>
#include <vector>
#include <tuple>
#include <map>
using namespace std;
struct Point
{
public:
	double x;
	double y;
	Point()
	{
		x = 0.0;
		y = 0.0;
	}
	Point(double xval, double yval)
	{
		x = xval;
		y = yval;
	}
	double getX()
	{
		return x;
	}
	double getY()
	{
		return y;
	}
    void setX(double newx)
    {
        x = newx;
    }
    void setY(double newy)
    {
        y = newy;
    }
	//SLOWER DISTANCE FORMULA
	/*double dist(Point j)
	{
		double xval = j.getX();
		double yval = j.getY();
		return sqrt((pow((xval - x), 2) + pow((yval - y), 2)));
	}*/
	//FASTER DISTANCE FORMULA
	double dist(Point j)
	{
		double xval = j.getX();
		double yval = j.getY();
		return (xval-x)*(xval-x) + (yval-y)*(yval-y);
	}
};
Point p0;
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
			setPix(array, j, i,2);
		else
			setPix(array, i, j,2);
		if (e >= 0)
		{
			j += y;
			e -= dx;
		}
		e += dy;
	}
}
int clockwise(Point p1, Point p2, Point p3)
{
    int direction = ((p2.getY() - p1.getY())*(p3.getX()-p2.getX())) - ((p2.getX()-p1.getX())*(p3.getY()-p2.getY()));
    if(direction == 0)
    {
        return 0;
    }
    else if (direction < 0)
    {
        return -1;
        return 1;
    }
}
bool compAngle(Point i, Point j)
{
    int orientation = clockwise(p0, i, j);
    if (orientation == 0)
    {
        return (p0.dist(j) >= p0.dist(i));
    }
    return (orientation == -1);
}
Point sec(stack<Point> s)
{
    Point a = s.top();
    s.pop();
    Point b = s.top();
    s.push(a);
    return b;
}
int main()
{	
    //CREATE PPM ARRAY
	int** array = new int* [800];
	for (int i = 0; i < 800; i++)
	{
		array[i] = new int[800];
	}
	const int pointNum = 75;
    vector<Point> points;
    double pointx, pointy = 0.0;
	srand(time(NULL));
    
    for (int i = 0; i < pointNum; i++)
    {
		pointx = ((double)rand() / RAND_MAX)*800;
		pointy = ((double)rand() / RAND_MAX)*800;
        points.push_back(Point(pointx, pointy));
        //cout << "{" << int(pointx) << "," << int(pointy) << "},";
        setPix(array,points[i].getX(),points[i].getY(),1);
    }
    cout << endl;
    
    //ADD POINTS TO INITIAL ARRAY
    /*
	int xarr[pointNum] = {100,400,700,100,400,700,100,400,700};
	int yarr[pointNum] = {100,100,100,400,400,400,700,700,700};
    int xarr[pointNum] = {100,200,300,400,300,200,100,100,750};
    int yarr[pointNum] = {100,400,600,200,150,350,700,250,100};
    
    int intx, inty;
	for (int i = 0; i < pointNum; i++)
    {
        intx = xarr[i];
        inty = yarr[i];
        points.push_back(Point(intx, inty));
        setPix(array,intx,inty,1);
    }
    */
    //FIND LOWEST Y COORD
    /*
    int ind = 0;
    for(int i = 0; i < pointNum; i++)
    {
        if(points[i].getY() > points[ind].getY())
        {
            ind = i;
        }
        if(points[i].getY() == points[ind].getY() && points[i].getX() < points[ind].getX())
        {
            ind = i;
        }
    }
    */
   
    p0 = points[0];
    for(int i = 0; i < pointNum; i ++)
    {
        if(points[i].getY() < p0.getY())
        {
            p0 = points[i];
        }
        if(points[i].getY() == p0.getY() && points[i].getX() < p0.getX())
        {
            p0 = points[i];
        }
    }

    //SORT BY ANGLES
    //cout << "p0: " << p0.getX() << " " << p0.getY() << endl;
    sort(points.begin(),points.end(),compAngle);
    /*
    for(int i = 0; i < pointNum; i++)
    {
        cout << points[i].getX() << " " << points[i].getY() << endl;
    }
    */
    //SELECT FARTHEST POINTS FROM DUPLICATE ANGLES
    
    vector<Point> newPoints;
    newPoints.push_back(p0);
    for(int i = 1; i < pointNum; i ++)
    {
        while(i < pointNum-1 && clockwise(p0,points[i],points[i+1]) == 0)
        {
            i++;
        }
        newPoints.push_back(points[i]);
    }
    
    /*
    vector<Point> newPoints;
    newPoints.push_back(p0);
    vector<vector<Point>> eachAngle;
    for(int i = 1; i < pointNum; i++)
    {
        vector<Point> currAngle;
        if(clockwise(p0,points[i],points[i+1]) == 0)
        {
            while(i < pointNum -1 && clockwise(p0,points[i],points[i+1]) == 0)
            {
                currAngle.push_back(points[i]);
                //cout<< points[i].getX() << " " << points[i].getY() << endl;
            }
            eachAngle.push_back(currAngle);
        }
        else
        {
            currAngle.push_back(points[i]);
            eachAngle.push_back(currAngle);
        }
    }
    
    //cout << "out" << endl;
    double maxdist;
    Point maxPoint;
    for(int i = 0; i < eachAngle.size(); i++)
    {
        maxdist = -1;
        for(int j = 0; j < eachAngle[i].size(); j++)
        {
            if(p0.dist(eachAngle[i][j]) > maxdist)
            {
                maxdist = p0.dist(eachAngle[i][j]);
                maxPoint = eachAngle[i][j];
            }
        }
        newPoints.push_back(maxPoint);
    }
    /*
    cout << "out" << endl;
    
    for(int i = 0; i < pointNum; i ++)
    {
        cout << "point: " << newPoints[i].getX() << " " << newPoints[i].getY() << endl;
    }
    */
    stack<Point> pointStack;
    pointStack.push(newPoints[0]);
    pointStack.push(newPoints[1]);
    pointStack.push(newPoints[2]);
    vector<Point> borderPoints;
    Point m, temp;
    stack<Point> copy;
    for(int i = 3; i < newPoints.size(); i++)
    {
        while(clockwise(sec(pointStack), pointStack.top(), newPoints[i]) != -1)
        {
            pointStack.pop();
        }
        pointStack.push(newPoints[i]);
    }
    while (!pointStack.empty())
    {
        borderPoints.push_back(pointStack.top());
        pointStack.pop();
    }
    cout << "Border points:" << endl;
    for(int i = 0; i < borderPoints.size(); i++)
    {
        cout << borderPoints[i].getX() << " " << borderPoints[i].getY() << endl;
        setPix(array,borderPoints[i].getX(),borderPoints[i].getY(),2);
    }
    for(int i = 0; i < borderPoints.size()-1; i++)
    {
        bresen(borderPoints[i].getX(),borderPoints[i].getY(),borderPoints[i+1].getX(),borderPoints[i+1].getY(),array);
    }
    bresen(borderPoints[borderPoints.size()-1].getX(),borderPoints[borderPoints.size()-1].getY(),borderPoints[0].getX(),borderPoints[0].getY(),array);


    //PRINTING
    ofstream file;
    file.open("Project7_Output.ppm");
    file << "P3 800 800 1" << endl;
    
    string s1 = "1 1 1 ";
	string s3 = "0 0 0 ";
    string s2 = "0 0 1 ";
	for (int i = 0; i < 800; i++)
	{
		for (int j = 0; j < 800; j++)
		{
			if (array[i][j] == 1)
			{
				file << s1;
			}
			else if(array[i][j] == 2)
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