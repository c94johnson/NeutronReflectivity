/*
	written by Connah Johnson		8th November 2016

	using the "gnuplot_i.hpp" Copyright (c) 2013 Daniel Stahlke (dan@stahlke.org)
	requiring the BOOST library


	Software to plot data from Neutron Reflectivity measurements of a sample
	composed of up to three layers of protein adsorbed at an oil layer.

	FUnctions stored in NRFUnctions.cpp with associated header file
	NRFunctions.h

	Modelling Assumptions:
    -substrate and aqueous layer assumed
    -constant angle of incidence at each layer
    -assuming measurements are taken at one angle of incidence
    -non-complex refraction angle
    -classical wavelike description of neutron
    -thermal neutrons
    -homogenous sample layers
    -born approximation

    Plotting Assumptions:
    -windows 32
    -gnuplot.exe.located at "C:/Program Files/gnuplot/bin/"
    -comma separated file on entry with three data columns: X, Y, Error in Y
    -data in format of Q or wavelength, Reflectivity, and error in Reflectivity
    -data file is located within the project directory

	Method:
	-Abeles matrix method
	-summation of reflectances from each of the sample layers
*/

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include "NRFunctions.h"
#include "Data.h"
#include "Layer.h"
#include "Model.h"

#define _PI 3.14159265

using namespace std;

int main()
{
    //define objects of classes
    DATA Data;
    MODEL Model;

	//------------------------------------------------------------------//
	//							Input Data 								//
	//------------------------------------------------------------------//

	cout<<"Please enter the name of the data file including the file extension. "<<endl;
    string InFileName;
    cin>>InFileName;

    vector< vector<double> > inData; // pass by reference
    // readFile takes in address of the inData vector and updates values, NoP is the number of data points
	unsigned int NoP = readFile(inData, InFileName);

    cout<<"Please enter the angle of incidence in degrees: "<<endl;
    double AoI;
    cin>>AoI;

    bool dataType;
    char choice;
    while(choice != Q||W)
    {   // while choice isn't Q or wavelength
    	cout<<"Is the data in [Q] or [W]avelength form? [Q/W] "<<endl;
    	cin>>choice;
    };
    if(choice == "Q")
    {	// data is in Q form
    	dataType = true;

    }else{dataType=false;};

    // send the information to the Data class object
	Data.SetData(inData, NoP, InFileName, dataType, AoI);

	//------------------------------------------------------------------//
	//					   	 Model Parameters 							//
	//------------------------------------------------------------------//


	NumberOfLayers();
	vector <LAYER> Layers;
	DetermineProperties(Layers);
	// now have the number of layers and the properties of each layer are
	// store in a vector of the layer class. Size of vector Layers is NoL.

	//------------------------------------------------------------------//
	//						   Execute Method 							//
	//------------------------------------------------------------------//
   /* if(choice == "Q")
    {	// data is in Q form
    	dataType = true;
    	inDataQ = inData;
    	ConvertQtoW(inDataQ, inDataW, NoP);


    }else{
    	// data is in wavelength form
    	dataType=false;
    	inDataW = inData;
    	ConvertWtoQ(inDataW, inDataQ, NoP);

    };

*/
	MatrixMethod(Model, Data, Layers);
	// here the data fpor the model is stored in Data class object




	//------------------------------------------------------------------//
	//							    Output								//
	//------------------------------------------------------------------//


	graphDataErr(Data.GetInData(), Data.GetFilename() ,Data.GetNoP());
	graphModel(Data.GetModelData(), Data.GetNoP());




return 0;
}
