/*

4th October 2016    by Connah Johnson

Programme or calculating the total refelctivity of neutrons from a
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

#define PI 3.14159265
using namespace std;

struct Properties {
    // structure containing all the properties of the layers in the sample

    // is the layer used, if false ignore the layer
    bool layerUsed;
    // is the layer contrast matched to the upper layer
    bool contrastMatched;

    //properties
    double Nb;
    //model absorption?
    bool incAbsorption;
    double NbA;
    // model roughness?
    bool incRoughness;
    double roughness;
    double thickness;
    double Stheta;
}LAYER[6];

struct ReflectivityValues{
    // matrix elements
    double A,B,C,D,E,F,G,H;

}REFLECTANCE;

int main(){

    cout<<"Please enter the name of the data file including the file extension. "<<endl;
    string fileName;
    cin>>fileName;
    // parse the file name to determine the file extension type
    string key(".");
    // find the last location of the '.' character, ignores if in file name
    size_t location = fileName.rfind(key);
    // search from the position after the '.' to the end of string npos
    string extension = fileName.substr(location+1);
    //determine the extension delimiter or if not know ask for delimiting character
    string delimiter;
    switch(extension){
        case 'csv': delimiter = ','; break;
        case 'tsv': delimiter = '\t'; break;
        default :
            cout<<"Error: Could not automatically determine delimiter from file extension.  Please manually enter the delimiter. (\n \t ,) "<<endl;
            cin>>delimiter;



    };




    numberOfLayers = numberOfLayers();

    // ask about layer properties such as substrate type

    // load each layer property

    // ask for incident angle if angle is large give warning
    cout<<"Please enter the incident angle? ";
    double incidentAngle;
    cin>>incidentAngle;

    // allow selection of attenuation condition


};

double qToLambda(double _Q, double _incidentAngle){
    double _L = 4*PI*sin(_incidentAngle)/_Q;
    return _L;
};

double lambdaToQ(double _L, double _incidentAngle){
    double _Q = 4*PI*sin(_incidentAngle)/L;
    return _Q;
};

unsigned int numberOfLayers(){
    unsigned int _layers;
    // number of layers equals substrate + up t 3 protein + up to 1 oil
    cout<<"Please enter the number of protein layers in the experimental sample? Max number is 3 layers ";
    unsigned int numberPL;
    cin>>numberPL;
    cout<<"Is there an oil layer present? y/n ";
    string choice;
    cin>>choice;
    // if choice is y set oil layer to true add to number of layers

    return _layers;
};

void populateLayers(unsigned int _layerNumber){


};

void matrixMethod(unsigned int _layer, double _wavelength, double _Q){
    // follow the matrix method to calculate the components of the optical matrix
    double _phase = phase(_layer,_wavelength);
    double _reflectance = reflectance(_layer, _wavelength, _Q);


    double A = cos(_phase);
    double B = sin(_phase);
    double C = _reflectance*cos(_phase);
    double D = _reflectance*sin(_phase);
    double E = _reflectance*cos(_phase);
    double F = -_reflectance*sin(_phase);
    double G = cos(_phase);
    double H = -sin(_phase);

    //calculate the new total matrix elements
    double Anew;
    double Bnew;
    double Cnew;
    double Dnew;
    double Enew;
    double Fnew;
    double Gnew;
    double Hnew;
    double Aold = REFLECTANCE.A;
    double Bold = REFLECTANCE.B;
    double Cold = REFLECTANCE.C;
    double Dold = REFLECTANCE.D;
    double Eold = REFLECTANCE.E;
    double Fold = REFLECTANCE.F;
    double Gold = REFLECTANCE.G;
    double Hold = REFLECTANCE.H;

    Anew = Aold*A - Bold*B + Cold*E - Dold*F;
    Bnew = Bold*A + Aold*B + Dold*E + Cold*F;
    Cnew = Aold*C - Bold*D + Cold*G - Dold*H;
    Dnew = Bold*C + Aold*D + Dold*G + Cold*H;
    Enew = Eold*A - Fold*B + Gold*E - Hold*F;
    Fnew = Fold*A + Eold*B + Gold*F + Hold*E;
    Gnew = Eold*C - Fold*D + Gold*G - Hold*H;
    Hnew = Fold*C + Eold*D + Hold*G + Gold*H;

    // update the reflectance structure
    REFLECTANCE.A = Anew;
    REFLECTANCE.B = Bnew;
    REFLECTANCE.C = Cnew;
    REFLECTANCE.D = Dnew;
    REFLECTANCE.E = Enew;
    REFLECTANCE.F = Fnew;
    REFLECTANCE.G = Gnew;
    REFLECTANCE.H = Hnew;

};

double phase(unsigned int _layer, double _wavelength){
    // the phase term for the interlayer interference
    double _phase;
    _phase = (2*PI/_wavelengh)*(1-0.5*pow(_wavelength,2)*LAYER.Nb[_layer]/PI)*LAYER.Stheta[_layer]*LAYER.thickness[_layer];
    return _phase;
};

double reflectance(unsigned int _layer; double _wavelength, double _Q){
    // calculate the reflectance form each layer
    double _reflectance;
    double _thickness = LAYER.thickness[_layer];
    double _Stheta = LAYER.Stheta[_layer];
    double _NbA = LAYER.NbA[_layer];

    _reflectance = 4*PI*pow(_Q, -2)*(LAYER.Nb[_layer]-LAYER.Nb[_layer-1]);
    if(LAYER.incAbsorption[_layer] == true){
        // account for absorption
        _reflectance = _reflectance*exp(-1.747*_thickness*_wavelength*_NbA*pow(_Stheta, -2)/PI);
    };
    if (LAYER.incRoughness[_layer] == true){
        // account for roughness
        _reflectance = _reflectance*exp(-0.5pow(_Q*LAYER.roughness[_layer],2));
    };

    return _reflectance;
};
// attenuation function for between layers

double Attenuation(unsigned int _layer, double _wavelength, double _theta){
    double _atten;

    double _NbA = LAYER.NbA[_layer];

    _atten = exp(-(0.5*_d*k*_wavelength/PI*pow(sin(_theta),2))*NbA);

    return _atten;

};

double roughness(double _layer, double _Q){
    double _roughnessFactor;
    double _layerRoughness = LAYER.roughness[_layer];
    _roughnessFactor = exp(-0.5*pow(_layerRoughness*_Q,2));

    return _roughnessFactor;
};

// data statistics

double Chi2(unsigned int _POINTS, double _fresnelPoint[POINTS], double _measuredPoint[POINTS], double _measuredError[POINTS]){
    double _chi2 = 0;
    double _dataPoint = 0;
    // while not every data point has been accounted for
    while(_dataPoint != _POINTS){
        _chi2=pow((_fresnelPoint[_dataPoint]-_measuredPoint[_dataPoint])/_measuredError[_dataPoint],2);
    };

    return _chi2;
};

double noise(){

};

// additional functionalities

double customMaterial(){


};

double surfaceAdsorbedAmount(){


};













