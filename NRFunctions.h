/*	written by Connah Johnson		8th November 2016

	using the "gnuplot_i.hpp" Copyright (c) 2013 Daniel Stahlke (dan@stahlke.org)
	requiring the BOOST library


	Software to plot data from Neutron Reflectivity measurements of a sample
	composed of up to three layers of protein adsorbed at an oil layer.

	Header file containing the declarations for the functions defined in
	"NRFunctions.cpp".

*/

#include <string>
#include <vector>
#include "Layer.h"
#include "Data.h"
#include "Model.h"

#ifndef NRFUNCTIONS_H
#define NRFUNCTIONS_H


unsigned int readFile(std::vector< std::vector< double > >& _data, std::string _InFileName);
void NumberOfLayers(MODEL& _Model);
void DetermineProperties(MODEL& _Model, std::vector <LAYER>& _Layers);
void MatixMethod(MODEL& _Model, std::vector <double>& _Layers);
void executeMatrixMethod(std::vector < LAYER >& _Layers, unsigned int _layerCounter);
void calculateCumulativeReflectance(std::vector < double >& _Layers, unsigned int _layerCounter);
double phase(double _Q, double _Nb1, double _d);
double reflectance(double _Q, double _Nb1,double _Nb2);
void Reflectivity();
void graphDataErr(std::vector< std::vector< double > >& _data, std::string _InFileName, unsigned int _NumberOfPoints);
void graphModel(std::vector< std::vector< double > >& _modelData, unsigned int _NumberOfPoints);



#endif //NRFUNCTIONS_H
