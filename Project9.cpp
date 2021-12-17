#include <iostream>
#include <iterator>
#include <array>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand, RAND_MAX */
using namespace std;
int main()
{
    //inputting file
    FILE* infile = fopen("beachinfile.ppm","r");
    int numx,numy;
    string s = "";
    int color = 0;
    fscanf(infile,"%s",&s);
    cout << s << endl;
    fscanf(infile,"%d",&numy);
    fscanf(infile,"%d",&numx);
    fscanf(infile,"%d",&color);
    cout << numx << " " << numy << " " << color << endl;

    //converting each rgb to grayscale
    int num = 0;
    int r,g,b = 0;
    vector <vector<int>> grayscale;
    for(int x = 0; x < numx; x ++)
    {
        vector<int> line;
        for(int y = 0; y < numy; y++)
        {
            fscanf(infile,"%d",&num);
            r = num;
            fscanf(infile,"%d",&num);
            g = num;
            fscanf(infile,"%d",&num);
            b = num;
            line.push_back(int((r+g+b)/3));
        }
        grayscale.push_back(line);
    }

    ofstream outfile;
    outfile.open("grayscale_infile.ppm");
    outfile << "P3 " << numy << " " << numx << " " << color << endl;
    for (int i = 0; i < numx; i ++)
    {
        for(int j = 0; j < numy; j ++)
        {
            outfile << grayscale[i][j]  << " " << grayscale[i][j]  << " " << grayscale[i][j]  << " ";
        }
        outfile << endl;
    }
    outfile.close();
    //sobel operator in x and y directions
    cout << "out" << endl;
    /*
    vector<vector<int>> gradientx = {};
    vector<vector<int>> gradienty = {};
    for(int i = 0; i < numx; i ++)
    {
        gradientx.push_back(new vector<int>());
        gradienty.push_back(new vector<int>());
    }
    */
    
    vector<vector<int>> gradientx (numx,vector<int>(numy,0));
    vector<vector<int>> gradienty (numx,vector<int>(numy,0));

    //int gradientx[numx][numy];
    //int gradienty[numx][numy];

    cout << "i1" << endl;
    /*
    gradientx = gradientx[0].insert(0,1,0);
    gradientx = gradientx[0].insert((numy-1),1,0);
    gradientx = gradientx[numx-1].insert(0,1,0);
    gradientx = gradientx[numx-1].insert((numy-1),1,0);
    */
/*
    gradientx[0][0] = 0;
    gradientx[0][numy-1] = 0;
    gradientx[numx-1][0] = 0;
    gradientx[numx-1][numy-1] = 0;
    
    cout << "i2" << endl;
    gradienty[0][0] = 0;
    gradienty[0][numy-1] = 0;
    gradienty[numx-1][0] = 0;
    gradienty[numx-1][numy-1] = 0;
    cout << "i3" << endl;
    */
    //cout << "2out" << endl;
    for (int i = 1; i < numx-1; i ++)
    {
        //cout << "in" << endl;
        for(int j = 1; j < numy-1; j ++)
        {
            //cout << "in for" << endl;
            /*
            gradientx[0][j] = 0;
            gradientx[i][0] = 0;
            gradienty[0][j] = 0;
            gradienty[i][0] = 0;
            */

            gradientx[i][j] = ((-1*grayscale[i-1][j-1]) + (-2*grayscale[i-1][j]) + (-1*grayscale[i-1][j+1]) \
                + grayscale[i+1][j-1] + (2*grayscale[i+1][j]) + grayscale[i+1][j+1]);

            gradienty[i][j] = ((grayscale[i-1][j-1]) + (-1*grayscale[i-1][j+1]) + (2*grayscale[i][j-1]) \
                + (-2*grayscale[i][j+1]) + (grayscale[i+1][j-1]) + (-1*grayscale[i+1][j+1]));
        }
    }

    cout << "out" << endl;
    //checking if gradient is above threshold and printing to outfile
    double thresh = 7;
    ofstream ofile;
    ofile.open("canny_output.ppm");
    ofile << "P3 " << numy << " " << numx << " " << 1 << endl;
    for (int i = 0; i < numx; i ++)
    {
        for(int j = 0; j < numy; j ++)
        {
            if(sqrt(gradientx[i][j]^2 + gradienty[i][j]^2) > thresh)
            {
                ofile << "1 1 1 ";
            }
            else
            {
                ofile << "0 0 0 ";
            }
            
        }
        ofile << endl;
    }
    ofile.close();

    //creating grayscale ppm
    /*
    */

    return 0;
}