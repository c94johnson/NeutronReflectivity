/*
	written by Connah Johnson		8th November 2016

	Header file containing the Data class definition


*/
#include <string>
#include <vector>

#ifndef DATA_H
#define DATA_H

class Data
{
private:

	std::string D_filename;

	std::vector< std::vector <double> > D_inData;
	//std::vector <double>  D_QData;
	//std::vector <double>  D_WData;
	std::vector< std::vector <double> > D_modelData;

	unsigned int D_NoP;

	bool D_dataType; // if true true then data is in Q form

	double D_AoI;



public:

	GetFilename();
	GetInData();
	GetNoP();
	GetDataType();
	GetAoI();
	GetModelData();
	//GetQData();
	//GetWData();


	SetData(std::vector< std::vector<double> >& _inData, unsigned int _NoP, std::string _fileName, bool _dataType, double _AoI);
	SetModelData(std::vector< std::vector<double> >& _modelData);
	//SetQData(std::vector <double>& _QData);
	//SetWData(std::vector <double>& _WData);


};




#endif
