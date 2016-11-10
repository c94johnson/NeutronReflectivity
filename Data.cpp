/*
	written by Connah Johnson		8th November 2016

	File containing the Data class functions
*/


#include "Data.h"
#include <vector>
#include <string>


// setter methods


void Data::SetData(std::vector< std::vector<double> >& _inData, unsigned int _NoP, std::string _filename, bool _dataType, double _AoI)
{
	D_inData = _inData;
	D_NoP = _NoP;
	D_filename = _filename;
	D_dataType = _dataType;
	D_AoI = _AoI;
}

void Data::SetModelData(std::vector< std::vector<double> >& _modelData)
{
	D_modelData = _modelData;

};
/*
void Data::SetQData(std::vector <double>& _QData)
{
	D_QData = _QData;
};


void Data::SetWData(std::vector <double>& _WData)
{
	D_WData = _WData;
};
*/
// getter methods

std::string Data::GetFilename()
{
	return D_filename;
};

// is this sending the vector object or the reference address of ???
std::vector< std::vector< double > > Data::GetInData()
{
	return D_inData;
};

unsigned int Data::GetNoP()
{
	return D_NoP;
};

bool Data::GetDataType()
{
	return D_dataType;
};

double Data::GetAoI()
{
	return D_AoI;
};

std::vector< std::vector< double > > Data::GetModelData()
{
	return D_modelData;
};

/*
std::vector< double > GetQData()
{
	return D_QData;
}

std::vector< double > GetWData()
{
	return D_WData;
}

*/
