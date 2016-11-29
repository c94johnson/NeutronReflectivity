// code to test the non-linear fitting technigue using mpfit
// Written by Connah Johnson 22nd November 2016

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include "plotTestFunctions.h"
#include "mpfit.h"

using namespace std;

int main()
{
	vector<vector<double> > vData;
    // determine the input file name
    cout<<"Please enter the name of the data file including the file extension. "<<endl;
    string InFileName;
    cin>>InFileName;

    // pass vector data by reference to readFile function, return the number of data points
    unsigned int m=readFile(vData, InFileName);

    // initial parameters
    unsigned int n = 5;
    // a, tau, phi, T, theta0
    vector <double> parameters [5] = {40,15,-0.5,15,10};

    vector < double > deviates;

    computeDeviates(vData, m, deviates);

    int status;
    mp_result result;
    double perror[5];
    memset(&result, 0, sizeof(result));
    result.xerror = perror;
    status = mpfit(myFunction,m, n, parameters, 0, 0, 0, &result);

    cout<<" testlinfit status = "<<status<<endl;
    cout<<"Fitted parameters:"<<endl;
    cout<<"a = "<<initialParameters[0]<<endl;
    cout<<"tau = "<<initialParameters[1]<<endl;
    cout<<"phi = "<<initialParameters[2]<<endl;
    cout<<"T = "<<initialParameters[3]<<endl;
    cout<<"theta0 = "<<initialParameters[4]<<endl;


	return 0;
}


void computeDeviates(vector< vector <double > >& _vData, unsigned int _m, vector <double>& _deviates)
{
	unsigned int counter=0;
	while (counter != m)
	{
		double deviate;
		deviate = (_vData[1][counter] - myFunction(vData[0][counter], _deviates))/_vData[2][counter]);
		_deviates.push_back(deviate);

		counter++;
	}
	return;
};

double myFunction(double _valueX, vector< double >& _parameters)
{
	double valueY;

	valueY = _parameters[4] + _parameters[0]*exp(_valueX/_parameters[1])*sin((2*PI*_valueX)/(_parameters[3]+_parameters[2]));

	return valueY;
};