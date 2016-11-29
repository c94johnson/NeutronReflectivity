#include <iostream>
#include <cmath>
#include <string>

#define PI 3.14159265
using namespace std;

class Properties
{
    // locate the properties for each layer in the substrate
public:
    void setNb(double _Nb)
    {
        Nb=_Nb;
    }
    void setRoughness(double _rough)
    {
        Rough=_rough;
    }
    void setNbA(double _NbA)
    {
        NbA = -NbA;
    }
    void setThickness(double _thickness)
    {
        d=_thickness;
    }
    void setAngle(double _stheta)
    {
        stheta=_stheta;
    }


protected:
    double Nb,NbA,Rough,d,stheta;

};

class Layer: public Properties
{
    // calculate the reflectances per layer
public:
    bool IsUsed;
    bool IsContrastMatched;

private:



};

int main(){
    // load data
    cout<<"Please enter the name of the data file including the file extension. "<<endl;
    string fileName;
    cin>>fileName;



    // get layer properties


    // run the reflectnace method


    // calculate the fit statistics


    // write the model to file


    // plot data


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
    double Anew, Bnew, Cnew, Dnew, Enew, Fnew, Gnew, Hnew;
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









