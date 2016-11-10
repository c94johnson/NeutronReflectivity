/*
	written by Connah Johnson		8th November 2016

	Header file containing the Layer class definition


*/

#ifndef LAYER_H
#define LAYER_H

class Layer
{
private:
	// declare a vector for each of the matrix elements at each data point
	// !!! could use a vector of vectors to store matrix of the data but may
	// be difficult to read and the reallocation of memory may be slower?
	std::vector< double > L_A, L_B, L_ C, L_D, L_E, L_F, L_G, L_H;

	// declare vectors for the comulative matrix elements
	std::vector< double > L_CA, L_CB, L_CC, L_CD, L_CE, L_CF, L_CG, L_CH;

	// declare the layer properties
	double L_Nb, L_NbA, L_rough, L_thickness;

	// declare layer type: substrate, oil, protein, aqueous
	string L_type;


public:

	SetMatrixElements(std::vector <double> _A, std::vector <double> _B, std::vector <double> _C, std::vector <double> _D, std::vector <double> _E, std::vector <double> _F, std::vector <double> _G, std::vector <double> _H);
	SetLayerProperties(double _Nb, double _NbA, double _rough, double _thickness);
	SetCumulativeElements(std::vector <double> _CA, std::vector <double> _CB, std::vector <double> _CC, std::vector <double> _CD, std::vector <double> _CE, std::vector <double> _CF, std::vector <double> _CG, std::vector <double> _CH);
	SetLayerType(string _type);
	
	GetA();
	GetB();
	GetC();
	GetD();
	GetE();
	GetF();
	GetG();
	GetH();
	GetCA();
	GetCB();
	GetCC();
	GetCD();
	GetCE();
	GetCF();
	GetCG();
	GetCH();

	GetNb();
	GetNbA();
	GetRough();
	GetThickness();
	GetLayerType();

	GetReflectivity();




}




#endif
