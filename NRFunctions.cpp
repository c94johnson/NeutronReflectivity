/*
	written by Connah Johnson		8th November 2016

	using the "gnuplot_i.hpp" Copyright (c) 2013 Daniel Stahlke (dan@stahlke.org)
	requireing the BOOST library


	Software to plot data from Neutron Reflecivity measurements of a sample
	composed of up to three layers of protein adsorbed at an oil layer.

	File defining the function declared by the associated header file
	"NRFuntions.h"


*/

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include "gnuplot_i.hpp"
#include <conio.h>
#include <windows.h>
#include "NRFunctions.h"
#include "Data.h"
#include "Model.h"
#include "Layer.h"


unsigned int readFile(std::vector< std::vector< double > >& _data, std::string _InFileName)
{// read file and store .csv data values into vector arrays

    const char* name = _InFileName.c_str();
    std::vector <double> temp;

    unsigned int numberOfLines=0;
    std::ifstream infile(name);
    if(infile.is_open())
    {
        std::cout<<"Successfully opened the input file "<<_InFileName<<std::endl;
        std::string fileLine, entryS;
        double entryD;
        while(!infile.eof())
        {// while not at the end of the file and data still to be read
            getline(infile, fileLine);
            if(fileLine == " ")
            {// then at the end of the file
                break;
            };
            // find the delimiter from the start of the line stream
            unsigned int delimiterPos=0;
            while(delimiterPos != std::string::npos)
            {// extract the data into temp vector line by line
               delimiterPos=fileLine.find(',',0);
               if(delimiterPos == std::string::npos)
                {// read substring in fileLine string and then push back double onto temp vector
                    entryS = fileLine.substr(0, fileLine.size());
                    if(entryS != "\n")
                    {// entry not at the end of the file push double onto temp vector
                        entryD = atof(entryS.c_str());
                        temp.push_back(entryD);
                    };
                }else{
                    entryS = fileLine.substr(0, delimiterPos-0);
                    fileLine = fileLine.substr(delimiterPos+1, fileLine.size() - (delimiterPos+1));
                    if(entryS != "\n")
                    {
                        entryD = atof(entryS.c_str());
                        temp.push_back(entryD);
                    };
                };
               };
            // push vector temp data back onto  vector file data
            _data.push_back(temp);
            temp.clear();
            numberOfLines++;
        };
    infile.close();
    }else{
        // error has occurred
        std::cout<<"unable to open file "<<_InFileName<<std::endl;
        exit(1);
    };


    return numberOfLines;
};


void NumberOfLayers(MODEL& _Model)
{// enter the number of layers of layer type

    unsigned int _NoPL, _NoL;
    bool _IsOil;
    std::cout<<"Please enter the number of protein layers in the experimental sample? Maximum number is 3 layers. ";
    std::cin>>_NoPL;
    // layer count: substrate +numberPL + oil + aqueous
    _NoL=2+_NoPL;
    char choice;
    while(choice != 'y'||'n')
    {
    	std::cout<<"Is there an oil layer present? y/n ";
    	std::cin>>choice;
    	// if choice is y set oil layer to true add to number of layers
    	if(choice == 'y')
        {
        	_NoL++;
        	_IsOil = true;
    	}else{
    		_IsOil = false;
    	};
    };

    _Model.SetModel(_NoL,_NoPL,_IsOil);
    return;
}

void DetermineProperties(MODEL& _Model, std::vector <LAYER>& _Layers)
{// function to set the properties of each member of the vector of layers
	unsigned int _NoL = _Model.GetNoL();
	LAYER temp;

	unsigned int _layerCounter=0;

	double _Nb, _NbA, _rough, _thickness;
	while(_layerCounter != _NoL)
	{
		std::cout<<"Please enter the properties for layer "<<_layerCounter+1<<"."<<std::endl;
		std::string _type = "N/A";
		while(_type != "substrate"||"protein"||"oil"||"aqueous")
		{
			std::cout<<"Please enter the type of layer number "<<_layerCounter<<": (substrate, protein, oil, or aqueous)"<<std::endl;
			std::cin>>_type;
		};
		std::cout<<"Scattering Length Density (Nb or SLD)"<<std::endl;
		std::cin>>_Nb;
		std::cout<<"Absorption Cross Section density (NbA) = "<<std::endl;
        std::cin>>_NbA;
        std::cout<<"Root mean square roughness = "<<std::endl;
        std::cin>>_rough;
        std::cout<<"Layer Thickness = "<<std::endl;
        std::cin>>_thickness;

        temp.SetLayerType(_type);
        temp.SetLayerProperties(_Nb, _NbA, _rough, _thickness);

        _Layers.push_back(temp);

		_layerCounter++;
	};
	return;
};


/*

void ConvertQtoW(vector< vector< double > >& _inDataQ, vector< vector< double > >& _inDataW, unsigned int _NoP)
{



};

void ConvertWtoQ(vector< vector< double > >& _inDataW, vector< vector< double > >& _inDataQ, unsigned int _NoP)
{
	unsigned int _counter=0;
	while(_counter != _NoP)
	{


	}



};

*/

void MatixMethod(MODEL& _Model, DATA& _Data, std::vector <LAYER>& _Layers)
{
	// run the reflectance method, updating class objects
    unsigned int _counter=0;
    unsigned int _NoL = _Model.GetNoL();
    unsigned int _NoP = _Data.GetNoP();

    while((_counter =! _NoL-1))
    {// calculate the layer matrix elements on a layer by layer basis
        executeMatrixMethod( _Layers, _counter);
        calculateCumulativeReflectance(_Layers, _counter);
        _counter++;
    };
    Reflectivity();

};

void executeMatrixMethod(std::vector < LAYER >& _Layers, unsigned int _layerCounter)
{// calculate the layer reflectance matrix elements
    // accepts the layer number and the wavelength of the data point and executes the matrix method.  Updates the class layer and TotalReflectance objects
    _Nb1=_Layers[_layerCounter].GetNb();
    _Nb2=_Layers[_layerCounter+1].GetNb;
    _NbA=_Layers[_layerCounter].GetNbA();
    _Rough=_Layers[_layerCounter+1].GetRough();
    _d=_Layers[_layerCounter].GetThickness();
    //_stheta=layer[counter].stheta;

    //double wavelength=Data.dataX[dataPoint];

    double Atten=1;//Attenuation(double wavelength, double NbA, double _d, double _stheta);
    double Deb=1;//Debye(double wavelength,double _roughness, double _stheta);

    std::vector <double> _A,_B,_C,_D,_E,_F,_G,_H;
    if(_Nb1 == _Nb2)
    {// the two layers are not contrast matched
    	// GetA() returns a vector <double> with elements for each datapoint
        _A=_Layers[_layerCounter].GetA();
        _B=_Layers[_layerCounter].GetB();
        _C=_Layers[_layerCounter].GetC();
        _D=_Layers[_layerCounter].GetD();
        _E=_Layers[_layerCounter].GetE();
        _F=_Layers[_layerCounter].GetF();
        _G=_Layers[_layerCounter].GetG();
        _H=_Layers[_layerCounter].GetH();
        // need to apply factors to C,D,E,F as depend on reflectance
       /* _C=_C*Atten*Deb;
        _D=_D*Atten*Deb;
        _E=_E*Atten*Deb;
        _F=_F*Atten*Deb; */
    }else{
        // the layer isn't contrast matched to the substrate
    	// calculate new values on datpoint basis
    	_NoP = Data.GetNoP();
    	unsigned int dataPoint=0;
    	std::vector< std::vector <double> > _data = Data.GetInData();
    	while(dataPoint != _NoP)
    	{
    		double _Q = _data[0][dataPoint];
    		double _phase = phase(double _Q, double _Nb1, double _d);
        	double _reflectance = reflectance(double _Q, double _Nb1, double _Nb2);
        	_A[dataPoint]=cos(_phase);
        	_B[dataPoint]=sin(_phase);
        	_C[dataPoint]=_reflectance*Atten*Deb*cos(_phase);
        	_D[dataPoint]=_reflectance*Atten*Deb*sin(_phase);
        	_E[dataPoint]=_reflectance*Atten*Deb*cos(_phase);
        	_F[dataPoint]=-_reflectance*Atten*Deb*sin(_phase);
        	_G[dataPoint]=cos(_phase);
        	_H[dataPoint]=-sin(_phase);

        	dataPoint++;
    	};
    };
    // write to the layer object
    _Layers[_layerCounter].SetMatrixElements(_A,_B,_C,_D,_E,_F,_G,_H);
    return;
}

void calculateCumulativeReflectance(std::vector < LAYER >& _Layers, unsigned int _layerCounter)
{// determine the cumulative matrix element values

	std::vector <double> A,B,C,D,E,F,G,H;
	std::vector <double> Aold,Bold,Cold,Dold,Eold,Fold,Gold,Hold;
	std::vector <double> Anew,Bnew,Cnew,Dnew,Enew,Fnew,Gnew,Hnew
    Aold=_Layers[_layerCounter-1].GetCA();
    Bold=_Layers[_layerCounter-1].GetCB();
    Cold=_Layers[_layerCounter-1].GetCC();
    Dold=_Layers[_layerCounter-1].GetCD();
    Eold=_Layers[_layerCounter-1].GetCE();
    Fold=_Layers[_layerCounter-1].GetCF();
    Gold=_Layers[_layerCounter-1].GetCG();
    Hold=_Layers[_layerCounter-1].GetCH();

    A=_Layers[_layerCounter].GetA();
    B=_Layers[_layerCounter].GetB();
    C=_Layers[_layerCounter].GetC();
    D=_Layers[_layerCounter].GetD();
    E=_Layers[_layerCounter].GetE();
    F=_Layers[_layerCounter].GetF();
    G=_Layers[_layerCounter].GetG();
    H=_Layers[_layerCounter].GetH();

	unsigned int NoP = Data.GetNoP();
	unsigned int counter =0;
	while(counter != NoP)
	{
		Anew.push_back(Aold[counter]*A[counter] - Bold[counter]*B[counter] + Cold[counter]*E[counter] - Dold[counter]*F[counter]);
    	Bnew.push_back(Bold[counter]*A[counter] + Aold[counter]*B[counter] + Dold[counter]*E[counter] + Cold[counter]*F[counter]);
    	Cnew.push_back(Aold[counter]*C[counter] - Bold[counter]*D[counter] + Cold[counter]*G[counter] - Dold[counter]*H[counter]);
    	Dnew.push_back(Bold[counter]*C[counter] + Aold[counter]*D[counter] + Dold[counter]*G[counter] + Cold[counter]*H[counter]);
    	Enew.push_back(Eold[counter]*A[counter] - Fold[counter]*B[counter] + Gold[counter]*E[counter] - Hold[counter]*F[counter]);
    	Fnew.push_back(Fold[counter]*A[counter] + Eold[counter]*B[counter] + Gold[counter]*F[counter] + Hold[counter]*E[counter]);
    	Gnew.push_back(Eold[counter]*C[counter] - Fold[counter]*D[counter] + Gold[counter]*G[counter] - Hold[counter]*H[counter]);
    	Hnew.push_back(Fold[counter]*C[counter] + Eold[counter]*D[counter] + Hold[counter]*G[counter] + Gold[counter]*H[counter]);

		counter++;
	};

    //update the TotalReflectance object entries, done in this order so that
    //the new elements do not feedback into the calculations

    // write to the layer object
    _Layers[_layerCounter].SetCumulativeElements(Anew,Bnew,Cnew,Dnew,Enew,Fnew,Gnew,Hnew);
    return;
};

double phase(double _Q, double _Nb1, double _d)
{// the phase term for the interlayer interference

    double _incidentAngle = Data.GetAoI();
    double _stheta = sin(_incidentAngle);
    double _wavelength = 4*PI*_stheta/_Q
    return = (2*PI/_wavelength)*(1-0.5*pow(_wavelength,2)*_Nb1/PI)*_stheta*_d;
};

double reflectance(double _Q, double _Nb1,double _Nb2)
{// the fresnel reflectance
    double _reflectance;
    _reflectance = 4*PI*pow(_Q, -2)*(_Nb2-_Nb1);
    return _reflectance;
};

void Reflectivity()
{// calculate the model reflectivity and update modelY
    unsigned int _dataPoint=0;
    unsigned int _NoP = Data.NoP();
    unsigned int _finalLayer = Data.GetNoL()-1;
    std::vector <double> _A,_B,_E,_F;
    std::vector < std::vector <double> > modelData;
    std::vector <double> temp;
    std::vector <double> Qvector;
	std::vector< std::vector <double> > _data = Data.GetInData();

	while(dataPoint != _NoP)
    {
    	Qvector[dataPoint] = _data[0][dataPoint];

    	dataPoint++;
    };

    modelData.push_back(Qvector);

    _A=_Layers[_finalLayer].GetCA();
    _B=_Layers[_finalLayer].GetCB();
    _E=_Layers[_finalLayer].GetCE();
    _F=_Layers[_finalLayer].GetCF();

    while(_dataPoint =! _NoP)
    {// calculate the reflectivity from the CumulativeReflectance

    	Reflect.push_back((pow(_E[_dataPoint],2)+pow(F[_dataPoint],2))/(pow(A[_dataPoint],2)+pow(B[_dataPoint],2)));

        dataPoint++;
    };
    modelData.push_back(Reflect);

    // send the model data to the data class

    Data.SetModelData(modelData);

    return;
}

void keyPress()
{
    std::cout << "Press any key to continue..." << std::endl;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    _getch();
    return;
}

void graphDataErr(std::vector< std::vector< double > >& _data, std::string _InFileName, unsigned int _NumberOfPoints)
{
    // parse data onto the vectors dataX, dataY, dataE.
    std::vector< double > dataX, dataY, dataE;
    unsigned int counter=0;
    while(counter != _NumberOfPoints)
    {
        dataX.push_back(_data[counter][0]);
        dataY.push_back(_data[counter][1]);
        dataE.push_back(_data[counter][2]);
        counter++;
    };

    Gnuplot g1("lines");
    std::cout<<"Plotting data"<<std::endl;
    std::string titleMessage;
    std::string titleStart = "Plot of the data in file: ";
    titleMessage.append(titleStart);
    titleMessage.append(_InFileName);
    g1.set_title(titleMessage);
    g1.plot_xy_err(dataX,dataY,dataE,"File data with error bars");
    g1.unset_title();
    g1.showonscreen();

    keyPress();
    return;
}

void graphModel(std::vector< std::vector< double > >& _modelData, unsigned int _NumberOfPoints)
{
	std::vector<double> dataX, dataY;
	unsigned int counter=0;
    while(counter != _NumberOfPoints)
    {
        dataX.push_back(_modelData[counter][0]);
        dataY.push_back(_modelData[counter][1]);
        counter++;
    };

    Gnuplot g2("lines");
    std::cout<< "Plotting model"<<std::endl;
    std::string titleMessage;
    titleMessage = "Plot of the model reflectivity data.";
    g2.set_title(titleMessage);
    g2.plot_xy(dataX,dataY,"Reflectivity");
    g2.unset_title();
    g2.showonscreen();

    keyPress();
    return;
}
