// Project7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <stdio.h>  /* printf, scanf, puts, NULL */
#include <stdlib.h> /* srand, rand, RAND_MAX */
#include <time.h>   /* time */
#include <array>
#include <chrono>
#include <set>
#include <vector>
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
vector<Point> border;
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
double distFromLine(Point p, Point end1, Point end2)
{
    return ((p.getY() - end1.getY()) * (end2.getX() - end1.getX()) - (end2.getY() - end1.getY()) * (p.getX() - end1.getX()));
}
int side(Point p, Point end1, Point end2)
{
    double dist = distFromLine(p,end1,end2);
    if(dist > 0)
    {
        return 1;
    }
    else if (dist < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
    
}
void hull(vector<Point> points, Point endleft, Point endright)
{
    if(points.size() == 0)
    {
        border.push_back(endleft);
        border.push_back(endright);
        return;
    }
    double maxdist = -1;
    Point maxpoint;
    for(int i = 0; i < points.size(); i++)
    {
        int dist = distFromLine(points[i],endleft,endright);
        if(abs(dist) > maxdist)
        {
            maxdist = abs(dist);
            maxpoint = points[i];
        }
    }
    
    if(maxdist == -1)
    {
        border.push_back(endleft);
        border.push_back(endright);
        return;
    }
    
    vector<Point> s1;
    vector<Point> s2;
    for(int i = 0; i < points.size(); i ++)
    {
        if(side(points[i],maxpoint,endleft) != side(endright,maxpoint,endleft))
        {
            s1.push_back(points[i]);
        }
        if(side(points[i],maxpoint,endright) != side(endleft,maxpoint,endright))
        {
            s2.push_back(points[i]);
        }
    }
    hull(s1, endleft, maxpoint);
    hull(s2, maxpoint, endright);
    /*
    
    double maxdist = -1;
    Point maxpoint;
    for(int i = 0; i < points.size(); i++)
    {
        int dist = distFromLine(points[i],endleft,endright);
        if(side(points[i],endleft,endright) == currside && abs(dist) > maxdist)
        {
            maxdist = abs(dist);
            maxpoint = points[i];
        }
    }
    if(maxdist == -1)
    {
        border.push_back(endleft);
        border.push_back(endright);
        return;
    }
    hull(points, pointNum, maxpoint,endleft, -side(endright,maxpoint,endleft));
    hull(points, pointNum, maxpoint,endright, -side(endleft,maxpoint,endright));
    */
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
    
    //ADD POINTS TO INITIAL ARRAY
    /*
	int xarr[pointNum] = {100,400,700,100,400,700,100,400,700};
	int yarr[pointNum] = {100,100,100,400,400,400,700,700,700};
    
    int intx, inty;
	for (int i = 0; i < pointNum; i++)
    {
        intx = xarr[i];
        inty = yarr[i];
        points.push_back(Point(intx, inty));
        setPix(array,intx,inty,1);
    }
    */
    //MIN AND MAX X VALS
    sort(points.begin(),points.end(),compX);
    Point mostLeft = points[0];
    Point mostRight = points[pointNum-1];
    //border.push_back(mostLeft);
    //border.push_back(mostRight);
    vector<Point> r;
    vector<Point> l;
    for(int i = 0; i < pointNum; i ++)
    {
        if(side(points[i],mostLeft,mostRight) > 0)
        {
            r.push_back(points[i]);
        }
        else if(side(points[i],mostLeft,mostRight) < 0)
        {
            l.push_back(points[i]);
        }
    }
    hull(r, mostLeft, mostRight);
    hull(l, mostLeft, mostRight);

    for(int i = 0; i < border.size(); i++)
    {
        setPix(array,border[i].getX(),border[i].getY(),2);
        //cout << border[i].getX() << " " << border[i].getY() << endl;
    }
    p0 = mostLeft;
    sort(border.begin(),border.end(),compAngle);
    for(int i = 0; i < border.size()-1; i++)
    {
        if(border[i].dist(border[i+1]) > 0)
        {
            bresen(border[i].getX(),border[i].getY(),border[i+1].getX(),border[i+1].getY(),array);
        }
    }
    bresen(border[border.size()-1].getX(),border[border.size()-1].getY(),border[0].getX(),border[0].getY(),array);
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