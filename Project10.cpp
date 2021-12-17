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

#define PI 3.14159265
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
    cout << "checkpoint1: after grayscale" << endl;
    
    vector<vector<double>> gradientx (numx,vector<double>(numy,0));
    vector<vector<double>> gradienty (numx,vector<double>(numy,0));
    vector<vector<double>> gradienttotal (numx,vector<double>(numy,0));

    //int gradientx[numx][numy];
    //int gradienty[numx][numy];

    //cout << "2out" << endl;
    for (int i = 1; i < numx-1; i ++)
    {
        //cout << "in" << endl;
        for(int j = 1; j < numy-1; j ++)
        {

            gradientx[i][j] = (double)((-1*grayscale[i-1][j-1]) + (-2*grayscale[i-1][j]) + (-1*grayscale[i-1][j+1]) \
                + grayscale[i+1][j-1] + (2*grayscale[i+1][j]) + grayscale[i+1][j+1]);

            gradienty[i][j] = (double)((grayscale[i-1][j-1]) + (-1*grayscale[i-1][j+1]) + (2*grayscale[i][j-1]) \
                + (-2*grayscale[i][j+1]) + (grayscale[i+1][j-1]) + (-1*grayscale[i+1][j+1]));

            gradienttotal[i][j] = sqrt(gradientx[i][j]*gradientx[i][j] + gradienty[i][j]*gradienty[i][j]);
            //cout << i << " " << j << " " << gradienttotal[i][j] << endl;
        }
    }
    vector<vector<double>> originalgradient = gradienttotal;
    
    double minthresh = 40;
    double maxthresh = 80;
    for(int i = 0; i < numx; i++)
    {
        for(int j = 0; j < numy; j++)
        {
            if(gradienttotal[i][j] > maxthresh)
            {
                gradienttotal[i][j] = 1;
            }
            else if(gradienttotal[i][j] < minthresh)
            {
                gradienttotal[i][j] = 0;
            }
            else
            {
                gradienttotal[i][j] = (double)(gradienttotal[i][j]/color);
            }
            //cout << gradienttotal[i][j] << "\t";
        }
    }
    cout << "checkpoint2: after gradient calc" << endl;
    
    //IDENTIFYING DIRECTION BASED ON ANGLES
    double angle;
    
    vector<vector<double>> anglebox (numx,vector<double>(numy,0));
    for(int i = 0; i < numx; i++)
    {
        for(int j = 0; j < numy; j++)
        {
            //cout << "before atan" << endl;
            //cout << gradienty[i][j] << gradientx[i][j] << endl;
            angle = atan((double)(gradienty[i][j]/gradientx[i][j])) * 180 / PI;
            //cout << angle << endl;
            //cout << "after atan" << endl;
            if(angle >= 0 && angle < 45)
            {
                anglebox[i][j] = 0;
            }
            else if(angle >= 45 && angle < 90)
            {
                anglebox[i][j] = 1;
            }
            else if(angle >= 90 && angle < 135)
            {
                anglebox[i][j] = 2;
            }
            else if(angle >= 135 && angle < 180)
            {
                anglebox[i][j] = 3;
            }
            else if(angle >= 180 && angle < 225)
            {
                anglebox[i][j] = 4;
            }
            else if(angle >= 225 && angle < 270)
            {
                anglebox[i][j] = 5;
            }
            else if(angle >= 270 && angle < 315)
            {
                anglebox[i][j] = 6;
            }
            else if(angle >= 315 && angle <= 360)
            {
                anglebox[i][j] = 7;
            }
            else
            {
                anglebox[i][j] = 7;
            }
        }
    }
    cout << "checkpoint3: after anglebox" << endl;
    //FINDING NEIGHBORS OF SAME DIRECTION

    /*
    for(int i = 0; i < numx; i ++)
    {
        for(int j = 0; j < numy; j++)
        {
            cout << anglebox[i][j] << endl;
        }
    }
    */
    
    //NON MAX SUPPRESSION
    vector<vector<int>> nms_nbrs;
    vector<vector<int>> hys_nbrs;
    bool isMiddleIntensity = false;
    for(int i = 1; i < numx-1; i++)
    {
        for(int j = 1; j < numy-1; j++)
        {
            //cout << anglebox[i][j] << endl;
            isMiddleIntensity = 0 < gradienttotal[i][j] && gradienttotal[i][j] < 1;
            if(anglebox[i][j] == 0 || anglebox[i][j] == 4)
            {
                nms_nbrs.push_back({i,j-1});
                nms_nbrs.push_back({i,j+1});
                
                if(isMiddleIntensity)
                {
                    hys_nbrs.push_back({i+1,j});
                    hys_nbrs.push_back({i-1,j});
                }
                
            }
            if(anglebox[i][j] == 1 || anglebox[i][j] == 5)
            {
                nms_nbrs.push_back({i-1,j-1});
                nms_nbrs.push_back({i+1,j+1});
                
                if(isMiddleIntensity)
                {
                    hys_nbrs.push_back({i+1,j-1});
                    hys_nbrs.push_back({i-1,j+1});
                }
                
            }
            if(anglebox[i][j] == 2 || anglebox[i][j] == 6)
            {
                nms_nbrs.push_back({i-1,j});
                nms_nbrs.push_back({i+1,j});
                
                if(isMiddleIntensity)
                {
                    hys_nbrs.push_back({i,j-1});
                    hys_nbrs.push_back({i,j+1});
                }
                
            }
            if(anglebox[i][j] == 3 || anglebox[i][j] == 7)
            {
                nms_nbrs.push_back({i+1,j-1});
                nms_nbrs.push_back({i-1,j+1});
                
                if(isMiddleIntensity)
                {
                    hys_nbrs.push_back({i-1,j-1});
                    hys_nbrs.push_back({i+1,j+1});
                }
                
            }
            //cout << "after neighbor" << endl;
            //cout << anglebox[i][j] << endl;
            //find max of neighbors
            if(!(gradienttotal[i][j] > gradienttotal[nms_nbrs[0][0]][nms_nbrs[0][1]] && gradienttotal[i][j] > gradienttotal[nms_nbrs[1][0]][nms_nbrs[1][1]]))
            {
                gradienttotal[i][j] = 0;
            }
            
            if(0 < gradienttotal[i][j] && gradienttotal[i][j] < 1 && gradienttotal[hys_nbrs[0][0]][hys_nbrs[0][1]] > 0 && gradienttotal[hys_nbrs[1][0]][hys_nbrs[1][1]] > 0)
            {
                gradienttotal[i][j] = 1;
            }
            hys_nbrs = {};
            
            nms_nbrs = {};
        }
        hys_nbrs = {};
        nms_nbrs = {};
    }
    cout << "checkpoint 4: after non max supp" << endl;
    
    //HYSTERESIS
/*    for(int i = 1; i < numx-1; i++)
    {
        for(int j = 1; j < numy-1; j++)
        {
            //cout << gradienttotal[i][j] << "\t";
            if(0 < gradienttotal[i][j] && gradienttotal[i][j] < 1)
            {
                //cout << gradienttotal[i][j] << " ";
                if(anglebox[i][j] == 0 || anglebox[i][j] == 4)
                {
                    neighbors.push_back({i+1,j});
                    neighbors.push_back({i-1,j});
                }
                if(anglebox[i][j] == 1 || anglebox[i][j] == 5)
                {
                    neighbors.push_back({i+1,j-1});
                    neighbors.push_back({i-1,j+1});
                }
                if(anglebox[i][j] == 2 || anglebox[i][j] == 6)
                {
                    neighbors.push_back({i,j-1});
                    neighbors.push_back({i,j+1});
                }
                if(anglebox[i][j] == 3 || anglebox[i][j] == 7)
                {
                    neighbors.push_back({i-1,j-1});
                    neighbors.push_back({i+1,j+1});
                }
                //find max of neighbors
                cout << "!: " << gradienttotal[i][j] << " " << gradienttotal[neighbors[0][0]][neighbors[0][1]] << " " << gradienttotal[neighbors[1][0]][neighbors[1][1]] << " ";
                if(gradienttotal[neighbors[0][0]][neighbors[0][1]] > 0 && gradienttotal[neighbors[1][0]][neighbors[1][1]] > 0)
                {
                    gradienttotal[i][j] = 1;
                }
                
            }
            neighbors = {};
        }
    }
    */
    cout << "last checkpoint: after hysteresis" << endl;
    //printing to outfile
    ofstream ofile;
    ofile.open("canny_output.ppm");
    ofile << "P3 " << numy << " " << numx << " " << 1 << endl;
    for (int i = 0; i < numx; i ++)
    {
        for(int j = 0; j < numy; j ++)
        {
            if(gradienttotal[i][j] == 1)
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