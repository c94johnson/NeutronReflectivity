// plotTest.cpp
/*
    Connah Johnson 07/11/2016

    To test the interface between c++ code and the gnuplot library,
    reading data from a .csv file and plotting the graph.

    Asumptions:
    -comma separated file on entry with three data columns: X, Y, Error in Y
    -data file is located within the project directory
*/

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>

#include <conio.h>
#include <windows.h>
#include "plotTestFunctions.h"

using namespace std;



int main()
{

    vector<vector<double> > vData;
    // determine the input file name
    cout<<"Please enter the name of the data file including the file extension. "<<endl;
    string InFileName;
    cin>>InFileName;

    // pass vector data by reference to readFile function, return the number of data points
    unsigned int NoP=readFile(vData, InFileName);

    graphData(vData, InFileName, NoP);


    return 0;
}
