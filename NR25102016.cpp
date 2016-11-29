/*
    Written by Connah Johnson    

    Model written 25th October 2016

    gnuplot graphing implemented 7th November 2016


    Assumptions:
    -substrate and aqueous layer assumed
    -constant angle of incidence at each layer
    -non-complex refraction angle

    Plotting Assumptions:
    -windows 32
    -gnuplot.exe.located at "C:/Program Files/gnuplot/bin/"
    -comma separated file on entry with three data columns: X, Y, Error in Y
    -data file is located within the project directory



*/


#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include "gnuplot_i.hpp"
#include <conio.h>
#include <windows>

#define PI 3.14159265

using namespace std;

///////////////////////
//  Define classes

class Model
{
    // hold the model values; number of layers, number of protein layers
    unsigned int NoL, NoPL;
    bool IsOil;
    // create vector to hold the model reflectivity values.
    vector<double> modelY;

    // output file name
    string OutFileName;

public:
    void setModel(unsigned int,unsigned int,bool)
};

void Model::setModel(unsigned int _NoL, unsigned int _NoPL, bool _IsOil)
{
    NoL=_NoL;
    NoPL = _NoPL;
    IsOil= _IsOil;
}

class Layer
{
    // layer properties
    bool IsUsed, IsContrastMatched;
    double Nb, NbA, Rough, d, stheta;

    // vectors for each matrix element at each wavelength data point
    vector<double> A,B,C,D,E,F,G,H;

public:
    void setValues(double,double,double,double,double);
    void setConditions(bool,bool);
    void getCoefficients();
};

void Layer::setValues(double _Nb, double _NbA, double _Rough, double _d, double _stheta)
{
    Nb=_Nb;
    NbA=_NbA;
    Rough=_Rough;
    d=_d;
    stheta=_stheta;
}

void Layer::setConditions(bool _IsUsed, bool _IsContrastMatched)
{
    bool IsUsed=_IsUsed;
    bool IsContrastMatched=_IsContrastMatched;
}


class TotalReflectance
{
    vector<double> A,B,C,D,E,F,G,H;
public:
    void getCumulativeCoefficients();
};

class Data
{
    // input file name
    string InFileName;

    bool IsWave;
    // hold value for the number of data points
    unsigned int NoP;
    // create vector to hold the Q or wavelength data values.  Q to be converted
    vector<double> dataX;
    // create vector to hold the Reflectivity values
    vector<double> dataY;
    // create vector to hold the error values of the reflectivity
    vector<double> dataE;


public:
    void setData(bool, unsigned int);
};

void Data::setData(bool _IsWave, unsigned int _numberOfDataPoints)
{
    IsWave = _IsWave;
    NoP = _numberOfDataPoints;
}

///////////////////////
//  Declare functions

void keyPress();
unsigned int readFile(vector< vector< double > >& _data, string _InFileName);





int main(){
    //-----------------------------------//
    //          LOAD DATA                //
    //-----------------------------------//
    // load data
    readFile();
    // number of data points N
    unsigned int N;
    vector<vector<double>> data;
    // store data into 2d vector data, data(0,N) is wavelength or Q, data(1,N) reflectivity

    // if data is in form Q convert to wavelength
    if (Data.IsWave == false)
    {// then data is in form Q
        counter=0;
        while(counter =! N)
        {
            Data.data[0,counter]=QtoWave(Data.data[0,counter]);

            counter++;
        }
    };

    //-----------------------------------//
    //        MODEL PARAMETERS           //
    //-----------------------------------//

    // determine the number of layers (NoL) in the model
    NumberOfLayers();
    // get layer properties
    Layer layer[Model.NoL];
    counter=0;
    while(counter != Model.NoL)
    {// on layer by layer basis ask for layer properties
        double _Nb=0, _NbA=0,_Rough=0,_d=0, _Stheta=0;
        bool _IsUsed, _IsContrastMatched;
        if(counter==0)
        {
            cout<<"Please enter the properties for the Substrate layer."<<endl;
            cout<<"Scattering Length Density (Nb or SLD) = "<<endl;
            cin>>_Nb;
            cout<<"Absorption Cross Section density (NbA) = "<<endl;
            cin>>_NbA;
            cout<<"Root mean square roughness = "<<endl;
            cin>>_Rough;
            cout<<"Layer Thickness = "<<endl;
            cin>>_d;
            cout<<"Incident Angle of Neutron Beam = "<<endl;
            cin>>_Stheta;
            layer[counter].setValues(_Nb,_NbA,_Rough,_d,_stheta);
            layer[counter].setConditions(true,false);
        };
        if(counter==1)
        {
            char choice;
            cout<<"Is the oil layer contrast matched to the substrate? [y/n]"<<endl;
            cin>>_choice;
            cout<<"Please enter the properties of the oil film."<<endl;
                if(choice=='n')
                {   // the oil layer exists and has it's own properties
                    cout<<"Scattering Length Density (Nb or SLD) = "<<endl;
                    cin>>_Nb;
                    _IsContrastMatched=false;
                }else
                {
                    _IsContrastMatched=true;
                    _Nb=0;
                };
                cout<<"Absorption Cross Section density (NbA) = "<<endl;
                cin>>_NbA;
                cout<<"Root mean square roughness = "<<endl;
                cin>>_Rough;
                cout<<"Layer Thickness = "<<endl;
                cin>>_d;
                cout<<"Incident Angle of Neutron Beam = "<<endl;
                cin>>_stheta;
                layer[counter].setValues(_Nb,_NbA,_Rough,_d,_stheta);
                layer[counter].setConditions(true,_IsContrastMatched);
        };
        if(2<=counter<=1+Model.NoPL)
        {
            cout<<"Please enter the properties of Protein layer "<<counter-1<<"."<<endl;
            cout<<"Scattering Length Density (Nb or SLD) = "<<endl;
            cin>>_Nb;
            _IsContrastMatched=false;
            cout<<"Absorption Cross Section density (NbA) = "<<endl;
            cin>>_NbA;
            cout<<"Root mean square roughness = "<<endl;
            cin>>_Rough;
            cout<<"Layer Thickness = "<<endl;
            cin>>_d;
            cout<<"Incident Angle of Neutron Beam = "<<endl;
            cin>>_stheta;
            layer[counter].setValues(_Nb,_NbA,_Rough,_d,_stheta);
            layer[counter].setConditions(true,_IsContrastMatched);
        };
        if(counter==Model.NoL-1)
        {   char choice;
            cout<<"Is the aqueous phase contrast matched to the substrate? [y/n]"<<endl;
            cin>>_choice;
            cout<<"Please enter the properties of the aqueous phase."<<endl;
                if(choice=='n')
                {   // the aqueous phase has it's own properties
                    cout<<"Scattering Length Density (Nb or SLD) = "<<endl;
                    cin>>_Nb;
                    _IsContrastMatched=false;
                }else
                {
                    _IsContrastMatched=true;
                    _Nb=0;
                };
                cout<<"Absorption Cross Section density (NbA) = "<<endl;
                cin>>_NbA;
                cout<<"Root mean square roughness = "<<endl;
                cin>>_Rough;
                cout<<"Layer Thickness = "<<endl;
                cin>>_d;
                cout<<"Incident Angle of Neutron Beam = "<<endl;
                cin>>_stheta;
                layer[counter].setValues(_Nb,_NbA,_Rough,_d,_stheta);
                layer[counter].setConditions(true,_IsContrastMatched);
        };
        counter++;
    };
    /*
    The initial properties of the model have been entered into the layer objects
    each of class Layer.  The number of protein layers and the total number of
    layers have been stored in the class model.  Here we have assumed that the is
    always one oil layer.  The oil layer and the aqueous phase may also be contrast
    matched to the substrate layer only.
    */

    //-----------------------------------//
    //          EXECUTE METHOD           //
    //-----------------------------------//

    // run the reflectance method, updating class objects
    unsigned int counter=0;
    while(counter =! Model.NoL)
    {// calculate the layer matrix elements on a layer by layer basis
        unsigned int dataPoint=0;
        while(dataPoint =! Data.NoP)
        {// for each wavelength value
            executeMatrixMethod(unsigned int counter; unsigned int dataPoint)
            calculateCumulativeReflectance(unsigned int counter, unsigned int dataPoint);

            dataPoint++;
        }
        counter++;
    };
    Reflectivity();
    // the model reflectivity values are now stored in Model.modelY;

    //-----------------------------------//
    //          STATISTICS               //
    //-----------------------------------//

    // calculate the fit statistics
    double fitQuality=0;
    fitQuality=ChiSquared()/Data.NoP;
    cout<<"Reduced Chi Squared data statistic value:    "<<fitQuality<<endl;


    //-----------------------------------//
    //          OUTPUT METHOD            //
    //-----------------------------------//

    // write the model to file
    cout<<"Please enter the output file name:"<<endl;
    string OutFileName;
    cin>>OutFileName;


    // plot data




};

void readFile()
{// read file and store .csv data values into vector arrays
    cout<<"Please enter the name of the data file including the file extension. "<<endl;
    string InFileName;
    cin>>InFileName;
    // read from data the number of data points.

    vector <double> temp;
    vector<vector <double> > fileData;
    unsigned int numberOfLines=0;
    ifstream infile;
    infile.open(InFileName);
    if(infile.is_open())
    {
        cout<<"Successfully opened the input file "<<InFileName<<endl;
        string fileLine, entryS;
        double entryD;
        while(!infile.eof())
        {// while not at the end of the file and data still to be read
            getline(infile, fileLine);
            if(fileLine == " ")
            {// then at the end of the file
                break;
            };
            // find the delimiter from the start of the line stream
            unsigned int delimiterPos=0;
            while(delimiterPos != strin::npos)
            {// extract the data into temp vector line by line
               delimiterPos=fileLine.find(',',0);
               if(delimiterPos == string::npos)
                {// read substring in fileLine string and then push back double onto temp vector
                    entryS = fileLine.substr(0, fileLine.size());
                    if(entry != "\n")
                    {// entry not at the end of the file push double onto temp vector
                        entryD = atof(entryS.c_str());
                        temp.push_back(entryD);
                    };
                }else{
                    entryS = fileLine.substr(0, delimiterPos-0);
                    fileLine = fileLine.substr(delimiterPos+1, fileLine.size() - (delimiterPos+1));
                    if(entryS != "\n")
                    {
                        entryD = atof(entryS.c_str());
                        temp.push_back(entryD);
                    };
                };
               };
            // push vector temp data back onto  vector file data
            fileData.push_back(temp);
            temp.clear();
            numberOfLines++;
        };
    infile.close();
    }else{
        // error has occurred
        cout<<"unable to open file "<<InFileName<<endl;
        exit(1);
    };
    // parse data onto the vectors dataX, dataY, dataE.
    counter=0;
    while(counter != numberOfLines)
    {
        Data.dataX[counter]=fileData[counter][0];
        Data.dataY[counter]=fileData[counter][1];
        Data.dataE[counter]=fileData[counter][2];
        counter++;
    };
    Data.NoP=numberOfLines;
    Data.InFileName=InFileName;

};

double QtoWave(_Q, _incidentAngle)
{//convert the Q value to a wavelength value
    double _L = 4*PI*sin(_incidentAngle)/_Q;
    return _L;
}

void executeMatrixMethod(unsigned int counter, unsigned int dataPoint)
{// calculate the layer reflectance matrix elements
    // accepts the layer number and the wavelength of the data point and executes the matrix method.  Updates the class layer and TotalReflectance objects
    _Nb1=layer[counter-1].Nb;
    _Nb2=layer[counter].Nb;
    _NbA=layer[counter].NbA;
    _Rough=layer[counter].Rough;
    _d=layer[counter].d;
    _stheta=layer[counter].stheta;
    _IsContrastMatched=layer[counter].IsContrastMatched;
    double wavelength=Data.dataX[dataPoint];

    double Atten=Attenuation(double wavelength, double NbA, double _d, double _stheta);
    double Deb=Debye(double wavelength,double _roughness, double _stheta);

    double _A,_B,_C,_D,_E,_F,_G,_H;
    if(_IsContrastMatched==true && counter =! 0)
    {//layer is contrast matched to the substrate and the layer isn't the substrate
     //retrieve the matrix elements form the previous layer and apply attenuation
     //and roughness factors
        _A=layer[counter-1].A[dataPoint];
        _B=layer[counter-1].B[dataPoint];
        _C=layer[counter-1].C[dataPoint];
        _D=layer[counter-1].D[dataPoint];
        _E=layer[counter-1].E[dataPoint];
        _F=layer[counter-1].F[dataPoint];
        _G=layer[counter-1].G[dataPoint];
        _H=layer[counter-1].H[dataPoint];
        // need to apply factors to C,D,E,F as depend on reflectance
        _C=_C*Atten*Deb;
        _D=_D*Atten*Deb;
        _E=_E*Atten*Deb;
        _F=_F*Atten*Deb;
    }else{
        // the layer isn't contrast matched to the substrate

        double _phase = phase(_layer,_wavelength);
        double _reflectance = reflectance(double _Q, double _Nb1, double _Nb2);


        _A=cos(_phase);
        _B=sin(_phase);
        _C=_reflectance*Atten*Deb*cos(_phase);
        _D=_reflectance*Atten*Deb*sin(_phase);
        _E=_reflectance*Atten*Deb*cos(_phase);
        _F=-_reflectance*Atten*Deb*sin(_phase);
        _G=cos(_phase);
        _H=-sin(_phase);

    };
    // write to the layer object
    layer[counter].A[dataPoint]=_A;
    layer[counter].B[dataPoint]=_B;
    layer[counter].C[dataPoint]=_C;
    layer[counter].D[dataPoint]=_D;
    layer[counter].E[dataPoint]=_E;
    layer[counter].F[dataPoint]=_F;
    layer[counter].G[dataPoint]=_G;
    layer[counter].H[dataPoint]=_H;

}

void calculateCumulativeReflectance(unsigned int counter, unsigned int dataPoint)
{// determine the cumulative matrix element values

    Aold=TotalReflectance.A[dataPoint];
    Bold=TotalReflectance.B[dataPoint];
    Cold=TotalReflectance.C[dataPoint];
    Dold=TotalReflectance.D[dataPoint];
    Eold=TotalReflectance.E[dataPoint];
    Fold=TotalReflectance.F[dataPoint];
    Gold=TotalReflectance.G[dataPoint];
    Hold=TotalReflectance.H[dataPoint];

    A=layer[counter].A[dataPoint];
    B=layer[counter].B[dataPoint];
    C=layer[counter].C[dataPoint];
    D=layer[counter].D[dataPoint];
    E=layer[counter].E[dataPoint];
    F=layer[counter].F[dataPoint];
    G=layer[counter].G[dataPoint];
    H=layer[counter].H[dataPoint];

    Anew = Aold*A - Bold*B + Cold*E - Dold*F;
    Bnew = Bold*A + Aold*B + Dold*E + Cold*F;
    Cnew = Aold*C - Bold*D + Cold*G - Dold*H;
    Dnew = Bold*C + Aold*D + Dold*G + Cold*H;
    Enew = Eold*A - Fold*B + Gold*E - Hold*F;
    Fnew = Fold*A + Eold*B + Gold*F + Hold*E;
    Gnew = Eold*C - Fold*D + Gold*G - Hold*H;
    Hnew = Fold*C + Eold*D + Hold*G + Gold*H;

    //update the TotalReflectance object entries, done in this order so that
    //the new elements do not feedback into the calculations
    TotalReflectance.A[dataPoint]=Anew;
    TotalReflectance.B[dataPoint]=Bnew;
    TotalReflectance.C[dataPoint]=Cnew;
    TotalReflectance.D[dataPoint]=Dnew;
    TotalReflectance.E[dataPoint]=Enew;
    TotalReflectance.F[dataPoint]=Fnew;
    TotalReflectance.G[dataPoint]=Gnew;
    TotalReflectance.H[dataPoint]=Hnew;

};

double Attenuation(double _wavelength, double NbA, double _d, double _stheta)
{// calculate the attenuation factor
    double _atten;
    double k=3.494;
    _atten = exp(-(0.5*_d*k*_wavelength/PI*pow(_stheta,2))*NbA);
    return _atten;
}

double Debye(double _wavelength, double _roughness, double _stheta)
{// calculate the roughness Debye-Waller factor
    double _roughnessFactor;
    _Q=4*PI*_stheta/_wavelength;
    _roughnessFactor = exp(-0.5*pow(_roughness*_Q,2));
    return _roughnessFactor;
}

double phase(double _wavelength, double _Nb2, double _stheta, double _d)
{// the phase term for the interlayer interference
    double _phase;
    _phase = (2*PI/_wavelength)*(1-0.5*pow(_wavelength,2)*_Nb2/PI)*_stheta*_d;
    return _phase;
}

double reflectance(double _Q, double _Nb1,double _Nb2)
{// the fresnel reflectance
    double _reflectance;
    _reflectance = 4*PI*pow(_Q, -2)*(_Nb2-_Nb1);
    return _reflectance;

}

void Reflectivity()
{// calculate the model reflectivity and update modelY
    unsigned int _dataPoint=0;
    while(_dataPoint =! Data.NoP)
    {// calculate the reflectivity from the CumulativeReflectance

        _A=TotalReflectance.A[dataPoint];
        _B=TotalReflectance.B[dataPoint];
        _E=TotalReflectance.E[dataPoint];
        _F=TotalReflectance.F[dataPoint];

        Model.modelY[_dataPoint]=(pow(E,2)+pow(F,2))/(pow(A,2)+pow(B,2));

        dataPoint++;
    };

}

void NumberOfLayers()
{// enter the number of layers of layer type
    unsigned int _NoPL, _NoL, _layers;
    cout<<"Please enter the number of protein layers in the experimental sample? Max number is 3 layers ";
    cin>>_NoPL;
    // layer count: substrate +numberPL + oil + aqueous
    double _layers=2+_NoPL;
    cout<<"Is there an oil layer present between the Substrate and Protein layer(s)? y/n ";
    string choice;
    cin>>choice;
    // if choice is y set oil layer to true add to number of layers
    if(choice = 'y'){
        _layers+;
        _IsOil = true;
    };
    _NoL = _layers

    Model::setModel(_NoL,_NoPL,_IsOil);
}

double ChiSquared()
{// determine the chi squared data statistic
    double _chiSquared=0;
    // for each data point calculate the weighted difference between the model and the data
    unsigned int _numberOfPoints=Data.NoP;
    unsigned int _counter=0;
    while(_counter != _numberOfPoints)
    {
        _chiSquared += pow(((Model.modelY[_counter]-Data.dataY[_counter]),2)*pow(Data.dataE[_counter],-4);
        _counter++;
    };

    return _chiSquared;
}

void NoiseCompensation()
{// determine the background noise
    // calculate a background noise and remove this from the data reflectivity values


// if Q value is greater than 0.2 then remove from the data vecotr but use
// to calculate a bckground noise through the weighted mean, subtract from
// data.



}


unsigned int readFile(vector< vector< double > >& _data, string _InFileName)
{/* read file and store .csv data values into vector of vector data as double values
    
    Input:
    -the address of the vector of vectors to store the read file data as doubles
    -the actual file name including the file extension as a string

    Output:
    -the number of lines in the read file as an unsigned int

*/
    const char* name = _InFileName.c_str();
    vector <double> temp;

    unsigned int numberOfLines=0;
    ifstream infile(name);
    if(infile.is_open())
    {
        cout<<"Successfully opened the input file "<<_InFileName<<endl;
        string fileLine, entryS;
        double entryD;
        while(!infile.eof())
        {// while not at the end of the file and data still to be read
            getline(infile, fileLine);
            if(fileLine == " ")
            {// then at the end of the file
                break;
            };
            // find the delimiter from the start of the line stream
            unsigned int delimiterPos=0;
            while(delimiterPos != string::npos)
            {// extract the data into temp vector line by line
               delimiterPos=fileLine.find(',',0);
               if(delimiterPos == string::npos)
                {// read substring in fileLine string and then push back double onto temp vector
                    entryS = fileLine.substr(0, fileLine.size());
                    if(entryS != "\n")
                    {// entry not at the end of the file push double onto temp vector
                        entryD = atof(entryS.c_str());
                        temp.push_back(entryD);
                    };
                }else{
                    entryS = fileLine.substr(0, delimiterPos-0);
                    fileLine = fileLine.substr(delimiterPos+1, fileLine.size() - (delimiterPos+1));
                    if(entryS != "\n")
                    {
                        entryD = atof(entryS.c_str());
                        temp.push_back(entryD);
                    };
                };
               };
            // push vector temp data back onto  vector file data
            _data.push_back(temp);
            temp.clear();
            numberOfLines++;
        };
    infile.close();
    }else{
        // error has occurred
        cout<<"unable to open file "<<_InFileName<<endl;
        exit(1);
    };


    return numberOfLines;
};


void keyPress()
{/* for the windows system need to wait after the graph is produced before terminating

*/
    cout << endl << "Press any key to continue..." << endl;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    _getch();
    return;
}


void graphData(vector< vector< double > >& _data, string _InFileName, unsigned int _NumberOfPoints)
{/* use a pipeline to gnuplot to graph the data, plots the data and titles graph with data file name

    Input:
    -address of the vector of vectors whichstores the numerical data as type double
    -name of the read data file in order to title graphs
    -number of data points 

*/



    // parse data onto the vectors dataX, dataY, dataE.
    vector<double> dataX, dataY, dataE;
    unsigned int counter=0;
    while(counter != _NumberOfPoints)
    {
        dataX.push_back(_data[counter][0]);
        dataY.push_back(_data[counter][1]);
        dataE.push_back(_data[counter][2]);
        counter++;
    };

    Gnuplot g1("lines");
    cout<<"Plotting data"<<endl;
    string titleMessage;
    string titleStart = "Plot of the data in file: ";
    titleMessage.append(titleStart);
    titleMessage.append(_InFileName);
    g1.set_title(titleMessage);
    g1.plot_xy_err(dataX,dataY,dataE,"File data with error bars");
    g1.unset_title();
    g1.showonscreen();

    // wait for key press 
    keyPress();
    return;
}













