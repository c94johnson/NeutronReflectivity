#ifndef PLOTTESTFUNCTIONS_H
#define PLOTTESTFUNCTIONS_H

using namespace std;
void keyPress();
unsigned int readFile(vector< vector< double > >& _data, string _InFileName);
void graphData(vector< vector< double > >& _data, string _InFileName, unsigned int _NumberOfPoints);

#endif // PLOTTESTFUNCTIONS_H
