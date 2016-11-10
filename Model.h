/*
	written by Connah Johnson		8th November 2016

	Header file containing the Model class definition


*/

#ifndef MODEL_H
#define MODEL_H

class Model
{
private:
	unsigned int M_NoL; // number of layers in sample
	unsigned int M_NoPL; // number of protein layers in the model of the sample
	bool M_IsOil; // true if oil layer is present
	string M_OutFilename; // the filename for the output model data

	bool M_IsOil; // true if an oil layer is present after substrate

public:

	GetNoL();
	GetNoPL();
	GetIsOil();
	GetOutFilename();


	SetModel(unsigned int _NoL, unsigned int NoPL, bool _IsOil);
	SetOutFilename(string _outFilename);
}




#endif
