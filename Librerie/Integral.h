#ifndef __INTEGRAL_H__
#define __INTEGRAL_H__

#include "../Random/random.h"
#include "float.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <functional>

using namespace std;

class Integral{

public:
   Integral(double a, double b, const function <double(double)> f);

   Integral(double a, double b, double prec, const function <double(double)> f);
   Integral(const function <double(double)> f);
    
   void SetPrec (double const prec) {
        if(prec>=DBL_EPSILON)m_prec=prec;
        else{
            cout<<"Precisione inferiore a quella della macchina, quindi impostata di default alla precisione della macchina"<<endl;
            m_prec=DBL_EPSILON;
        }
    };
   double GetPrec() const {return m_prec;};

   void SetH(double const h) {m_h = h;};
   double GetH() const {return m_h;};

   double MediaInt (int punti);
   double Distr (int punti, const function <double(double)> f);

    double Metropolis (int punti,const function <double(double)> rho, double x0, double dx, int neq);
    


private:
   double m_a, m_b;                                        //Estremi di integrazione
   double m_sum;                                           //Integrale senza segno
   double m_h;                                             //Larghezza intervalli
   int m_sign;                                             //Se estremi non sono in ordine
   double m_integral;                                      //Valore dell'integrale
   function <double(double)> m_f;                    //Funzione integranda
   double m_prec;                                          //Precisione
   Random *m_myrand;
    int accepted, attempted;
};

#endif
