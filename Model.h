/*
	written by Connah Johnson		8th November 2016

	Header file containing the Model class definition


*/

#include <string>
#include <vector>

#ifndef MODEL_H
#define MODEL_H

class MODEL
{
private:
	unsigned int M_NoL; // number of layers in sample
	unsigned int M_NoPL; // number of protein layers in the model of the sample
	bool M_IsOil; // true if oil layer is present
	std::string M_OutFilename; // the filename for the output model data

public:

	unsigned int GetNoL();
	unsigned int GetNoPL();
	bool GetIsOil();
	std::string GetOutFilename();


	void SetModel(unsigned int _NoL, unsigned int NoPL, bool _IsOil);
	void SetOutFilename(std::string _OutFilename);
};




#endif
