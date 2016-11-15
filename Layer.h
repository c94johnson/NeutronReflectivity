/*
	written by Connah Johnson		8th November 2016

	Header file containing the Layer class definition


*/

#include <string>
#include <vector>

#ifndef LAYER_H
#define LAYER_H

class LAYER
{
private:
	// declare a vector for each of the matrix elements at each data point
	// !!! could use a vector of vectors to store matrix of the data but may
	// be difficult to read and the reallocation of memory may be slower?
	std::vector< double > L_A, L_B, L_C, L_D, L_E, L_F, L_G, L_H;

	// declare vectors for the comulative matrix elements
	std::vector< double > L_CA, L_CB, L_CC, L_CD, L_CE, L_CF, L_CG, L_CH;

	// declare the layer properties
	double L_Nb, L_NbA, L_rough, L_thickness;

	// declare layer type: substrate, oil, protein, aqueous
	std::string L_type;


public:

	void SetMatrixElements(std::vector <double> _A, std::vector <double> _B, std::vector <double> _C, std::vector <double> _D, std::vector <double> _E, std::vector <double> _F, std::vector <double> _G, std::vector <double> _H);
	void SetLayerProperties(double _Nb, double _NbA, double _rough, double _thickness);
	void SetCumulativeElements(std::vector <double> _CA, std::vector <double> _CB, std::vector <double> _CC, std::vector <double> _CD, std::vector <double> _CE, std::vector <double> _CF, std::vector <double> _CG, std::vector <double> _CH);
	void SetLayerType(std::string _type);

	std::vector <double> GetA();
	std::vector <double> GetB();
	std::vector <double> GetC();
	std::vector <double> GetD();
	std::vector <double> GetE();
	std::vector <double> GetF();
	std::vector <double> GetG();
	std::vector <double> GetH();
	std::vector <double> GetCA();
	std::vector <double> GetCB();
	std::vector <double> GetCC();
	std::vector <double> GetCD();
	std::vector <double> GetCE();
	std::vector <double> GetCF();
	std::vector <double> GetCG();
	std::vector <double> GetCH();

	double GetNb();
	double GetNbA();
	double GetRough();
	double GetThickness();
	std::string GetLayerType();

	GetReflectivity();




};




#endif
