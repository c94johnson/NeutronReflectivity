/*
	written by Connah Johnson		8th November 2016

	File containing the Layer class functions
*/

#include "Layer.h"
#include <vector>
#include <string>



// setter methods

void Layer::SetMatrixElements(double _A, double _B, double _C, double _D, double _E, double _F, double _G, double _H)
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
	
void Layer::SetLayerProperties(double _Nb, double _NbA, double _rough, double _thickness)
{
	L_Nb = _Nb;
	L_NbA = _NbA;
	L_rough = _rough;
	L_thickness = _thickness;
}

void Layer::SetCumulativeElements(double _CA, double _CB, double _CC, double _CD, double _CE, double _CF, double _CG, double _CH)
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


void Layer::SetLayerType(string _type)
{
	L_type = _type;
}

// getter methods


std::vector <double> Layer::GetA()
{
	return L_A;
}

std::vector <double> Layer::GetB()
{
	return L_B;
}

std::vector <double> Layer::GetC()
{
	return L_C;
}

std::vector <double> Layer::GetD()
{
	return L_D;
}

std::vector <double> Layer::GetE()
{
	return L_E;
}

std::vector <double> Layer::GetF()
{
	return L_F;
}

std::vector <double> Layer::GetG()
{
	return L_G;
}

std::vector <double> Layer::GetH()
{
	return L_H;
}

std::vector <double> Layer::GetCA()
{
	return L_CA;
}

std::vector <double> Layer::GetCB()
{
	return L_CB;
}

std::vector <double> Layer::GetCC()
{
	return L_CC;
}

std::vector <double> Layer::GetCD()
{
	return L_CD;
}

std::vector <double> Layer::GetCE()
{
	return L_CE;
}

std::vector <double> Layer::GetCF()
{
	return L_CF;
}

std::vector <double> Layer::GetCG()
{
	return L_CG;
}

std::vector <double> Layer::GetCH()
{
	return L_CH;
}

double Layer::GetNb()
{
	return L_Nb;
}

double Layer::GetNbA()
{
	return L_NbA;
}

double Layer::GetRough()
{
	return L_rough;
}

double LAyer::GetThickness()
{
	return L_thickness;
}

string Layer::GetLAyerType()
{
	return L_type;
}