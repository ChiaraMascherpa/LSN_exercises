#ifndef __Funzioni_h__
#define __Funzioni_h__

#include <vector>
#include <string>

using namespace std;

double TrovaMin(const vector <double> &);
double TrovaMax(const vector <double> &);

double Mean(const vector <double> &);
double Mean_square(const vector <double> &);
double MeanXY(const vector <double> &, const vector <double> &);

vector<double> Medie(const vector <double> &, const vector <double> &,const vector <double> &, const vector <double> &,const vector <double> );

vector<double> Errori(const vector <double> &, const vector <double> &,const vector <double> &, const vector <double> &,const vector <double> );

double ErrMedPes(const vector <double> &);
double MedPes(const vector <double> &, const vector <double> &);

void PrintStima(const vector <double> &, string);
void PrintStime(const vector <double> &, const vector <double> &,const vector <string> &);
void PrintCorr(const vector <double> &, const vector <double> &, string);

double sign(double x);

double DevStd(const vector<double>&);

#endif