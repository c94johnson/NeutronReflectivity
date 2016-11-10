
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include "gnuplot_i.hpp"
#include <conio.h>
#include <windows.h>

using namespace std;
unsigned int readFile(vector< vector< double > >& _data, string _InFileName)
{// read file and store .csv data values into vector arrays

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
{
    cout << endl << "Press any key to continue..." << endl;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    _getch();
    return;
}
void graphData(vector< vector< double > >& _data, string _InFileName, unsigned int _NumberOfPoints)
{
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

    keyPress();
    return;
}

