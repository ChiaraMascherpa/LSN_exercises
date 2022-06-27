#include "Funzioni.h"

#include <cmath>
#include <iostream>
#include <iomanip>

double TrovaMin(const vector <double> & x)
{
	double min = x[0];

	for(int i=1; i<x.size(); ++i)
	{
		if(x[i] < min) min = x[i];
	}
	return min;
}

double TrovaMax(const vector <double> & x)
{
	double max = x[0];

	for(int i=1; i<x.size(); ++i)
	{
		if(x[i] > max) max = x[i];
	}
	return max;
}

double sign(double x)
{
  if(x == 0){return 0;}
  if(x > 0){return 1;}
  if(x < 0){return -1;}
}




double DevStd(const vector<double> & v)
{
 	double DSC=0, varianza=0;

	double media=0, vecchiamedia=0;
  
  for (int index=0; index < v.size(); ++index)
  {  
    vecchiamedia = media;
    media= (double) media*index/(index+1) +(double) v[index]/(index+1);

    varianza = 1./(index+1)*(varianza*index+ pow(v[index],2) + index *pow(vecchiamedia,2)) - pow(media,2);
  }
	return sqrt(varianza);
}


double Mean(const vector <double> & x)
{
	double mean=0;
  
  for (int i=0; i < x.size(); ++i)
  {
    mean = (double) mean*i/(i+1) +                                   (double) x[i]/(i+1);
  } 
  return mean ;
}


double Mean_square(const vector <double> & x)
{
	double mean=0;
  
  for (int i=0; i < x.size(); ++i)
  {
    mean = (double) mean*i/(i+1) +                                   (double) pow(x[i],2)/(i+1);
  } 
  return mean ;
}


double MeanXY(const vector <double> & x, const vector <double> & y)
{
	if(x.size() != y.size())
	{
		cout << "I vettori non hanno stessa dimensione, impossibile eseguire somma" << endl;
		exit(0);
	}

	double mean=0;
  
  for (int i=0; i < x.size(); ++i)
  {
    mean = (double) mean*i/(i+1) +                                   (double) (x[i]*y[i])/(i+1);
  } 
  return mean ;
}





vector<double> Medie(const vector <double> & v1, const vector <double> & v2,const vector <double> & v3, const vector <double> & v4,const vector <double> & v5)
{
	vector <double> v;
	v.push_back(Mean(v1));
	v.push_back(Mean(v2));
	v.push_back(Mean(v3));
	v.push_back(Mean(v4));
	v.push_back(Mean(v5));

	return v;
}

vector<double> Errori(const vector <double> & v1, const vector <double> & v2,const vector <double> & v3, const vector <double> & v4,const vector <double> & v5)
{
	vector <double> v;
	v.push_back(DevStd(v1));
	v.push_back(DevStd(v2));
	v.push_back(DevStd(v3));
	v.push_back(DevStd(v4));
	v.push_back(DevStd(v5));

	return v;
}





double MedPes(const vector <double> & medie,const vector <double> & errori)
{
	double err = ErrMedPes(errori);
	double mean = 0;

	for(int i=0; i<medie.size(); ++i)
	{
		mean += medie[i]/pow(errori[i],2);
	}

	return mean*pow(err,2);
}


double ErrMedPes(const vector <double> & errori)
{
	double err = 0;

	for(int i=0; i<errori.size(); ++i)
	{
		err+= pow(1/errori[i],2);
	}

	return sqrt(1/err);
}





void PrintStima(const vector <double> & x, string name)
{
	double media = Mean(x);
	double error = sqrt(Mean_square(x) - pow(media,2));

	cout << endl << endl <<  setw(8) << name << setw(20) << fixed << setprecision(ceil(-log10(error))) << media << " +/- " << setw(20) << error;
}


void PrintStime(const vector <double> & medie, const vector <double> & errori, const vector <string> & nome)
{
	for(int i=0; i<medie.size(); ++i)
	{
		cout << endl << endl <<  setw(8) << nome[i] << setw(20) << fixed << setprecision(ceil(-log10(errori[i]))) << medie[i] << " +/- " << setw(20) << errori[i];
	}
}


void PrintCorr(const vector <double> & x, const vector <double> & y, string name)
{
	double media_x = Mean(x);
	double media_y = Mean(y);

	double corr = (MeanXY(x,y) - media_x*media_y)/sqrt((Mean_square(x)-pow(media_x,2))*(Mean_square(y)-pow(media_y,2)));

	cout << endl  << endl << "correlation between " << name << " = " << fixed << setprecision(2) << corr*100 << "%";
}
