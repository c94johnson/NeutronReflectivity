/*
	written by Connah Johnson		8th November 2016

	File containing the Model class functions
*/

#include "Model.h"
#include <vector>
#include <string>

// setter methods

void MODEL::SetModel(unsigned int _NoL, unsigned int _NoPL, bool _IsOil)
{
	M_NoL = _NoL;
	M_NoPL = _NoPL;
	M_IsOil = _IsOil;


}

void MODEL::SetOutFilename(std::string _OutFilename)
{
	M_OutFilename = _OutFilename;
}
// getter methods

unsigned int MODEL::GetNoL()
{
	return M_NoL;
}

unsigned int MODEL::GetNoPL()
{
	return M_NoPL;
}

bool MODEL::GetIsOil()
{
	return M_IsOil;
}

std::string MODEL::GetOutFilename()
{
	return M_OutFilename;
}
