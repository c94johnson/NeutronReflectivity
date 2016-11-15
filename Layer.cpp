/*
	written by Connah Johnson		8th November 2016

	File containing the Layer class functions
*/

#include "Layer.h"
#include <vector>
#include <string>



// setter methods

void LAYER::SetMatrixElements(std::vector <double> _A, std::vector <double> _B, std::vector <double> _C, std::vector <double> _D, std::vector <double> _E, std::vector <double> _F, std::vector <double> _G, std::vector <double> _H)
{
	L_A = _A;
	L_B = _B;
	L_C = _C;
	L_D = _D;
	L_E = _E;
	L_F = _F;
	L_G = _G;
	L_H = _H;
}

void LAYER::SetLayerProperties(double _Nb, double _NbA, double _rough, double _thickness)
{
	L_Nb = _Nb;
	L_NbA = _NbA;
	L_rough = _rough;
	L_thickness = _thickness;
}

void LAYER::SetCumulativeElements(std::vector <double> _CA, std::vector <double> _CB, std::vector <double> _CC, std::vector <double> _CD, std::vector <double> _CE, std::vector <double> _CF, std::vector <double> _CG, std::vector <double> _CH)
{
	L_CA = _CA;
	L_CB = _CB;
	L_CC = _CC;
	L_CD = _CD;
	L_CE = _CE;
	L_CF = _CF;
	L_CG = _CG;
	L_CH = _CH;
}


void LAYER::SetLayerType(std::string _type)
{
	L_type = _type;
}

// getter methods


std::vector <double> LAYER::GetA()
{
	return L_A;
}

std::vector <double> LAYER::GetB()
{
	return L_B;
}

std::vector <double> LAYER::GetC()
{
	return L_C;
}

std::vector <double> LAYER::GetD()
{
	return L_D;
}

std::vector <double> LAYER::GetE()
{
	return L_E;
}

std::vector <double> LAYER::GetF()
{
	return L_F;
}

std::vector <double> LAYER::GetG()
{
	return L_G;
}

std::vector <double> LAYER::GetH()
{
	return L_H;
}

std::vector <double> LAYER::GetCA()
{
	return L_CA;
}

std::vector <double> LAYER::GetCB()
{
	return L_CB;
}

std::vector <double> LAYER::GetCC()
{
	return L_CC;
}

std::vector <double> LAYER::GetCD()
{
	return L_CD;
}

std::vector <double> LAYER::GetCE()
{
	return L_CE;
}

std::vector <double> LAYER::GetCF()
{
	return L_CF;
}

std::vector <double> LAYER::GetCG()
{
	return L_CG;
}

std::vector <double> LAYER::GetCH()
{
	return L_CH;
}

double LAYER::GetNb()
{
	return L_Nb;
}

double LAYER::GetNbA()
{
	return L_NbA;
}

double LAYER::GetRough()
{
	return L_rough;
}

double LAYER::GetThickness()
{
	return L_thickness;
}

std::string LAYER::GetLayerType()
{
	return L_type;
}
