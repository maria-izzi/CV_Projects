#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <math.h>
using namespace std;
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand, RAND_MAX */
#include <time.h>       /* time */

void fillRandom(double* arr)
{
	for (int i = 0; i < sizeof(arr); i++) arr[i] = (double)rand() / RAND_MAX;
	return;
}
void fillPixel(int** array, int x, int y)
{
	if (x < 800 && x >= 0 && y < 800 && y >= 0)
	{
		array[x][y] = 1;
	}
	//else
		//cout << "out of bounds";
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
			fillPixel(array, j, i);
		else
			fillPixel(array, i, j);
		if (e >= 0)
		{
			j += y;
			e -= dx;
		}
		e += dy;
	}
}
int main()
{
	int** array = new int* [800];
	for (int i = 0; i < 800; i++)
	{
		array[i] = new int[800];
	}
	ofstream file;
	file.open("output.ppm");
	file << "P3 800 800 1" << endl;
	//int points[3][2];
	//randomly selecting points and putting them into array
	srand(time(NULL));

	//filling array and drawing sides using bresenham
	double doublex[3];
	fillRandom(doublex);
	double doubley[3];
	fillRandom(doubley);
	int x[3];
	int y[3];
	for (int i = 0; i < 3; i++)
	{
		x[i] = doublex[i] * 800;
		y[i] = doubley[i] * 800;
		array[x[i]][y[i]] = 1;
	}
	/*x[0] = 536;
	y[0] = 44;
	x[1] = 700;
	y[1] = 569;
	x[2] = 727;
	y[2] = 632;*/
	bresen(x[0], y[0], x[1], y[1], array);
	bresen(x[1], y[1], x[2], y[2], array);
	bresen(x[0], y[0], x[2], y[2], array);
	/*int x1 = 100;
	int y1 = 200;
	int x2 = 300;
	int y2 = 100;
	array[x1][y1] = 1;
	array[x2][y2] = 1;
	drawsides(x1,y1,x2,y2, array);*/

	//drawing circles
	double len1 = sqrt(pow(x[1] - x[0], 2) + pow(y[1] - y[0], 2));
	double len2 = sqrt(pow(x[2] - x[1], 2) + pow(y[2] - y[1], 2));
	double len3 = sqrt(pow(x[2] - x[0], 2) + pow(y[2] - y[0], 2));
	//inscribed circle
	double peri = len1 + len2 + len3;
	double s = (peri) / 2;
	//double area = sqrt(s * (s - len1) * (s - len2) * (s - len3));
	double radius = sqrt(((s - len1) * (s - len2) * (s - len3)) / s);
	int xs, ys, xmax, y2, y2_new, ty;
	xmax = (int)(radius * 0.70710678); // maximum x at radius/sqrt(2)
	ys = radius;
	y2 = ys * ys;
	ty = (2 * ys) - 1;
	y2_new = y2;
	int incenterx = (x[2] * len1 + x[0] * len2 + x[1] * len3) / (peri);
	int incentery = (y[2] * len1 + y[0] * len2 + y[1] * len3) / (peri);
	//fillPixel(array, incenterx, incentery);
	//cout << "GOT TO INCENTER" << endl;
	for (xs = 0; xs <= xmax; xs++)
	{
		if ((y2 - y2_new) >= ty)
		{
			y2 -= ty;
			ys -= 1;
			ty -= 2;
		}
		//if (abs(xs)+ incenterx <= 800 && abs(ys)+ incentery <= 800)
		{
			fillPixel(array, incenterx + xs, incentery + ys);
			fillPixel(array, incenterx + xs, incentery - ys);
			fillPixel(array, incenterx - xs, incentery + ys);
			fillPixel(array, incenterx - xs, incentery - ys);
			fillPixel(array, incenterx + ys, incentery + xs);
			fillPixel(array, incenterx + ys, incentery - xs);
			fillPixel(array, incenterx - ys, incentery + xs);
			fillPixel(array, incenterx - ys, incentery - xs);
			/*array[incenterx + xs][incentery + ys] = 1;
			array[incenterx + xs][incentery - ys] = 1;
			array[incenterx - xs][incentery + ys] = 1;
			array[incenterx - xs][incentery - ys] = 1;
			array[incenterx + ys][incentery + xs] = 1;
			array[incenterx + ys][incentery - xs] = 1;
			array[incenterx - ys][incentery + xs] = 1;
			array[incenterx - ys][incentery - xs] = 1;*/
		}
		y2_new -= (2 * xs) - 3;
	}

	//CIRCUMCIRCLE
	double semi = peri / 2;
	double radius2 = (len1 * len2 * len3) / (4 * semi * radius);
	//cout << "radius: " << radius << endl;
	//double radius2 = (len1 * len2 * len3) / (sqrt((len1 + len2 + len3) * (len2 + len3 - len1) * (len3 + len1 - len2) * (len1 + len2 - len3)));
	double mid1x = (x[0] + x[1]) / 2;
	double mid1y = (y[0] + y[1]) / 2;
	double mid2x = (x[1] + x[2]) / 2;
	double mid2y = (y[1] + y[2]) / 2;
	double mid3x = (x[2] + x[0]) / 2;
	double mid3y = (y[2] + y[0]) / 2;
	/*cout << y[1] << " " << y[0] << " " << x[1] << " " << x[0]<<endl;
	cout << y[2] << " " << y[1] << " " << x[2] << " " << x[1]<<endl;
	cout << y[2] << " " << y[0] << " " << x[2] << " " << x[0]<<endl;
	cout << (y[1] - y[0]) << x[1] - x[0];
	cout << -1/((y[1] - y[0]) / (x[1] - x[0]));*/
	/*cout << mid1x << " " << mid1y << " " << mid2x << " " << mid2y <<" "<< mid3x << " " << mid3y << endl;
	cout << "GOT TO M1" << endl;*/
	double mm1 = ((double)((double)y[1] - y[0]) / ((double)x[1] - x[0]));
	double mm2 = ((double)((double)y[2] - y[1]) / ((double)x[2] - x[1]));
	double mm3 = ((double)((double)y[2] - y[0]) / ((double)x[2] - x[0]));

	double m1 = -1 / mm1;
	double m2 = -1 / mm2;
	double m3 = -1 / mm3;
	//cout << m1 << " " << m2 << " " << m3 << endl;

	double b1 = (-m1 * mid1x) + mid1y;
	double b2 = (-m2 * mid2x) + mid2y;
	double b3 = (-m3 * mid3x) + mid3y;

	int circumcenterx = (b2 - b1) / (m1 - m2);
	//int circumcentery = (m1*circumcenterx) + b1;
	int circumcentery = ((m2 * b1) - (m1 * b2)) / (m2 - m1);

	/*int part1 = (pow(x[0], 2) + pow(y[0], 2) - pow(x[1], 2) - pow(y[1], 2)) * (y[0] - y[2]);
	int part2 = (pow(x[0], 2) + pow(y[0], 2) - pow(x[2], 2) - pow(y[2], 2)) * (y[0] - y[1]);
	int part3 = (2 * (x[0] - x[1]) * (y[0] - y[2])) - (2 * (x[0] - x[2] * (y[0] - y[1])));

	int circumcenterx = (part1 - part2) / part3;

	part1 = (x[0] - x[1]) * (pow(x[0], 2) + pow(y[0], 2) - pow(x[2], 2) - pow(y[2], 2));
	part2 = (x[0] - x[2]) * (pow(x[0], 2) + pow(y[0], 2) - pow(x[1], 2) - pow(y[1], 2));
	part3 = (2 * (x[0] - x[1]) * (y[0] - y[2])) - (2 * (x[0] - x[2]) * (y[0] - y[1]));

	int circumcentery = (part1 - part2) / part3;*/
	//cout << "x: " << circumcenterx << " Y: " << circumcentery<<" R: "<<radius2<<endl;
	//array[circumcenterx][circumcentery] = 1;
	xmax = (int)(radius2 * 0.70710678); // maximum x at radius/sqrt(2)
	//cout << "radius ratio: " << double(radius / radius2)<<endl;
	ys = radius2;
	y2 = ys * ys;
	ty = (2 * ys) - 1;
	y2_new = y2;
	for (xs = 0; xs < xmax; xs++)
	{
		if ((y2 - y2_new) >= ty)
		{
			y2 -= ty;
			ys -= 1;
			ty -= 2;
		}
		//if (abs(xs) + circumcenterx <= 800 && abs(ys) + circumcentery <= 800)
		{
			fillPixel(array, circumcenterx + xs, circumcentery + ys);
			fillPixel(array, circumcenterx + xs, circumcentery - ys);
			fillPixel(array, circumcenterx - xs, circumcentery + ys);
			fillPixel(array, circumcenterx - xs, circumcentery - ys);
			fillPixel(array, circumcenterx + ys, circumcentery + xs);
			fillPixel(array, circumcenterx + ys, circumcentery - xs);
			fillPixel(array, circumcenterx - ys, circumcentery + xs);
			fillPixel(array, circumcenterx - ys, circumcentery - xs);
		}
		y2_new -= (2 * xs) - 3;
	}

	//9 POINT CIRCLE
	if (x[1] - x[0] != 0)
		mm1 = ((double)y[1] - (double)y[0]) / ((double)x[1] - (double)x[0]);
	else
		mm1 = 10000;
	if (x[2] - x[1] != 0)
		mm2 = ((double)y[2] - (double)y[1]) / ((double)x[2] - (double)x[1]);
	else
		mm2 = 10000;
	if (x[2] - x[0] != 0)
		mm3 = ((double)y[2] - (double)y[0]) / ((double)x[2] - (double)x[0]);
	else
		mm3 = 10000;

	if (mm1 != 0)
		m1 = -1 / mm1;
	else
		m1 = 10000;
	if (mm2 != 0)
		m2 = -1 / mm2;
	else
		m2 = 10000;
	if (mm3 != 0)
		m3 = -1 / mm3;
	else
		m3 = 10000;
	//cout << m1 << " " << m2 << " " << m3 << endl;

	b1 = (-m1 * x[2]) + y[2];
	b2 = (-m2 * x[0]) + y[0];
	b3 = (-m3 * x[1]) + y[1];

	double orthox = (b2 - b1) / (m1 - m2);
	double orthoy = ((m2 * b1) - (m1 * b2)) / (m2 - m1);

	int ninex = (orthox + circumcenterx) / 2;
	int niney = (orthoy + circumcentery) / 2;
	double radius3 = radius2 / 2;
	xmax = (int)(radius3 * 0.70710678); // maximum x at radius/sqrt(2)
	ys = radius3;
	y2 = ys * ys;
	ty = (2 * ys) - 1;
	y2_new = y2;
	for (xs = 0; xs < xmax; xs++)
	{
		if ((y2 - y2_new) >= ty)
		{
			y2 -= ty;
			ys -= 1;
			ty -= 2;
		}
		{
			fillPixel(array, ninex + xs, niney + ys);
			fillPixel(array, ninex + xs, niney - ys);
			fillPixel(array, ninex - xs, niney + ys);
			fillPixel(array, ninex - xs, niney - ys);
			fillPixel(array, ninex + ys, niney + xs);
			fillPixel(array, ninex + ys, niney - xs);
			fillPixel(array, ninex - ys, niney + xs);
			fillPixel(array, ninex - ys, niney - xs);
		}
		y2_new -= (2 * xs) - 3;
	}


	string s1 = "1 1 1 ";
	string s2 = "0 0 0 ";
	//printing image
	//cout << "GOT TO End" << endl;
	for (int i = 0; i < 800; i++)
	{
		for (int j = 0; j < 800; j++)
		{
			//cout << "in loop" << i << " " << j << endl;
			if (array[i][j] == 1)
			{
				//cout << "printed " << i << " " << j;
				file << s1;
				//file.flush();
			}
			else
			{
				//cout << "else" << endl;
				file << s2;
				//file.flush();
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
