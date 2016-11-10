/*
	written by Connah Johnson		8th November 2016

	File containing the Model class functions
*/

#include "Model.h"
#include <vector>
#include <string>

// setter methods

void Model::SetModel(unsigned int _NoL, unsigned int NoPL, bool _IsOil, string _OutFilename)
{
	M_NoL = _NoL;
	M_NoPL = _NoPL;
	M_IsOil = _IsOil;


}

void Model::SetOutFilename(string _OutFilename)
{
	M_outFilename = _OutFilename;
}
// getter methods

unsigned int Model::GetNoL()
{
	return M_NoL;
}

unsigned int Model::GetNoPL()
{
	return M_NoPL;
}

bool Model::GetIsOil()
{
	return M_IsOil;
}

string Model::GetOutFilename()
{
	return M_outFilename;
}