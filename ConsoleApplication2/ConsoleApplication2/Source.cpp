/*

01st November 2016 by Connah Johnson + Sean Ruane 

Programme calculating the total refelctivity of neutrons from a
sample cell composed of substrate and aqueous layers with up to 3
layers of protein and the addition of an oil layer.  This is done
through combining the reflectivities of each layer accounting for
absorption and interference between layers.

Assumptions:
- neutron behaves as a wave
- the angle of incidence at each surface is equal to the angle of
incidence to the sample
- maximum of three layers of protein
- data is in format Q or Lambda, R, error in R

*/

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>

#define PI 3.14159265
using namespace std;

//Mathematical structures
class matrix
{
public:
	//Matrix members
	double A, B,    C, D;
	double E, F,    G, H;

	//Constructors
	matrix() :A(0), B(0), C(0), D(0), E(0), F(0), G(0), H(0) {}
	matrix(double _A, double _B, double _C, double _D, double _E, double _F, double _G, double _H) :A(_A), B(_B), C(_C), D(_D), E(_E), F(_F), G(_G), H(_H) {}

	//Performs matrix method and updates matrix
	void reflect(matrix _matrix)
	{
		double Anew = A*_matrix.A - B*_matrix.B + C*_matrix.E - D*_matrix.F;
		double Bnew = B*_matrix.A + A*_matrix.B + D*_matrix.E + C*_matrix.F;
		double Cnew = A*_matrix.C - B*_matrix.D + C*_matrix.G - D*_matrix.H;
		double Dnew = B*_matrix.C + A*_matrix.D + D*_matrix.G + C*_matrix.H;
		double Enew = E*_matrix.A - F*_matrix.B + G*_matrix.E - H*_matrix.F;
		double Fnew = F*_matrix.A + E*_matrix.B + G*_matrix.F + H*_matrix.E;
		double Gnew = E*_matrix.C - F*_matrix.D + G*_matrix.G - H*_matrix.H;
		double Hnew = F*_matrix.C + E*_matrix.D + H*_matrix.G + G*_matrix.H;
		A = Anew; B = Bnew; C = Cnew; D = Dnew; E = Enew; F = Fnew; G = Gnew; H = Hnew;
	}
	//Performs matrix method and returns new matrix.
	matrix mreflect(matrix _matrix)
	{
		double Anew = A*_matrix.A - B*_matrix.B + C*_matrix.E - D*_matrix.F;
		double Bnew = B*_matrix.A + A*_matrix.B + D*_matrix.E + C*_matrix.F;
		double Cnew = A*_matrix.C - B*_matrix.D + C*_matrix.G - D*_matrix.H;
		double Dnew = B*_matrix.C + A*_matrix.D + D*_matrix.G + C*_matrix.H;
		double Enew = E*_matrix.A - F*_matrix.B + G*_matrix.E - H*_matrix.F;
		double Fnew = F*_matrix.A + E*_matrix.B + G*_matrix.F + H*_matrix.E;
		double Gnew = E*_matrix.C - F*_matrix.D + G*_matrix.G - H*_matrix.H;
		double Hnew = F*_matrix.C + E*_matrix.D + H*_matrix.G + G*_matrix.H;
		return matrix(Anew, Bnew, Cnew, Dnew, Enew, Fnew, Gnew, Hnew);
	}

};

double QToLambda(const double _Q, const double _incidentAngle) {
	return 4 * PI*sin(_incidentAngle) / _Q;
};

double lambdaToQ(const double _L, const double _incidentAngle) {
	return 4 * PI*sin(_incidentAngle) / _L;
};


//Layers and workspace.

class material
{
	//Members
	double Nb, Na;
	string name;

public:
	//Accessors
	double getNa() { return Na; }
	double getNb() { return Nb; }
	string getname() { return name; }
	//Mutators
	void setNa(const double _Na) { Na = _Na; }
	void setNb(const double _Nb) { Nb = _Nb; }
	void setname(string _name) { name = _name; }
	//Display
	//Constructors
	material() : Na(0), Nb(0), name("Default") { cout << "Constructing Default Material" << endl; }
	material(double _Na, double _Nb, string _name) : Na(_Na), Nb(_Nb), name(_name) { cout << "Constructing Material "<<name<<endl; }
	~material() { cout << "Destroying " << name << endl; }
};

class layer : public material
{
	//Members
	double thickness, roughness, Stheta;
public:
	//Accessors
	double getthickness() { return thickness; }
	double getroughness() { return roughness; }
	double getStheta() { return Stheta; }
	//Mutators
	void setthickness(const double _thickness) { thickness = _thickness; }
	void setroughness(const double _roughness) { roughness = _roughness; }
	void setStheta(const double _Stheta) { Stheta=_Stheta; }
	//Display
	string string()// Return aa string with the later information.
	{
		stringstream stream;
		stream << getname() << "(" << getNa() << "," << getNb() << ") T = " << getthickness()<< ", R = " << getroughness() << endl;
		return stream.str();
	}
	//Constructors
	layer() :material(), thickness(0), roughness(0) { cout << "Constructing default layer" << endl; }
	layer(material _material) : thickness(0), roughness(0) { cout << "Constructing infinitesimal "<< _material.getname()  <<" layer" << endl; }
	layer(material _material, double _thickness, double _roughness,double _Stheta) : thickness(_thickness), roughness(_roughness), Stheta(_Stheta) { cout << "Constructing" << _material.getname() << " layer" << endl; }
	//Destructors
	~layer() { cout << "Destroying " << getname() << endl; }

	//Methods
	double phase(double _wavelength)
	{
		// the phase term for the interlayer interference
		return (2 * PI / _wavelength)*(1 - 0.5*pow(_wavelength, 2)*getNb() / PI)*Stheta*thickness;
	}


	// Turn into 2 layers

	double reflectance(double _wavelength, double _Q) 
	{
		// calculate the reflectance form each layer
		double _reflectance;
		double _thickness = thickness;///////////Not a good idea?
		double _Stheta = Stheta;
		double _NbA = getNa();

		_reflectance = 4 * PI*pow(_Q, -2)*(LAYER.Nb[_layer] - LAYER.Nb[_layer - 1]);
		if (LAYER.incAbsorption[_layer] == true) {
			// account for absorption
			_reflectance = _reflectance*exp(-1.747*_thickness*_wavelength*_NbA*pow(_Stheta, -2) / PI);
		}
		if (LAYER.incRoughness[_layer] == true) {
			// account for roughness
			_reflectance = _reflectance*exp(-0.5pow(_Q*LAYER.roughness[_layer], 2));
		}

		return _reflectance;
	}

};

//Container for a vector of layers.
class layerspace
{
	vector<layer> layervec;

public:
	//Accessors
	double getNa(int layernum) { return layervec[layernum].getNa(); }
	double getNb(int layernum) { return layervec[layernum].getNb(); }
	double getthickness(int layernum) { return layervec[layernum].getthickness(); }
	double getroughness(int layernum) { return layervec[layernum].getroughness(); }
	//Mutators
	void addlayer(layer _layer){layervec.push_back(_layer);}
	void addlayer(material _material) { layervec.push_back(layer(_material)); }
	void addlayer(material _material, double _thickness, double _roughness, double _Stheta) { layervec.push_back(layer(_material,_thickness,_roughness,_Stheta)); }
	void removelayer(int layernum) { layervec.erase(layervec.begin() + layernum); }
	//Double check these change actual value.
	void setthickness(int layernum, double _thickness) { layervec[layernum].setthickness(_thickness); }
	void setroughness(int layernum, double _roughness) { layervec[layernum].setroughness(_roughness); }
	//Constructors
	layerspace() { cout << "Creating layer vector" << endl; }

	//Reflectivity


};

//Contains layerspace and extras.
class workspace : public layerspace
{
	//Material library.
	vector<material> matlib;

public:

	workspace() :layerspace() { cout << "Initialising workspace"; }
};

int main()
{
	return 0;
}